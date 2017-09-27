#include "BST.h"

BST::BST()
{
	this->root = NULL;
}

BST::~BST()
{

}


void BST::SetRoot(Region* rNode)
{
	this->root = rNode;

}

Region* BST::GetRoot()
{
	return root;
}

bool BST::Insert(Region* rNode)
{
	Region* rpWalker = this->root, *pPrev = NULL;

	while (rpWalker)
	{
		pPrev = rpWalker;
		if (strcmp(rNode->GetRegionCode(), rpWalker->GetRegionCode()) == 0)  //���� �ڵ尡 ���� ��尡 �̹� �����ϸ� �������� ����
		{
			return false;
		}

		if (strcmp(rNode->GetRegionCode(), rpWalker->GetRegionCode()) < 0) rpWalker = rpWalker->GetLeft(); //������ ��尡 �� ������ ���� �ڽ� ����
		else rpWalker = rpWalker->GetRight(); //������ ��尡 �� ũ�� ������ �ڽ� ����
	}

	if (root == NULL) root = rNode; //����Ʈ�� ������ ������ ��尡 ����Ʈ�� ù��° ���
	else if (strcmp(rNode->GetRegionCode(), pPrev->GetRegionCode()) < 0) pPrev->SetLeft(rNode); //������ ��� ���� �θ� ��庸�� ������ ��������
	else pPrev->SetRight(rNode); //������ ��� ���� �θ� ��庸�� ũ�� ����������
	return true;
}

bool BST::Delete(Region* pNode)
{
	Region* pTemp = new Region();
	Region* pPrev = NULL;
	Region* ptr_1 = NULL, *ptr_2 = NULL, *ptr_3 = NULL;
	int check = 0;

	pTemp = root;
	while (pTemp && check == 0) //������ ��� ��ġ Ž��
	{
		if (strcmp(pNode->GetRegionCode(), pTemp->GetRegionCode()) == 0) check = 1; //���� �ڵ尡 ������ ���� üũ ����
		else
		{
			pPrev = pTemp;
			if (strcmp(pNode->GetRegionCode(), pTemp->GetRegionCode()) < 0) pTemp = pTemp->GetLeft(); //������ ����� ���� �� ������ ��������
			else pTemp = pTemp->GetRight(); //������ ����� ���� �� ũ�� ����������
		}
	}

	if (pTemp == NULL) return false; //������ ��尡 BST ���� �������� ������ false ��ȯ
	if (pTemp->GetLeft() == NULL) ptr_1 = pTemp->GetLeft(); //���� �ڽ� ��尡 �������� ������ ������ ��� ����Ű�� �����͸� ���� �ڽ� ���� �ű�
	else
	{
		ptr_3 = pTemp;
		ptr_1 = pTemp->GetLeft();
		ptr_2 = ptr_1->GetRight();

		while (ptr_2) //������ �Űܰ��� ���� ����Ʈ������ ���� ū ���� ���� ��� ã��
		{
			ptr_3 = ptr_1;
			ptr_1 = ptr_2;
			ptr_2 = ptr_1->GetRight();
		}

		if (ptr_3 != pTemp) //������ ��尡 ��尡 �ƴ� ��� ������ ������ִ� �ڽ� ��带 ��������
		{
			ptr_3->SetRight(ptr_1->GetLeft());
			ptr_1->SetLeft(pTemp->GetLeft());
		}
		ptr_1->SetRight(pTemp->GetRight()); //��ü ����� ������ �ڽ� ��带 ������ ����� ������ �ڽ� ���� ��������
	}

	if (pPrev == NULL) root = ptr_1; //�θ� ��尡 ������ ��ü�� ��尡 ��尡 ��
	else if (pTemp == pPrev->GetLeft()) pPrev->SetLeft(ptr_1); //������ ��尡 �� �θ� ����� ���� �ڽ� ��忴�� ���
	else pPrev->SetRight(ptr_1); //������ ��尡 �� �θ� ����� ������ �ڽ� ��忴�� ���
	return true;

}

Employment* BST::Search(char* region_code)
{
	Region* rpWalker = this->root;
	
	while (rpWalker)
	{
		if (strcmp(rpWalker->GetRegionCode(), region_code) == 0) return rpWalker->GetDown(); //���� �ڵ� ���� ��� ����� ����� ��� ��ȯ
		if (strcmp(rpWalker->GetRegionCode(), region_code) > 0) rpWalker = rpWalker->GetLeft(); //ã�� ����� ���� �� ������ ���� �ڽ� ����
		else rpWalker = rpWalker->GetRight(); //ã�� ����� ���� �� ũ�� ������ �ڽ� ����
	}

	if (rpWalker == NULL)
		return NULL;
}
