#include "pch.h"

using namespace std;

template<typename T>
class ListTests : public testing::Test
{
protected:
	List<int> _sut;
};

using MyTypes = testing::Types< int >;
TYPED_TEST_CASE(ListTests, MyTypes);

TYPED_TEST(ListTests, a_new_list_has_zero_count_and_is_empty)
{
	int actualCount = _sut.Count();
	bool actualIfEmpty = _sut.IsEmpty();

	EXPECT_EQ(actualCount, 0);
	EXPECT_TRUE(actualIfEmpty);

}

TYPED_TEST(ListTests, a_list_becomes_non_empty_when_pushing_new_item)
{
	_sut.PushBack(1);

	bool actualIfEmpty = _sut.IsEmpty();

	EXPECT_FALSE(actualIfEmpty);
}

TYPED_TEST(ListTests, a_list_becomes_empty_if_no_item_left_in_it)
{
	_sut.PushBack(1);
	_sut.PushBack(1);
	_sut.PushBack(1);

	_sut.PopFront();
	_sut.PopBack();
	_sut.PopBack();

	bool actualIfEmpty = _sut.IsEmpty();

	EXPECT_TRUE(actualIfEmpty);
}

TYPED_TEST(ListTests, Count_is_incremented_when_pushing_an_item)
{
	_sut.PushBack(1);
	_sut.PushBack(1);
	int actualCountAfterPush = _sut.Count();

	EXPECT_EQ(actualCountAfterPush, 2);

	_sut.PushFront(1);
	_sut.PushFront(1);
	actualCountAfterPush = _sut.Count();

	EXPECT_EQ(actualCountAfterPush, 4);
}

TYPED_TEST(ListTests, a_new_list_has_non_zero_size)
{
	int actualSize = _sut.Size();

	EXPECT_NE(actualSize, 0);
}

TYPED_TEST(ListTests, Size_is_increased_when_not_enough_space_to_push_a_new_item)
{
	int initialSize = _sut.Size();

	for (auto i = 0; i < initialSize + 1; i++)
		_sut.PushBack(i);

	int actualSizeAfterPush = _sut.Size();

	EXPECT_NE(actualSizeAfterPush, initialSize);
	for (auto i = 0; i < _sut.Count(); i++)
		EXPECT_EQ(_sut[i], i);

	initialSize = _sut.Size();

	for (auto i = 0; i < initialSize + 1; i++)
		_sut.PushFront(1);

	actualSizeAfterPush = _sut.Size();

	EXPECT_NE(actualSizeAfterPush, initialSize);
}

TYPED_TEST(ListTests, Size_is_increased_when_not_enough_space_to_insert_a_new_item)
{
	int initialSize = _sut.Size();

	for (auto i = 0; i < initialSize; i++)
		_sut.PushBack(i);

	int insertionIndex = 5;
	_sut.Insert(insertionIndex, 0);

	int actualSizeAfterPush = _sut.Size();

	EXPECT_NE(actualSizeAfterPush, initialSize);
	for (auto i = 0; i < _sut.Count(); i++)
	{
		if (i < insertionIndex)
			EXPECT_EQ(_sut[i], i);
		else if (i > insertionIndex)
			EXPECT_EQ(_sut[i], i - 1);
		else
			EXPECT_EQ(_sut[i], 0);
	}
}

TYPED_TEST(ListTests, accessing_out_of_range_index_throws_exception)
{
	EXPECT_THROW(_sut[1], out_of_range);
	EXPECT_THROW(_sut[0], out_of_range);
	EXPECT_THROW(_sut[-1], out_of_range);
}

TYPED_TEST(ListTests, PushBack_adds_the_item_to_end_of_the_list)
{
	int item_1 = 1;
	int item_2 = 2;

	_sut.PushBack(item_1);
	_sut.PushBack(item_2);

	int actualCount = _sut.Count();
	int lastIndex = actualCount - 1;
	int actualLastItem = _sut[lastIndex];

	EXPECT_EQ(actualCount, 2);
	EXPECT_EQ(actualLastItem, item_2);
}

TYPED_TEST(ListTests, PushFront_adds_the_item_to_start_of_the_list)
{
	int item_1 = 1;
	int item_2 = 2;

	_sut.PushFront(item_1);
	_sut.PushFront(item_2);

	int actualFirstItem = _sut[0];
	int actualSecondItem = _sut[1];

	EXPECT_EQ(actualFirstItem, item_2);
	EXPECT_EQ(actualSecondItem, item_1);
}

