#pragma once

#include "tscantable.h"

enum SortType  { BUBBLE, QUICK, MERGE };

class TSortTable : public TScanTable {
protected:
	void BubbleSort();		
	void QuickSort(int _left, int _right);
	void MergeSort(int _left, int _right);
	void Merge(int _left, int _mid, int _right);
public:
	TSortTable(int = 0);
	TSortTable(const TRecord&);
	TSortTable(const TScanTable&, SortType = MERGE);
	TSortTable(const TSortTable&);

	TSortTable& operator=(const TRecord&);
	TSortTable& operator=(const TScanTable&);
	TSortTable& operator=(const TSortTable);

	bool FindRecord(const TKey&) override;
	void InsRecord(const TKey&, const TValue&) override;
	void DelRecord(const TKey&) override;

	void SetKey(const TKey&) override;
};