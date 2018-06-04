#include "polynom.h"

using namespace std;

list<monom> polynom::such(list <monom> & op)
{
	list<monom> res;
	res.Reset();
	op.Reset();
	node<monom> mon(op.GetCurr().cff);
	list<monom> y(op);
	while (!op.IsOver())
	{
		mon.data.svr = op.GetCurr().svr;
		y.gonext();
		if (op.GetCurr().svr == y.GetCurr().svr && (y.GetCurr().cff || y.GetCurr().svr))
			mon.data.cff += y.GetCurr().cff;
		else
		{
			if (mon.data.cff)
			{
				res.InsertToTail(mon.data);
				res.gonext();
			}
			mon.data.cff = y.GetCurr().cff;
		}
		op.gonext();
	}
	return res;
}

polynom::polynom(const polynom& p)
{
	list_monom = p.list_monom;
}

polynom::polynom(string op)
{
	int d[3] = { 100,10,1 };
	while (op.length())
	{
		string pt;
		monom t;
		int pos = 1;
		while (pos < op.length() && op[pos] != '+' && op[pos] != '-')
			pos++;
		pt = op.substr(0, pos);																						//берет с нулевой позиции pos эл-тов
		op.erase(0, pos);																							//”дал€ет элементы в диапазоне
		pos = 0;
		while (pt[pos] != 'x' && pt[pos] != 'y' && pt[pos] != 'z' && pos < pt.length())
			pos++;

		string pstr = pt.substr(0, pos);
		if (pstr == "+" || pstr.length() == 0)
			t.cff = 1;
		else if (pstr == "-")
			t.cff = -1;
		else t.cff = stod(pstr);																					//преобразование строки в число

		pt.erase(0, pos);
		pt += ' ';

		for (int i = 0; i < 3; i++)
		{
			pos = pt.find((char)(OFFSET + i));
			if (pos > -1)
			{
				if (pt[pos + 1] != '^')
					pt.insert(pos + 1, "^1");
				t.svr += d[i] * stoi(pt.substr(pos + 2, 1));														// преобразует последовательность элементов  в целое число.
				pt.erase(pos, 3);
			}
		}

		list_monom.InsertInOrder(t);
	}

	list_monom = such(list_monom);
}


const polynom & polynom::operator=(const polynom & p)
{
	list_monom = p.list_monom;
	return *this;
}

polynom polynom::operator+(const polynom& p) const
{

	polynom res;
	polynom pthis = *this;
	polynom pol = p;

	pthis.list_monom.Reset();
	pol.list_monom.Reset();
	res.list_monom.Reset();

	while (!pthis.list_monom.IsOver() && !pol.list_monom.IsOver())
	{
		if (pthis.list_monom.GetCurr() > pol.list_monom.GetCurr())													//упор€дочивание
		{
			res.list_monom.InsertToTail(pol.list_monom.GetCurr());
			pol.list_monom.gonext();
			res.list_monom.gonext();
		}
		else if (pthis.list_monom.GetCurr() < pol.list_monom.GetCurr())
		{
			res.list_monom.InsertToTail(pthis.list_monom.GetCurr());
			pthis.list_monom.gonext();
			res.list_monom.gonext();
		}
		else
		{
			double new_c = pthis.list_monom.GetCurr().cff + pol.list_monom.GetCurr().cff;
			if (new_c)
			{
				res.list_monom.InsertToTail(monom(new_c, pthis.list_monom.GetCurr().svr));
				res.list_monom.gonext();
			}
			pthis.list_monom.gonext();
			pol.list_monom.gonext();
		}
	}
	while (!pthis.list_monom.IsOver())
	{
		res.list_monom.InsertToTail(pthis.list_monom.GetCurr());
		pthis.list_monom.gonext();
		res.list_monom.gonext();
	}
	while (!pol.list_monom.IsOver())
	{
		res.list_monom.InsertToTail(pol.list_monom.GetCurr());
		pol.list_monom.gonext();
		res.list_monom.gonext();
	}

	return res;
}

polynom polynom::operator*(const polynom& p) const
{

	polynom res;
	polynom pth = *this;
	polynom pol = p;

	pth.list_monom.Reset();
	pol.list_monom.Reset();

	while (!pth.list_monom.IsOver())
	{
		double pth_cff = pth.list_monom.GetCurr().cff;
		int pth_svr = pth.list_monom.GetCurr().svr;
		polynom tp(p);
		tp.list_monom.Reset();
		while (!tp.list_monom.IsOver())
		{
			int tp_svr = tp.list_monom.GetCurr().svr;
			if ((tp_svr % 10 + pth_svr % 10) < 10 && (tp_svr / 10 % 10 + pth_svr / 10 % 10) < 10 && (tp_svr / 100 + pth_svr / 100) < 10)	//остаток от делени€
			{
				tp.list_monom.GetCurr().svr += pth_svr;
				tp.list_monom.GetCurr().cff *= pth_cff;
			}
			else
				throw "Error";
			tp.list_monom.gonext();
		}
		res = res + tp;
		pth.list_monom.gonext();
	}
	return res;
}

polynom polynom::operator*(const double k) const
{
	polynom res;
	res = *this;
	res.list_monom.Reset();
	while (!res.list_monom.IsOver())
	{
		res.list_monom.GetCurr().cff *= k;
		res.list_monom.gonext();
	}
	return res;
}

ostream& operator<<(ostream &str, const polynom& p)
{
	polynom pl = p;
	pl.list_monom.Reset();

	while (!pl.list_monom.IsOver())
	{

		monom tp = pl.list_monom.GetCurr();

		if (tp.cff > 0)
		{
			str << "+";
			if (tp.cff == 1 && tp.svr == 0)
				str << "1";
			else
				if (tp.cff != 1)
					str << tp.cff;
		}
		else
			str << tp.cff;

		int a = tp.svr / 100;
		if (a>1)
			str << "x^" << a;
		else
			if (a == 1)
				str << "x";
		a = tp.svr / 10 % 10;
		if (a>1)
			str << "y^" << a;
		else
			if (a == 1)
				str << "y";
		a = tp.svr % 10;
		if (a>1)
			str << "z^" << a;
		else
			if (a == 1)
				str << "z";
		pl.list_monom.gonext();
	}
	return str;
}
