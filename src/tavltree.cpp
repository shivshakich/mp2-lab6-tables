#include "../include/tavltree.h"

// LEFT- AND RIGHT- BALANCE

void TAVLTree::LeftBalance(TTreeNode*& pointer) {
	// � ������� pointer ������ ����� -2
	// � ��� �������� ���������� ������
	// � ��� ������ ��������� ������ ���� -1, ���� +1
	// ����� ���� 0 ������ � ������� :
	// 1) ����� ������� - ���� (��� �������� �������, ��� ������� ������� �������� LeftBalance)
	// 2) � ������ ������� pointer-������� ��� ������ ������� (��� ������� � �������������������� ������ ��� �� ������ ins ��� del)

	++Eff;

	TTreeNode * b, * c;
	switch (pointer->pLeft->bal) {
	case BAL_LEFT: 
		// ����������� ������ (�����)
		//////////////////////////////////////////////////////////////////////////////////////
		//											//										//				
		//											//				bal= 0					//
		//						bal= -2				//		 +------[B]------+				//
		//			 +----------[A]------+			//		 |				 |				//
		//			 |					 |			//		 v				 v bal = 0		//
		//			 v	bal= -1			 v			//		[t1]	 +------[A]------+		//
		//		 +--[B]------+			[t3]		//		[  ]	 |				 |		//
		//		 |			 |			[  ]		//		[  ]	 v				 v		//
		//		 v			 v			[  ]		//		[  ]	[t2]			[t3]	//
		//		[t1]		[t2]		[  ]		//	 ===[xx]====[  ]============[  ]==	//
		//		[  ]		[  ]		[  ]		//										//
		//	====[  ]========[  ]=================	//										//
		//		[xx]								//										//
		//											//										//
		//////////////////////////////////////////////////////////////////////////////////////
		// TTreeNode *a = pointer, *b = pointer->pLeft;
		// TTreeNode* t1 = b->pLeft, * t2 = b->pRight, * t3 = a->pRight;

		b = pointer->pLeft;

		pointer->pLeft = b->pRight;
		b->pRight = pointer;

		pointer->bal = BAL_OK;
		pointer = b;
		pointer->bal = BAL_OK;

		// ������ ������ � ������ pointer ���� h+3, ����� h+2; ������ ����������� �� 1
		break;
	case BAL_RIGHT: 
		// ���������� ������ (�����)
		//////////////////////////////////////////////////////////////////////////////////////////
		//											//
		//				bal= -2						//
		//		 +--[A]----------------------+		//
		//		 |							 |		//
		//		 v	bal= +1					 v		//
		//	 +--[B]----------+				[t4]	//
		//	 |				 |				[  ]	//
		//	 v				 v	bal= 0		[  ]	//
		//	[t1]	 +------[C]------+		[  ]	//
		//	[  ]	 |				 |		[  ]	//
		//  [  ]	 v				 v		[  ]	//
		//	[  ]	[t2]			[t3]	[  ]	//
		//	[  ]	[  ]			[  ]	[  ]	//
		// =[  ]====[  ]============[  ]=========== //
		//			[xx]			[xx]			//
		//											//
		//////////////////////////////////////////////////////////////////////////////////////////

		b = pointer->pLeft;
		c = b->pRight;

		b->pRight = c->pLeft;
		c->pLeft = b;
		pointer->pLeft = c->pRight;
		c->pRight = pointer;
		
		if (c->bal == BAL_RIGHT) {
			b->bal = BAL_LEFT;
			pointer->bal = BAL_OK;
		}
		else {
			b->bal = BAL_OK;
			pointer->bal = BAL_RIGHT;
		}

		pointer = c;
		pointer->bal = BAL_OK;

		// ������ ������ � ������ pointer ���� h+3, ����� h+2; ������ ����������� �� 1
		break;
	default:
		throw std::exception("Kak?");
	}
}

void TAVLTree::RightBalance(TTreeNode*& pointer) {
	// pointer->bal == +2

	++Eff;

	TTreeNode* b, * c;
	switch (pointer->pRight->bal) {
	case BAL_RIGHT:
		// ����������� ������ (������)

		b = pointer->pRight;

		pointer->pRight = b->pLeft;
		b->pLeft = pointer;

		pointer->bal = BAL_OK;
		pointer = b;
		pointer->bal = BAL_OK;

		break;
	case BAL_LEFT:
		// ���������� ������ (������)

		b = pointer->pRight;
		c = b->pLeft;

		b->pLeft = c->pRight;
		c->pRight = b;
		pointer->pRight = c->pLeft;
		c->pLeft = pointer;

		if (c->bal == BAL_LEFT) {
			b->bal = BAL_RIGHT;
			pointer->bal = BAL_OK;
		}
		else {
			b->bal = BAL_OK;
			pointer->bal = BAL_LEFT;
		}

		pointer = c;
		pointer->bal = BAL_OK;

		break;
	default:
		throw std::exception("Kak?");
	}
}

