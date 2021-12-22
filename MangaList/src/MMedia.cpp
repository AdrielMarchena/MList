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

	
}