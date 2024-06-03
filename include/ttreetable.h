#pragma once

#include <stack>
#include "ttable.h"

// ������ ������ - �������� ������, ��� ��� ����� ��� ������� � ����� ��������� ��������� �������� ������, ��� � ���� �������, � � ������ - ������
class TTreeTable : public TTable {
protected:
	struct TTreeNode {
		TRecord rec;
		TTreeNode* pLeft = nullptr, * pRight = nullptr;
		int bal;	// ��� ���-������
	};
	TTreeNode *pRoot;
	TTreeNode *pCurr, *pPrev;

	// �������������� ������� �� ���� �� ����� �� ������� ������������ � �����
	std::stack<TTreeNode*> st;		// ��� ������ ������: ������ reset, gonext, isend

	void ClearStack();
	void CopyTree(const TTreeNode* const _from, TTreeNode* _to);
	void ClearTree(TTreeNode*);
	void ClearTree() { ClearTree(pRoot); }
	ostream& Print(ostream&, TTreeNode*, int shift);
public:
	TTreeTable();
	TTreeTable(const TRecord&);
	TTreeTable(const TTreeTable&);
	virtual ~TTreeTable();

	TTreeTable& operator=(const TRecord&);
	TTreeTable& operator=(const TTreeTable&);

	bool FindRecord(const TKey&) override;	// ���������� pCurr �� ������� �������
	virtual void InsRecord(const TKey&, const TValue&);
	virtual void DelRecord(const TKey&);

	// iterator methods: ������ ������ - LTR

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
	ostream& Print(ostream& = std::cout);
};