// CONSTRUCOTRS

TAVLTree::TAVLTree() : TTreeTable() {}

TAVLTree::TAVLTree(const TRecord& _rec) : TTreeTable(_rec) {
	pRoot->bal = BAL_OK;
}

TAVLTree::TAVLTree(TTreeTable& t) : TTreeTable() {
	for (t.Reset(); !t.IsEnd(); t.GoNext())
		this->InsRecord(t.GetKey(), t.GetValue());
}

TAVLTree::TAVLTree(const TAVLTree& t) {
	Eff = t.Eff;
	DataCount = t.DataCount;

	CopyTree(t.pRoot, this->pRoot);
	
	pCurr = nullptr;
	pPrev = nullptr;
}

// OPERATOR=

TAVLTree& TAVLTree::operator=(const TRecord& _rec) {
	this->TTreeTable::operator=(_rec);
	pRoot->bal = BAL_OK;

	return *this;
}

TAVLTree& TAVLTree::operator=(TTreeTable& t) {
	Eff = t.GetEff();
	DataCount = t.GetDataCount();
	this->ClearTree();

	for (t.Reset(); !t.IsEnd(); t.GoNext())
		this->InsRecord(t.GetKey(), t.GetValue());

	pCurr = nullptr;
	pPrev = nullptr;
	ClearStack();

	return *this;
}

TAVLTree& TAVLTree::operator=(const TAVLTree& t) {
	this->ClearTree();

	Eff = t.Eff;
	DataCount = t.DataCount;

	CopyTree(t.pRoot, this->pRoot);

	pCurr = nullptr;
	pPrev = nullptr;
	ClearStack();

	return *this;
}

// INS, DEL

/*
void TAVLTree::InsRecord(TTreeNode*& pointer, const TKey& _key, const TValue& _val) {
// ������ ���������� ���������� ����� ins, ��� ����������� ���� �� ����� �� ����������� �������

	++Eff;

	if (pointer == nullptr) {	// ����� �����, ���� ��������
		pointer = new TTreeNode{ TRecord{_key, _val}, nullptr, nullptr, BAL_OK };
		if (pointer == nullptr) throw std::exception("TabNoMem");
		++DataCount;
	}
	else if (_key == pointer->rec.key) throw std::exception("duplicate_key");
	else if (_key < pointer->rec.key) {
		this->InsRecord(pointer->pLeft, _key, _val);
		// ���� �� ��������� ����������, ������ ���� ��������� ������
		--pointer->bal;
		if (pointer->bal == -2) LeftBalance(pointer);
	}
	else {
		this->InsRecord(pointer->pRight, _key, _val);
		++pointer->bal;
		if (pointer->bal == +2) RightBalance(pointer);
	}
}
*/

void TAVLTree::InsRecord(const TKey& _key, const TValue& _val) {
	// ������� ���������� ���� ��� ���������� ������ � ������ _key
	
	// ����������� ������� ������ ������ ������
	// � ������� ������������ ������� ���������� ���� �� ����� �� ����������� �������� ������������
	
	// �� ����, ��� ���� ��������� ����� �������, ������ ���� ����������������
	// ����� - ���� �������� ����������������, ���� ��� ������� ������ (���� +2 ��� -2) �� ����� �� ������, ������������� ����, ���������� � st

	// ��������� �� ������������ ����� �� ����� �� ����

	// ����� �������, ��� �� ������ INS-������, ������ ���� ����������������

	++Eff;

	pCurr = pRoot;
	pPrev = nullptr;
	std::stack<TTreeNode*> tmpSt;	// ����� ������� ����

	// ���������� ���� �� ����������� �������
	while (pCurr != nullptr) {
		++Eff;
		tmpSt.push(pCurr);

		if (pCurr->rec.key == _key) throw std::exception("duplicate_key");
		else if (_key < pCurr->rec.key)
			pCurr = pCurr->pLeft;
		else
			pCurr = pCurr->pRight;
	}

	// �� ��������� ���������� ~~> ��� ������������ ������ ~~> ����� ��������� ����� �������

	TTreeNode* addNode = new TTreeNode{ TRecord{_key,_val} };
	if (addNode == nullptr) throw std::exception("TabNoMem");
	addNode->bal = BAL_OK;

	// tmpSt �������� ������� �� ����� �� �������, �� ������� ����� ���� ����� �������, ������������

	// ��������� ���� � ������
	if (tmpSt.empty()) 	// ���� pRoot == nullptr ����������
		pRoot = addNode;
	else if (_key < (pCurr = tmpSt.top())->rec.key) 
		pCurr->pLeft = addNode;
	else
		pCurr->pRight = addNode;
	
	++Eff;
	++DataCount;

	// ����� ������� �� ����� �� ������ ���� tmpSt, �������� ����� �������� ������ (������ -2 ��� +2)

	pPrev = addNode;

	// tmpSt �� �������� addNode
	while (!tmpSt.empty()) {
		++Eff;

		pCurr = tmpSt.top();

		if (pCurr->pLeft == pPrev) {
			--pCurr->bal;
			if (pCurr->bal == -2) {
				LeftBalance(pCurr);
				break;
			}
		}
		else {
			++pCurr->bal;
			if (pCurr->bal == +2) {
				RightBalance(pCurr);
				break;
			}
		}

		pPrev = pCurr;
		tmpSt.pop();
	}

	pCurr = nullptr;
	pPrev = nullptr;
}

