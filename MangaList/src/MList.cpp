#include "core/pch.h"
#include "MList.h"

#include "uuid/uuid.h"

namespace mlist
{
	MList::MList()
		:m_UUID(UUID())
	{
	}

	Ref<MList> MList::CreateRefMList()
	{
		return MakeRef<MList>();
	}

	Ref<MList> MList::CreateRefMList(const Ref<MList>& other)
	{
		auto ml = MakeRef<MList>();
		ml->Title = other->Title;
		ml->SubTitle = other->SubTitle;
		ml->Category = other->Category;
		ml->Description = other->Description;
		ml->TotalChapters = other->TotalChapters;
		ml->ReadedChapters = other->ReadedChapters;
		ml->Language = other->Language;
		return ml;
	}
}