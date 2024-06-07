#include "../include/ttreetable.h"

// –ј«Ћ»„Ќќ≈

void TTreeTable::ClearStack() {
	while (!st.empty()) st.pop();
}

void TTreeTable::CopyTree(const TTreeNode* const _from, TTreeNode* _to) {
	if (_from == nullptr) return;
	_to = new TTreeNode{ _from->rec };
	_to->bal = _from->bal;
	CopyTree(_from->pLeft, _to->pLeft);
	CopyTree(_from->pRight, _to->pLeft);
}

void TTreeTable::ClearTree(TTreeNode *p) {
	if (p == nullptr) return;

	ClearTree(p->pLeft);
	ClearTree(p->pRight);
	delete p;
}

// COSNTRUCTORS & DESTRUCTOR

TTreeTable::TTreeTable() : TTable() {
	pRoot = nullptr;
	pCurr = nullptr;
	pPrev = nullptr;
}

TTreeTable::TTreeTable(const TRecord& _rec) {
	pRoot = new TTreeNode{ _rec };
	if (pRoot == nullptr) throw std::exception("TabNoMem");

	Eff = 0;
	DataCount = 1;
	pCurr = nullptr;
	pPrev = nullptr;
}

TTreeTable::TTreeTable(const TTreeTable& t) {
	Eff = t.Eff;
	DataCount = t.DataCount;

	CopyTree(t.pRoot, this->pRoot);

	pCurr = nullptr;
	pPrev = nullptr;
}

TTreeTable::~TTreeTable() {
	ClearTree(pRoot);
}

// OPERATOR=

TTreeTable& TTreeTable::operator=(const TRecord& _rec) {
	ClearTree();
	pRoot = new TTreeNode{ _rec };
	DataCount = 1;
	pCurr = nullptr;
	pPrev = nullptr;
	ClearStack();

	return *this;
}

TTreeTable& TTreeTable::operator=(const TTreeTable& t) {
	Eff = t.Eff;
	DataCount = t.DataCount;

	this->ClearTree();
	CopyTree(t.pRoot, this->pRoot);

	pCurr = nullptr;
	pPrev = nullptr;
	ClearStack();

	return *this;
}

// FIND, INS, DEL

bool TTreeTable::FindRecord(const TKey& _key) {
	bool res;
	pCurr = pRoot; 
	pPrev = nullptr;

	while (pCurr != nullptr) {
		++Eff;

		if (pCurr->rec.key == _key) break; 

		pPrev = pCurr;

		if (_key < pCurr->rec.key)
			pCurr = pCurr->pLeft;
		else
			pCurr = pCurr->pRight;
	}

	// зайдЄт, если pRoot == nullptr и/или ключ не найден
	if ((res = pCurr == nullptr)) pCurr = pPrev;
	res = !res;

	return res;
}

void TTreeTable::InsRecord(const TKey& _key, const TValue& _val) {
	bool find = FindRecord(_key);
	if (find) throw std::exception("duplicate_key");

	++Eff;
	++DataCount;
	TTreeNode* addNode = new TTreeNode{ TRecord{_key, _val } };

	if (pRoot == nullptr) pRoot = addNode;
	else if (pCurr->rec.key < _key)
		pCurr->pRight = addNode;
	else
		pCurr->pLeft = addNode;

	pCurr = nullptr;
	pPrev = nullptr;
}

void TTreeTable::DelRecord(const TKey& _key) {
	bool find = FindRecord(_key);
	if (!find) return;

	TTreeNode* pDel = pCurr;

	if (pCurr->pLeft == nullptr) {			// нету левого потомка
		if (pCurr == pRoot) pRoot = pRoot->pRight;
		else if (pPrev->pLeft == pCurr)
			pPrev->pLeft = pCurr->pRight;
		else
			pPrev->pRight = pCurr->pRight;
	}
	else if (pCurr->pRight == nullptr) {	// нет правого потомка
		if (pCurr == pRoot) pRoot = pRoot->pLeft;
		else if (pPrev->pLeft == pCurr)
			pPrev->pLeft = pCurr->pLeft;
		else
			pPrev->pRight = pCurr->pLeft;
	}
	else {									// присутствуют оба потомка
		// найдЄм вершину с наибольшим ключом, который меньше ключа в вершине pCurr
		// по сути ищем макс. ключ в поддереве с корнем pCurr->pLeft
		pPrev = pCurr;
		pDel = pCurr->pLeft;

		while (pDel->pRight != nullptr) {
			++Eff;
			pPrev = pDel;
			pDel = pDel->pRight;
		}
		pCurr->rec = pDel->rec;
		// у pDel либо нет потомков, либо только левый потомок
		if (pPrev == pCurr) pPrev->pLeft = pDel->pLeft;
		else pPrev->pRight = pDel->pLeft;
	}

	delete pDel;

	++Eff;
	--DataCount;
	pCurr = nullptr;
	pPrev = nullptr;
}

// ITERATOR METHODS

void TTreeTable::Reset() {
	// 1) переместить pCurr на самую левую вершину
	// 2) записать в st путь до pCurr, включа€ pRoot и pCurr

	if (IsEmpty()) return;
	//if (IsEmpty()) throw std::exception("EmptyTab");

	this->ClearStack();
	pCurr = pRoot;

	while (pCurr != nullptr) {
		st.push(pCurr);
		pCurr = pCurr->pLeft;
	}
	pCurr = st.top();
}

void TTreeTable::GoNext() {
	// 1) переместить pCurr на вершину с ключом, который €вл€етс€ наименьшим после ключа из исходного pCurr
	// 2) хранить в  st путь до новой вершины

	if (IsEnd() || IsEmpty()) throw std::exception("iterator_range_out_(?)");
	// pCurr != nullptr

	if (pCurr->pRight != nullptr) {
		pCurr = pCurr->pRight;

		while (pCurr != nullptr) {
			st.push(pCurr);
			pCurr = pCurr->pLeft;
		}
		pCurr = st.top();
	}
	else {	// нет правого потомка
		// т.к. нет правого потомка, то нужно искать бќльшее значение на предыдущих €русах
		do {
			if (pCurr == pRoot) { pCurr = nullptr; break; }

			pPrev = pCurr;
			st.pop();
			pCurr = st.top();
		} while (pCurr->pRight == pPrev);
		// если pCurr изначально был левым потомком своего непосредственного предка, то цикл сработает 1 раз
	}
	
}

bool TTreeTable::IsEnd() const noexcept { return pCurr == nullptr; }

// GET-SET METHODS

TKey TTreeTable::GetKey() const {
	if (pCurr == nullptr) throw std::exception("invalid_current_pointer");

	return pCurr->rec.key;
}

TValue TTreeTable::GetValue() const {
	if (pCurr == nullptr) throw std::exception("invalid_current_pointer");

	return pCurr->rec.val;
}

void TTreeTable::SetValue(const TValue& _val) {
	if (pCurr == nullptr) throw std::exception("invalid_current_pointer");

	pCurr->rec.val = TValue(_val);
}