#pragma once

#include "core/core.h"
#include "MList.h"
namespace mlist
{
	class MListSerializer
	{
	private:
		Ref<std::vector<MList>> m_MList;
	public:
		MListSerializer(Ref<std::vector<MList>>& mlist)
			:m_MList(mlist)
		{}

		bool Serialize(const std::string& filepath);
		bool Deserialize(const std::string& filepath);
	};
}

