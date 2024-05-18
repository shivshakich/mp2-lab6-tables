#pragma once

#include "tarraytable.h"

// таблица на массиве с методами FindRecord, InsRecord, DelRecord; порядок записей не важен
class TScanTable : public TArrayTable {
public:
	TScanTable(int);
	TScanTable(const TArrayTable&);

	TScanTable& operator=(const TScanTable&);

	virtual bool FindRecord(const TKey&);
	virtual void InsRecord(const TKey&, const TValue&);
	virtual void DelRecord(const TKey&);
};