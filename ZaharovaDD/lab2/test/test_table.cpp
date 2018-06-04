#include "monom.h"
#include "list.h"
#include "gtest.h"

#include "tableHash.h"
#include "tableUnorder.h"
#include "table.h"
#include "tableOrder.h"
#include "polynom.h"


TEST(ScanTable, can_create)
{
	TableUnorder<string, polynom> A(20);
	polynom a("x+1");
	ASSERT_NO_THROW(A.Insert("x+1", a));

}

class Table_Check : public ::testing::Test
{
public:
	TableHash <string, polynom> HashT;
	TableOrder <string, polynom> OrdT;
	TableUnorder <string, polynom> ScanT;

	Table_Check() : HashT(10), OrdT(10), ScanT(10)
	{
		HashT.Insert("x+1", polynom("x+1"));
		OrdT.Insert("x+1", polynom("x+1"));
		ScanT.Insert("x+1", polynom("x+1"));
		HashT.Insert("10+xyz", polynom("10+xyz"));
		OrdT.Insert("10+xyz", polynom("10+xyz"));
		ScanT.Insert("10+xyz", polynom("10+xyz"));
		HashT.Insert("x^4", polynom("x^4"));
		OrdT.Insert("x^4", polynom("x^4"));
		ScanT.Insert("x^4", polynom("x^4"));
	};

};


TEST_F(Table_Check, can_GetCur_ScanT)
{
	ScanT.Reset();
	polynom p("x+1");
	EXPECT_EQ(ScanT.GetCurr(), p);
}

TEST_F(Table_Check, can_gonext_OrdT)
{
	ASSERT_NO_THROW(OrdT.GoNext());
}

TEST_F(Table_Check, can_gonext_HashT)
{
	ASSERT_NO_THROW(HashT.GoNext());
}

TEST_F(Table_Check, can_get_next_ScanT)
{
	ASSERT_NO_THROW(ScanT.GoNext());
}

TEST_F(Table_Check, can_Search_existed_element_HashT)
{
	EXPECT_EQ(HashT.Search("x+1")->data, polynom("x+1"));
}

TEST_F(Table_Check, can_Search_existed_element_ScanT)
{
	EXPECT_EQ(ScanT.Search("x+1")->data, polynom("x+1"));
}

TEST_F(Table_Check, can_Search_existed_element_OrdT)
{
	EXPECT_EQ(OrdT.Search("x+1")->data, polynom("x+1"));
}

TEST_F(Table_Check, can_Delete_existed_element_HashT)
{
	HashT.Dell("x+1");
	ASSERT_ANY_THROW(HashT.Search("x+1"));
}

TEST_F(Table_Check, can_Delete_existed_element_ScanT)
{
	ScanT.Dell("x+1");
	ASSERT_ANY_THROW(ScanT.Search("x+1"));
}

TEST_F(Table_Check, can_Delete_existed_element_OrdT)
{
	OrdT.Dell("x+1");
	ASSERT_ANY_THROW(OrdT.Search("x+1"));
}


TEST_F(Table_Check, can_Insert_element_ScanT)
{
	ScanT.Insert("1+z", polynom("1+z"));
	EXPECT_EQ(ScanT.Search("1+z")->data, polynom("1+z"));
}

TEST_F(Table_Check, can_Insert_element_OrdT)
{
	OrdT.Insert("xyz+z^5", polynom("xyz+z^5"));
	EXPECT_EQ(OrdT.Search("xyz+z^5")->data, polynom("xyz+z^5"));
}

TEST_F(Table_Check, can_Search_existed_element_ScanT2)
{
	EXPECT_EQ(ScanT.Search("10+xyz")->data, polynom("10+xyz"));
}

TEST_F(Table_Check, can_Search_existed_element_OrdT2)
{
	EXPECT_EQ(OrdT.Search("10+xyz")->data, polynom("10+xyz"));
}

TEST_F(Table_Check, can_Search_existed_element_HashT3)
{
	EXPECT_EQ(HashT.Search("x^4")->data, polynom("x^4"));
}

TEST_F(Table_Check, can_Search_existed_element_ScanT3)
{
	EXPECT_EQ(ScanT.Search("x^4")->data, polynom("x^4"));
}

TEST_F(Table_Check, can_Search_existed_element_OrdT3)
{
	EXPECT_EQ(OrdT.Search("x^4")->data, polynom("x^4"));
}

TEST_F(Table_Check, can_Insert_element_HashT2)
{
	HashT.Insert("111+z", polynom("111+z"));
	EXPECT_EQ(HashT.Search("111+z")->data, polynom("111+z"));
}

TEST_F(Table_Check, can_Insert_element_ScanT2)
{
	ScanT.Insert("1+32.1x", polynom("1+32.1x"));
	EXPECT_EQ(ScanT.Search("1+32.1x")->data, polynom("1+32.1x"));
}

TEST_F(Table_Check, can_Insert_element_OrdT2)
{
	OrdT.Insert("xyz", polynom("xyz"));
	EXPECT_EQ(OrdT.Search("xyz")->data, polynom("xyz"));
}

TEST_F(Table_Check, cannot_Delete_element_HashT)
{
	ASSERT_ANY_THROW(HashT.Dell("12"));
}

TEST_F(Table_Check, cannot_Delete_element_ScanT)
{
	ASSERT_ANY_THROW(ScanT.Dell("12"));
}

TEST_F(Table_Check, cannot_Delete_element_OrdT)
{
	ASSERT_ANY_THROW(OrdT.Dell("12"));
}

TEST_F(Table_Check, cannot_Inset_ex_element_ScanT)
{
	ASSERT_ANY_THROW(ScanT.Insert("x+1", polynom("x+1")));
}

TEST_F(Table_Check, cannot_Inset_ex_element_OrdT)
{
	ASSERT_ANY_THROW(OrdT.Insert("x+1", polynom("x+1")));
}

TEST_F(Table_Check, cannot_Inset_ex_element_ScanT2)
{
	ASSERT_ANY_THROW(ScanT.Insert("x^4", polynom("x+1")));
}

TEST_F(Table_Check, cannot_Inset_ex_element_OrdT2)
{
	ASSERT_ANY_THROW(OrdT.Insert("x^4", polynom("x+1")));
}

TEST_F(Table_Check, can_Delete_OrdT)
{
	ASSERT_ANY_THROW(OrdT.Dell("100"));
}

TEST_F(Table_Check, can_Delete_Ord2T)
{
	ASSERT_ANY_THROW(OrdT.Dell("10"));
}