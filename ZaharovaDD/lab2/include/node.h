#pragma once

//Шаблон класса "Элемент списка"
template<class TP>
class node
{
public:
	TP data;																							//Данные в эл.
	node<TP>* next;																						//Указатель на следующий эл.

	node() { next = NULL; };																			//К. по умолчанию
	node(TP a1, node<TP>* a2 = NULL) { data = a1; next = a2; };											//К. с параметром
	bool operator< (const node<TP>& a) const { return (data < a.data); };								//О. сравнения
	bool operator> (const node<TP>& a) const { return (data > a.data); };								//О. сравнения
};

