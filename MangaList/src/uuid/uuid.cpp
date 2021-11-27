#include "core/pch.h"

#include "uuid.h"

#include <random>

namespace mlist
{
	static std::random_device s_RandomDevice;
#ifdef MLIST_USING_UUID_64_T
	static std::mt19937_64 s_Engine(s_RandomDevice());
#else
	static std::mt19937 s_Engine(s_RandomDevice);
#endif
	static std::uniform_int_distribution<UUID_T> s_UniformDistribution;

	UUID::UUID()
		:m_UUID(s_UniformDistribution(s_Engine))
	{
	}

	UUID::UUID(UUID_T uuid)
		: m_UUID(uuid)
	{
	}
}