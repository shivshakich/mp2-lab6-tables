#pragma once

#include "ttreetable.h"

// для работы find, ins, del; показывают изменение в высоте
//#define H_DEC -1
//#define H_OK 0
//#define H_INC 1

#define BAL_LEFT -1
#define BAL_OK 0
#define BAL_RIGHT 1

// (АВЛ - Аделльсон-Вельский, Ландие)
// Сбалансированное дерево поиска - дерево поиска, где для любой его вершины высоты левого и правого поддеревьев отличаются не более, чем на единицу
class TAVLTree : public TTreeTable {
	// для каждого узла АВЛ-дерева введём показатель баланса - разность высот правого и левого поддеревьев
	// по определению АВЛ-дерева допустимые балансы вершин: -1, 0, +1
protected:
	//TTreeNode* FindMin(TTreeNode*&);
	//void RemoveMin(TTreeNode*&);
	//int DelDel(TTreeNode*&, const TKey&);
	//void InsRecord(TTreeNode*&, const TKey&, const TValue&);
	//void DelRecord(TTreeNode*&, const TKey&);

	void LeftBalance(TTreeNode*&);
	void RightBalance(TTreeNode*&);
public:
	TAVLTree();
	TAVLTree(const TRecord&);
	TAVLTree(TTreeTable&);
	TAVLTree(const TAVLTree&);

	TAVLTree& operator=(const TRecord&);
	TAVLTree& operator=(TTreeTable&);
	TAVLTree& operator=(const TAVLTree&);

	void InsRecord(const TKey&, const TValue&) override;
	void DelRecord(const TKey&) override;
};