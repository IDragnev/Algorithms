#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "algorithm.hpp"
#include "functional.hpp"
#include <vector>
#include <numeric>

namespace alg = IDragnev::Algorithm;

constexpr auto max = [](auto x, auto y) { return x >= y ? x : y; };

const auto iota = [](auto from, auto to) {
	const auto count = to - from + 1;
	auto result = std::vector<decltype(from)>(count, 0);

	std::iota(std::begin(result), std::end(result), from);

	return result;
};

const auto reverse = [](auto list) 
{
	std::reverse(std::begin(list), std::end(list));
	return list;
};

const auto find_if = [](const auto& range, auto pred) 
{
	return std::find_if(std::cbegin(range), std::cend(range), pred);
};

const auto find = [](const auto& range, auto value) 
{
	return find_if(range, [&value](const auto& x) { return x == value;});
};

TEST_CASE_TEMPLATE("sortings ", Sorter, alg::InsertionSorter, alg::SelectionSorter)
{
	const auto expected = iota(1, 100);
	auto nums = reverse(expected);

	Sorter{}(std::begin(nums), std::end(nums));

	CHECK(nums == expected);
}

TEST_CASE("minElementPosition")
{
	using alg::minElementPosition;

	SUBCASE("non-empty range")
	{
		const int nums[] = {1, 12, 100, -1, 10};

		const auto result = minElementPosition(std::cbegin(nums), std::cend(nums), std::less{});

		CHECK(result == find(nums, -1));
	}

	SUBCASE("empty range")
	{
		const auto nums = std::vector<int>{};
		
		const auto result = minElementPosition(std::cbegin(nums), std::cend(nums), std::less{});

		CHECK(result == std::cend(nums));
	}
}

TEST_CASE("lower bound")
{
	SUBCASE("with present key")
	{
		const auto nums = iota(0, 100);

		const auto pos = alg::lowerBound(std::cbegin(nums), std::cend(nums), 40);

		CHECK(pos == find(nums, 40));
	}

	SUBCASE("with no equal but greater key")
	{
		const auto nums = iota(0, 100);

		const auto pos = alg::lowerBound(std::begin(nums), std::end(nums), -1);

		CHECK(pos == std::begin(nums));
	}

	SUBCASE("lower bound with no geater or equal key")
	{
		const auto nums = iota(0, 100);

		auto pos = alg::lowerBound(std::begin(nums), std::end(nums), 10'000);

		CHECK(pos == std::end(nums));
	}
}

TEST_CASE("upper bound")
{
	SUBCASE("with no greater key in the sequence")
	{
		const auto nums = iota(0, 100);

		const auto position = alg::upperBound(std::cbegin(nums), std::cend(nums), 1'000);

		CHECK(position == std::cend(nums));
	}

	SUBCASE("with greater key in the sequence")
	{
		const auto nums = iota(0, 100);
		
		const auto position = alg::upperBound(std::cbegin(nums), std::cend(nums), 97);

		CHECK(position == find(nums, 98));
	}
}

TEST_CASE("binary search")
{
	SUBCASE("with missing key")
	{
		const auto nums = iota(0, 100);

		const auto position = alg::binarySearch(std::begin(nums), std::end(nums), 10'000);

		CHECK(position == std::cend(nums));
	}

	SUBCASE("with present key")
	{
		const auto nums = iota(0, 100);

		const auto position = alg::binarySearch(std::begin(nums), std::end(nums), 40);

		CHECK(position == find(nums, 40));
	}
}

TEST_CASE("rotate")
{
	SUBCASE("with empty first subrange")
	{
		auto nums = iota(1, 10);

		const auto midPoint = alg::rotate(std::begin(nums), std::begin(nums), std::end(nums));

		CHECK(nums == iota(1, 10));
		CHECK(midPoint == std::end(nums));
	}

	SUBCASE("with empty second subrange")
	{
		auto nums = iota(1, 10);

		const auto midPoint = alg::rotate(std::begin(nums), std::end(nums), std::end(nums));

		CHECK(nums == iota(1, 10));
		CHECK(midPoint == std::begin(nums));
	}

	SUBCASE("with non empty subranges")
	{
		auto nums = iota(1, 10);
		using Nums = decltype(nums);

		const auto midPoint = alg::rotate(std::begin(nums), std::begin(nums) + 5, std::end(nums));

		CHECK(nums == Nums{6, 7, 8, 9, 10, 1, 2, 3, 4, 5});
		CHECK(midPoint == std::begin(nums) + 5);
	}
}

TEST_CASE("stable partition")
{
	SUBCASE("with empty range")
	{
		auto nums = std::vector<int>{};
		const auto isPositive = [](auto x) { return x > 0; };

		const auto positivesEnd = alg::stablePartition(std::begin(nums), std::end(nums), isPositive);

		CHECK(positivesEnd == std::begin(nums));
	}

	SUBCASE("with non-empty range")
	{
		auto nums = iota(1, 10);
		using Nums = decltype(nums);
		const auto isEven = [](auto x) { return x % 2 == 0; };

		const auto evensEnd = alg::stablePartition(std::begin(nums), std::end(nums), isEven);

		CHECK(nums == Nums{2, 4, 6, 8, 10, 1, 3, 5, 7, 9});
		CHECK(evensEnd == std::begin(nums) + 5);
	}
}

TEST_CASE("zipReduce")
{
	const auto nums = std::vector<int>{ 2, 3, 5, 9, 11 };

	const auto result = alg::zipReduce(std::cbegin(nums) + 1, std::cend(nums),
									   std::cbegin(nums),
									   0,
									   std::minus{},
									   max);

	CHECK(result == 4);
}

TEST_CASE("transformReduce")
{
	using IDragnev::Functional::plus;

	const auto nums = { 2, 3, 5, 9, 11 };

	const auto result = alg::transformReduce(std::cbegin(nums),
									   		 std::cend(nums),
									   		 0,
								 	   		 plus(1),
									   		 max);
	CHECK(result == 12);
}

TEST_CASE("inclusiveScan")
{
	using Ints = std::vector<int>;

	const auto nums = Ints{ 2, 3, 5, 9, 11 };
	auto result = Ints(nums.size(), 0);

	alg::inclusiveScan(std::cbegin(nums),
					   std::cend(nums),
					   std::begin(result),
				       std::plus{});

	CHECK(result == Ints{ 2, 5, 10, 19, 30 });
}

TEST_CASE("exclusiveScan")
{
	using Ints = std::vector<int>;

	SUBCASE("with singleton range")
	{
		const auto nums = Ints{2};
		auto result = Ints(nums.size(), 0);

		alg::exclusiveScan(std::cbegin(nums),
						   std::cend(nums),
						   std::begin(result),
						   100,
						   std::plus{});

		CHECK(result == Ints{100});
	}

	SUBCASE("with larger range")
	{
		const auto nums = Ints{2, 3, 5, 9, 11};
		auto result = Ints(nums.size(), 0);

		alg::exclusiveScan(std::cbegin(nums),
						   std::cend(nums),
						   std::begin(result),
						   0,
						   std::plus{});

		CHECK(result == Ints{0, 2, 5, 10, 19});
	}
}





