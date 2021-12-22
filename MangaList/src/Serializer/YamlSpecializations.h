#pragma once

#include "Time/Date.h"

#include "yaml-cpp/yaml.h"

namespace YAML
{

	template<>
	struct convert<mlist::Date>
	{
		static Node encode(const mlist::Date& date)
		{
			Node node;
			node.push_back(date.GetDate());
			node.push_back((int)date.GetFormat());
			return node;
		}

		static bool decode(const Node& node, mlist::Date& date)
		{
			if (!node.IsSequence())
				return false;

			date.SetFormat(node[1].as<int>());
			date.SetDate(node[0].as<std::string>());
			return true;
		}
	};


	Emitter& operator<<(YAML::Emitter& out, const mlist::Date& date)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << date.GetDate() << date.GetFormat() << YAML::EndSeq;
		return out;
	}

}