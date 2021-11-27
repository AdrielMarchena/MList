#include "core/pch.h"
#include "MListSerializer.h"
#include "uuid/uuid.h"
#include "yaml-cpp/yaml.h"

namespace mlist
{

	bool MListSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "MangaList" << YAML::Value << filepath;
		out << YAML::Key << "Mangas" << YAML::Value << YAML::BeginSeq;


		for (auto& m : *m_MList)
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Manga" << YAML::Value << m.m_UUID;
			out << YAML::Key << "Manga-Title" << YAML::Value << m.Title;
			out << YAML::Key << "Manga-SubTitle" << YAML::Value << m.SubTitle;
			out << YAML::Key << "Manga-Category" << YAML::Value << m.Category;
			out << YAML::Key << "Manga-Description" << YAML::Value << m.Description;
			out << YAML::Key << "Manga-Language" << YAML::Value << m.Language;
			out << YAML::Key << "Manga-TotalChapters" << YAML::Value << m.TotalChapters;
			out << YAML::Key << "Manga-ReadedChapters" << YAML::Value << m.ReadedChapters;
			out << YAML::EndMap;
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();

		return true;
	}

	bool MListSerializer::Deserialize(const std::string& filepath)
	{
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(filepath);
		}
		catch (const std::exception& ex)
		{
			return false;
		}

		if (!data["MangaList"])
			return false;

		MLIST_CORE_LOG_TRACE("Deserializing MangaList");

		auto mangas = data["Mangas"];
		if (mangas)
		{
			for (auto manga : mangas)
			{
				uint64_t uuid = manga["Manga"].as<uint64_t>();
				MList list(uuid);

				list.Title = manga["Manga-Title"].as<std::string>();

				MLIST_CORE_LOG_TRACE("Deserialized manga with UUID = {0}, title = {1}", uuid, list.Title);

				list.SubTitle = manga["Manga-SubTitle"].as<std::string>();
				list.Category = manga["Manga-Category"].as<std::string>();
				list.Description = manga["Manga-Description"].as<std::string>();
				list.Language = manga["Manga-Language"].as<std::string>();
				list.TotalChapters = manga["Manga-TotalChapters"].as<uint32_t>();
				list.ReadedChapters = manga["Manga-ReadedChapters"].as<uint32_t>();

				m_MList->push_back(list);
			}
		}

		return true;
	}

}
