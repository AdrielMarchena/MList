#pragma once

#include "core/core.h"
#include "MMEdia.h"
namespace mlist
{
	class MLIST_API MMediaSerializer
	{
	private:
		Ref<std::vector<MMedia>> m_MList;
	public:
		MMediaSerializer(Ref<std::vector<MMedia>>& mlist)
			:m_MList(mlist)
		{}

		bool Serialize(const std::string& filepath);
		bool Deserialize(const std::string& filepath);
		bool CreateNewFile(const std::string& filepath);
	};
}

