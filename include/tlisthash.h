#pragma once

#include <list>
#include "thashtable.h"

// ���-������� �� ������
class TListHash : public THashTable {
protected:
	std::list<TRecord>* pList;					// ������ �������
	int CurrList;								// ������� �������� ������
	std::list<TRecord>::iterator pCurr;			// ��� ������ find, ins, del
public:
	// _size - ������ �������, _maxListSize - ����. ����� ������
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

	ostream& Print(ostream& os) override {
		for (int _currList = 0; _currList < Size; ++_currList) {
			std::list<TRecord>::iterator _currPos = pList[_currList].begin();

			if (_currPos == pList[_currList].end())
				os << '[' << _currList << ']' << ' ' << "is empty" << std::endl;
			else {
				while (_currPos != pList[_currList].end()) {
					os << '[' << _currList << ']' << '\t' << _currPos->key << std::endl;
					++_currPos;
				}
			}
		}
		
		return os;
	}
};