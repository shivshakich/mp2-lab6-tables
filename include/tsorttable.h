#pragma once

#include "tscantable.h"

enum SortType  { BUBBLE, QUICK, MERGE };
enum SearchType { LIN, BIN };

class TSortTable : public TScanTable {
protected:
	SortType SortT;
	SearchType SearchT;

	void Sort();

	void BubbleSort() noexcept;		
	void QuickSort(int _left, int _right);
	void QuickSort() { QuickSort(0, DataCount - 1); }
	void MergeSort(int _left, int _right);
	void MergeSort() { MergeSort(0, DataCount - 1); }
	void Merge(int _left, int _mid, int _right);

	bool LinSearch(const TKey&) noexcept;
	bool BinSearch(const TKey&) noexcept;
public:
	TSortTable(int = 0);
	TSortTable(const TRecord&);
	TSortTable(const TScanTable&, SortType = MERGE);
	TSortTable(const TSortTable&);

	TSortTable& operator=(const TRecord&);
	TSortTable& operator=(const TScanTable&);
	TSortTable& operator=(const TSortTable&);

	bool FindRecord(const TKey&) override;
	void InsRecord(const TKey&, const TValue&) override;
	void DelRecord(const TKey&) override;

	void SetKey(const TKey&) override;
	SortType GetSortType() const noexcept;
	void SetSortType(const SortType&) noexcept;
	SearchType GetSearchType() const noexcept;
	void SetSearchType(const SearchType&) noexcept;
};