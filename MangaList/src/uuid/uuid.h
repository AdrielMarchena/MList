#pragma once
#include "core/pch.h"

#include <xhash>

namespace mlist
{
	/* uuid type */
	typedef uint64_t UUID_T;
#define MLIST_USING_UUID_64_T
	class UUID
	{
	public:
		UUID();
		UUID(UUID_T uuid);
		UUID(const UUID&) = default;

		operator UUID_T() const { return m_UUID; }
	private:
		UUID_T m_UUID = NULL;
	};
}

namespace std
{
#ifdef MLIST_USING_UUID_64_T
	template<>
	struct hash<mlist::UUID>
	{
		std::size_t operator()(const mlist::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
#endif
}