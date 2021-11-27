#pragma once
#include "core/pch.h"
#include "core/core.h"
namespace mlist
{

	class MListSerializer;
	class MList
	{
	private:
		uint64_t m_UUID = NULL;
		MList(uint64_t uuid):m_UUID(uuid) {}
	public:
		std::string Title;
		std::string SubTitle;
		std::string Category;
		std::string Description;
		std::string Language;
		uint16_t TotalChapters;
		uint16_t ReadedChapters;

		MList();
		MList(const MList&) = default;
		~MList() = default;

		/* Create new MList as Ref */
		static Ref<MList> CreateRefMList();

		/* Copy the content of a Ref MList to a new one */
		static Ref<MList> CreateRefMList(const Ref<MList>& other);

		uint64_t GetUUID() const { return m_UUID; }

	private:
		friend class MListSerializer;
	};

	static Ref<std::vector<mlist::MList>> CreateMListVector()
	{
		return MakeRef< std::vector<mlist::MList>>();
	}
}