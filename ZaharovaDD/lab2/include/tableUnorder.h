#pragma once
#include "table.h" 
#include "math.h"
#include <string>
using namespace std;
template <class key_T, class data_T>
class TableUnorder : public Table <key_T, data_T>
{
public:
	TableUnorder(int Dim = MIN_DIM) : Table<key_T, data_T>(Dim) {};								//К.
	virtual ~TableUnorder() {};																	//Деструктор
	virtual void Insert(const key_T &_k, const data_T &_d);										//Вставка
	virtual void Dell(const key_T &_k);															//Удаление элемента 
	virtual RecordTable<key_T, data_T>* Search(const key_T &_k) const;							//Поиск элемента (по ключу) 

private:
	virtual void Repack();																		//Функция, увеличивающая размер таблицы 
};

template <class key_T, class data_T>
void TableUnorder< key_T, data_T> ::Insert(const key_T &_k, const data_T &_d)
{
	if ((double)this->Index / (double)this->Max_Dim > 0.7)										// перераспределить если до заполнения осталось менее 30 процентов 
		Repack();
	for (int i = 0; i < this->Index; i++)
	{
		if ((*(this->A_T[i])).key == _k)
		{
			throw "key - duplicate";															//ключ дублируется
		}
	}
	this->A_T[this->Index++] = new RecordTable<key_T, data_T>(_k, _d);
};

template <class key_T, class data_T>
void TableUnorder< key_T, data_T> ::Dell(const key_T &_k)
{
	int i = 0;
	int FLAG = 0;
	while ((i < this->Index) && (FLAG == 0)) {
		if ((*(this->A_T[i])).key == _k) FLAG = 1;
		i++;
	}
	if (FLAG == 1) {
		i--;
		delete this->A_T[i];
		while (i < this->Index - 1) {
			this->A_T[i] = this->A_T[i + 1];
			i++;
		}
		this->A_T[i] = NULL;
		this->Index--;
	}
	else throw "item does not exist";															//элемент не существует
};

template <class key_T, class data_T>
RecordTable<key_T, data_T>* TableUnorder< key_T, data_T> ::Search(const key_T &_k) const
{
	int i = 0;
	while (i < this->Index)
	{
		if ((*(this->A_T[i])).key == _k)
			return this->A_T[i];
		i++;
	}
	throw "item does not exist";
}

template <class key_T, class data_T>
void TableUnorder <key_T, data_T> ::Repack()
{
	int Nxt_Dim = (int)(this->Max_Dim + 20)*1.65;
	RecordTable<key_T, data_T> ** New_A = new RecordTable<key_T, data_T>*[Nxt_Dim];
	for (int i = 0; i<this->Max_Dim; i++)
		New_A[i] = this->A_T[i];
	for (int i = this->Max_Dim; i<Nxt_Dim; i++)
		New_A[i] = NULL;
	delete[] this->A_T;
	this->A_T = New_A;
	this->Max_Dim = Nxt_Dim;
};
