#include "CppUnitTest.h"
#include "../../../src/onodrim-c/math/vector.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace onodrim;
namespace onodrim_unit_tests
{
	TEST_CLASS(Vector)
	{
	public:

		TEST_METHOD(Vector_Ctor)
		{
			float x = 1.f;
			float y = 3.f; 
			float z = 1.f;
			onodrim::Vector<float, 3> vector
			{
				x, y, z
			};
			Assert::AreEqual(x, vector[0]);
			Assert::AreEqual(y, vector[1]);
			Assert::AreEqual(z, vector[2]);
		}

		TEST_METHOD(Vector_Length)
		{

			onodrim::Vector<float, 2> vectorSingleLength
			{
				4.f, 0
			};
			float lenghtFor_vectorSingleLength = vectorSingleLength.Length();
			float expectedLenghtFor_vectorSingleLength = 4.f;
			Assert::AreEqual(lenghtFor_vectorSingleLength, expectedLenghtFor_vectorSingleLength);

			onodrim::Vector<float, 3> vector3dLength
			{
				4.f, 4.f, 4.f
			};
			float lenghtFor_vector3dLength = vector3dLength.Length();
			float expectedLenghtFor_vector3dLength = 6.92820323028f;
			Assert::AreEqual(lenghtFor_vector3dLength, expectedLenghtFor_vector3dLength);
		}

		TEST_METHOD(Vector_LengthSquared)
		{

			onodrim::Vector<float, 2> vectorSingleLength
			{
				4.f, 0
			};
			float lenghtFor_vectorSingleLength = vectorSingleLength.LengthSquared();
			float expectedLenghtFor_vectorSingleLength = 16.f;
			Assert::AreEqual(lenghtFor_vectorSingleLength, expectedLenghtFor_vectorSingleLength);

			onodrim::Vector<float, 3> vector3dLength
			{
				4.f, 4.f, 4.f
			};
			float lenghtFor_vector3dLength = vector3dLength.LengthSquared();
			float expectedLenghtFor_vector3dLength = 48;
			Assert::AreEqual(lenghtFor_vector3dLength, expectedLenghtFor_vector3dLength);
		}

		TEST_METHOD(Vector_Normalize)
		{
			onodrim::Vector<float, 3> vector
			{
				10.0f, 0.0f, 0.0f
			};
			vector.Normalize();
			float length = vector.Length();
			float expectedLength = 1.f;
			Assert::AreEqual(length, expectedLength);
		}

		TEST_METHOD(Vector_OperatorAdd)
		{
			onodrim::Vector<float, 2> vector
			{
				0.f, 0.f
			};
			onodrim::Vector<float, 2> toAdd{ 1.f, 2.f };
			// Make sure vectors are added properly, and return a new vector object
			Assert::AreEqual((vector + toAdd)[0], 1.f);
			Assert::AreEqual((vector + toAdd)[1], 2.f);
			// Make sure vector object is not manipulated
			Assert::AreEqual(vector[0], 0.f);
			Assert::AreEqual(vector[1], 0.f);
		}

		TEST_METHOD(Vector_OperatorCompare)
		{
			onodrim::Vector<float, 3> firstVector
			{
				1.f, 2.f, 3.f
			};
			onodrim::Vector<float, 3> secondVector
			{
				1.f, 2.f, 3.f
			};
			onodrim::Vector<float, 3> thirdVector
			{
				3.f, 4.f, 5.f
			};
			Assert::IsTrue(firstVector == secondVector);
			Assert::IsFalse(firstVector == thirdVector);
		}

		TEST_METHOD(Vector_OperatorAssignInitializer)
		{
			onodrim::Vector<int, 2> vector
			{
				1, 2
			};
			vector =
			{
				3, 4
			};

			Assert::AreEqual(vector[0], 3);
			Assert::AreEqual(vector[1], 4);
		}

		TEST_METHOD(Vector_OperatorAssignVector)
		{
			onodrim::Vector<float, 2> vector{ 1.f, 2.f };
			vector = onodrim::Vector<float, 2>{ 6.f, 7.f };

			Assert::AreEqual(vector[0], 6.f);
			Assert::AreEqual(vector[1], 7.f);
		}

	};
}
