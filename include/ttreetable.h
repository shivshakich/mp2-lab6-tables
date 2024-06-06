#pragma once

#include <stack>
#include "ttable.h"

// Дерево поиска - бинарное дерево, где для любой его вершины в левом поддереве находятся значения меньше, чем в этой вершине, а в правом - больше
class TTreeTable : public TTable {
protected:
	struct TTreeNode {
		TRecord rec;
		TTreeNode* pLeft = nullptr, * pRight = nullptr;
		int bal;	// для АВЛ-дерева
	};
	TTreeNode *pRoot;
	TTreeNode *pCurr, *pPrev;

	// необработанные вершины на пути от корня до текущей запоминаются в стеке
	std::stack<TTreeNode*> st;		// для обхода дерева: методы reset, gonext, isend

	void ClearStack();
	void CopyTree(const TTreeNode* const _from, TTreeNode* _to);
	void ClearTree(TTreeNode*);
	void ClearTree() { ClearTree(pRoot); }

	ostream& Print(ostream& os, TTreeNode* p, int shift) {
		if (p == nullptr) return os;

		os << '[' << shift << ']' << '\t';
		for (int i = 0; i < shift; ++i) os << ' ';
		os << p->rec.key << std::endl;

		Print(os, p->pLeft, shift + 1);
		Print(os, p->pRight, shift + 1);

		return os;
	}

public:
	TTreeTable();
	TTreeTable(const TRecord&);
	TTreeTable(const TTreeTable&);
	virtual ~TTreeTable();

	TTreeTable& operator=(const TRecord&);
	TTreeTable& operator=(const TTreeTable&);

	bool FindRecord(const TKey&) override;	// перемещает pCurr на искомую вершину
	virtual void InsRecord(const TKey&, const TValue&);
	virtual void DelRecord(const TKey&);

	// iterator methods: методы обхода - LTR

	void Reset() override;
	void GoNext() override;
	bool IsEnd() const noexcept override;

	TKey GetKey() const override;
	TValue GetValue() const override;
	void SetValue(const TValue&);

	/*
	TKey GetRootKey() const noexcept {
		if (pRoot == nullptr) return "~";
		else return pRoot->rec.key;
	}
	*/

	//friend TTreeNode& GetRootKey
	/*
	friend std::ostream& Print(const TTreeNode, std::ostream& os = std::cout, int shift = 0) {
		if ()
	}
	*/

	ostream& Print(ostream& os) override { return Print(os, pRoot, 0); }
};