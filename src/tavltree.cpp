#include "../include/tavltree.h"

// LEFT- AND RIGHT- BALANCE

int TAVLTree::LeftBalance(TTreeNode*& pointer) {
	// в вершине pointer баланс равен -2
	// у его потомков допустимый баланс
	// у его левого поддерева баланс либо -1, либо +1
	// может быть 0 только в случаях :
	// 1) левый потомок - лист (что нарушает условия, при которых следует вызывать LeftBalance)
	// 2) у левого потомка pointer-вершины два прямых потомка (что говорит о несбалансированности дерева ещё до вызова ins или del)

	int res = H_OK;
	++Eff;

	TTreeNode * b, * c;

	switch (pointer->bal) {
	case BAL_RIGHT: pointer->bal = BAL_OK; res = H_OK; break;
	case BAL_OK: pointer->bal = BAL_LEFT; res = H_INC; break;
	case BAL_LEFT: // нарушение баланса
		TTreeNode* b, * c;
		b = pointer->pLeft;

		switch (b->bal) {
		case BAL_LEFT:
			// однократный подъём (слева)
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

			pointer->pLeft = b->pRight;
			b->pRight = pointer;

			pointer->bal = BAL_OK;
			pointer = b;
			pointer->bal = BAL_OK;

			break;
		case BAL_RIGHT:
			// двукратный подъём (слева)
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

			c = b->pRight;

			b->pRight = c->pLeft;
			pointer->pLeft = c->pRight;
			c->pLeft = b;
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

			// высота дерева с корнем pointer была h+3, стала h+2; высота уменьшилась на 1
			break;
		default: break;
			//throw std::exception("Kak?");
		}
		
		res = H_OK;
		break;
	}

	return res;
}

