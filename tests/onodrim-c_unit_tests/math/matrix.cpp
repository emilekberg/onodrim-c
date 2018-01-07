#include "CppUnitTest.h"
#include "../../../src/onodrim-c/math/matrix.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace onodrim;
namespace onodrim_unit_tests
{
	TEST_CLASS(Matrix)
	{
	public:

		TEST_METHOD(Matrix_Ctor)
		{
			onodrim::Matrix<float, 3> matrix;
			Assert::AreEqual(matrix[0], 1.0f);
			Assert::AreEqual(matrix[1], 0.0f);
			Assert::AreEqual(matrix[2], 0.0f);
			Assert::AreEqual(matrix[3], 0.0f);
			Assert::AreEqual(matrix[4], 1.0f);
			Assert::AreEqual(matrix[5], 0.0f);
			Assert::AreEqual(matrix[6], 0.0f);
			Assert::AreEqual(matrix[7], 0.0f);
			Assert::AreEqual(matrix[8], 1.0f);
		}
	};
}
