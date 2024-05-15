#pragma once

#include "ttable.h"

const size_t TAB_MAX_SIZE = 99;

// ������� �� ������ �������, ������ � ��������� ����� ���� CurrPos
class TArrayTable : public TTable {
protected:
	TRecord* Arr;			// ��������� �� ������ �������
	size_t TabSize;			// ������� ������ �������, ����. �����
	int CurrPos;			// (��������� � 0) ��� ������ � �������� ��������
public:
	// CONSTRUCTORS & DESTRUCTOR

	TArrayTable(int = 0);							// default constructor
	TArrayTable(const TRecord&);					// conversion constructor
	TArrayTable(const TArrayTable&);				// copy constructor
	~TArrayTable() override;

	// ITERATION METHODS

	void Reset() override;
	void GoNext() override;
	bool IsEnd() const noexcept override;

	// GET-SET METHODS

	size_t GetSize() const noexcept;
	TKey GetKey() const override;
	TValue GetValue() const override;
	TRecord GetRecord() const override;
	int GetCurrPos() const noexcept;

	void SetKey(const TKey&);
	void SetValue(const TValue&);
	void SetRecord(const TRecord&);
	void SetCurrPos(int);

	// OTHERS METHODS

	virtual bool IsFull() const noexcept;

	// FindRecord, InsRecord, DelRecord ����� ����������� � ������-�������
};