#pragma once

#include <stack>
#include "ttable.h"

// ������ ������ - �������� ������, ��� ��� ����� ��� ������� � ����� ��������� ��������� �������� ������, ��� � ���� �������, � � ������ - ������
class TTreeTable : public TTable {
protected:
	struct TTreeNode {
		TRecord rec;
		TTreeNode* pLeft = nullptr, * pRight = nullptr;
	};
	TTreeNode *pRoot;
	TTreeNode *pCurr, *pPrev;

	// �������������� ������� �� ���� �� ����� �� ������� ������������ � �����
	std::stack<TTreeNode*> st;		// ��� ������ ������

	void ClearStack();
	void CopyTree(const TTreeNode* const _from, TTreeNode* _to);
	void ClearTree(TTreeNode*);
	void ClearTree() { ClearTree(pRoot); }
	ostream& Print(ostream&, TTreeNode*);
public:
	TTreeTable();
	TTreeTable(const TRecord&);
	TTreeTable(const TTreeTable&);
	virtual ~TTreeTable();

	TTreeTable& operator=(const TRecord&);
	TTreeTable& operator=(const TTreeTable&);

	bool FindRecord(const TKey&) override;
	virtual void InsRecord(const TKey&, const TValue&);
	virtual void DelRecord(const TKey&);

	// iterator methods: ������ ������ - LTR

	void Reset();
	void GoNext();
	bool IsEnd() const noexcept;

	TKey GetKey() const override;
	TValue GetValue() const override;
	void SetValue(const TValue&);

	ostream& Print(ostream& = std::cout);
};