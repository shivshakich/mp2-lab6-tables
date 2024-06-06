#pragma once

#include "thashtable.h"

#define EMPTYREC_KEY "EMPTY"
#define DELREC_KEY "DEL"

// ���-������� �� �������; TKey - ��� std::string
class TArrayHash : public THashTable {
protected:
	TRecord* pRecs;						// ������ 
	TRecord EmptyRec, DelRec;
	int CurrPos, FreePos;				// CurrPos - ��� ������ Find, Ins, Del; FreePos - ��� ������ Ins
	int Step;							// 1 <= Step < Size; Step � Size - ������� ������� �����: ���(Step, Size) == 1

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