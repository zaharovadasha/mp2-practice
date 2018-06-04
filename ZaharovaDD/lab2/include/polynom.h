#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "monom.h"
#include "list.h"

#define OFFSET 120																										//Код символа 'x'

class polynom
{
private:
	list<monom> list_monom;																								//список мономов
	list<monom> such(list <monom> & op);																				//объединение подобные

public:
	polynom(const polynom& p); 																							
	const polynom& operator=(const polynom &p);	
	polynom(list<monom> &in_list) : list_monom(in_list) {}																//К. по списку
	polynom(const string op = "");																						//К. по строке

	polynom operator-(const polynom& p) const { return *this + p*(-1); }												//Бинарный минус
	polynom operator-() const { return (-1)*(*this); }																	//Унарный минус
	bool operator==(const polynom& p) const { return list_monom == p.list_monom; }										//О. сравнения
	bool operator!=(const polynom& p) const { return list_monom != p.list_monom; }										//О. сравнения
	polynom operator+(const polynom& p) const;																			//О. сложения полиномов
	polynom operator*(const polynom& p) const;																			//О. умножения полиномов
	polynom operator*(const double k) const;																			//Умножение на константу
	friend polynom operator*(const double k, const polynom& p) { return p*k; }											//Умножение на константу с другой стороны

	friend std::ostream& operator<<(std::ostream &str, const polynom &p);												//О. вставки в поток
};