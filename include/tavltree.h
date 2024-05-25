#pragma once

#include "ttreetable.h"

// ��� ������ find, ins, del; ���������� ��������� � ������
#define H_DEC -1
#define H_OK 0
#define H_INC 1

#define BAL_LEFT -1
#define BAL_OK 0
#define BAL_RIGHT 1

// (��� - ���������-��������, ������)
// ���������������� ������ ������ - ������ ������, ��� ��� ����� ��� ������� ������ ������ � ������� ����������� ���������� �� �����, ��� �� �������
class TAVLTree : public TTreeTable {
	// ��� ������� ���� ���-������ ����� ���������� ������� - �������� ����� ������� � ������ �����������
	// �� ����������� ���-������ ���������� ������� ������: -1, 0, +1
protected:
	TTreeNode* FindMin(TTreeNode*);
	int RemoveMin(TTreeNode*&);
	int Insert(TTreeNode*&, const TKey&, const TValue&);
	int Delete(TTreeNode*&, const TKey&);

	int LeftBalance(TTreeNode*&);
	int RightBalance(TTreeNode*&);
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