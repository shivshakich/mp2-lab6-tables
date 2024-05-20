#pragma once

#include "thashtable.h"

// ���-������� �� �������
class TArrayHash : public THashTable {
protected:
	TRecord* pRecs;						// ������ 
	const TRecord EMPTY_REC, DEL_REC;
	int CurrPos, FreePos;				// CurrPos - ��� ������ Find, Ins, Del; FreePos - ��� ������ Ins
	int Step;							// 1 <= Step < Size; Step � Size - ������� ������� �����: ���(Step, Size) == 1

	void SetStep();
	void HashHash();
public:
	TArrayHash(int = TAB_MAX_SIZE);
	TArrayHash(const TRecord&);
	TArrayHash(const TArrayHash&);
	~TArrayHash();

	bool FindRecord(const TKey&) override;
	void InsRecord(const TKey&, const TValue&) override;
	void DelRecord(const TKey&) override;

	void Reset() override;
	void GoNext() override;
	bool IsEnd() const noexcept override;

	TKey GetKey() const override;
	TValue GetValue() const override;

	void SetKey(const TKey&);
	void SetValue(const TValue&);
};