#pragma once

#include "ttable.h"

#define HASH_TAB_MIN_SIZE 2

class THashTable : public TTable {
protected:
	size_t Size;		// число записей; Size >= HASH_TAB_MIN_SIZE
public:
	THashTable(int = TAB_MAX_SIZE);

	int Hash(int);
	int Hash(const string&);
};