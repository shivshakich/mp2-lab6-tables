#pragma once

#include "ttable.h"

class THashTable : public TTable {
protected:
	size_t Size;		// число записей; Size >= 1
public:
	THashTable(int = TAB_MAX_SIZE);

	int Hash(int);
	int Hash(const string&);
};