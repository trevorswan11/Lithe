#pragma once

#include <xhash>

namespace Lithe {

	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint64_t() const { return m_UUID; }
	private:
		uint64_t m_UUID;
	};

	inline std::string format_as(const UUID& uuid)
	{
		return std::to_string(uuid);
	}
}

namespace std {

	template<>
	struct hash<Lithe::UUID>
	{
		std::size_t operator()(const Lithe::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}

