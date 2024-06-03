#include "../include/tscantable.h"

// CONSTRUCTORS

TScanTable::TScanTable(int _size) : TArrayTable(_size) {}

TScanTable::TScanTable(const TArrayTable& t) : TArrayTable(t) {}

TScanTable::TScanTable(const TScanTable& t) {
	Arr = new TRecord[t.Size];
	if (Arr == nullptr) throw std::exception("TabNoMem");

	DataCount = t.DataCount;
	Eff = t.Eff;
	Size = t.Size;
	CurrPos = t.CurrPos;

	for (int i = 0; i < DataCount; ++i)
		Arr[i] = t.Arr[i];
}

TScanTable::TScanTable(TScanTable&& t) noexcept {
	std::swap(Arr, t.Arr);
	DataCount = t.DataCount;
	Eff = t.Eff;
	Size = t.Size;
	CurrPos = int(t.Size);
}

// OPERATOR=

TScanTable& TScanTable::operator=(const TScanTable& t) {
	TRecord* pointer = new TRecord[t.Size];
	if (pointer == nullptr) throw std::exception("TabNoMem");

	DataCount = t.DataCount;
	Eff = t.Eff;
	Size = t.Size;
	CurrPos = t.CurrPos;

	std::swap(pointer, Arr);
	delete[] pointer;

	for (int i = 0; i < DataCount; ++i)
		Arr[i] = t.Arr[i];

	return *this;
}

TScanTable& TScanTable::operator=(TScanTable&& t) noexcept {
	std::swap(Arr, t.Arr);
	DataCount = t.DataCount;
	Eff = t.Eff;
	Size = t.Size;
	CurrPos = int(t.Size);

	return *this;
}

// FIND, INS, DEL

bool TScanTable::FindRecord(const TKey& _key) {
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

void TScanTable::InsRecord(const TKey& _key, const TValue& _val) {
	bool find = FindRecord(_key);
	if (find) throw std::exception("input_key_is_existing_in_table");

	if (!IsFull()) {
		Arr[CurrPos] = { _key, _val };
		++Eff;
		++DataCount;
	}
	else if (IsFull() && Size == TAB_MAX_SIZE) throw std::exception("Max_DataCount");
	else {		// IsFull() && Size != TAB_MAX_SIZE
		size_t tmp = Size * 2 + 1 < TAB_MAX_SIZE ? Size * 2 + 1 : TAB_MAX_SIZE;		// наименьшее между Size*2+1 и TAB_MAX_SIZE
		TRecord* pointer = new TRecord[tmp];
		if (pointer == nullptr) throw std::exception("TabNoMem");

		for (int i = 0; i < Size; ++i) 
			pointer[i] = Arr[i];
		pointer[Size] = { _key, _val };

		std::swap(Arr, pointer);
		Eff += int(Size + 1);
		++DataCount;
		Size = tmp;

		delete[] pointer;
	}
}

void TScanTable::DelRecord(const TKey& _key) {
	bool find = FindRecord(_key);
	if (!find) return;

	Arr[CurrPos] = Arr[Size - 1];
	--DataCount;
	++Eff;
}