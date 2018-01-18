#include "CppUnitTest.h"
#include "../../src/onodrim-c/json.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
static std::string data = R"(
{
	str: "hello",
	num: 42,
	arr: [
		0,
		2,
		4,
		8
	],
	strArr: [
		"hej",
		"dig",
		"du"
	],	
	obj: {
		num: 41,
		arrayOfObjects: [
			{someNumber: 0},
			{someNumber: 2},
			{someNumber: 4}
		]
	},
	digit: 3.14
})";
onodrim::JSON obj;
namespace onodrim_unit_tests
{
	TEST_CLASS(JSON)
	{
	public:

		TEST_METHOD(JSON_HasValues_Empty)
		{
			Assert::IsFalse(obj.HasValues());
		}
		TEST_METHOD(JSON_Ctor)
		{
			obj = onodrim::JSON(data);
			Assert::IsTrue(obj.HasValues());
			
		}
		TEST_METHOD(JSON_Get_int_)
		{
			Assert::AreEqual(42, obj.Get<int>("num"));
		}
		TEST_METHOD(JSON_Get_string_)
		{
			Assert::AreEqual((std::string)"hello", obj.Get<std::string>("str"));
		}
		TEST_METHOD(JSON_GetArray_int)
		{
			auto actual = obj.Get<std::vector<int>>("arr");
			Assert::AreEqual(0, actual[0]);
			Assert::AreEqual(2, actual[1]);
			Assert::AreEqual(4, actual[2]);
			Assert::AreEqual(8, actual[3]);
		}
		TEST_METHOD(JSON_GetArray_string)
		{
			auto actual = obj.Get<std::vector<std::string>>("strArr");
			Assert::AreEqual((std::string)"hej", actual[0]);
			Assert::AreEqual((std::string)"dig", actual[1]);
			Assert::AreEqual((std::string)"du", actual[2]);
		}
		TEST_METHOD(JSON_GetObject)
		{
			auto actual = obj.Get<onodrim::JSON>("obj");
			Assert::IsTrue(actual.HasValues());
		}

		TEST_METHOD(JSON_GetObject_Get_Int)
		{
			auto actual = obj.Get<onodrim::JSON>("obj");
			Assert::AreEqual(41, actual.Get<int>("num"));
		}

		TEST_METHOD(JSON_GetObject_GetArray_object)
		{
			auto sub = obj.Get<onodrim::JSON>("obj");
			auto arr = sub.Get<std::vector<onodrim::JSON>>("arrayOfObjects");
			Assert::AreEqual((size_t)3, arr.size());
			for (int i = 0; i < (int)arr.size(); i++)
			{
				int number = arr[i].Get<int>("someNumber");
				Assert::AreEqual(i * 2, number);
			}
		}
	};
}
