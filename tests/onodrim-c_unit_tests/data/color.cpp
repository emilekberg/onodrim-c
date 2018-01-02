#include "CppUnitTest.h"
#include "../../../src/onodrim-c/data/color.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace onodrim;
namespace onodrim_unit_tests
{
	TEST_CLASS(Color)
	{
	public:
		TEST_METHOD(Color_DefaultCtor)
		{
			onodrim::Color color;
			Assert::AreEqual(color.R, 1.0f);
			Assert::AreEqual(color.G, 1.0f);
			Assert::AreEqual(color.B, 1.0f);
			Assert::AreEqual(color.A, 1.0f);
		}

		TEST_METHOD(Color_HexCtor)
		{
			onodrim::Color color(0xFF0000);
			Assert::AreEqual(color.R, 1.0f);
			Assert::AreEqual(color.G, 0.0f);
			Assert::AreEqual(color.B, 0.0f);
			Assert::AreEqual(color.A, 1.0f);
		}

		TEST_METHOD(Color_RGBACtor)
		{
			onodrim::Color color(1.0f, 1.0f, 0.0f, 1.0f);
			Assert::AreEqual(color.R, 1.0f);
			Assert::AreEqual(color.G, 1.0f);
			Assert::AreEqual(color.B, 0.0f);
			Assert::AreEqual(color.A, 1.0f);
		}

		TEST_METHOD(Color_SetHex)
		{
			onodrim::Color color;
			color.SetHex(0xFFFF00);
			Assert::AreEqual(color.R, 1.0f);
			Assert::AreEqual(color.G, 1.0f);
			Assert::AreEqual(color.B, 0.0f);
		}

		TEST_METHOD(Color_SetRGBA)
		{
			onodrim::Color color;
			color.SetRGBA(1.0f, 0.0f, 1.0f, 0.0f);
			Assert::AreEqual(color.R, 1.0f);
			Assert::AreEqual(color.G, 0.0f);
			Assert::AreEqual(color.B, 1.0f);
			Assert::AreEqual(color.A, 0.0f);
		}
	};
}