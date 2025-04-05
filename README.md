# Lithe
A simple yet performant 2D Game Engine written in C++.

## Getting Started
Start by cloning this repository by using `git clone --recursive https://github.com/trevorswan11/Lithe`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

### Setup
- To proceed with the rest of Lithe's setup, ensure you have [Python](https://www.python.org/downloads/) and [Microsoft Visual Studio](https://visualstudio.microsoft.com/) installed on your machine. 
    - Python is *required* to run the setup scripts, but needed packages will be installed on their own. 
- Lithe has not been tested with other IDE's/build systems, nor has it been tested outside of a strictly windows environments. Visual Studio 2022 is recommended and is called by the Premake binary. Other versions may be functional, but require a manual change of `Win-GenProjects.bat` located in the `scripts` folder. 
- Certain versions of Visual Studio may not be supported by Lithe's enforced Premake version, but you can download alternative binaries [here](https://github.com/premake/premake-core/releases/). 

### Dependencies
1. Run the `Setup.bat` file found in scripts folder from **your file explorer**. This will download the required prerequisites for the project if they are not present yet.
    - Among general dependency installation prompts, the script will ask you if you would like to update submodules. This is only necessary if you are not working off of a fresh clone of this repository.
2. One prerequisite is the [Vulkan SDK](https://vulkan.lunarg.com/). If it is not installed, the script will execute the VulkanSDK.exe file, and will prompt the user to install the SDK (any location should work). When prompted through the Vulkan installer, ensure you install the debug libraries if you intend on running Lithe with the Debug configuration.
3. The Premake binary and license will also be downloaded automatically, and `Setup.bat` will call `Win-GenProjects.bat` to generate Visual Studio solution files.

If changes are made to any Premake configuration files (including dependencies and submodules), or if you want to regenerate project files, rerun the `Win-GenProjects.bat` script file found in scripts folder.
