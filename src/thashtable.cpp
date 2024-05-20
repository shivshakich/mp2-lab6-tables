#include "../include/thashtable.h"

THashTable::THashTable(int _size) : TTable() {
	if (_size < HASH_TAB_MIN_SIZE || _size > TAB_MAX_SIZE) throw std::exception("invalid_input_size");
	Size = _size;
}

int THashTable::Hash(int _in) { return _in % Size; }

int THashTable::Hash(const string& _s) {
	int sum = 0;
	for (char ch : _s) sum += ch;
	return sum % Size;
}