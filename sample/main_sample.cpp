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

	cout << "(delta = �������� ���-�� / ��������� ���-��)" << endl;
	cout << endl;

	cout << " = ������������ ������������� ��������������� ������� TScanTable = " << endl;
	sample_scan_table();

	cout << endl;
	cout << "(������� ����� �������)" << endl;
	getchar();
	cout << endl;

	cout << " = ������������ ������������� ������������� ������� TSortTable = " << endl;
	sample_sort_table();

	cout << endl;
	cout << "(������� ����� �������)" << endl;
	getchar();
	cout << endl;

	cout << " = ������������ ������������� ���-������� �� ������� TArrayHash = " << endl;
	sample_array_hash();

	cout << endl;
	cout << "(������� ����� �������)" << endl;
	getchar();
	cout << endl;

	cout << " = ������������ ������������� ���-������� (������) = " << endl;
	sample_list_hash();

	cout << endl;
	cout << "(������� ����� �������)" << endl;
	getchar();
	cout << endl;

	cout << " = ������������ ������������� ���-������ = " << endl;
	sample_avl_tree();

	cout << endl;
	cout << "(������� ����� �������)" << endl;
	getchar();
	cout << endl;

	return 0;
}

void sample_scan_table() {
	TScanTable tab;
	const int MAXSIZE = tab.GetTabMaxSize();

	double minDelta = 1000.0, maxDelta= 0.0;

	cout << " - ��������������� ��������� ������\t: N " << endl;
	cout << " - ��������������� ��������� �������\t: N+1" << endl;
	cout << " - ��������������� ��������� ��������\t: N+1" << endl;

	cout << endl;

	cout << "1) ��������� ������ � ������� 0..." << MAXSIZE - 1 << " � ����� +1" << endl;
	cout << "2) ���� ������ ����" << endl;
	cout << "3) ������� ����� ��������� ������ " << endl;

	cout << endl;

	for (int i = 0; i < MAXSIZE; ++i) {
		tab.InsRecord(std::to_string(i), 0.0);
		int e = tab.GetEff();
		tab.ClearEff();

		double delta = 1.0 * e / (i + 1 + 1);
		if (delta < minDelta) minDelta = delta;
		if (delta > maxDelta) maxDelta = delta;
	}

	cout << "�������: ���. ���������� = " << minDelta << ", ����. ���������� = " << maxDelta << endl;
	minDelta = 1000.0, maxDelta = 0.0;

	for (int i = 0; i < MAXSIZE; ++i) {
		tab.FindRecord(std::to_string(i));
		int e = tab.GetEff();
		tab.ClearEff();

		double delta = 1.0 * e / (MAXSIZE);
		if (delta < minDelta) minDelta = delta;
		if (delta > maxDelta) maxDelta = delta;
	}

	cout << "�����: ���. ���������� = " << minDelta << ", ����. ���������� = " << maxDelta << endl;
	minDelta = 1000.0, maxDelta = 0.0;

	for (int i = MAXSIZE-1; i >= 0; --i) {
		tab.DelRecord(std::to_string(i));
		int e = tab.GetEff();
		tab.ClearEff();

		double delta = 1.0 * e / (i + 1);
		if (delta < minDelta) minDelta = delta;
		if (delta > maxDelta) maxDelta = delta;
	}

	cout << "��������: ���. ���������� = " << minDelta << ", ����. ���������� = " << maxDelta << endl;
}

void sample_sort_table() {
	TSortTable tab;
	const int MAXSIZE = tab.GetTabMaxSize();

	cout << " - ��������������� ��������� ������\t: log2(N)" << endl;
	cout << " - ��������������� ��������� �������\t: log2(N) + N" << endl;
	cout << " - ��������������� ��������� ��������\t: log2(N) + N" << endl;
}

void sample_array_hash() {
	TArrayHash tab;
	const int MAXSIZE = tab.GetTabMaxSize();

	cout << " - ��������������� ��������� ������\t: O(1) " << endl;
	cout << " - ��������������� ��������� �������\t: O(1)" << endl;
	cout << " - ��������������� ��������� ��������\t: O(1)" << endl;
}

void sample_list_hash() {
	TListHash tab;
	const int MAXSIZE = tab.GetTabMaxSize();

	cout << " - ��������������� ��������� ������\t: O(1) " << endl;
	cout << " - ��������������� ��������� �������\t: O(1)" << endl;
	cout << " - ��������������� ��������� ��������\t: O(1)" << endl;
}

void sample_avl_tree() {
	TAVLTree tab;
	const int MAXSIZE = tab.GetTabMaxSize();

	cout << " - ��������������� ��������� ������\t: 1.45*log2(N) " << endl;
	cout << " - ��������������� ��������� �������\t: 1.45*log2(N)+A" << endl;
	cout << " - ��������������� ��������� ��������\t: B*1.45*log2(N)" << endl;
}