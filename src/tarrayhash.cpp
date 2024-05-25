#include "../include/tarrayhash.h"

// установить шаг

void TArrayHash::SetStep() {
	// ищем минимальное число, подходящее на роль Step (при возможности не 1)

	if (Size == 2) { 
		Step = 1; 
		return; 
	}
	else if (Size % 2 == 1) {
		Step = 2;
		return;
	}

	for (int i = 3; i < Size; i += 2) {
		int a = i, b = Size;
		while (a && b) {
			if (a > b) a %= b;
			else b %= a;
		}
		// a + b == НОД(i, Size)

		if (a + b == 1) {
			Step = i; 
			return;
		}
	}

	Step = 1;
}

// CONSTRUCTORS & DESTRUCTOR

TArrayHash::TArrayHash(int _size) : THashTable(_size) {
	pRecs = new TRecord[Size];
	if (pRecs == nullptr) throw std::exception("TabNoMem");

	EmptyRec.key = EMPTYREC_KEY;
	DelRec.key = DELREC_KEY;
	CurrPos = FreePos = -1;
	SetStep();

	for (int i = 0; i < Size; ++i)
		pRecs[i] = EmptyRec;
}

TArrayHash::TArrayHash(const TRecord& rec) : THashTable() {
	if (rec.key == EMPTYREC_KEY || rec.key == DELREC_KEY)
		throw std::exception("invalid_key");

	const int IND = Hash(rec.key);

	pRecs = new TRecord[Size];
	if (pRecs == nullptr) throw std::exception("TabNoMem");

	EmptyRec.key = EMPTYREC_KEY;
	DelRec.key = DELREC_KEY;
	CurrPos = FreePos = -1;
	SetStep();
	DataCount = 1;

	for (int i = 0; i < IND; ++i)
		pRecs[i] = EmptyRec;
	pRecs[IND] = { rec.key, rec.val };
	for (int i = IND + 1; i < Size; ++i)
		pRecs[i] = EmptyRec;
}

TArrayHash::TArrayHash(const TArrayHash& t) {
	pRecs = new TRecord[t.Size];
	if (pRecs == nullptr) throw std::exception("TabNoMem");

	Eff = t.Eff;
	DataCount = t.DataCount;
	Size = t.Size;
	EmptyRec.key = EMPTYREC_KEY;
	DelRec.key = DELREC_KEY;
	CurrPos = t.CurrPos;
	FreePos = t.FreePos;
	Step = t.Step;

	for (int i = 0; i < Size; ++i)
		pRecs[i] = t.pRecs[i];
}

TArrayHash::~TArrayHash() { delete[] pRecs; }

// OPERATOR=

TArrayHash& TArrayHash::operator=(const TRecord& rec) {
	if (rec.key == EMPTYREC_KEY || rec.key == DELREC_KEY)
		throw std::exception("invalid_input_key");

	const int IND = this->Hash(rec.key);

	for (int i = 0; i < IND; ++i)
		if (pRecs[i].key != DELREC_KEY && pRecs[i].key != EMPTYREC_KEY) 
			pRecs[i] = DelRec;
	pRecs[IND] = { rec.key, rec.val };
	for (int i = IND + 1; i < Size; ++i)
		if (pRecs[i].key != DELREC_KEY && pRecs[i].key != EMPTYREC_KEY)
			pRecs[i] = DelRec;

	DataCount = 1;

	return *this;
}

TArrayHash& TArrayHash::operator=(const TArrayHash& t) {
	if (this == &t) return *this;

	if (this->Size != t.Size) {
		TRecord* pointer = new TRecord[t.Size];
		if (pointer == nullptr) throw std::exception("TabNoMem");

		std::swap(pRecs, pointer);
		Size = t.Size;
		delete[] pointer;
	}

	Eff = t.Eff;
	DataCount = t.DataCount;
	CurrPos = t.CurrPos;
	FreePos = t.FreePos;
	Step = t.Step;

	for (int i = 0; i < Size; ++i)
		pRecs[i] = t.pRecs[i];

	return *this;
}

// ITERATOR METHODS

void TArrayHash::Reset() {
	for (CurrPos = 0; CurrPos < Size; ++CurrPos)
		if (pRecs[CurrPos].key != EMPTYREC_KEY && pRecs[CurrPos].key != DELREC_KEY)
			break;
}

void TArrayHash::GoNext() {
	if (CurrPos < 0 || CurrPos > Size) throw std::exception("invalid_current_position");

	++CurrPos;
	for (; CurrPos < Size; ++CurrPos)
		if (pRecs[CurrPos].key != EMPTYREC_KEY && pRecs[CurrPos].key != DELREC_KEY)
			break;
}

bool TArrayHash::IsEnd() const noexcept { return CurrPos == Size; }

// GET-SET METHODS

TKey TArrayHash::GetKey() const {
	if (CurrPos < 0 || CurrPos >= Size) throw std::exception("invalid_current_position");

	return pRecs[CurrPos].key;
}

TValue TArrayHash::GetValue() const {
	if (CurrPos < 0 || CurrPos >= Size) throw std::exception("invalid_current_position");

	return pRecs[CurrPos].val;
}

void TArrayHash::SetValue(TValue& _val) {
	if (CurrPos < 0 || CurrPos >= Size) throw std::exception("invalid_current_position");

	pRecs[CurrPos].val = _val;
}

// FIND, INS, DEL

bool TArrayHash::FindRecord(const TKey& _key) {
	if (_key == EMPTYREC_KEY || _key == DELREC_KEY)
		throw std::exception("invalid_input_key");

	bool res = false;

	FreePos = -1;
	CurrPos = Hash(_key);
	
	for (int i = 0; i < Size; ++i) {
		++Eff;
		
		if (pRecs[CurrPos].key == _key) {
			res = true;
			break;
		}
		if (pRecs[CurrPos].key == DELREC_KEY && FreePos == -1)
			FreePos = CurrPos;
		if (pRecs[CurrPos].key == EMPTYREC_KEY) {
			res = false;
			break;
		}

		CurrPos = (CurrPos + Step) % Size;
	}

	return res;
}

void TArrayHash::InsRecord(const TKey& _key, const TValue& _val) {
	if (IsFull()) throw std::exception("Max_DataCount");

	bool find = FindRecord(_key);
	if (find) throw std::exception("duplicate_key");

	if (FreePos != -1) CurrPos = FreePos;
	pRecs[CurrPos] = { _key, _val };
	++DataCount;
}

void TArrayHash::DelRecord(const TKey& _key) {
	if (IsEmpty()) throw std::exception();

	bool find = FindRecord(_key);
	if (!find) return;

	pRecs[CurrPos].key = DELREC_KEY;
	--DataCount;
}