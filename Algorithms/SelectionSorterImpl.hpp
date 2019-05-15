
namespace IDragnev::Algorithm
{
	template<class ForwardIt, typename CompareFn>
	ForwardIt minElementPosition(ForwardIt first, ForwardIt last, CompareFn lessThan)
	{
		if (first == last)
		{
			return last;
		}

		auto smallest = first;

		for (auto current = std::next(first);
			current != last;
			++current)
		{
			if (lessThan(*current, *smallest))
			{
				smallest = current;
			}
		}

		return smallest;
	}

	template <typename ForwardIt, typename CompareFn>
	void SelectionSorter::operator()(ForwardIt first, ForwardIt last, CompareFn lessThan) const
	{
		auto end = std::next(first, std::distance(first, last) - 1);

		for (auto current = first;
			current != end;
			++current)
		{
			auto min = minElementPosition(std::next(current), last);
			swapIfLess(*min, *current, lessThan);
		}
	}
}