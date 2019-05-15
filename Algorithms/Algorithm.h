#ifndef __SORTINGS_H_INCLUDED__
#define __SORTINGS_H_INCLUDED__

#include "Functional\Functional.h"
#include "UtilityFunctions.h"
#include <future>

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
	ForwardIt minElementPosition(ForwardIt first, ForwardIt last, CompareFn lessThan = {});

	class SelectionSorter
	{
	public:
		template<typename ForwardIt, typename CompareFn = Functional::LessThan>
		void operator()(ForwardIt first, ForwardIt last, CompareFn lessThan = {}) const;
	};

	template <typename RandomAccessIt, std::size_t lowerBound = 25> 
	class MergeSorter
	{
	private:
		using Item = typename std::iterator_traits<RandomAccessIt>::value_type;
		using Difference = typename std::iterator_traits<RandomAccessIt>::difference_type;
		using Buffer = std::vector<Item>;
		using CallOnDestruction = Utility::CallOnDestruction;

	public:
		MergeSorter() = default;
		MergeSorter(const MergeSorter& source) noexcept;
		~MergeSorter() = default;

		MergeSorter& operator=(const MergeSorter& rhs) noexcept;

		template <typename CompareFn = Functional::LessThan>
		void operator()(RandomAccessIt first, RandomAccessIt last, CompareFn lessThan = {});

	private:
		template <typename CompareFn>
		void merge(RandomAccessIt first, RandomAccessIt middle, RandomAccessIt last, CompareFn lessThan);
		void init(RandomAccessIt first, RandomAccessIt middle, RandomAccessIt last);
		template <typename CompareFn>
		void mergeInBuffer(CompareFn lessThan);
		void insertFromLeftPart();
		void insertFromRightPart();
		void insertFrom(Difference& partIndex);
		void moveResultBack();
		void clear() noexcept;

		bool isLeftPartExhausted() const noexcept;
		bool isRightPartExhausted() const noexcept;
		
	private:
		RandomAccessIt first;
		Difference left = 0;
		Difference right = 0;
		Difference middle = 0;
		Difference length = 0;
		Buffer buffer;
	};
}

#include "SelectionSorterImpl.hpp"
#include "InsertionSorterImpl.hpp"
#include "MergeSorterImpl.hpp"
#endif //__SORTINGS_H_INCLUDED__
