mp2-lab6-tables
# Лабораторная работа № 6 "Таблицы"

Иерархия наследования классов:
- TTable
	- TArrayTable
		- TScanTable (неупорядоченная таблица, хранящая записи на массиве)
			- TSortTable (упорядоченная таблица, хранящая записи на массиве)
	- THashTable
		- TArrayHash (хэш-таблица, хранящая записи на массиве)
		- TListHash (хэш-таблица, использующая метод цепочек)
	- TTreeTable
		- TAVLTree
		- TRBTree
