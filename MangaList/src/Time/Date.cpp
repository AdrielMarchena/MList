#include "core/pch.h"
#include "Date.h"

namespace mlist
{
    namespace utils
    {
        template<typename T>
        T StringAs(const std::string& in)
        {
            return (T)StringAs<double>(in);
        }

        template<>
        int StringAs<int>(const std::string& in)
        {
            try
            {
                return std::stoi(in);
            }
            catch (const std::exception& ex)
            {
                MLIST_CORE_LOG_WARN("StringAs conversion failed and it's returning 0 by default. Error: {0}", ex.what());
                return 0;
            }
        }

        template<>
        double StringAs<double>(const std::string& in)
        {
            try
            {
                return std::stod(in);
            }
            catch (const std::exception& ex)
            {
                MLIST_CORE_LOG_WARN("StringAs conversion failed and it's returning 0 by default. Error: {0}", ex.what());
                return 0;
            }
        }

    }

    Date::Date(const std::string& date, DateFormat format)
        :m_Date(date)
    {
        MLIST_PROFILE_FUNCTION();
        SetDate(date,format);
    }
    void Date::SetDate(const std::string& date, DateFormat format)
    {
        MLIST_PROFILE_FUNCTION();
        std::vector<std::string*> dates_sep;
        std::string Day = "";
        std::string Month = "";
        std::string Year = "";

        switch (format)
        {
        case DateFormat::DD_MM_YYYY:
            dates_sep = { &Day,&Month,&Year };
            break;
        case DateFormat::MM_DD_YYYY:
            dates_sep = { &Month, &Day ,&Year };
            break;
        case DateFormat::YYYY_MM_DD:
            dates_sep = { &Year, &Month ,&Day };
            break;
        case DateFormat::YYYY_DD_MM:
            dates_sep = { &Year, &Day ,&Month };
            break;
        }

        std::string delimiter = "/";
        std::string parsed = date;
        
        size_t pos = 0;
        int count = 0;
        while ((pos = parsed.find(delimiter)) != std::string::npos)
        {
            auto& r = *dates_sep[count];
            r = parsed.substr(0,pos);
            parsed.erase(0, pos + delimiter.length());
            count++;
        }

        auto& r = *dates_sep[2];
        r = parsed.erase(0, pos + delimiter.length());

        m_Day = utils::StringAs<int>(Day);
        SetDay(m_Day);

        m_Month = utils::StringAs<int>(Month);
        SetMonth(m_Month);

        m_Year = utils::StringAs<int>(Year);
        SetYear(m_Year);

    }

    void Date::SetDay(uint8_t day)
    {
        m_Day = std::clamp(day,(uint8_t)0, (uint8_t)31);
    }

    void Date::SetMonth(uint8_t month)
    {
        m_Month = std::clamp(month,(uint8_t)0 ,(uint8_t)12);
    }

    void Date::SetYear(uint16_t year)
    {
        m_Year = std::clamp(year, (uint16_t)0, (uint16_t)9999);
    }
}