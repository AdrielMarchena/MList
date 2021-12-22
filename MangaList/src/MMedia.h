#pragma once

#include <string>
#include "core/core.h"
#include "Time/Date.h"
#include "Serializer/Reflection.h"
namespace mlist
{
	class MMediaSerializer;
	class MLIST_API MMedia
	{
	private:
		uint64_t m_UUID = NULL;
		MMedia(uint64_t uuid):m_UUID(uuid) {}
	public:
		std::string MediaType = "Not specified";
		std::string Title = "Not specified";
		std::string SubTitle = "Not specified";
		std::string Category = "Not specified";
		std::string Description = "Not specified";
		std::string Language = "Not specified";
		std::vector<std::string> Authors = { "Unamed Author" };
		mlist::Date ReleaseDate = "01/01/1900";
		mlist::Date BeginReadDate = "01/01/1900";
		mlist::Date EndReadDate = "01/01/1900";
		uint16_t TotalChapters = 1;
		uint16_t ReadedChapters = 0;

		MMedia();
		MMedia(const MMedia&) = default;
		~MMedia() = default;

		/* Create new MMedia as Ref */
		static Ref<MMedia> CreateRefMList();

		/* Copy the content of a Ref MMedia to a new one */
		//static Ref<MMedia> CreateRefMList(const Ref<MMedia>& other);

		uint64_t GetUUID() const { return m_UUID; }

	private:
		friend class MMediaSerializer;
	};

	static Ref<std::vector<mlist::MMedia>> CreateMListVector()
	{
		return MakeRef< std::vector<mlist::MMedia>>();
	}


}
//Idk, i will keep this here, maybe i try this again later
DEFINE_TYPE(mlist::MMedia);

BEGIN_ATTRIBUTES_FOR(mlist::MMedia);
DEFINE_MEMBER(MediaType);
DEFINE_MEMBER(Title);
DEFINE_MEMBER(SubTitle);
DEFINE_MEMBER(Category);
DEFINE_MEMBER(Description);
DEFINE_MEMBER(Language);
DEFINE_MEMBER(Authors);
DEFINE_MEMBER(ReleaseDate);
DEFINE_MEMBER(BeginReadDate);
DEFINE_MEMBER(EndReadDate);
DEFINE_MEMBER(TotalChapters);
DEFINE_MEMBER(ReadedChapters);
END_ATTRIBUTES;