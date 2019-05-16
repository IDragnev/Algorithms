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
			const auto expected = numsFromTo(1, 100);
			auto nums = reverse(expected);

			Sorter{}(std::begin(nums), std::end(nums), LessThan{});

			return nums == expected;
		}

		template <typename T>
		static auto numsFromTo(T from, T to)
		{
			auto count = to - from + 1;
			auto generator = [i = from]() mutable { return i++; };
			auto result = std::vector<T>(count, 0);

			std::generate_n(std::begin(result), count, generator);

			return result;
		}

		template <typename Container>
		static Container reverse(Container c)
		{
			std::reverse(std::begin(c), std::end(c));		
			return std::move(c);
		}
	};
}