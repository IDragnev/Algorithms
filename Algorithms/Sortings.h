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
}

#include "InsertionSorterImpl.hpp"
#endif //__SORTINGS_H_INCLUDED__
