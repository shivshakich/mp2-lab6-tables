#include "../include/tsorttable.h"

// CONSTRUCTORS

TSortTable::TSortTable(int _size) : TScanTable(_size), SortT(MERGE) {}

TSortTable::TSortTable(const TRecord& rec) : TScanTable(rec), SortT(MERGE) {}

TSortTable::TSortTable(const TScanTable& t, SortType s) : TScanTable(t), SortT(s) {
	Sort();
}

TSortTable::TSortTable(const TSortTable& t) {
	Arr = new TRecord[t.Size];
	if (Arr == nullptr) throw std::exception("TabNoMem");

	DataCount = t.DataCount;
	Eff = t.Eff;
	Size = t.Size;
	CurrPos = t.CurrPos;
	SortT = t.SortT;

	for (int i = 0; i < DataCount; ++i) {
		Arr[i].key = t.Arr[i].key;
		Arr[i].val = t.Arr[i].val;
	}
}

// SORT METHODDS

void TSortTable::Sort() {
	switch (SortT) {
	case BUBBLE:	this->BubbleSort();	break;
	case QUICK:		this->QuickSort();	break;
	case MERGE: 	this->MergeSort();	break;
	default: throw std::exception("invalid_input_sort_type");
	}
}

void TSortTable::BubbleSort() noexcept{
	bool IsExchanged = false;

	for (int i = 0; i < DataCount; ++i) {
		for (int j = 1; j < DataCount - i; ++j) {
			++Eff;

			if (Arr[j - 1].key > Arr[j].key) {	// порядок нарушен
				IsExchanged = true;
				std::swap(Arr[j - 1], Arr[j]);
			}
		}
		// в конце массива - наибольший после предыдущего наибольшего

		if (!IsExchanged) break;
	}
}

void TSortTable::QuickSort(int _left, int _right) {
	if (this->IsEmpty()) return;

	int mid = (_left + _right) / 2;
	TKey midKey = Arr[mid].key;

	int l = _left, r = _right;

	while (l < r) {
		while (Arr[l].key < midKey) {
			++l;
			++Eff;
		}
		while (Arr[r].key > midKey) {
			--r;
			++Eff;
		}

		if (l <= r) {
			std::swap(Arr[l], Arr[r]);
			++l;
			--r;
			++Eff;
		}
	}

	if (_left < r) QuickSort(_left, r);
	if (l < _right) QuickSort(l, _right);
}

void TSortTable::MergeSort(int _left, int _right) {
	if (_left >= _right) return;

	int mid = (_left + _right) / 2;
	MergeSort(_left, mid);
	MergeSort(mid + 1, _right);
	Merge(_left, mid, _right);
}

void TSortTable::Merge(int _left, int _mid, int _right) {
	const int COUNT = _right - _left + 1;

	TRecord* tmpArr = new TRecord[COUNT];
	if (tmpArr == nullptr) throw std::exception("TabNoMem");

	int pos1 = _left, pos2 = _mid + 1, tmpPos = 0;

	while (pos1 <= _mid && pos2 <= _right) {
		++Eff;

		if (Arr[pos1].key < Arr[pos2].key)
			tmpArr[tmpPos++] = Arr[pos1++];
		else
			tmpArr[tmpPos++] = Arr[pos2++];
	}
	// выход из цикла означает что один из подмассивов был пройден полностью

	while (pos1 <= _mid) {
		++Eff;
		tmpArr[tmpPos++] = Arr[pos1++];
	}
	while (pos2 <= _right) {
		++Eff;
		tmpArr[tmpPos++] = Arr[pos2++];
	}

	for (int i = 0; i < COUNT; ++i) {
		++Eff;
		Arr[_left + i] = tmpArr[i];
	}

	delete[] tmpArr;
}

// SEARCH METHODS

bool TSortTable::LinSearch(const TKey& _key) noexcept {
	bool res = false;
	int i;

	for (i = 0; i < DataCount; ++i) {
		++Eff;
		res = _key == Arr[i].key;
		if (res) break;
	}

	CurrPos = i;

	return res;
}

bool TSortTable::BinSearch(const TKey& _key) noexcept {
	bool res = false;

	int l = 0, r = DataCount - 1, mid;
	while (l <= r) {	// программа не зайдёт сюда при DataCount == 0
		++Eff;

		mid = (l + r) / 2;

		if (Arr[mid].key == _key) {
			res = true;
			l = mid;
			break;
		}
		else if (Arr[mid].key < _key) l = mid + 1;
		else r = mid - 1;
	}

	CurrPos = l;

	return res;
}

// OPERATOR=

TSortTable& TSortTable::operator=(const TRecord& rec) {
	TRecord* pointer = new TRecord[1];
	if (pointer == nullptr) throw std::exception("TabNoMem");

	pointer[0] = { rec.key, rec.val };

	std::swap(Arr, pointer);
	DataCount = 1;
	Size = 1;

	delete[] pointer;

	return *this;
}

TSortTable& TSortTable::operator=(const TScanTable& t) {
	TScanTable::operator=(t);
	Sort();

	return *this;
}

TSortTable& TSortTable::operator=(const TSortTable& t) {
	TRecord* pointer = new TRecord[t.Size];
	if (pointer == nullptr) throw std::exception("TabNoMem");

	std::swap(Arr, pointer);
	DataCount = t.DataCount;
	Eff = t.Eff;
	Size = t.Size;
	CurrPos = t.CurrPos;

	for (int i = 0; i < DataCount; ++i)
		Arr[i] = t.Arr[i];

	delete[] pointer;
}