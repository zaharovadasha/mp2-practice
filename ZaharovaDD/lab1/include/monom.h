#pragma once
#include <math.h>


class monom
{
public:
	double cff;																									//Коэфф. перед мономом
	int svr;																									//Свёрнутая степень

	monom(const monom& a) { cff = a.cff; svr = a.svr; }
	monom(const double index_cff = 0.0, const unsigned int index_svr = 0) { cff = index_cff; svr = index_svr; }	//К.
	const monom& operator=(const monom& a) { cff = a.cff; svr = a.svr; return *this; }							//О. присваивания
	bool operator< (const monom& a) const { return (svr<a.svr); }												//О. сравнения
	bool operator> (const monom& a) const { return (svr>a.svr); }												//О. сравнения
	bool operator==(const monom& a) const { return ((svr == a.svr) && (cff == a.cff)); }						//перегружено ==
	bool operator!=(const monom& a) const { return !(*this == a); }												//перегружено !=


};
