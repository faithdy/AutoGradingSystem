#include "List_Circular.h"

List_Circular::List_Circular()
{
	this->pHead = NULL;
}


List_Circular::~List_Circular()
{

}


void List_Circular::SetHead(Employment* pNode)
{
	pHead = pNode;
}

Employment* List_Circular::GetHead()
{
	if (pHead != NULL) //����Ʈ�� ������� ������ ��� ��ȯ
	{
		return pHead;
	}
	else
	{
		return NULL;
	}

}

void List_Circular::Insert(Employment* pNode)
{
	
	Employment* epWalker = new Employment();
	if (this->pHead == NULL) //����Ʈ�� ��� �ִ� ���
	{
		pNode->SetNext(pNode); //������ ����� ���� �ڽ����� ����
		pHead = pNode; //��尡 ������ ��尡 ��
	}
	else
	{
		epWalker = pHead;
		while (epWalker->GetNext() != pHead) //���� ��尡 ����� ������ Ž��
		{
			epWalker = epWalker->GetNext();
		}
		epWalker->SetNext(pNode);
		pNode->SetNext(pHead); //������ ����� ���� ��尡 ��尡 ��
	}
}

Employment* List_Circular::Delete(Employment* pNode)
{
	Employment* epWalker = pHead;
	Employment* pPrev = NULL;

	
	while (epWalker->GetNext() != pHead) //���� ��尡 ����� ������ Ž���ϸ鼭 ���� ��� ã��
	{
		if (strcmp(epWalker->GetRegionCode(), pNode->GetRegionCode()) == 0
			&& strcmp(epWalker->GetCompany(), pNode->GetCompany()) == 0 )
			break;
		pPrev = epWalker;
		epWalker = epWalker->GetNext();
	}

	if (epWalker == pHead) //Ž���� ��尡 ����� ���
	{
		Employment* pNew = new Employment();
		while (epWalker->GetNext() != pHead)
		{
			epWalker = epWalker->GetNext();
		}
		//��带 ���� ���� �ű�� �����ϴ� ����
		pNew = pHead->GetNext();
		epWalker->SetNext(pNew);
		epWalker = pHead;
		pHead = pNew;
		return epWalker;
	}
	else
	{
		pPrev->SetNext(epWalker->GetNext()); //��尡 �ƴϸ� ������ ���� ��带 ��������
		return epWalker;
	}	
}





