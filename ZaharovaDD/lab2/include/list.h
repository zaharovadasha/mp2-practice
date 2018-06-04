#pragma once
#include "node.h"
#include <iostream>

using namespace std;

//Шаблон класса Циклический список с головой
template<class TP>
class list
{
private:
	node<TP>* head; 																								//голова
	node<TP>* Curr;																									//Указатель на текущий					
public:
	list();																											//К. по умолчанию
	~list();																										//Деструктор
	list(const list<TP>& a);																						//К.
	void Clean();																									//очистка списка
		
	void InsertInOrder(const TP& a);																				//Вставить в упорядоченный список
	void InsertAfter(node<TP>* a1, const TP& a2);																	//вставить после
	void InsertToTail(const TP a);																					//вставить в конец
	
	bool IsEmpty() const { return (head->next == head);	};															//проверка на пустоту
	//написать метод isfull
	TP& GetCurr() const { return Curr->data; }																		//Получение текущего адреса
	void Reset() { Curr = head->next; }																				//Установка на начало
	void gonext() { Curr = Curr->next; };																			//переход на следующее звено																	
	bool IsOver()  { if (Curr->next == head->next) return true; else return false; }								//проверка на  конец

	const list<TP>& operator=(const list<TP>& a);																	//Перегрузка оператора =
	
	bool operator==(const list<TP>& a) const;																		//Оператор сравнения ==
	bool operator!=(const list<TP>& a) const { return !(*this == a); }												//Оператор сравнения не равно	
};


template <class TP>																									//К. по умолчанию
list<TP>::list()
{
	head = new node<TP>();
	Curr = head->next;
	head->next = head;
}

template <class TP>
list<TP>::~list()
{
	Clean();
	delete head;
}


template <class TP>																									//К. копирования
list<TP>::list(const list<TP>& a)
{
	head = new node<TP>;
	node<TP>* E1 = a.head;
	node<TP>* E2 = head;
	if (E1->next == a.head)
	{
		head->next = head;
		return;
	}
	while (E1->next != a.head)
	{
		E1 = E1->next;
		E2->next = new node<TP>(E1->data);
		E2 = E2->next;
	}
	E2->next = head;
	Curr = head->next;
}

template <class TP>																									//Очистка списка
void list<TP>::Clean()
{
	node<TP>* curr = head->next;
		while (curr != head)
		{
			node<TP>* temp = curr->next;
			delete curr;
			curr = temp;
		}
		head->next = head;
}


template <class TP>																									//Вставить в упорядоченный список
void list<TP>::InsertInOrder(const TP& a)
{
	if (IsEmpty())
	{
		head->next = new node<TP>(a);
		head->next->next = head;
	}
	else
	{
		node<TP>* t = new node<TP>(a);
		node<TP>* c = head;

		while (c->next != head && (*(c->next) < *t))
		{
			c = c->next;
		}
		node<TP>* t1 = c->next;
		c->next = t;
		c->next->next = t1;
	}
}

template <class TP>																									//вставить после
void list<TP>::InsertAfter(node<TP>* a1, const TP& a2)
{
	if (head == NULL)
		throw "empty list";
	else
	{
		node<TP>* t = a1->next;
		a1->next = new node<TP>(a2, t);
	}
}

template<class TP>																									//вставить в конец
void list<TP> ::InsertToTail(const TP a)
{
	Reset();
	while (Curr->next != head)
		gonext();
	node<TP>* t = Curr->next;
	Curr->next = new node<TP>(a);
	Curr->next->next = t;
}

template <class TP>																									//присваивание
const list<TP>& list<TP>::operator=(const list<TP>& a) 
{
	Clean();
	node<TP>* p_a = a.head;
	node<TP>* p_curr = head;
	while (p_a->next != a.head)
	{
		p_a = p_a->next;
		p_curr->next = new node<TP>(p_a->data);
		p_curr = p_curr->next;
	}
	p_curr->next = head;
	Curr = head->next;
	return *this;
}

																											
template<class TP>																									//сравнение
bool list<TP>::operator==(const list<TP>& a) const
{
	bool res = true;
	if (this != &a)
	{
		node<TP>* t1 = a.head->next;
		node<TP>* t2 = head->next;
		while (t1->data == t2->data && t2 != head && t1 != a.head)
		{
			t1 = t1->next;
			t2 = t2->next;
		}
		if (t2 != head || t1 != a.head)
			res = false;
	}
	return res;
}
