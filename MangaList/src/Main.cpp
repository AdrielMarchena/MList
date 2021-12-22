#include "core/pch.h"
#include "Log/Log.h"
#include "Time/Date.h"
#include "MMedia.h"
#include "Serializer/MMediaSerializer.h"

#include "standalone/PasrseArgs.h"

static mlist::Ref<mlist::MMediaSerializer> s_MediaSerializer;

void gInvalidateS(mlist::Ref<std::vector<mlist::MMedia>> media)
{
	s_MediaSerializer = mlist::MakeRef<mlist::MMediaSerializer>(media);
}

mlist::Ref<std::vector<mlist::MMedia>> gBlanckMMedia()
{
	using namespace mlist;
	
	return CreateMListVector();
}

void CreateNewFile(const std::string& filepath)
{
	if (std::filesystem::exists(filepath))
	{
		//Do i give a warn and override the thing, or i do nothing?
		// Probably give a option
		MLIST_USER_LOG_WARN("The file in the path '{0}' already exists!", filepath);
	}
	else
	{
		gInvalidateS(gBlanckMMedia());
		s_MediaSerializer->Serialize(filepath);
	}
}

//C
void InsertMedia()
{

}

//R
void ReadMedia()
{

}

//U
void UpdateMedia()
{

}

//D
void DeleteMedia()
{

}

int main(int argv, char** argc)
{
	MLIST_PROFILE_BEGIN_SESSION("Profile", "Profile/Profile.json");

	mlist::ConsoleArgsParser parser;
	{// Scope
		MLIST_PROFILE_SCOPE("Parsing console args");
		parser.DisableRegistryMode();
		parser.ParseArgs(argv,argc);
	}

	std::string error = mlist::Log::Init();
	if (!error.empty())
	{
		std::cout << "Error initializing spdlog: " << error << std::endl;
		return EXIT_FAILURE;
	}

	auto list = mlist::CreateMListVector();
	mlist::MMedia media;

	media.MediaType = "Book";
	media.Title = "Life";
	media.SubTitle = "SubLife";
	media.Category = "Ukay";
	media.Description = "A series of books based on bla bla bla, it is about the hero bla bla who gain powers throw horrific experiences that involves cocaine, the FBI, vietnam and a bunch of bananas";
	media.Language = "PT-BR";
	media.Authors = {"Adriel Marchena", "Karl Marx", "Aquele cara que apanha no programa do ratinho"};

	media.ReleaseDate = mlist::Date("12/08/1958");
	media.BeginReadDate = mlist::Date("16/08/2021");
	media.EndReadDate = mlist::Date("26/08/2021");

	media.TotalChapters = 12;
	media.ReadedChapters = 12;

	list->push_back(media);

	media.MediaType = "Manga";
	media.Title = "Walking";
	media.SubTitle = "";
	media.Category = "Calm";
	media.Description = "A history about a man walking";
	media.Language = "PT-BR";
	media.Authors = { "Some", "One" };

	media.ReleaseDate = mlist::Date("19/06/2001");
	media.BeginReadDate = mlist::Date("16/08/2011");
	media.EndReadDate = mlist::Date("20/08/2011");

	media.TotalChapters = 12;
	media.ReadedChapters = 12;

	list->push_back(media);

	mlist::MMediaSerializer serializer(list);

	serializer.Serialize("mList.mlist");

	//Desirialize
	//-----------
	auto dlist = mlist::CreateMListVector();
	mlist::MMediaSerializer deserializer(dlist); //You can use the same obj to serialize and deserialize, i'm just showing deserialization with blanck obj

	deserializer.Deserialize("mList.mlist");

	for (auto& media : *dlist)
	{
		MLIST_USER_LOG_INFO("Media type {0}", media.MediaType);
		MLIST_USER_LOG_INFO("Media Title {0}", media.Title);
		MLIST_USER_LOG_INFO("Media SubTitle {0}", media.SubTitle);
		MLIST_USER_LOG_INFO("Media Category {0}", media.Category);
		MLIST_USER_LOG_INFO("Media Description {0}", media.Description);
		MLIST_USER_LOG_INFO("Media Language {0}", media.Language);

		MLIST_USER_LOG_INFO("Media Authors:");
		for (auto& aut : media.Authors)
			MLIST_USER_LOG_INFO("	Author: {0}", aut);

		MLIST_USER_LOG_INFO("Media Release Date {0}", media.ReleaseDate.GetDate());
		MLIST_USER_LOG_INFO("Media Begin Read Date {0}", media.BeginReadDate.GetDate());
		MLIST_USER_LOG_INFO("Media End Read Date {0}", media.EndReadDate.GetDate());
		MLIST_USER_LOG_INFO("Media Total Chapters {0}", media.TotalChapters);
		MLIST_USER_LOG_INFO("Media Readed Chapters {0}", media.ReadedChapters);
	}

	MLIST_PROFILE_END_SESSION();

	return EXIT_SUCCESS;
}