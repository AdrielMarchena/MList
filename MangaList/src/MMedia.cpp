#include "core/pch.h"
#include "MMedia.h"

#include "uuid/uuid.h"
namespace mlist
{
	MMedia::MMedia()
		:m_UUID(UUID())
	{
	}

	Ref<MMedia> MMedia::CreateRefMList()
	{
		return MakeRef<MMedia>();
	}

	Ref<MMedia> MMedia::CreateRefMList(const Ref<MMedia>& other)
	{

		auto ml = MakeRef<MMedia>();
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