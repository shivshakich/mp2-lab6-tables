#pragma once

#include "thashtable.h"

#define EMPTYREC_KEY "EMPTY"
#define DELREC_KEY "DEL"

// хэш-таблица на массиве; TKey - это std::string
class TArrayHash : public THashTable {
protected:
	TRecord* pRecs;						// массив 
	TRecord EmptyRec, DelRec;
	int CurrPos, FreePos;				// CurrPos - для работы Find, Ins, Del; FreePos - для работы Ins
	int Step;							// 1 <= Step < Size; Step и Size - взаимно простые числа: НОД(Step, Size) == 1

	void SetStep();
public:
	TArrayHash(int = TAB_MAX_SIZE);
	TArrayHash(const TRecord&);
	TArrayHash(const TArrayHash&);
	~TArrayHash();

	TArrayHash& operator=(const TRecord&);
	TArrayHash& operator=(const TArrayHash&);

	bool FindRecord(const TKey&) override;
	void InsRecord(const TKey&, const TValue&) override;
	void DelRecord(const TKey&) override;

	void Reset() override;
	void GoNext() override;
	bool IsEnd() const noexcept override;

	TKey GetKey() const override;
	TValue GetValue() const override;

	ostream& Print(ostream& os) override {
		for (int i = 0; i < Size; ++i) {
			std::string _key = pRecs[i].key;

			os << '[' << i << ']' << '\t' << _key << std::endl;
		}

		return os;
	}

	void SetValue(TValue&);
};