#pragma once

#include "Serializer/Reflection.h"
#include <string>
#include <ctime>

//namespace mlist
//{
//	class Date;
//}
//FORWARD_DECLARATION(mlist::Date);

namespace mlist
{
	/* Represent a date in DD/MM/YYYY */
	class MMediaSerializer;
	class Date
	{
	public:
		enum DateFormat : int
		{
			DD_MM_YYYY = 1,
			MM_DD_YYYY,
			YYYY_MM_DD,
			YYYY_DD_MM
		};
	private:
		std::string m_Date = "26/12/2000";
		//clamp to 0-31
		uint8_t m_Day = 26;
		//clamp to 0-12
		uint8_t m_Month = 12;
		//clamp to 0-9999
		uint16_t m_Year = 2000;
		DateFormat m_Format;
	public:
		unsigned char Delimiter = '/';

		Date(const std::string& date, DateFormat format = DateFormat::DD_MM_YYYY, unsigned char delimiter = '/');
		Date(){}
		~Date() = default;
		Date(const Date&) = default;

		void SetDate(const std::string& date, DateFormat format = DateFormat::DD_MM_YYYY);

		const std::string& GetDate() const { return m_Date; }
		const DateFormat GetFormat() const { return m_Format; }

		uint8_t GetDay() const { return m_Day; }
		uint8_t GetMonth() const { return m_Month; }
		uint16_t GetYear() const { return m_Year; }

		void SetDay(uint8_t day);
		void SetMonth(uint8_t month);
		void SetYear(uint16_t year);
		void SetFormat(int format) { m_Format = (DateFormat)format; }
		void SetFormat(DateFormat format) { m_Format = format; }

	private:
		/* Parse string date that does not contain a delimiter */
		void ParseNoDelimiter(const std::string& date, DateFormat format = DateFormat::DD_MM_YYYY);
		void ParseDelimiter(const std::string& date, DateFormat format = DateFormat::DD_MM_YYYY);

		friend class MMediaSerializer;
		//FRIEND_FOR_REFLECTION(::mlist::Date);
	};

}

//DEFINE_TYPE(mlist::Date);
//DEFINE_TYPE(mlist::Date::DateFormat);
//
//BEGIN_ATTRIBUTES_FOR(mlist::Date);
//DEFINE_MEMBER(m_Date);
//DEFINE_MEMBER(m_Day);
//DEFINE_MEMBER(m_Month);
//DEFINE_MEMBER(m_Year);
//DEFINE_MEMBER(m_Format);
//END_ATTRIBUTES;