#include "stdafx.h"
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
	"some key with space": 1,
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
onodrim::JSON obj = onodrim::JSON(data);
namespace onodrim_unit_tests
{
	TEST_CLASS(JSON)
	{
	public:

		TEST_METHOD(JSON_HasValues_Empty)
		{
			onodrim::JSON emptyObject;
			Assert::IsFalse(emptyObject.HasValues());
		}
		TEST_METHOD(JSON_Ctor)
		{
			onodrim::JSON obj_ctor(data);
			Assert::IsTrue(obj_ctor.HasValues());
		}
		TEST_METHOD(JSON_Get_int)
		{
			Assert::AreEqual(42, obj.Get<int>("num"));
		}
		TEST_METHOD(JSON_Get_string)
		{
			Assert::AreEqual((std::string)"hello", obj.Get<std::string>("str"));
		}
		TEST_METHOD(JSON_Get_key_with_space)
		{
			Assert::AreEqual(1, obj.Get<int>("some key with space"));

		}
		TEST_METHOD(JSON_Get_Array_int)
		{
			auto actual = obj.Get<std::vector<int>>("arr");
			Assert::AreEqual(0, actual[0]);
			Assert::AreEqual(2, actual[1]);
			Assert::AreEqual(4, actual[2]);
			Assert::AreEqual(8, actual[3]);
		}
		TEST_METHOD(JSON_Get_Array_string)
		{
			auto actual = obj.Get<std::vector<std::string>>("strArr");
			Assert::AreEqual((std::string)"hej", actual[0]);
			Assert::AreEqual((std::string)"dig", actual[1]);
			Assert::AreEqual((std::string)"du", actual[2]);
		}
		TEST_METHOD(JSON_Get_Object)
		{
			auto actual = obj.Get<onodrim::JSON>("obj");
			Assert::IsTrue(actual.HasValues());
		}

		TEST_METHOD(JSON_Get_Object_Get_Int)
		{
			auto actual = obj.Get<onodrim::JSON>("obj");
			Assert::AreEqual(41, actual.Get<int>("num"));
		}

		TEST_METHOD(JSON_Get_Object_Get_Array_object)
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

		TEST_METHOD(JSON_Set_int)
		{
			onodrim::JSON obj;
			obj.Set("someInt", 42);
			Assert::AreEqual(42, obj.Get<int>("someInt"));
		}

		TEST_METHOD(JSON_Set_string)
		{
			onodrim::JSON obj;
			obj.Set("someString", "This is a string");
			Assert::AreEqual((std::string)"This is a string", obj.Get<std::string>("someString"));
		}
	};
}
