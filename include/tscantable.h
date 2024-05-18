#pragma once

#include "tarraytable.h"

// неупорядоченная таблица на массиве 
class TScanTable : public TArrayTable {
public:
	TScanTable(int = 0);
	TScanTable(const TArrayTable&);
	TScanTable(const TScanTable&);
	TScanTable(const TRecord& rec) : TArrayTable(rec) {}
	TScanTable(TScanTable&&) noexcept;

	TScanTable& operator=(const TScanTable&);
	TScanTable& operator=(TScanTable&&) noexcept;

	virtual bool FindRecord(const TKey&);
	virtual void InsRecord(const TKey&, const TValue&);
	virtual void DelRecord(const TKey&);

	// SetKey переопределять не требуется
};