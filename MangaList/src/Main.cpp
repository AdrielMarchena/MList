#include "core/pch.h"
#include "Log/Log.h"
#include "Time/Date.h"
#include "MMedia.h"
#include "Serializer/MMediaSerializer.h"

int main(int argv, char** argc)
{
	MLIST_PROFILE_BEGIN_SESSION("Profile", "Profile/Profile.json");

	std::string error = mlist::Log::Init();
	if (!error.empty())
	{
		std::cout << "Error initializing spdlog: " << error << std::endl;
		return EXIT_FAILURE;
	}

	std::string date_string = "09/12/1968";
	mlist::Date date(date_string);

	auto vlist = mlist::CreateMListVector();
	mlist::MMediaSerializer serializer(vlist);

	if (serializer.Deserialize("MyList.mlist"))
	{
		for (auto& m : *vlist)
		{
			MLIST_USER_LOG_INFO("Manga Title {0}", m.Title);
			MLIST_USER_LOG_INFO("Manga SubTitle {0}", m.SubTitle);
			MLIST_USER_LOG_INFO("Manga Category {0}", m.Category);
			MLIST_USER_LOG_INFO("Manga Description {0}", m.Description);
			MLIST_USER_LOG_INFO("Manga Language {0}", m.Language);
			MLIST_USER_LOG_INFO("Manga Total Chapters {0}", m.TotalChapters);
			MLIST_USER_LOG_INFO("Manga Readed Chapters {0}", m.ReadedChapters);
			double percentage = (m.ReadedChapters * 100.0) / m.TotalChapters;
			MLIST_USER_LOG_INFO("You Readed {0}% of this Manga", percentage);
			return EXIT_SUCCESS;
		}
	}

	mlist::MMedia manga;

	manga.Title = "Vinland";
	manga.SubTitle = "Saga";
	manga.Category = "Action";
	manga.Description = "Dudes doing things";
	manga.Language = "PT-BR";
	manga.TotalChapters = 200;
	manga.ReadedChapters = 200;

	vlist->push_back(manga);

	serializer.Serialize("MyList.mlist");

	MLIST_PROFILE_END_SESSION();

	return EXIT_SUCCESS;
}