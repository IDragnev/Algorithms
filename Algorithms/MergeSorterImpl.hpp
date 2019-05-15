
namespace IDragnev::Algorithm
{
	//all members act like local
	//variables and thus need not be copied
	template <typename RandomAccessIt, std::size_t lowerBound>
	MergeSorter<RandomAccessIt, lowerBound>::MergeSorter(const MergeSorter&) noexcept
	{
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	inline auto MergeSorter<RandomAccessIt, lowerBound>::operator=(const MergeSorter&) noexcept -> MergeSorter&
	{
		return *this;
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	template <typename CompareFn>
	void MergeSorter<RandomAccessIt, lowerBound>::operator()(RandomAccessIt first, RandomAccessIt last, CompareFn lessThan)
	{
		if (auto length = std::distance(first, last);
			length <= lowerBound)
		{
			InsertionSorter{}(first, last, lessThan);
		}
		else
		{
			auto x = CallOnDestruction{ [this]() noexcept { clear(); } };
			auto middle = std::next(first, length / 2);
			auto mergeSort = [sorter = *this, first, middle, lessThan]() mutable { sorter(first, middle, lessThan); };
			auto lowerHalfBarrier = std::async(mergeSort);

			(*this)(middle, last, lessThan);
			lowerHalfBarrier.wait();

			merge(first, middle, last, lessThan);
		}
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	template <typename CompareFn>
	void MergeSorter<RandomAccessIt, lowerBound>::merge(RandomAccessIt first, RandomAccessIt middle, RandomAccessIt last, CompareFn lessThan)
	{
		init(first, middle, last);
		mergeInBuffer(lessThan);
		moveResultBack();
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	void MergeSorter<RandomAccessIt, lowerBound>::init(RandomAccessIt first, RandomAccessIt mid, RandomAccessIt last)
	{
		this->first = first;
		left = 0;
		right = middle = std::distance(first, mid);
		length = std::distance(first, last);
		buffer.reserve(length);
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	template <typename CompareFn>
	void MergeSorter<RandomAccessIt, lowerBound>::mergeInBuffer(CompareFn lessThan)
	{
		while (!(isLeftPartExhausted() && isRightPartExhausted()))
		{
			while (!isLeftPartExhausted() && (isRightPartExhausted() || !lessThan(buffer[right], buffer[left])))
			{
				insertFromLeftPart();
			}

			while (!isRightPartExhausted() && (isLeftPartExhausted() || lessThan(buffer[right], buffer[left])))
			{
				insertFromRightPart();
			}
		}
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	inline bool MergeSorter<RandomAccessIt, lowerBound>::isLeftPartExhausted() const noexcept
	{
		return left >= middle;
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	inline bool MergeSorter<RandomAccessIt, lowerBound>::isRightPartExhausted() const noexcept
	{
		return right >= length;
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	inline void MergeSorter<RandomAccessIt, lowerBound>::insertFromLeftPart()
	{
		insertFrom(left);
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	inline void MergeSorter<RandomAccessIt, lowerBound>::insertFromRightPart()
	{
		insertFrom(right);
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	inline void MergeSorter<RandomAccessIt, lowerBound>::insertFrom(Difference& partIndex)
	{
		auto it = first + partIndex;
		buffer.push_back(std::move_if_noexcept(*it));
		++partIndex;
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	inline void MergeSorter<RandomAccessIt, lowerBound>::moveResultBack()
	{
		std::move(std::begin(buffer), std::end(buffer), first);
	}

	template <typename RandomAccessIt, std::size_t lowerBound>
	inline void MergeSorter<RandomAccessIt, lowerBound>::clear() noexcept
	{
		buffer.clear();
	}
}