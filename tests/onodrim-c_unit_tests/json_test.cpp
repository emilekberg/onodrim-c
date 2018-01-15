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
namespace onodrim_unit_tests
{
	TEST_CLASS(JSON)
	{
	public:

		TEST_METHOD(JSON_Ctor)
		{
			auto obj = onodrim::JSON::parse(data);
			
		}
		TEST_METHOD(JSON_Get_int_)
		{
			auto obj = onodrim::JSON::parse(data);
			Assert::AreEqual(42, obj->Get<int>("num"));
		}
		TEST_METHOD(JSON_Get_string_)
		{
			auto obj = onodrim::JSON::parse(data);
			Assert::AreEqual((std::string)"hello", obj->Get<std::string>("str"));
		}
		TEST_METHOD(JSON_GetArray_int)
		{
			auto obj = onodrim::JSON::parse(data);
			auto actual = obj->GetArray<int>("arr");
			Assert::AreEqual(0, actual[0]);
			Assert::AreEqual(2, actual[1]);
			Assert::AreEqual(4, actual[2]);
			Assert::AreEqual(8, actual[3]);
		}
		TEST_METHOD(JSON_GetArray_string)
		{
			auto obj = onodrim::JSON::parse(data);
			auto actual = obj->GetArray<std::string>("strArr");
			Assert::AreEqual((std::string)"hej", actual[0]);
			Assert::AreEqual((std::string)"dig", actual[1]);
			Assert::AreEqual((std::string)"du", actual[2]);
		}
		TEST_METHOD(JSON_GetObject)
		{
			auto obj = onodrim::JSON::parse(data);
			auto actual = obj->GetObject("obj");
			bool result = actual == nullptr;
			Assert::IsFalse(result);
		}

		TEST_METHOD(JSON_GetObject_Get_Int)
		{
			auto obj = onodrim::JSON::parse(data);
			auto actual = obj->GetObject("obj");
			Assert::AreEqual(41, actual->Get<int>("num"));
		}

		TEST_METHOD(JSON_GetObject_GetArray_object)
		{
			auto obj = onodrim::JSON::parse(data);
			auto sub = obj->GetObject("obj");
			auto arr = sub->GetArrayObj("arrayOfObjects");
			Assert::AreEqual((size_t)3, arr.size());
			for (int i = 0; i < (int)arr.size(); i++)
			{
				int number = arr[i]->Get<int>("someNumber");
				Assert::AreEqual(i * 2, number);
			}
		}
	};
}
