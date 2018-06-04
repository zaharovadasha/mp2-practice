
#pragma once
#include "table.h"

template <class key_T, class data_T>
class TableOrder : public Table<key_T, data_T>
{
public:
	TableOrder(int Dim = MIN_DIM) : Table<key_T, data_T>(Dim) {};
	virtual ~TableOrder() {};
	virtual void Insert(const key_T &_k, const data_T &_d);										//Вставка
	virtual void Dell(const key_T &_k);															//Удаление
	virtual RecordTable<key_T, data_T>* Search(const key_T &_k) const;							//Поиск (по ключу) 
private:
	virtual void Repack();																		//Функция, увеличивающая размер таблицы
	int BinarSearch(const key_T &Key) const;													//Бинарный поиск
};

template <class key_T, class data_T>
void TableOrder <key_T, data_T> ::Insert(const key_T &_k, const data_T &_d)
{
	int pa = BinarSearch(_k);
	int i;
	if ((this->A_T[pa] == NULL) || ((*(this->A_T[pa])).key != _k))
	{
		if ((double)this->Index / (double)this->Max_Dim > 0.7)								// перераспределить если до заполнения осталось 30 процентов 
			Repack();
		for (i = this->Index; i > pa; i--)
			this->A_T[i] = this->A_T[i - 1];
		this->A_T[i] = new RecordTable<key_T, data_T>(_k, _d);
		this->Index++;
	}
	else throw "key - duplicate";
}

template <class key_T, class data_T>
void  TableOrder <key_T, data_T> ::Dell(const key_T &_k)
{
	int pa = BinarSearch(_k);

	if ((this->A_T[pa] != NULL) && ((*(this->A_T[pa])).key == _k))
	{
		delete this->A_T[pa];
		for (int i = pa; i < this->Index; i++)
			this->A_T[i] = this->A_T[i + 1];
		this->Index -= 1;
	}
	else
		throw "item does not exist";
}

template <class key_T, class data_T>
RecordTable<key_T, data_T>* TableOrder <key_T, data_T> ::Search(const key_T &_k) const
{
	int pa = BinarSearch(_k);
	if ((this->A_T[pa]!=NULL)&&((*(this->A_T[pa])).key == _k))
		return this->A_T[pa];
	else
		throw "item does not exist";
}

template <class key_T, class data_T>
void TableOrder <key_T, data_T> ::Repack()
{
	int Nxt_Dim = (int)(this->Max_Dim + 20)*1.65;
	RecordTable <key_T, data_T> ** New_A = new RecordTable <key_T, data_T>*[Nxt_Dim];
	for (int i = 0; i<this->Max_Dim; i++)
		New_A[i] = this->A_T[i];
	for (int i = this->Max_Dim; i<Nxt_Dim; i++)
		New_A[i] = NULL;
	delete[] this->A_T;
	this->A_T = New_A;
	this->Max_Dim = Nxt_Dim;
}

template <class key_T, class data_T>
int TableOrder <key_T, data_T> ::BinarSearch(const key_T &k) const								//возвращает индекс (номер строки в таблице)
{
	int right = this->Index - 1;
	int mid = 0;
	int left = 0;
	while (right >= left)
	{
		mid = (right + left) / 2;
		if ((*(this->A_T[mid])).key < k)
			left = mid + 1;
		else if ((*(this->A_T[mid])).key > k)
			right = mid - 1;
		else return mid; 
	}
	if (left > right)
		mid = left;
	return mid;
}
