#include "List_2D.h"

List_2D::List_2D()
{
	this->pHead = NULL;
}


List_2D::~List_2D()
{

}

void List_2D::SetHead(Region* pNode)
{
	pHead = pNode;
}

Region* List_2D::GetHead()
{
	return pHead;
}

void List_2D::Insert(Region* pNode) //List의 지역노드 삽입 함수
{
	int check = 0;
	Region* rpNew = new Region;
	Region* rpWalker = new Region;

	rpNew = pNode;
	rpWalker = this->pHead;

	if (pHead == NULL) //리스트가 구성되어 있지 않으면
	{
		pHead = rpNew; //리스트의 헤드로 새로 삽입된 노드가 됨
		return;
	}

	while (rpWalker) //중복 노드 있는지 확인
	{
		if (strcmp(rpWalker->GetRegionCode(), rpNew->GetRegionCode()) == 0) //노드가 동일한 경우
		{
			check++; //확인 플래그 증가 시키고 종료
			break;
		}
		rpWalker = rpWalker->GetNext(); //다음 노드로 이동
	}

	rpWalker = pHead; //walker 노드 초기화

	if (check == 0) //리스트 내에 중복되는 노드가 존재하지 않으면 리스트에 삽입
	{
		while (1)
		{
			if (rpWalker->GetNext() == NULL)
			{
				rpWalker->SetNext(rpNew); //가로 리스트 마지막에 새로운 노드 삽입
				break;
			}
			rpWalker = rpWalker->GetNext();
		}
	}
	else return; //리스트 내에 중복되는 노드가 존재하면 리스트에 삽입하지 않고 종료

}

void List_2D::Insert(Employment* pNode)
{
	Region* rpWalker = new Region;
	Employment* epNew = new Employment;
	Employment* epWalker = new Employment;
	Employment* epPrev = NULL;
	epNew = pNode;
	rpWalker = this->pHead;

	while (rpWalker)
	{

		if (strcmp(epNew->GetRegionCode(), rpWalker->GetRegionCode()) == 0) //가로축 리스트의 지역번호와 같은 경우, 세로축 구성
		{

			if (rpWalker->GetDown() == NULL) //지역 노드의 아래로 리스트가 없는 경우
			{
				rpWalker->SetDown(epNew);
				break;
			}
			else //세로 리스트가 존재하는 경우
			{
				epWalker = rpWalker->GetDown(); //세로 리스트의 처음 노드로 설정

				//처음
				if (strcmp(epNew->GetCompany(), epWalker->GetCompany()) < 0)
				{
					epNew->SetDown(epWalker);
					rpWalker->SetDown(epNew);
				}
				else 
				{				
					while (1)
					{
						if (strcmp(epNew->GetCompany(), epWalker->GetCompany()) == 0)
							return;

						if (epWalker->GetDown() == NULL)
						{
							epWalker->SetDown(epNew);
							return;
						}

						if (strcmp(epNew->GetCompany(), epWalker->GetDown()->GetCompany()) < 0)
						{
							epNew->SetDown(epWalker->GetDown());
							epWalker->SetDown(epNew);
							return;
						}
														
						epWalker = epWalker->GetDown();
					}
				}		
			}		
							
		}
		else //가로축 리스트의 지역번호와 다른 경우, 가로축의 다음 노드로 이동
			rpWalker = rpWalker->GetNext();
	}
}

bool List_2D::Delete(Employment* pNode)
{
	
	Employment* epWalker = new Employment;
	Employment* epPrev = NULL;
	Region* rpWalker = new Region;
	Region* rpPrev = NULL;


	rpWalker = this->pHead;

	while (rpWalker)
	{
		if (strcmp(rpWalker->GetRegionCode(), pNode->GetRegionCode()) == 0)
		{
			epWalker = rpWalker->GetDown();
			while (epWalker)
			{
				//삭제할 노드 찾으면
				if (strcmp(epWalker->GetCompany(), pNode->GetCompany()) == 0)
				{					
					//노드가 처음에 있는 경우
					if (epPrev == NULL)
					{
						rpWalker->SetDown(epWalker->GetDown());
						return true;
					}
					//노드가 끝에 있는 경우
					else if (epPrev != NULL && epWalker->GetDown() == NULL)
					{
						epPrev->SetDown(NULL);
						return true;
					}

					//노드가 중간에 있는 경우
					else
					{
						epPrev->SetDown(epWalker->GetDown());
						return true;
					}

					//노드가 한 개만 있는 경우, 지역 노드도 리스트에서 삭제해야 함
					if (epWalker->GetDown() == NULL && epPrev == NULL)
					{
						//삭제할 지역 노드가 헤드일 때
						if (rpPrev == NULL)
						{
							pHead = rpWalker->GetNext();
							return true;
						}
						//삭제할 지역 노드가 마지막일 경우
						else if (rpPrev != NULL && rpWalker->GetNext() == NULL)
						{
							rpPrev->SetNext(NULL);
							return true;
						}
						//삭제할 지역 노드가 중간일 경우
						else
						{
							rpPrev->SetNext(rpWalker->GetNext());
							return true;
						}
					}
				}
				epPrev = epWalker;
				epWalker = epWalker->GetDown();

			 }
		}
		rpPrev = rpWalker;
		rpWalker = rpWalker->GetNext();

	}
}

