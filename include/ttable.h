#pragma once

//////////////////////////////////////////////////////////////////////////
//																		//
//	[TTable] -----------+---------------------------+					//
//		|				|							|					//
//		v				v							v					//
//	[TArrayTable]	[THashTable]				[TTreeTable]			//
//		|				|							|					//
//		|				+---------------+			+-----------+		//
//		|				|				|			|			|		//
//		v				v				v			v			v		//
//	[TScanTable]	[TArrayHash]	[TListHash]	[TAVLTree]	[TRBTRee]	//
//		|																//
//		v																//
//	[TSortTable]														//
//																		//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <exception>
#include "tpolynom.h"

#define TAB_MAX_SIZE 100

typedef std::string TKey;
typedef TPolynom TValue;

using std::ostream;

struct TRecord {
	TKey key;
	TValue val;
};

// таблица состоит из записей (TRecord), каждая из которых имеет свой уникальный ключ (TKey)
class TTable {
protected:
	int DataCount;							// реальное количество записей в таблице
	int Eff;
public:
	TTable() : DataCount(0), Eff(0) {}
	virtual ~TTable() {}			// не делай деструктор базового класса чисто виртуальным

	int GetDataCount() const noexcept { return DataCount; }
	int GetEff() const noexcept { return Eff; }
	void ClearEff() noexcept { Eff = 0; }
	bool IsEmpty() const noexcept { return DataCount == 0; }

	virtual bool FindRecord(const TKey&) = 0;
	virtual void InsRecord(const TKey&, const TValue&) = 0;
	virtual void DelRecord(const TKey&) = 0;

	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() const noexcept = 0;

	virtual TKey GetKey() const  = 0;
	virtual TValue GetValue() const  = 0;

	friend ostream& operator<<(ostream& os, TTable& t) {
		for (t.Reset(); !t.IsEnd(); t.GoNext())
			os << t.GetKey() << ' ' << t.GetValue().ToString() << std::endl;

		return os;
	}
};