#include "lipch.h"
#include "ScriptEngine.h"

#include "Lithe/Core/FileSystem.h"
#include "Lithe/Core/Timer.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/object.h>
#include <mono/metadata/tabledefs.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/threads.h>

namespace Lithe {

	struct ScriptEngineData
	{
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;

		MonoAssembly* CoreAssembly = nullptr;
	};

	static ScriptEngineData* s_Data = nullptr;

	void ScriptEngine::Init()
	{
		s_Data = new ScriptEngineData();
		InitMono();
	}

	void ScriptEngine::Shutdown()
	{
		ShutdownMono();
		delete s_Data;
		s_Data = nullptr;
	}

	static MonoAssembly* LoadCSharpAssembly(const std::string& assemblyPath)
	{
		ScopedBuffer fileData = FileSystem::ReadFileBinary(assemblyPath);

		MonoImageOpenStatus status;
		MonoImage* image = mono_image_open_from_data_full(fileData.As<char>(), (uint32_t)fileData.Size(), 1, &status, 0);

		if (status != MONO_IMAGE_OK)
		{
			const char* errorMessage = mono_image_strerror(status);
			return nullptr;
		}

		MonoAssembly* assembly = mono_assembly_load_from_full(image, assemblyPath.c_str(), &status, 0);
		mono_image_close(image);

		return assembly;
	}

	static void PrintAssemblyTypes(MonoAssembly* assembly)
	{
		MonoImage* image = mono_assembly_get_image(assembly);
		const MonoTableInfo* typeDefinitionsTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
		int32_t numTypes = mono_table_info_get_rows(typeDefinitionsTable);

		for (int32_t i = 0; i < numTypes; i++)
		{
			uint32_t cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinitionsTable, i, cols, MONO_TYPEDEF_SIZE);

			const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);

			LI_CORE_TRACE("{0}.{1}", nameSpace, name);
		}
	}

	void ScriptEngine::InitMono()
	{
		mono_set_assemblies_path("mono/lib");

		MonoDomain* rootDomain = mono_jit_init("LitheJITRuntime");
		LI_CORE_ASSERT(rootDomain);
		if (rootDomain == nullptr)
			return;
		s_Data->RootDomain = rootDomain;

		s_Data->AppDomain = mono_domain_create_appdomain("LitheScriptRuntime", nullptr);
		mono_domain_set(s_Data->AppDomain, true);
		s_Data->CoreAssembly = LoadCSharpAssembly("Resources/Scripts/Lithe-ScriptCore.dll");
		PrintAssemblyTypes(s_Data->CoreAssembly);

		// TEMP: Mono Testing/Demo
		{
			Timer timer;
			MonoImage* assemblyImage = mono_assembly_get_image(s_Data->CoreAssembly);
			MonoClass* monoClass = mono_class_from_name(assemblyImage, "Lithe", "Main");

			MonoObject* instance = mono_object_new(s_Data->AppDomain, monoClass);
			mono_runtime_object_init(instance);

			// Parameterless function
			MonoMethod* printMessageFunc = mono_class_get_method_from_name(monoClass, "PrintMessage", 0);
			mono_runtime_invoke(printMessageFunc, instance, nullptr, nullptr);

			// Integer input function
			MonoMethod* printIntFunc = mono_class_get_method_from_name(monoClass, "PrintInt", 1);
			int value = 5;
			void* intParam = &value;
			mono_runtime_invoke(printIntFunc, instance, &intParam, nullptr);

			// Multiple Inputs
			MonoMethod* printIntsFunc = mono_class_get_method_from_name(monoClass, "PrintInts", 2);
			int v1 = 10;
			int v2 = 20;
			void* intParams[2] = { &v1, &v2 };
			mono_runtime_invoke(printIntsFunc, instance, intParams, nullptr);

			// String input function
			MonoString* monoString = mono_string_new(s_Data->AppDomain, "Hello World from C++");
			MonoMethod* printCustomMessageFunc = mono_class_get_method_from_name(monoClass, "PrintCustomMessage", 1);
			void* stringParam = monoString;
			mono_runtime_invoke(printCustomMessageFunc, instance, &stringParam, nullptr);
			LI_CORE_WARN("Mono demo took: {0} ms", timer.ElapsedMillis());
		}
	}

	void ScriptEngine::ShutdownMono()
	{
		mono_domain_set(mono_get_root_domain(), false);

		mono_domain_unload(s_Data->AppDomain);
		s_Data->AppDomain = nullptr;

		mono_jit_cleanup(s_Data->RootDomain);
		s_Data->RootDomain = nullptr;
	}

}