TYPED_TEST(ListTests, First_returns_the_first_item_in_the_list)
{
	_sut.PushBack(1);
	_sut.PushBack(2);
	_sut.PushBack(3);

	int actualFirstItem = _sut.First();

	EXPECT_EQ(actualFirstItem, 1);
}

TYPED_TEST(ListTests, Last_returns_the_last_item_in_the_list)
{
	_sut.PushBack(1);
	_sut.PushBack(2);
	_sut.PushBack(3);

	int actualLastItem = _sut.Last();

	EXPECT_EQ(actualLastItem, 3);
}

TYPED_TEST(ListTests, Insert_adds_a_new_item_at_the_specified_index_location)
{
	_sut.PushBack(1);
	_sut.PushBack(2);
	_sut.PushBack(4);

	_sut.Insert(2, 3);
	int actualInsertedItem = _sut[2];

	EXPECT_EQ(actualInsertedItem, 3);
}

TYPED_TEST(ListTests, Insert_throws_exception_if_passed_out_of_range_index)
{
	EXPECT_THROW(_sut.Insert(1, 0), out_of_range);
	EXPECT_THROW(_sut.Insert(-1, 0), out_of_range);
}

TYPED_TEST(ListTests, Erase_removes_an_item_by_its_index_and_returns_it_plus_shift_other_items_to_fill_the_gap)
{
	//arrange
	int firstItem = 1;
	int secondItem = 2;
	int thirdItem = 3;

	_sut.PushBack(firstItem);
	_sut.PushBack(secondItem);
	_sut.PushBack(thirdItem);

	//act
	int countBeforeErase = _sut.Count();
	int erasingIndex = 1;
	int actualReturnItem = _sut.Erase(erasingIndex);
	int actualCountAfterErase = _sut.Count();
	int actualShiftedItem = _sut[erasingIndex];

	//assert
	EXPECT_EQ(actualCountAfterErase, countBeforeErase - 1);
	EXPECT_EQ(actualReturnItem, secondItem);
	EXPECT_EQ(actualShiftedItem, thirdItem);
}

TYPED_TEST(ListTests, Erase_throws_exception_if_passed_out_of_range_index)
{
	EXPECT_THROW(_sut.Erase(1), out_of_range);
	EXPECT_THROW(_sut.Erase(0), out_of_range);
	EXPECT_THROW(_sut.Erase(-1), out_of_range);
}

TYPED_TEST(ListTests, Remove_removes_an_item_and_shift_other_items_to_fill_the_gap)
{
	//arrange
	int itemToBeRemoved = 1;
	int secondItem = 2;
	int thirdItem = 3;

	_sut.PushBack(itemToBeRemoved);
	_sut.PushBack(secondItem);
	_sut.PushBack(thirdItem);

	//act
	int countBeforeErase = _sut.Count();
	_sut.Remove(itemToBeRemoved);
	int actualCountAfterErase = _sut.Count();
	int actualShiftedItem = _sut[0];

	//assert
	EXPECT_EQ(actualCountAfterErase, countBeforeErase - 1);
	EXPECT_EQ(actualShiftedItem, secondItem);
}

TYPED_TEST(ListTests, PopBack_removes_last_item_and_returns_it)
{
	//arrange
	int firstItem = 1;
	int middleItem = 2;
	int lastItem = 3;

	_sut.PushBack(firstItem);
	_sut.PushBack(middleItem);
	_sut.PushBack(lastItem);

	//act
	int countBeforeErase = _sut.Count();
	int actualReturnItem = _sut.PopBack();
	int actualCountAfterErase = _sut.Count();

	//assert
	EXPECT_EQ(actualCountAfterErase, countBeforeErase - 1);
	EXPECT_EQ(actualReturnItem, lastItem);
}

TYPED_TEST(ListTests, PopFront_removes_first_item_and_returns_it)
{//arrange
	int firstItem = 1;
	int middleItem = 2;
	int lastItem = 3;

	_sut.PushBack(firstItem);
	_sut.PushBack(middleItem);
	_sut.PushBack(lastItem);

	//act
	int countBeforeErase = _sut.Count();
	int actualReturnItem = _sut.PopFront();
	int actualCountAfterErase = _sut.Count();

	//assert
	EXPECT_EQ(actualCountAfterErase, countBeforeErase - 1);
	EXPECT_EQ(actualReturnItem, firstItem);
}

