#include "core/pch.h"
#include "MMediaSerializer.h"
#include "Reflection.h"
#include "uuid/uuid.h"
#include "yaml-cpp/yaml.h"
#include "YamlSpecializations.h"

namespace mlist
{

	bool MMediaSerializer::Serialize(const std::string& filepath)
	{
		MLIST_PROFILE_FUNCTION();

		if (m_MList->empty())
			return false;

		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "MediaSequence" << YAML::Value << UUID(); //Temp
		out << YAML::Key << "MediaList" << YAML::Value << YAML::BeginSeq;

		for (auto& m : *m_MList)
		{
			out << YAML::BeginMap;

			out << YAML::Key << "Media" << YAML::Value << m.m_UUID;

			out << YAML::Key << "Type" << YAML::Value << m.MediaType;
			out << YAML::Key << "Title" << YAML::Value << m.Title;
			out << YAML::Key << "SubTitle" << YAML::Value << m.SubTitle;
			out << YAML::Key << "Category" << YAML::Value << m.Category;
			out << YAML::Key << "Description" << YAML::Value << m.Description;
			out << YAML::Key << "Language" << YAML::Value << m.Language;
			out << YAML::Key << "Authors" << YAML::Value << m.Authors;

			out << YAML::Key << "ReleaseDate" << YAML::Value << m.ReleaseDate;
			out << YAML::Key << "BeginReadDate" << YAML::Value << m.BeginReadDate;
			out << YAML::Key << "EndReadDate" << YAML::Value << m.EndReadDate;


			out << YAML::Key << "TotalChapters" << YAML::Value << m.TotalChapters;
			out << YAML::Key << "ReadedChapters" << YAML::Value << m.ReadedChapters;
			out << YAML::EndMap;
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();

		return true;
	}

	bool MMediaSerializer::Deserialize(const std::string& filepath)
	{
		MLIST_PROFILE_FUNCTION();
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(filepath);
		}
		catch (const std::exception&)
		{
			return false;
		}

		if (!data["MediaSequence"])
			return false;

		MLIST_USER_LOG_TRACE("Deserializing MediaSequence {0}", data["MediaSequence"].as<uint64_t>());

		auto medias = data["MediaList"];
		if (medias)
		{
			for (auto media : medias)
			{
				uint64_t uuid = media["Media"].as<uint64_t>();
				MMedia list(uuid);

				list.MediaType = media["Type"].as<std::string>();
				list.Title = media["Title"].as<std::string>();

				MLIST_CORE_LOG_TRACE("Deserialized media with UUID = {0}, type = {1} ,title = {2}", uuid, list.MediaType ,list.Title);

				list.SubTitle = media["SubTitle"].as<std::string>();
				list.Category = media["Category"].as<std::string>();
				list.Description = media["Description"].as<std::string>();
				list.Language = media["Language"].as<std::string>();
				list.Authors = media["Authors"].as<std::vector<std::string>>();

				list.ReleaseDate = media["ReleaseDate"].as<mlist::Date>();
				list.BeginReadDate = media["BeginReadDate"].as<mlist::Date>();
				list.EndReadDate = media["EndReadDate"].as<mlist::Date>();

				list.TotalChapters = media["TotalChapters"].as<uint32_t>();
				list.ReadedChapters = media["ReadedChapters"].as<uint32_t>();

				m_MList->push_back(list);
			}
		}

		return true;
	}

	bool MMediaSerializer::CreateNewFile(const std::string& filepath)
	{
		return false;
	}

}
