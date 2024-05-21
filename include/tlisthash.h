#pragma once

#include <list>
#include "thashtable.h"

// хэш-таблица на списке
class TListHash : public THashTable {
protected:
	std::list<TRecord>* pList;					// массив списков
	int CurrList;								// позиция текущего списка
	std::list<TRecord>::iterator pCurr;			// для работы find, ins, del
public:
	// _size - размер массива, _maxListSize - макс. длина списка
	TListHash(int _size = TAB_MAX_SIZE);
	TListHash(const TRecord&);
	TListHash(const TListHash&);
	~TListHash();

	TListHash& operator=(const TRecord&);
	TListHash& operator=(const TListHash&);

	bool FindRecord(const TKey&) override;
	void InsRecord(const TKey&, const TValue&) override;
	void DelRecord(const TKey&);

	void Reset() override;
	void GoNext() override;
	bool IsEnd() const noexcept override;

	TKey GetKey() const override;
	TValue GetValue() const override;
	void SetValue(TValue&);
};