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

    Date::Date(const std::string& date, DateFormat format, unsigned char delimiter)
        :m_Date(date),Delimiter(delimiter),m_Format(format)
    {
        MLIST_PROFILE_FUNCTION();
        SetDate(date, format);
    }

    void Date::SetDate(const std::string& date, DateFormat format)
    {
        //TODO: Remove all this logic, since i always have the date format, there is no
        // need to use a delimiter to parse the date, i can just do the ParseNoDelimiter and
        // store the unparsed date string
        MLIST_PROFILE_FUNCTION();
        if (date.find(Delimiter) == std::string::npos)
            ParseNoDelimiter(date, m_Format);
        else
        {
            //Check if there is 2 delimiters on the string, if isn't, use the ParseNoDelimiter instead
            int occurrences = 0;
            std::string::size_type start = 0;

            while ((start = date.find(Delimiter, start)) != std::string::npos)
            {
                ++occurrences;
                start += 1; // 1 because the Delimiter is just a char
            }
            if (occurrences == 2)
                ParseDelimiter(date, m_Format);
            else
                ParseNoDelimiter(date, m_Format);
        }
    }

    void Date::ParseDelimiter(const std::string& date, DateFormat format)
    {
        MLIST_PROFILE_FUNCTION();
        m_Date = date;
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
        default:
            MLIST_CORE_LOG_WARN("DateFormat '{0}' not reconized, using DD_MM_YYYY as default", format);
            dates_sep = { &Day,&Month,&Year };
            break;
        }

        std::string parsed = date;

        size_t pos = 0;
        int count = 0;
        while ((pos = parsed.find(Delimiter)) != std::string::npos)
        {
            auto& r = *dates_sep[count];
            r = parsed.substr(0,pos);
            parsed.erase(0, pos + 1); // 1 because the Delimiter is just a char
            count++;
        }

        auto& r = *dates_sep[2];
        r = parsed.erase(0, pos + 1);

        m_Day = utils::StringAs<int>(Day);
        SetDay(m_Day);

        m_Month = utils::StringAs<int>(Month);
        SetMonth(m_Month);

        m_Year = utils::StringAs<int>(Year);
        SetYear(m_Year);

    }

    void Date::ParseNoDelimiter(const std::string& date, DateFormat format)
    {
        //TODO: improve this method
        MLIST_PROFILE_FUNCTION();
        int parse_order[3]{0}; 
        std::vector<std::string*> dates_sep;
        std::string Day = "";
        std::string Month = "";
        std::string Year = "";

        // Removes all non numeric characters from string, for cases where
        // The user specify the wrong delimiter to the one there is in the date string
        std::string parsed = date;
        parsed.erase(
            std::remove_if(parsed.begin(), parsed.end(), [](char c) { return !std::isdigit(c); }),
            parsed.end());

        switch(format)
        {
        case DateFormat::DD_MM_YYYY:
            parse_order[0] = 2;
            parse_order[1] = 2;
            parse_order[2] = 4;
            dates_sep = { &Day,&Month,&Year };
            break;
        case DateFormat::MM_DD_YYYY:
            parse_order[0] = 2;
            parse_order[1] = 2;
            parse_order[2] = 4;
            dates_sep = { &Month,&Day,&Year };
            break;
        case DateFormat::YYYY_MM_DD:
            parse_order[0] = 4;
            parse_order[1] = 2;
            parse_order[2] = 2;
            dates_sep = { &Year,&Month,&Day };
            break;
        case DateFormat::YYYY_DD_MM:
            parse_order[0] = 4;
            parse_order[1] = 2;
            parse_order[2] = 2;
            dates_sep = { &Year,&Day,&Month };
            break;
        default:
            MLIST_CORE_LOG_WARN("DateFormat '{0}' not reconized, using DD_MM_YYYY as default", format);
            parse_order[0] = 2;
            parse_order[1] = 2;
            parse_order[2] = 4;
            dates_sep = { &Day,&Month,&Year };
            break;
        }

        for (int i = 0; i < 3; i++)
        {
            auto& r = *dates_sep[i];
            int n = parse_order[i];

            r = parsed.substr(0, n);
            parsed.erase(0, n);

        }

        m_Day = utils::StringAs<int>(Day);
        SetDay(m_Day);

        m_Month = utils::StringAs<int>(Month);
        SetMonth(m_Month);

        m_Year = utils::StringAs<int>(Year);
        SetYear(m_Year);

    }

    void Date::SetDay(uint8_t day)
    {
        m_Day = std::clamp(day,(uint8_t)1, (uint8_t)31);
    }

    void Date::SetMonth(uint8_t month)
    {
        m_Month = std::clamp(month,(uint8_t)1 ,(uint8_t)12);
    }

    void Date::SetYear(uint16_t year)
    {
        m_Year = std::clamp(year, (uint16_t)1, (uint16_t)9999);
    }
}