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
	if (pHead != NULL) //리스트가 비어있지 않으면 헤드 반환
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
	if (this->pHead == NULL) //리스트가 비어 있는 경우
	{
		pNode->SetNext(pNode); //삽입할 노드의 끝을 자신으로 연결
		pHead = pNode; //헤드가 삽입할 노드가 됨
	}
	else
	{
		epWalker = pHead;
		while (epWalker->GetNext() != pHead) //다음 노드가 헤드일 때까지 탐색
		{
			epWalker = epWalker->GetNext();
		}
		epWalker->SetNext(pNode);
		pNode->SetNext(pHead); //삽입할 노드의 다음 노드가 헤드가 됨
	}
}

Employment* List_Circular::Delete(Employment* pNode)
{
	Employment* epWalker = pHead;
	Employment* pPrev = NULL;

	
	while (epWalker->GetNext() != pHead) //다음 노드가 헤드일 때까지 탐색하면서 같은 노드 찾음
	{
		if (strcmp(epWalker->GetRegionCode(), pNode->GetRegionCode()) == 0
			&& strcmp(epWalker->GetCompany(), pNode->GetCompany()) == 0 )
			break;
		pPrev = epWalker;
		epWalker = epWalker->GetNext();
	}

	if (epWalker == pHead) //탐색한 노드가 헤드인 경우
	{
		Employment* pNew = new Employment();
		while (epWalker->GetNext() != pHead)
		{
			epWalker = epWalker->GetNext();
		}
		//헤드를 다음 노드로 옮기고 삭제하는 과정
		pNew = pHead->GetNext();
		epWalker->SetNext(pNew);
		epWalker = pHead;
		pHead = pNew;
		return epWalker;
	}
	else
	{
		pPrev->SetNext(epWalker->GetNext()); //헤드가 아니면 이전과 다음 노드를 연결해줌
		return epWalker;
	}	
}





