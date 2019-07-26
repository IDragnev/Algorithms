#include "CppUnitTest.h"
#include "Algorithm.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using IDragnev::Functional::LessThan;

namespace alg = IDragnev::Algorithm;

namespace Test
{		
	auto max = [](auto x, auto y) { return x >= y ? x : y; };

	TEST_CLASS(Tests)
	{
		using IntArray = std::vector<int>;
		using MergeSorter = alg::MergeSorter<IntArray::iterator>;

	public:
		TEST_METHOD(insertionSort)
		{
			Assert::IsTrue(sortsNonTrivialArray<alg::InsertionSorter>());
		}

		TEST_METHOD(selectionSort)
		{
			Assert::IsTrue(sortsNonTrivialArray<alg::SelectionSorter>());
		}

		TEST_METHOD(mergeSort)
		{
			Assert::IsTrue(sortsNonTrivialArray<MergeSorter>());
		}

		TEST_METHOD(findingMinElement)
		{
			const int nums[] = { 1, 12, 100, -1, 10 };
			const auto expected = nums + 3;

			auto result = alg::minElementPosition(std::cbegin(nums), std::cend(nums), LessThan{});

			Assert::AreEqual(result, expected);
		}

		TEST_METHOD(findingMinElementOfEmptyRange)
		{
			std::vector<int> nums;

			auto result = alg::minElementPosition(std::cbegin(nums), std::cend(nums), LessThan{});

			Assert::IsTrue(result == std::cend(nums));
		}

		TEST_METHOD(lowerBoundWithPresentKeyInTheSequence)
		{
			const auto nums = numsFromTo(0, 100);
			
			auto position = alg::lowerBound(std::begin(nums), std::end(nums), 40);

			Assert::IsTrue(position == std::begin(nums) + 40);
		}

		TEST_METHOD(lowerBoundWithNoEqualButGreaterKeyInTheSequence)
		{
			const auto nums = numsFromTo(0, 100);

			auto position = alg::lowerBound(std::begin(nums), std::end(nums), -1);

			Assert::IsTrue(position == std::begin(nums));
		}

		TEST_METHOD(lowerBoundWithNoGreaterOrEqualKeyInTheSequence)
		{
			const auto nums = numsFromTo(0, 100);

			auto position = alg::lowerBound(std::begin(nums), std::end(nums), 10'000);

			Assert::IsTrue(position == std::end(nums));
		}

		TEST_METHOD(upperBoundWithNoGreaterKeyInTheSequence)
		{
			const auto nums = numsFromTo(0, 100);

			auto position = alg::upperBound(std::cbegin(nums), std::cend(nums), 1'000);

			Assert::IsTrue(position == std::cend(nums));
		}

		TEST_METHOD(upperBoundWithGreaterKeyInTheSequence)
		{
			const auto nums = numsFromTo(0, 100);

			auto position = alg::upperBound(std::cbegin(nums), std::cend(nums), 97);

			Assert::IsTrue(position == std::begin(nums) + 98);
		}

		TEST_METHOD(binarySearchWithMissingKey)
		{
			const auto nums = numsFromTo(0, 100);

			auto position = alg::binarySearch(std::begin(nums), std::end(nums), 10'000);

			Assert::IsTrue(position == std::end(nums));
		}

		TEST_METHOD(binarySearchWithPresentKey)
		{
			const auto nums = numsFromTo(0, 100);

			auto position = alg::binarySearch(std::begin(nums), std::end(nums), 40);

			Assert::IsTrue(position == std::begin(nums) + 40);
		}

		TEST_METHOD(rotateWithEmptyFirstSubrange)
		{
			auto nums = numsFromTo(1, 10);
		
			auto midPoint = alg::rotate(std::begin(nums), std::begin(nums), std::end(nums));

			Assert::IsTrue(nums == numsFromTo(1, 10));
			Assert::IsTrue(midPoint == std::end(nums));
		}

		TEST_METHOD(rotateWithEmptySecondSubrange)
		{
			auto nums = numsFromTo(1, 10);

			auto midPoint = alg::rotate(std::begin(nums), std::end(nums), std::end(nums));

			Assert::IsTrue(nums == numsFromTo(1, 10));
			Assert::IsTrue(midPoint == std::begin(nums));
		}

		TEST_METHOD(rotateWithNonEmptySubranges)
		{
			auto nums = numsFromTo(1, 10);
			using Nums = decltype(nums);

			auto midPoint = alg::rotate(std::begin(nums), std::begin(nums) + 5, std::end(nums));

			Assert::IsTrue(nums == Nums{ 6, 7, 8, 9, 10, 1, 2, 3, 4, 5});
			Assert::IsTrue(midPoint == std::begin(nums) + 5);
		}

		TEST_METHOD(stablePartitionWithEmptyRange)
		{
			auto nums = std::vector<int>{};
			auto isPositive = [](auto x) { return x > 0; };

			auto it = alg::stablePartition(std::begin(nums), std::end(nums), isPositive);

			Assert::IsTrue(it == std::begin(nums));
		}

		TEST_METHOD(stablePartitionWithNonEmptyRange)
		{
			auto nums = numsFromTo(1, 10);
			using Nums = decltype(nums);
			auto isEven = [](auto x) { return x % 2 == 0; };

			auto it = alg::stablePartition(std::begin(nums), std::end(nums), isEven);

			Assert::IsTrue(nums == Nums{ 2, 4, 6, 8, 10, 1, 3, 5, 7, 9 });
			Assert::IsTrue(it == std::begin(nums) + 5);
		}

		TEST_METHOD(zipReduce)
		{
			auto nums = std::vector<int>{ 2, 3, 5, 9, 11 };

			auto result = alg::zipReduce(std::cbegin(nums) + 1, std::cend(nums),
				                         std::cbegin(nums),
										 0,
										 std::minus<int>{},
										 max);

			Assert::AreEqual(result, 4);
		}

		TEST_METHOD(transformReduce)
		{
			using IDragnev::Functional::plus;

			auto nums = { 2, 3, 5, 9, 11 };

			auto result = alg::transformReduce(std::cbegin(nums),
											   std::cend(nums),
											   0,
										 	   plus(1),
											   max);
			Assert::AreEqual(result, 12);
		}

		TEST_METHOD(inclusiveScan)
		{
			using Ints = std::vector<int>;

			auto nums = Ints{ 2, 3, 5, 9, 11 };
			auto result = Ints(nums.size(), 0);

			alg::inclusiveScan(std::cbegin(nums),
							   std::cend(nums),
							   std::begin(result),
						       std::plus{});

			Assert::IsTrue(result == Ints{ 2, 5, 10, 19, 30 });
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