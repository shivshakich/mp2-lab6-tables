#pragma once

#include <iostream>

typedef int TKey;
typedef std::string TValue;

using std::ostream;

struct TRecord {
	TKey key;
	TValue val;
};

class TTable {
protected:
	int DataCount;
	int eff;
public:
	TTable() : DataCount(0), eff(0) {}
	virtual ~TTable() = 0;

	int GetDataCount() const noexcept { return DataCount; }
	int GetEff() const noexcept { return eff; }
	void ClearEff() noexcept { eff = 0; }
	bool IsEmpty() const noexcept { return DataCount == 0; }

	virtual bool IsFull() = 0;
	virtual bool Find(const TKey&) = 0;
	virtual bool InsRecord(const TRecord&) = 0;
	virtual void DelRecord(const TKey&) = 0;

	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;

	virtual TKey GetKey() const noexcept = 0;
	virtual TValue GetValue() const noexcept = 0;
	virtual TRecord& GetRecord() = 0;


	friend ostream& operator<<(ostream& os, TTable& t) {
		for (t.Reset(); !t.IsEnd(); t.GoNext())
			os << t.GetKey() << ' ' << t.GetValue() << std::endl;

		return os;
	}
};