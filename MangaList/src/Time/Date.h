#pragma once

#include <string>
#include <ctime>
namespace mlist
{
	/* Represent a date in DD/MM/YYYY */
	class Date
	{
	private:
		std::string m_Date = "26/12/2000";
		//clamp to 0-31
		uint8_t m_Day = 26;
		//clamp to 0-12
		uint8_t m_Month = 12;
		//clamp to 0-9999
		uint16_t m_Year = 2000;
	public:
		enum DateFormat: uint8_t
		{
			DD_MM_YYYY = 1,
			MM_DD_YYYY,
			YYYY_MM_DD,
			YYYY_DD_MM
		};

		Date(const std::string& date, DateFormat format = DateFormat::DD_MM_YYYY);
		Date(){}
		~Date() = default;
		Date(const Date&) = default;

		/* DD/MM/YYYY */
		void SetDate(const std::string& date, DateFormat format = DateFormat::DD_MM_YYYY);
		/* DD/MM/YYYY */
		const std::string& GetDate() const { return m_Date; }

		uint8_t GetDay() const { return m_Day; }
		uint8_t GetMonth() const { return m_Month; }
		uint16_t GetYear() const { return m_Year; }

		void SetDay(uint8_t day);
		void SetMonth(uint8_t month);
		void SetYear(uint16_t year);

	};

}