TYPED_TEST(ListTests, Clear_removes_all_items)
{
	_sut.PushBack(1);
	_sut.PushBack(1);
	_sut.PushBack(1);

	bool actualIfEmptyBeforeClear = _sut.IsEmpty();
	_sut.Clear();
	bool actualIfEmptyAfterClear = _sut.IsEmpty();

	EXPECT_FALSE(actualIfEmptyBeforeClear);
	EXPECT_TRUE(actualIfEmptyAfterClear);
	EXPECT_THROW(_sut[0], out_of_range);
}

TYPED_TEST(ListTests, Sort_sorts_the_items)
{
	_sut.PushBack(4);
	_sut.PushBack(5);
	_sut.PushBack(1);
	_sut.PushBack(3);
	_sut.PushBack(2);

	_sut.Sort();

	EXPECT_EQ(_sut[0], 1);
	EXPECT_EQ(_sut[1], 2);
	EXPECT_EQ(_sut[2], 3);
	EXPECT_EQ(_sut[3], 4);
	EXPECT_EQ(_sut[4], 5);
}

TYPED_TEST(ListTests, Sort_can_sort_the_items_using_a_predicate_funtion)
{
	_sut.PushBack(4);
	_sut.PushBack(5);
	_sut.PushBack(1);
	_sut.PushBack(3);
	_sut.PushBack(2);

	_sut.Sort([](int l, int r) {return l > r; });

	EXPECT_EQ(_sut[0], 1);
	EXPECT_EQ(_sut[1], 2);
	EXPECT_EQ(_sut[2], 3);
	EXPECT_EQ(_sut[3], 4);
	EXPECT_EQ(_sut[4], 5);
}

TYPED_TEST(ListTests, QuickSort_sorts_the_items)
{
	_sut.PushBack(4);
	_sut.PushBack(5);
	_sut.PushBack(1);
	_sut.PushBack(3);
	_sut.PushBack(2);

	_sut.QuickSort();

	EXPECT_EQ(_sut[0], 1);
	EXPECT_EQ(_sut[1], 2);
	EXPECT_EQ(_sut[2], 3);
	EXPECT_EQ(_sut[3], 4);
	EXPECT_EQ(_sut[4], 5);
}

TYPED_TEST(ListTests, QuickSort_can_sort_the_items_using_a_sortBy_funtion)
{
	_sut.PushBack(4);
	_sut.PushBack(5);
	_sut.PushBack(1);
	_sut.PushBack(3);
	_sut.PushBack(2);

	_sut.QuickSort([](int item) {return item; });

	EXPECT_EQ(_sut[0], 1);
	EXPECT_EQ(_sut[1], 2);
	EXPECT_EQ(_sut[2], 3);
	EXPECT_EQ(_sut[3], 4);
	EXPECT_EQ(_sut[4], 5);
}

TYPED_TEST(ListTests, MergeSort_sorts_the_items)
{
	_sut.PushBack(4);
	_sut.PushBack(5);
	_sut.PushBack(1);
	_sut.PushBack(3);
	_sut.PushBack(2);

	_sut.MergeSort();

	EXPECT_EQ(_sut[0], 1);
	EXPECT_EQ(_sut[1], 2);
	EXPECT_EQ(_sut[2], 3);
	EXPECT_EQ(_sut[3], 4);
	EXPECT_EQ(_sut[4], 5);
}

TYPED_TEST(ListTests, two_lists_are_equal_if_they_have_same_items)
{
	List<int> sut_1;
	sut_1.PushBack(1);
	sut_1.PushBack(2);
	sut_1.PushBack(3);
	sut_1.PushBack(4);
	sut_1.PushBack(5);

	List<int> sut_2;
	sut_2.PushBack(1);
	sut_2.PushBack(2);
	sut_2.PushBack(3);
	sut_2.PushBack(4);
	sut_2.PushBack(5);

	bool actualEquals = sut_1.Equals(&sut_2);

	EXPECT_TRUE(actualEquals);
}
