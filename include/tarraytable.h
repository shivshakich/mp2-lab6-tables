#pragma once

#include "ttable.h"

const size_t TAB_MAX_SIZE = 99;

// таблица на основе массива, доступ к элементам через поле CurrPos
class TArrayTable : public TTable {
protected:
	TRecord* Arr;			// указатель на начало массива
	size_t TabSize;			// текущий размер массива, макс. число
	int CurrPos;			// (нумерация с 0) для работы с методами итерации
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

	// FindRecord, InsRecord, DelRecord будут реализованы в классе-потомке
};