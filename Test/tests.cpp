#include "CppUnitTest.h"
#include "Algorithm.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using IDragnev::Functional::LessThan;
using namespace IDragnev::Algorithm;

namespace Test
{		
	TEST_CLASS(Tests)
	{
		using IntArray = std::vector<int>;
		using MergeSorter = MergeSorter<IntArray::iterator>;

	public:
		TEST_METHOD(insertionSort)
		{
			Assert::IsTrue(sortsNonTrivialArray<InsertionSorter>());
		}

		TEST_METHOD(selectionSort)
		{
			Assert::IsTrue(sortsNonTrivialArray<SelectionSorter>());
		}

		TEST_METHOD(mergeSort)
		{
			Assert::IsTrue(sortsNonTrivialArray<MergeSorter>());
		}

		TEST_METHOD(findingMinElement)
		{
			const int nums[] = { 1, 12, 100, -1, 10 };
			const auto expected = nums + 3;

			auto result = minElementPosition(std::cbegin(nums), std::cend(nums), LessThan{});

			Assert::AreEqual(result, expected);
		}

		TEST_METHOD(findingMinElementOfEmptyRange)
		{
			std::vector<int> nums;

			auto result = minElementPosition(std::cbegin(nums), std::cend(nums), LessThan{});

			Assert::IsTrue(result == std::cend(nums));
		}

	private:
		template <typename Sorter>
		static bool sortsNonTrivialArray()
		{
			auto nums = IntArray{ 3, 5, 4, 1, 0, 2 };
			const auto expected = IntArray{ 0, 1, 2, 3, 4, 5 };

			Sorter{}(std::begin(nums), std::end(nums), LessThan{});

			return nums == expected;
		}
	};
}