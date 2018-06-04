#include "monom.h"
#include "polynom.h"
#include <iostream>

using namespace std;

void main()
{
	int flag = 1;
	int k = 0;
	while (flag == 1)
	{
		system("cls");//очистить экран
		cout << "Write first polynom" << endl;
		string s1;
		cin >> s1;
		polynom S1(s1);
		cout << "Write second polynom" << endl;
		string s2;
		cin >> s2;
		polynom S2(s2);
		cout << "Choose operation" << endl;
		cout << "1  +" << endl;
		cout << "2  -" << endl;
		cout << "3  *" << endl;
		cout << "4  * const" << endl;
		cin >> k;
		switch (k)
		{
		case 1:
		{
			polynom res = S1 + S2;
			cout << res;
			break;
		}
		case 2:
		{
			polynom res = S1 - S2;
			cout << res;
			break;
		}
		case 3:
		{
			polynom res = S1 * S2;
			cout << res;
			break;
		}
		case 4:
		{
			string con;
			cout << " Write const" << endl;
			cin >> con;
			polynom C(con);
			polynom res = C*S1;
			cout << res;
			break;
		}
		default:
			break;
		}

		cout << " \n Repead : 1" << endl;
		cin >> flag;

	}
}