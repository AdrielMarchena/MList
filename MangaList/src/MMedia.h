#pragma once

#include <string>
#include "core/core.h"
#include "Time/Date.h"
namespace mlist
{

	class MMediaSerializer;
	class MMedia
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
		std::string Authors = "Unamed Author"; //TODO: Make a vector
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
		static Ref<MMedia> CreateRefMList(const Ref<MMedia>& other);

		uint64_t GetUUID() const { return m_UUID; }

	private:
		friend class MMediaSerializer;
	};

	static Ref<std::vector<mlist::MMedia>> CreateMListVector()
	{
		return MakeRef< std::vector<mlist::MMedia>>();
	}
}