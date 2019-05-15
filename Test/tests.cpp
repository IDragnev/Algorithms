#include "CppUnitTest.h"
#include "Sortings.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using IDragnev::Functional::LessThan;
using namespace IDragnev::Algorithm;

namespace Test
{		
	TEST_CLASS(Tests)
	{
		using IntArray = std::vector<int>;

	public:
		TEST_METHOD(insertionSort)
		{
			Assert::IsTrue(sortsNonTrivialArray<InsertionSorter>());
		}

	private:
		template <typename Sorter>
		static bool sortsNonTrivialArray()
		{
			auto nums = IntArray{ 3, 5, 4, 1, 0, 2 };
			const auto expected = IntArray{ 0, 1, 2, 3, 4, 5 };

			Sorter{}(std::begin(nums), std::end(nums), LessThan{});

			return nums == expected;
		}
	};
}