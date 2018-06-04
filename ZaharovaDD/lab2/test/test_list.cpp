#include "gtest.h"
#include "list.h"

TEST(lists, create_empty_list)
{
	ASSERT_NO_THROW(list<double> m);
}

class List : public ::testing::Test {
protected:
	list<int> l;
	list<int> l2;

public:
	List()
	{
		l2.InsertInOrder(10);
		l2.InsertInOrder(15);
	}

	~List() {}
};

TEST_F(List, created_empty_list_is_correct)
{
	EXPECT_EQ(true, l.IsEmpty());
}

TEST_F(List, copy_empty_list)
{
	ASSERT_NO_THROW(list<int> n(l));
}

TEST_F(List, copied_empty_list_is_correct)
{
	list<int> n(l);
	EXPECT_EQ(true, n.IsEmpty());
}

TEST_F(List, assign_empty_list)
{
	ASSERT_NO_THROW(list<int> n = l);
}

TEST_F(List, assigned_empty_list_is_correct)
{
	list<int> n = l;
	EXPECT_EQ(true, n.IsEmpty());
}

TEST_F(List, insert_in_empty_list)
{
	ASSERT_NO_THROW(l.InsertInOrder(10));
}

TEST_F(List, insert_in_empty_list_is_correct)
{
	l.InsertInOrder(10);
	l.Reset();
	EXPECT_EQ(10, l.GetCurr());
	l.gonext();
	l.gonext();
	EXPECT_EQ(l.GetCurr(), l.GetCurr());
}

TEST_F(List, compare_list_with_itself)
{
	EXPECT_EQ(true, l == l);
}

TEST_F(List, empty_lists_are_equal)
{
	list<int> n(l);
	EXPECT_EQ(true, n == l);
}

TEST_F(List, copy_full_list)
{
	ASSERT_NO_THROW(list<int> n(l2));
}

TEST_F(List, assign_full_list)
{
	ASSERT_NO_THROW(list<int> n = l2);
}

TEST_F(List, insert_in_the_beginning)
{
	l2.InsertInOrder(0);
	l2.Reset();
	EXPECT_EQ(0, l2.GetCurr());
	l2.gonext();
	EXPECT_EQ(10, l2.GetCurr());
	l2.Reset();
	EXPECT_EQ(0, l2.GetCurr());
}

TEST_F(List, insert_in_the_middle)
{
	l2.InsertInOrder(15);
	l2.Reset();
	EXPECT_EQ(10, l2.GetCurr());
	l2.gonext();
	EXPECT_EQ(15, l2.GetCurr());
	EXPECT_EQ(15, l2.GetCurr());
}


TEST_F(List, full_lists_are_equal1)
{
	list<int> n(l2);
	EXPECT_EQ(true, n == l2);
}

TEST_F(List, full_lists_are_equal2)
{
	list<int> n(l2);
	EXPECT_EQ(true, n == l2);
}

TEST_F(List, full_lists_are_equal3)
{
	list<int> n(l2);
	EXPECT_EQ(true, n == l2);
}

TEST_F(List, empty_and_full_lists_are_not_equal)
{
	EXPECT_NE(true, l2 == l);
}

TEST_F(List, lists_with_different_sizes_and_same_beginnings_are_not_equal)
{
	l.InsertInOrder(1);
	EXPECT_NE(true, l2 == l);
}