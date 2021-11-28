#include "pch.h"
#include "CppUnitTest.h"

#include "Date.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:

		TEST_METHOD(TestDateParse_DD_MM_YYYY)
		{
			std::string date_string = "26/12/2000";
			mlist::Date date(date_string, mlist::Date::DateFormat::DD_MM_YYYY);
			Assert::AreEqual(26.0f, (float)date.GetDay());
			Assert::AreEqual(12.0f, (float)date.GetMonth());
			Assert::AreEqual(2000.0f, (float)date.GetYear());
			Assert::AreEqual(date_string, date.GetDate());
		}

		TEST_METHOD(TestDateParse_MM_DD_YYYY)
		{
			std::string date_string = "12/26/2000";
			mlist::Date date(date_string, mlist::Date::DateFormat::MM_DD_YYYY);
			Assert::AreEqual(26.0f, (float)date.GetDay());
			Assert::AreEqual(12.0f, (float)date.GetMonth());
			Assert::AreEqual(2000.0f, (float)date.GetYear());
			Assert::AreEqual(date_string, date.GetDate());
		}

		TEST_METHOD(TestDateParse_YYYY_MM_DD)
		{
			std::string date_string = "2000/12/26";
			mlist::Date date(date_string, mlist::Date::DateFormat::YYYY_MM_DD);
			Assert::AreEqual(26.0f, (float)date.GetDay());
			Assert::AreEqual(12.0f, (float)date.GetMonth());
			Assert::AreEqual(2000.0f, (float)date.GetYear());
			Assert::AreEqual(date_string, date.GetDate());
		}

		TEST_METHOD(TestDateParse_YYYY_DD_MM)
		{
			std::string date_string = "2000/26/12";
			mlist::Date date(date_string, mlist::Date::DateFormat::YYYY_DD_MM);
			Assert::AreEqual(26.0f, (float)date.GetDay());
			Assert::AreEqual(12.0f, (float)date.GetMonth());
			Assert::AreEqual(2000.0f, (float)date.GetYear());
			Assert::AreEqual(date_string, date.GetDate());
		}

	};
}
