#include "../include/tarraytable.h"

// CONSTRUCTORS & DESTRUCTOR

TArrayTable::TArrayTable(int _size) : TTable() {
	if (_size < 0 || _size > TAB_MAX_SIZE) throw std::exception("invalid _size");

	Arr = new TRecord[_size];
	if (Arr == nullptr) throw std::exception("TabNoMem");

	Size = _size;
	CurrPos = 0;
}

TArrayTable::TArrayTable(const TRecord& r) {
	Arr = new TRecord[1];
	if (Arr == nullptr) throw std::exception("TabNoMem");
	Arr[0] = { r.key, r.val };

	Size = 1;
	DataCount = 1;
	Eff = 0;
	CurrPos = 0;
}

TArrayTable::TArrayTable(const TArrayTable& t) {
	Arr = new TRecord[t.Size];
	if (Arr == nullptr) throw std::exception("TabNoMem");

	DataCount = t.DataCount;
	Size = t.Size;
	Eff = t.Eff;
	CurrPos = t.CurrPos;

	for (int i = 0; i < DataCount; ++i)
		Arr[i] = t.Arr[i];
}

TArrayTable::TArrayTable(TArrayTable&& t) noexcept {
	std::swap(Arr, t.Arr);
	DataCount = t.DataCount;
	Eff = t.Eff;
	Size = t.Size;
	CurrPos = t.CurrPos;
}

TArrayTable::~TArrayTable() { delete[] Arr; }

// OPERATOR=

TArrayTable& TArrayTable::operator=(const TArrayTable& t) {
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

TArrayTable& TArrayTable::operator=(const TRecord& r) {
	TRecord* pointer = new TRecord[1];
	if (pointer == nullptr) throw std::exception("TabNoMem");

	DataCount = 1;
	Eff = 0;
	Size = 0;
	CurrPos = 0;

	std::swap(Arr, pointer);
	delete[] pointer;

	Arr[0] = { r.key, r.val };

	return *this;
}

TArrayTable& TArrayTable::operator=(TArrayTable&& t) noexcept {
	std::swap(Arr, t.Arr);
	DataCount = t.DataCount;
	Eff = t.Eff;
	Size = t.Size;
	CurrPos = t.CurrPos;

	return *this;
}

// ITERATION METHODS

void TArrayTable::Reset() noexcept { CurrPos = 0; }

void TArrayTable::GoNext() noexcept { ++CurrPos; }

bool TArrayTable::IsEnd() const noexcept { return CurrPos == DataCount; }

// GET-SET METHODS

TKey TArrayTable::GetKey() const {
	if (CurrPos < 0 || CurrPos >= DataCount) throw std::exception("invalid CurrPos");

	return Arr[CurrPos].key;
}

void TArrayTable::SetKey(const TKey& _key) {
	if (CurrPos < 0 || CurrPos >= DataCount) throw std::exception("invalid CurrPos");

	Arr[CurrPos].key = _key;
}

TValue TArrayTable::GetValue() const {
	if (CurrPos < 0 || CurrPos >= DataCount) throw std::exception("invalid CurrPos");

	return Arr[CurrPos].val;
}

void TArrayTable::SetValue(const TValue& _v) {
	if (CurrPos < 0 || CurrPos >= DataCount) throw std::exception("invalid CurrPos");

	Arr[CurrPos].val = TValue(_v);
}

int TArrayTable::GetCurrPos() const noexcept { return CurrPos; }

void TArrayTable::SetCurrPos(int _p) noexcept { CurrPos = _p; }

// COMPARISON METHODS

bool TArrayTable::operator==(const TArrayTable& t) const noexcept {
	if (this == &t) return true;
	else if (this->DataCount != t.DataCount) return false;

	bool res = true;

	for (int i = 0; (i < DataCount) && res; ++i)
		res = (Arr[i].key == t.Arr[i].key) && (Arr[i].val == t.Arr[i].val);

	return res;
}

bool TArrayTable::operator!=(const TArrayTable& t) const noexcept {
	return !this->operator==(t);
}

// OTHER METHODS 

bool TArrayTable::IsFull() const noexcept { return DataCount == Size; }