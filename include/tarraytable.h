#pragma once

#include "ttable.h"

// (абстрактный класс) таблица на массиве
class TArrayTable : public TTable {
protected:
	TRecord* Arr;			// указатель на начало массива
	size_t Size;			// текущий размер массива, макс. число записей (может увеличиться до TAB_MAX_SIZE)
	int CurrPos;			// (нумерация с 0) для работы с методами итерации
public:
	// CONSTRUCTORS & DESTRUCTOR

	TArrayTable(int = 0);							// default constructor
	TArrayTable(const TRecord&);					// conversion constructor
	TArrayTable(const TArrayTable&);				// copy constructor
	~TArrayTable() override;						// destructor

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

	// OTHER METHODS

	bool IsFull() const noexcept;

	// FindRecord, InsRecord, DelRecord будут реализованы в классе-потомке
};