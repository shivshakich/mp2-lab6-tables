#include <locale>
#include <string>

#include "../include/tscantable.h"
#include "../include/tsorttable.h"
#include "../include/tarrayhash.h"
#include "../include/tlisthash.h"
#include "../include/tavltree.h"

using std::cout;
using std::endl;

void sample_scan_table();
void sample_sort_table();
void sample_array_hash();
void sample_list_hash();
void sample_avl_tree();

int main() {
	setlocale(LC_CTYPE, "Russian");

	cout << "(delta = реальная эфф-ть / ожидаемая эфф-ть)" << endl;
	cout << endl;

	cout << " = Исследование эффективности неупорядоченной таблицы TScanTable = " << endl;
	sample_scan_table();

	cout << endl;
	cout << "(Нажмите любую клавишу)" << endl;
	getchar();
	cout << endl;

	cout << " = Исследование эффективности упорядоченной таблицы TSortTable = " << endl;
	sample_sort_table();

	cout << endl;
	cout << "(Нажмите любую клавишу)" << endl;
	getchar();
	cout << endl;

	cout << " = Исследование эффективности хэш-таблицы на массиве TArrayHash = " << endl;
	sample_array_hash();

	cout << endl;
	cout << "(Нажмите любую клавишу)" << endl;
	getchar();
	cout << endl;

	cout << " = Исследование эффективности хэш-таблицы (список) = " << endl;
	sample_list_hash();

	cout << endl;
	cout << "(Нажмите любую клавишу)" << endl;
	getchar();
	cout << endl;

	cout << " = Исследование эффективности АВЛ-дерева = " << endl;
	sample_avl_tree();

	cout << endl;
	cout << "(Нажмите любую клавишу)" << endl;
	getchar();
	cout << endl;

	return 0;
}

void sample_scan_table() {
	TScanTable tab;
	const int MAXSIZE = tab.GetTabMaxSize();

	double minDelta = 1000.0, maxDelta= 0.0;

	cout << " - Алгоритмическая сложность поиска\t: N " << endl;
	cout << " - Алгоритмическая сложность вставки\t: N+1" << endl;
	cout << " - Алгоритмическая сложность удаления\t: N+1" << endl;

	cout << endl;

	cout << "1) вставляем записи с ключами 0..." << MAXSIZE - 1 << " с шагом +1" << endl;
	cout << "2) ищем каждый ключ" << endl;
	cout << "3) Удаляем самую последнюю запись " << endl;

	cout << endl;

	for (int i = 0; i < MAXSIZE; ++i) {
		tab.InsRecord(std::to_string(i), 0.0);
		int e = tab.GetEff();
		tab.ClearEff();

		double delta = 1.0 * e / (i + 1 + 1);
		if (delta < minDelta) minDelta = delta;
		if (delta > maxDelta) maxDelta = delta;
	}

	cout << "Вставка: мин. отклонение = " << minDelta << ", макс. отклонение = " << maxDelta << endl;
	minDelta = 1000.0, maxDelta = 0.0;

	for (int i = 0; i < MAXSIZE; ++i) {
		tab.FindRecord(std::to_string(i));
		int e = tab.GetEff();
		tab.ClearEff();

		double delta = 1.0 * e / (MAXSIZE);
		if (delta < minDelta) minDelta = delta;
		if (delta > maxDelta) maxDelta = delta;
	}

	cout << "Поиск: мин. отклонение = " << minDelta << ", макс. отклонение = " << maxDelta << endl;
	minDelta = 1000.0, maxDelta = 0.0;

	for (int i = MAXSIZE-1; i >= 0; --i) {
		tab.DelRecord(std::to_string(i));
		int e = tab.GetEff();
		tab.ClearEff();

		double delta = 1.0 * e / (i + 1);
		if (delta < minDelta) minDelta = delta;
		if (delta > maxDelta) maxDelta = delta;
	}

	cout << "Удаление: мин. отклонение = " << minDelta << ", макс. отклонение = " << maxDelta << endl;
}

void sample_sort_table() {
	TSortTable tab;
	const int MAXSIZE = tab.GetTabMaxSize();

	cout << " - Алгоритмическая сложность поиска\t: log2(N)" << endl;
	cout << " - Алгоритмическая сложность вставки\t: log2(N) + N" << endl;
	cout << " - Алгоритмическая сложность удаления\t: log2(N) + N" << endl;
}

void sample_array_hash() {
	TArrayHash tab;
	const int MAXSIZE = tab.GetTabMaxSize();

	cout << " - Алгоритмическая сложность поиска\t: O(1) " << endl;
	cout << " - Алгоритмическая сложность вставки\t: O(1)" << endl;
	cout << " - Алгоритмическая сложность удаления\t: O(1)" << endl;
}

void sample_list_hash() {
	TListHash tab;
	const int MAXSIZE = tab.GetTabMaxSize();

	cout << " - Алгоритмическая сложность поиска\t: O(1) " << endl;
	cout << " - Алгоритмическая сложность вставки\t: O(1)" << endl;
	cout << " - Алгоритмическая сложность удаления\t: O(1)" << endl;
}

void sample_avl_tree() {
	TAVLTree tab;
	const int MAXSIZE = tab.GetTabMaxSize();

	cout << " - Алгоритмическая сложность поиска\t: 1.45*log2(N) " << endl;
	cout << " - Алгоритмическая сложность вставки\t: 1.45*log2(N)+A" << endl;
	cout << " - Алгоритмическая сложность удаления\t: B*1.45*log2(N)" << endl;
}