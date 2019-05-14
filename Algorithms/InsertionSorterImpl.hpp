
namespace IDragnev::Algorithm
{
	template <typename T, typename CompareFn>
	void swapIfLess(T& lhs, T& rhs, CompareFn lessThan)
	{
		using std::swap;

		if (lessThan(lhs, rhs))
		{
			swap(lhs, rhs);
		}
	}

	template <typename RandomAcessIt, typename CompareFn>
	inline void InsertionSorter::operator()(RandomAcessIt first, RandomAcessIt last, CompareFn lessThan) const
	{
		putMinimalInFront(first, last, lessThan);
		doSort(first + 2, last, lessThan);
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
			current != last;
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
