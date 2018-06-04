#pragma once
#include "table.h" 
#include <string>
using namespace std;
//0 - свободен; 
//1 - место занято; 
//-1 - был удалён;

template <class key_T, class data_T>
class TableHash : public Table <key_T, data_T>
{
public:
	TableHash(int Dim = 20) : Table<key_T, data_T>(Dim) { P_ = new int[Dim]; for (int i = 0; i < Dim; i++) P_[i] = 0; }; //К.
	~TableHash() {};
	void Insert(const key_T &_k, const data_T &_d);													//Вставка
	void Dell(const key_T &_k);																		//Удаление элемента 
	RecordTable<key_T, data_T>* Search(const key_T &_k) const;										//Поиск элемента по ключу 
private:
	int *P_;																						

	void Repack();																					//Перехеширование
	int Hash_function(const key_T &k) const;
};

template<class key_T>
int Get_Key(const key_T& k) { return 0; }

template<>
int Get_Key<string>(const string &k)																//Хэш - функции (от string)
{
	int g = 31;
	int hash = 0;
	for (int i = 0; i < k.length(); i++)
		hash = g * hash + k[i];
	return hash;
}

template <class key_T, class data_T>																//Хэш-функция МЕТОД	
int TableHash<key_T, data_T>::Hash_function(const key_T& k) const
{
	int temp = abs(Get_Key(k));
	return (temp % (this->Max_Dim));
}

template <class key_T, class data_T>
void TableHash<key_T, data_T>::Repack()
{
	int i = 0;
	int Nxt_Dim = (int)(this->Max_Dim + 20)*1.5;
	RecordTable<key_T, data_T> ** New_A = new RecordTable<key_T, data_T> *[Nxt_Dim];
	int * PM_ = new int[Nxt_Dim];
	for (int i = 0; i < this->Max_Dim; i++)
		PM_[i] = P_[i];
	for (int i = this->Max_Dim; i < Nxt_Dim; i++)
		PM_[i] = 0;
	delete[]P_;
	P_ = PM_;
	for (int i = 0; i<this->Max_Dim; i++)
		New_A[i] = this->A_T[i];
	for (int i = this->Max_Dim; i < Nxt_Dim; i++)
		New_A[i] = NULL;
	delete[] this->A_T;
	this->A_T = New_A;
	this->Max_Dim = Nxt_Dim;
}

template <class key_T, class data_T>
void TableHash<key_T, data_T>::Insert(const key_T &_k, const data_T &_d)
{
	if ((double)this->_Dim / (double)this->Max_Dim > 0.7)						 // перераспределить если до заполнения осталось 40 процентов 
		Repack();
	int loc = Hash_function(_k);
	if (P_[loc] == 0)															//ячейка свободна
	{
		this->A_T[loc] = new RecordTable<key_T, data_T>(_k, _d);
		P_[loc] = 1;
		this->_Dim++;
	}
	else if (P_[loc] == -1)
	{
		this->A_T[loc] = new RecordTable<key_T, data_T>(_k, _d);
		P_[loc] = 1;
	}
	else
	{
		if ((*(this->A_T[loc])).key == _k)
		{
			throw "key - duplicated";
		}
		int label = loc + 1;
		while (P_[label] == 1) //пока элемент занят 
		{
			label = label + 1;
			if ((this->A_T[label] != NULL) && ((*(this->A_T[label])).key == _k))
			{
				throw "key - duplicated";
			}
		}
		this->A_T[label] = new RecordTable<key_T, data_T>(_k, _d);
		if (P_[label] == 0)
			this->_Dim++;
		P_[label] = 1;
	}
}

template <class key_T, class data_T>
void TableHash<key_T, data_T>::Dell(const key_T &_k)
{
	int loc = Hash_function(_k);
	if (P_[loc] == 0) //элемента нет
		throw "item does not exist";
	if ((this->A_T[loc] != NULL) && ((*(this->A_T[loc])).key == _k))
	{
		delete this->A_T[loc];
		this->A_T[loc] = NULL;
		P_[loc] = -1;
	}
	else
	{
		while ((P_[loc] == -1) || ((P_[loc] == 1) && ((*(this->A_T[loc])).key != _k))) //если элемент был удалён, или он занят, но не совпадают ключи - обновить место
			loc = loc + 1;
		if (P_[loc] == 1) // совпадают ключи
		{
			delete this->A_T[loc];
			this->A_T[loc] = NULL;
			P_[loc] = -1;
		}
		else throw "item does not exist";
	}
}


template <class key_T, class data_T>
RecordTable<key_T, data_T>* TableHash<key_T, data_T>::Search(const key_T &_k) const
{
	int loc = Hash_function(_k);
	if (P_[loc] == 0) //элемента нет
		throw "item does not exist";
	if ((this->A_T[loc] != NULL) && ((*(this->A_T[loc])).key) == _k)
	{
		return this->A_T[loc];
	}
	else
	{
		while ((P_[loc] == -1) || ((P_[loc] == 1) && ((*(this->A_T[loc])).key != _k))) //если элемент был удалён, или он занят, но не совпадают ключи - обновить место
			loc = loc + 1;
		if (P_[loc] == 1) // совпадают ключи
		{
			return this->A_T[loc];
		}
		else
			throw "item does not exist";
	}

}
