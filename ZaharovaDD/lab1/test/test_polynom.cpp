#include "gtest.h"
#include "polynom.h"


using namespace std;
TEST(polynom, check_build_polinom)
{

	ASSERT_NO_THROW(polynom a("x+2"));
}


TEST(polynom, degree_not_more_than_9_1)
{
	polynom a("x^5"), b("x^4");
	ASSERT_NO_THROW(a*b);
}

struct parse_test
{
	string str;
	polynom res;
	parse_test(string istr, const vector<monom> &ms)
	{
		str = istr;
		list<monom> temp;
		for (int i = 0; i < ms.size(); i++)
			temp.InsertInOrder(ms[i]);
		res = polynom(temp);
	}
};

class pol_parse : public ::testing::TestWithParam<parse_test>
{
protected: polynom a_test;
public:
	pol_parse() : a_test(GetParam().str)
	{
	}
	~pol_parse() {}
};

TEST_P(pol_parse, correct_parse_of_polynom_strings)
{
	EXPECT_EQ(GetParam().res, a_test);
}


struct calc_test
{
	string left;
	string right;
	double c;
	string res;
	calc_test(string ires, string il, string ir = "", double ic = 0)
	{
		left = il;
		right = ir;
		c = ic;
		res = ires;
	}
};




class pol_plus : public ::testing::TestWithParam<calc_test>
{
protected: polynom pl, pr, pres;
public:
	pol_plus() : pl(GetParam().left), pr(GetParam().right), pres(GetParam().res)
	{
	}
	~pol_plus() {}
};

TEST_P(pol_plus, polynom_plus_polynom)
{
	EXPECT_EQ(pres, pl + pr);
}

INSTANTIATE_TEST_CASE_P(Inst2,
	pol_plus,
	::testing::Values(
		calc_test("2x+2y", "2x", "2y"),
		calc_test("10x", "10x", ""),
		calc_test("2x", "-4x", "6x"),
		calc_test("", "-20.5xy", "20.5xy"),
		calc_test("10xy^2", "7x^2y", "10xy^2-7x^2y"),
		calc_test("1+x+2y+3z", "1+x+2y", "3z"),
		calc_test("", "10.1", "-10.1"),
		calc_test("", "0", "0"),
		calc_test("0", "2.7z", "-2.7z"),
		calc_test("2x-15y+30", "x", "-15y+30+x")
	));

TEST(polynom, power_is_more_than_9_while_mult)
{
	polynom a("x^5"), b("x^5");
	ASSERT_ANY_THROW(a*b);
}




class pol_mult : public ::testing::TestWithParam<calc_test>
{
protected: polynom pl, pr, pres;
public:
	pol_mult() : pl(GetParam().left), pr(GetParam().right), pres(GetParam().res)
	{
	}
	~pol_mult() {}
};

TEST_P(pol_mult, polynom_mult_polynom)
{
	EXPECT_EQ(pres, pl * pr);
}

INSTANTIATE_TEST_CASE_P(Inst3,
	pol_mult,
	::testing::Values(
		calc_test("6xy", "3x", "2y"),
		calc_test("25", "5", "5"),
		calc_test("20xy^3", "5y^3", "4x"),
		calc_test("3x+3y^2+3x^2-3xy^2-6y^4", "3+3x-6y^2", "x+y^2"),
		calc_test("x^2y^2", "-x^2", "-y^2"),
		calc_test("x^2y^2z+x^2y^2z^2", "xyz", "xyz+xy"),
		calc_test("9-x^2", "3-x", "3+x"),
		calc_test("10xy+x^2y^2+2x^3+5y^3", "x^2+5y", "2x+y^2")
	));




class c_mult : public ::testing::TestWithParam<calc_test>
{
protected: polynom p, pres; double cn;
public:
	c_mult() : p(GetParam().left), pres(GetParam().res)
	{
		cn = GetParam().c;
	}
	~c_mult() {}
};