#pragma once

namespace IDragnev::Algorithm
{
	template <typename RandomAcessIt, typename CompareFn>
	inline void InsertionSorter::operator()(RandomAcessIt first, RandomAcessIt last, CompareFn lessThan) const
	{
		putMinimalInFront(first, last, lessThan);
		doSort(++first, last, lessThan);
	}

	template <typename RandomAcessIt, typename CompareFn>
	void InsertionSorter::putMinimalInFront(RandomAcessIt first, RandomAcessIt last, CompareFn lessThan)
	{
		for (auto current = last - 1;
			current > first;
			--current)
		{
			swapIfLess(*current, *(current - 1), lessThan);
		}
	}

	template <typename RandomAcessIt, typename CompareFn>
	void InsertionSorter::doSort(RandomAcessIt first, RandomAcessIt last, CompareFn lessThan)
	{
		for (auto current = first;
			current < last;
			++current)
		{
			auto item = std::move(*current);
			auto emptyPos = current;

			while (lessThan(item, *(emptyPos - 1)))
			{
				*emptyPos = std::move(*(emptyPos - 1));
				--emptyPos;
			}

			*emptyPos = std::move(item);
		}
	}	
}
