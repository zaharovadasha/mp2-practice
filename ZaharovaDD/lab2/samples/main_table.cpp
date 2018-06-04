#include "monom.h"
#include "polynom.h"
#include <iostream>
#include <ostream>
#include "tableUnorder.h"
#include "tableOrder.h"
#include "tableHash.h"
using namespace std;

int main()
{
	int c = 0;
	int k;
	int SIZE;

	cout << "Enter the size of the table" << endl;
	cin >> SIZE;
	TableUnorder<string, polynom> A(SIZE);
	string a;
	TableOrder<string, polynom> B(SIZE);
	TableHash<string, polynom> C(SIZE);

	while (c != 1)
	{
		system("cls");
		cout << "Chouse operation" << endl;
		cout << "1 - Insert" << endl;
		cout << "2 - Dell" << endl;
		cout << "3 - Search" << endl;
		cout << "4 - Print" << endl;
		cin >> k;
		switch (k)
		{
		case 1:
		{
			string str;
			cout << "Write your Polinom" << endl;
			cin >> str;
			polynom a(str);
			try { A.Insert(str, a); }
			catch (...) { cout << "duplicated key" << endl; }
			try { B.Insert(str, a); }
			catch (...) { cout << "duplicated key" << endl; }
			try { C.Insert(str, a); }
			catch (...) { cout << "duplicated key" << endl; }
			cout << "Unordered :" << endl;
			cout << A << endl;
			cout << "Ordered :" << endl;
			cout << B << endl;
			cout << "Hash :" << endl;
			cout << C << endl;
			break;
		}
		case 2:
		{
			string str;
			cout << "Write polynom" << endl;
			cin >> str;
			polynom a(str);
			try { A.Dell(str); }
			catch (...) { cout << "element doesn't exist" << endl; }
			try { B.Dell(str); }
			catch (...) { cout << "element doesn't exist" << endl; }
			try { C.Dell(str); }
			catch (...) { cout << "element doesn't exist" << endl; }
			cout << "Unordered :" << endl;
			cout << A << endl;
			cout << "Ordered :" << endl;
			cout << B << endl;
			cout << "Hash :" << endl;
			cout << C << endl;
			break;
		}
		case 3:
		{
			string str;
			cout << "Write polynom" << endl;
			cin >> str;
			polynom a(str);
			try { cout << "finded: " << A.Search(str)->data; }
			catch (...) { cout << "element doesn't exist" << endl; }
			try { cout << "finded: " << B.Search(str)->data; }
			catch (...) { cout << "element doesn't exist" << endl; }
			try { cout << "finded: " << C.Search(str)->data; }
			catch (...) { cout << "element doesn't exist" << endl; }
			break;
		}
		case 4:
		{
			cout << "Unordered :" << endl;
			cout << A << endl;
			cout << "Ordered :" << endl;
			cout << B << endl;
			cout << "Hash :" << endl;
			cout << C << endl;
			break;
		}
		default:
		{
			cout << "ERROR, choose again" << endl;
			break;
		}
		}

		cout << "Exit - 1" << endl;
		cin >> c;
	}
	return 0;
}