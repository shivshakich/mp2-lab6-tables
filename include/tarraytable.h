#pragma once

#include "ttable.h"

// ������� �� �������
class TArrayTable : public TTable {
protected:
	TRecord* Arr;			// ��������� �� ������ �������
	size_t Size;			// ������� ������ �������, ����. ����� ������� (����� ����������� �� TAB_MAX_SIZE)
	int CurrPos;			// (��������� � 0) ��� ������ � �������� ��������
public:
	// CONSTRUCTORS & DESTRUCTOR

	TArrayTable(int = 0);							// default constructor
	TArrayTable(const TRecord&);					// conversion constructor
	TArrayTable(const TArrayTable&);				// copy constructor
	TArrayTable(TArrayTable&&) noexcept;
	virtual ~TArrayTable();							// destructor

	// OPERATOR=
	
	TArrayTable& operator=(const TArrayTable&);
	TArrayTable& operator=(const TRecord&);
	TArrayTable& operator=(TArrayTable&&) noexcept;

	// ITERATION METHODS

	void Reset() noexcept;
	void GoNext() noexcept;
	bool IsEnd() const noexcept;

	// GET-SET METHODS

	size_t GetSize() const noexcept { return Size; }

	TKey GetKey() const override;
	virtual void SetKey(const TKey&);

	TValue GetValue() const override;
	void SetValue(const TValue&);

	int GetCurrPos() const noexcept;
	void SetCurrPos(int) noexcept;

	// COMPARISON METHODS

	bool operator==(const TArrayTable&) const noexcept;
	bool operator!=(const TArrayTable&) const noexcept;

	// OTHER METHODS

	bool IsFull() const noexcept;

	// FindRecord, InsRecord, DelRecord ����� ����������� � ������-�������
};