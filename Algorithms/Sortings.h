#ifndef __SORTINGS_H_INCLUDED__
#define __SORTINGS_H_INCLUDED__

#include "Functional\Functional.h"

namespace IDragnev::Algorithm
{
	template <typename T, typename CompareFn>
	void swapIfLess(T& lhs, T& rhs, CompareFn lessThan);

	class InsertionSorter
	{
	public:
		template <typename RandomAcessIt, typename CompareFn = Functional::LessThan>
		void operator()(RandomAcessIt first, RandomAcessIt last, CompareFn lessThan = {}) const;

	private:
		template <typename RandomAcessIt, typename CompareFn>
		static void putMinimalInFront(RandomAcessIt first, RandomAcessIt last, CompareFn less);
			
		template <typename RandomAcessIt, typename CompareFn>
		static void doSort(RandomAcessIt first, RandomAcessIt last, CompareFn less);
	};

	template<class ForwardIt, typename CompareFn = Functional::LessThan>
	ForwardIt minElementPosition(ForwardIt first, ForwardIt last, CompareFn lessThan = {})
	{
		if (first == last)
		{
			return last;
		}

		auto smallest = first;

		for (auto current = ++first;
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
}

#include "InsertionSorterImpl.hpp"
#endif //__SORTINGS_H_INCLUDED__
