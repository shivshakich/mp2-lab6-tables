#include "../include/tlisthash.h"

// CONSTRUCORS & DESTRUCTOR

TListHash::TListHash(int _size) : THashTable(_size) {
	pList = new std::list<TRecord>[Size];
	if (pList == nullptr) throw std::exception("TabNoMem");

	CurrList = 0;
}

TListHash::TListHash(const TRecord& _rec) : THashTable() {
	pList = new std::list<TRecord>[Size];
	if (pList == nullptr) throw std::exception("TabNoMem");

	CurrList = Hash(_rec.key);
	pList[CurrList].push_front(TRecord{ _rec.key, _rec.val });
}

TListHash::TListHash(const TListHash& t) {
	pList = new std::list<TRecord>[t.Size];
	if (pList == nullptr) throw std::exception("TabNoMem");

	Eff = t.Eff;
	DataCount = t.DataCount;
	Size = t.Size;

	//pList[i] = t.pList[i];
	for (int i = 0; i < Size; ++i) {
		for (std::list<TRecord>::iterator temp = t.pList[i].begin(); temp != t.pList[i].end(); ++temp)
			pList[i].push_back(*temp);
	}

	CurrList = t.CurrList;
	pCurr = t.pCurr;
}

TListHash::~TListHash() { delete[] pList; }

// OPERATOR=

TListHash& TListHash::operator=(const TRecord& _rec) {
	CurrList = Hash(_rec.key);

	DataCount = 1;

	for (int i = 0; i < Size; ++i)
		pList[i].clear();

	pList[CurrList].push_front(_rec);

	return *this;
}

TListHash& TListHash::operator=(const TListHash& t) {
	if (this == &t) return *this;

	if (this->Size != t.Size) {
		std::list<TRecord>* pointer = new std::list<TRecord>[t.Size];
		if (pointer == nullptr) throw std::exception("TabNoMem");

		std::swap(pList, pointer);
		Size = t.Size;
		delete[] pointer;
	}

	Eff = t.Eff;
	DataCount = t.DataCount;
	/*
	for (int i = 0; i < Size; ++i)
		pList[i] = t.pList[i];
	*/
	for (int i = 0; i < Size; ++i) {
		for (std::list<TRecord>::iterator temp = t.pList[i].begin(); temp != t.pList[i].end(); ++temp)
			pList[i].push_back(*temp);
	}

	CurrList = t.CurrList;
	pCurr = t.pCurr;

	return *this;
}

// ITERATORS METHODS

void TListHash::Reset() {
	CurrList = 0;
	while ((pCurr = pList[CurrList].begin()) == pList[CurrList].end()) {
		++CurrList;

		if (CurrList >= Size) break;
		
		pCurr = pList[CurrList].begin();
	}
}

void TListHash::GoNext() {
	++pCurr;
	while (pCurr == pList[CurrList].end()) {
		++CurrList;
		if (CurrList >= Size) break;
		pCurr = pList[CurrList].begin();
	}
}

bool TListHash::IsEnd() const noexcept { return CurrList == Size; }

// FIND, INS, DEL

bool TListHash::FindRecord(const TKey& _key) {
	CurrList = Hash(_key);
	for (pCurr = pList[CurrList].begin(); pCurr != pList[CurrList].end(); ++pCurr) {
		++Eff;

		if (pCurr->key == _key) return true;
	}

	return false;
}

void TListHash::InsRecord(const TKey& _key, const TValue& _val) {
	bool find = FindRecord(_key);
	if (find) throw std::exception("duplicate_key");

	pList[CurrList].push_front(TRecord{_key, _val});

	++DataCount;
}

void TListHash::DelRecord(const TKey& _key) {
	bool find = FindRecord(_key);
	if (!find) return;

	pList[CurrList].erase(pCurr);

	--DataCount;
}

// GET-SET METHODS

TKey TListHash::GetKey() const {		// ???
	if (CurrList < 0 || CurrList >= Size) throw std::exception("invalid_current_list");
	
	return pCurr->key;
}

TValue TListHash::GetValue() const {	// ???
	if (CurrList < 0 || CurrList >= Size) throw std::exception("invalid_current_list");

	return pCurr->val;
}

void TListHash::SetValue(TValue& _val) {
	if (CurrList < 0 || CurrList >= Size) throw std::exception("invalid_current_list");

	pCurr->val = _val;
}