/*

// ������ ���������� ���������� ����� del, ��� ����������� ���� �� ����� �� ����������� �������
void TAVLTree::DelRecord(TTreeNode*& pointer, const TKey& _key, bool& isDeleted) {
	++Eff;

	if (pointer == nullptr) return;
	else if (_key < pointer->rec.key) {
		DelRecord(pointer->pLeft, _key, isDeleted);

		// ���� isDeleted == true, �� ���� ������� ������� � ����� ���������
		pointer->bal += int(isDeleted);
		if (pointer->bal == +2) RightBalance(pointer);
	}
	else if (_key > pointer->rec.key) {
		DelRecord(pointer->pRight, _key, isDeleted);

		pointer->bal -= int(isDeleted);
		if (pointer->bal == -2) LeftBalance(pointer);
	}
}

void TAVLTree::DelRecord(const TKey& _key) {
	bool isDeleted = false;
	this->DelRecord(this->pRoot, _key, isDeleted);

	pCurr = nullptr;
	pPrev = nullptr;
}

*/

void TAVLTree::DelRecord(const TKey& _key) {
	// ����� �������, ��� �� ������ DEL-������, ������ ���� ����������������

	++Eff;

	pCurr = pRoot;
	std::stack<TTreeNode*> tmpSt;	// ����� ������� ����

	// ���������� ���� �� ��������� �������
	while (pCurr != nullptr) {
		++Eff;
		tmpSt.push(pCurr);

		if (pCurr->rec.key == _key) break;
		else if (_key < pCurr->rec.key)
			pCurr = pCurr->pLeft;
		else
			pCurr = pCurr->pRight;
	}

	if (pCurr == nullptr) return;	// ����� ������� �� ���� ����������

	// ���������� �������, ������� ���� �������

	TTreeNode* pDel = pCurr;

	bool l = pCurr->pLeft == nullptr, r = pCurr->pRight == nullptr;

	// ��� �� ��������� ������� � �����

	if (l) {			// ���� ������ �������
		tmpSt.pop();

		if (pCurr == pRoot) 
			pRoot = pRoot->pRight;
		else if ((pPrev = tmpSt.top())->pLeft == pCurr) {
			pPrev->pLeft = pCurr->pRight;
			++pPrev->pLeft->bal;
		}
		else
			pPrev->pRight = pCurr->pRight;
	}
	else if (r) {	// ��� ������� �������
		if (pCurr == pRoot) {
			pRoot = pRoot->pLeft; 
			tmpSt.pop();
		}
		else if (pPrev->pLeft == pCurr)
			pPrev->pLeft = pCurr->pLeft;
		else
			pPrev->pRight = pCurr->pLeft;
	}
	else {									// ������������ ��� �������
		pPrev = pCurr;
		pDel = pCurr->pLeft;

		while (pDel->pRight != nullptr) {
			++Eff;
			pPrev = pDel;
			pDel = pDel->pRight;
		}
		pCurr->rec = pDel->rec;
		if (pPrev == pCurr) pPrev->pLeft = pDel->pLeft;
		else pPrev->pRight = pDel->pLeft;
	}

	delete pDel;

	--DataCount;
	pCurr = nullptr;
	pPrev = nullptr;
}