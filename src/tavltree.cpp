#include "../include/tavltree.h"

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