int TAVLTree::RightBalance(TTreeNode*& pointer) {
	// pointer->bal == +2

	int res = H_OK;

	++Eff;

	

	switch (pointer->bal) {
	case BAL_LEFT: pointer->bal = BAL_OK; res = H_OK; break;
	case BAL_OK: pointer->bal = BAL_RIGHT; res = H_INC; break;
	case BAL_RIGHT:
		TTreeNode* b, * c;
		b = pointer->pRight;

		switch (pointer->pRight->bal) {
		case BAL_RIGHT:
			// однократный подъём (справа)

			pointer->pRight = b->pLeft;
			b->pLeft = pointer;

			pointer->bal = BAL_OK;
			pointer = b;
			pointer->bal = BAL_OK;

			break;
		case BAL_LEFT:
			// двукратный подъём (справа)

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
		default: break; // throw std::exception("Kak?"); break;
		}

		res = H_OK;
		break;
	}

	return res;
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

// INS, DEL, FINDMIN, REMOVEMIN

TTreeTable::TTreeNode* TAVLTree::FindMin(TTreeNode* pointer) {
	++Eff;

	if (pointer == nullptr) return pointer;

	while (pointer->pLeft != nullptr) {
		++Eff;
		pointer = pointer->pLeft;
	}

	return pointer;
}

// убирает, но не удаляет вершину
int TAVLTree::RemoveMin(TTreeNode*& pointer) {
	++Eff;

	int res = H_OK;

	if (pointer->pLeft == nullptr) {
		pointer = pointer->pRight;
		res = H_DEC;
	}
	else {
		res = RemoveMin(pointer->pLeft);
		if (res != H_OK)
			res = RightBalance(pointer);
	}

	return res;
}

int TAVLTree::Insert(TTreeNode*& pointer, const TKey& _key, const TValue& _val) {
	int res = H_OK;

	++Eff;

	if (pointer == nullptr) {
		pointer = new TTreeNode{ TRecord{_key, _val} };
		pointer->bal = BAL_OK;

		res = H_INC;
		++DataCount;
	}
	else if (pointer->rec.key == _key) throw std::exception("duplicate_key");
	else if (_key < pointer->rec.key) {
		int tmp = Insert(pointer->pLeft, _key, _val);
		if (tmp == H_INC) 
			res = LeftBalance(pointer);
	}
	else { // _key > pointer->rec.key
		int tmp = Insert(pointer->pRight, _key, _val);
		if (tmp == H_INC)
			res = RightBalance(pointer);
	}

	return res;
}

void TAVLTree::InsRecord(const TKey& _key, const TValue& _val) { 
	if (FindRecord(_key)) throw std::exception("duplicate_key");

	Insert(pRoot, _key, _val);
}

int TAVLTree::Delete(TTreeNode*& pointer, const TKey& _key) {
	++Eff;

	int res;

	if (pointer == nullptr) return H_OK;
	else if (_key < pointer->rec.key) {
		res = Delete(pointer->pLeft, _key);
		if (res != H_OK) res = RightBalance(pointer);
	}
	else if (_key > pointer->rec.key) {
		res = Delete(pointer->pRight, _key);
		if (res != H_OK) res = LeftBalance(pointer);
	}
	else {
		--DataCount;

		bool l = pointer->pLeft == nullptr, r = pointer->pRight == nullptr;

		if (l && r) {
			delete pointer;
			pointer = nullptr;
			res = H_DEC;
		}
		else if (r) {
			pointer->rec = pointer->pLeft->rec;
			delete pointer->pLeft;
			pointer->pLeft = nullptr;
			pointer->bal = BAL_OK;
			res = H_DEC;
		}
		else if (l) {
			pointer->rec = pointer->pRight->rec;
			delete pointer->pRight;
			pointer->pRight = nullptr;
			pointer->bal = BAL_OK;
			res = H_DEC;
		}
		else {
			TTreeNode* left = pointer->pLeft, * right = pointer->pRight;
			TTreeNode* min = FindMin(right);
			res = RemoveMin(right);
			pointer->rec = min->rec;
			delete min;
			pointer->pLeft = left;
			pointer->pRight = right;

			if (res != H_OK) res = LeftBalance(pointer);
		}
	}

	return res;
}

void TAVLTree::DelRecord(const TKey& _key) { 
	if (!FindRecord(_key)) return;
	
	Delete(pRoot, _key); 
}

/*
void TAVLTree::InsRecord(TTreeNode*& pointer, const TKey& _key, const TValue& _val) {
// вводим рекурсивно вызываемый метод ins, для запоминания пути от корня до вставляемой вершины

	++Eff;

	if (pointer == nullptr) {	// нашли место, куда вставить
		pointer = new TTreeNode{ TRecord{_key, _val}, nullptr, nullptr, BAL_OK };
		if (pointer == nullptr) throw std::exception("TabNoMem");
		++DataCount;
	}
	else if (_key == pointer->rec.key) throw std::exception("duplicate_key");
	else if (_key < pointer->rec.key) {
		this->InsRecord(pointer->pLeft, _key, _val);
		// если не выбросило исключения, значит была добавлена запись
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

/*
void TAVLTree::InsRecord(const TKey& _key, const TValue& _val) {
	// выкинет исключение если уже существует запись с ключом _key
	
	// вставляемая вершина станет листом дерева
	// с помощью рекурсивного вызыова запоминаем путь от корня до вставленной вершнины включительно
	
	// до того, как была втсавлена новая вершина, дерево было сбалансированным
	// после - либо отсалось сбалансированным, либо был нарушен баланс (стал +2 или -2) на одной из вершин, принадлежащей пути, записанном в st

	// двигаемся от вставленного листа до корня по пути

	// БУДЕМ СЧИТАТЬ, ЧТО ДО ВЫЗОВА INS-МЕТОДА, ДЕРЕВО БЫЛО СБАЛАНСИРОВАННЫМ

	++Eff;

	pCurr = pRoot;
	pPrev = nullptr;
	std::stack<TTreeNode*> tmpSt;	// будет хранить путь

	// составляем путь до вставляемой вершины
	while (pCurr != nullptr) {
		++Eff;
		tmpSt.push(pCurr);

		if (pCurr->rec.key == _key) throw std::exception("duplicate_key");
		else if (_key < pCurr->rec.key)
			pCurr = pCurr->pLeft;
		else
			pCurr = pCurr->pRight;
	}

	// не вызвалось исключение ~~> нет дублирования ключей ~~> можно вставлять новую вершину

	TTreeNode* addNode = new TTreeNode{ TRecord{_key,_val} };
	if (addNode == nullptr) throw std::exception("TabNoMem");
	addNode->bal = BAL_OK;

	// tmpSt содержит вершины от корня до вершины, от которой будет идти новая вершина, включительно

	// вставляем лист в дерево
	if (tmpSt.empty()) 	// если pRoot == nullptr изначально
		pRoot = addNode;
	else if (_key < (pCurr = tmpSt.top())->rec.key) 
		pCurr->pLeft = addNode;
	else
		pCurr->pRight = addNode;
	
	++Eff;
	++DataCount;

	// после вставки на одной из вершин пути tmpSt, возможно будет нарушена баланс (станет -2 или +2)

	pPrev = addNode;

	// tmpSt не содержит addNode
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
*/
/*

// вводим рекурсивно вызываемый метод del, для запоминания пути от корня до вставляемой вершины
void TAVLTree::DelRecord(TTreeNode*& pointer, const TKey& _key, bool& isDeleted) {
	++Eff;

	if (pointer == nullptr) return;
	else if (_key < pointer->rec.key) {
		DelRecord(pointer->pLeft, _key, isDeleted);

		// если isDeleted == true, то была удалена вершина в левом поддереве
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

/*
void TAVLTree::DelRecord(const TKey& _key) {
	// БУДЕМ СЧИТАТЬ, ЧТО ДО ВЫЗОВА DEL-МЕТОДА, ДЕРЕВО БЫЛО СБАЛАНСИРОВАННЫМ

	++Eff;

	pCurr = pRoot;
	std::stack<TTreeNode*> tmpSt;	// будет хранить путь

	// составляем путь до удаляемой вершины
	while (pCurr != nullptr) {
		++Eff;
		tmpSt.push(pCurr);

		if (pCurr->rec.key == _key) break;
		else if (_key < pCurr->rec.key)
			pCurr = pCurr->pLeft;
		else
			pCurr = pCurr->pRight;
	}

	if (pCurr == nullptr) return;	// такой вершины не было изначально

	// существует вершина, которую надо удалить

	TTreeNode* pDel = pCurr;

	bool l = pCurr->pLeft == nullptr, r = pCurr->pRight == nullptr;

	// идём от удаляемой вершины к корню

	if (l) {			// нету левого потомка
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
	else if (r) {	// нет правого потомка
		if (pCurr == pRoot) {
			pRoot = pRoot->pLeft; 
			tmpSt.pop();
		}
		else if (pPrev->pLeft == pCurr)
			pPrev->pLeft = pCurr->pLeft;
		else
			pPrev->pRight = pCurr->pLeft;
	}
	else {									// присутствуют оба потомка
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
*/