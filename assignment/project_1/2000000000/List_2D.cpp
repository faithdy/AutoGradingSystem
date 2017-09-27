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

void List_2D::Insert(Region* pNode) //List�� ������� ���� �Լ�
{
	int check = 0;
	Region* rpNew = new Region;
	Region* rpWalker = new Region;

	rpNew = pNode;
	rpWalker = this->pHead;

	if (pHead == NULL) //����Ʈ�� �����Ǿ� ���� ������
	{
		pHead = rpNew; //����Ʈ�� ���� ���� ���Ե� ��尡 ��
		return;
	}

	while (rpWalker) //�ߺ� ��� �ִ��� Ȯ��
	{
		if (strcmp(rpWalker->GetRegionCode(), rpNew->GetRegionCode()) == 0) //��尡 ������ ���
		{
			check++; //Ȯ�� �÷��� ���� ��Ű�� ����
			break;
		}
		rpWalker = rpWalker->GetNext(); //���� ���� �̵�
	}

	rpWalker = pHead; //walker ��� �ʱ�ȭ

	if (check == 0) //����Ʈ ���� �ߺ��Ǵ� ��尡 �������� ������ ����Ʈ�� ����
	{
		while (1)
		{
			if (rpWalker->GetNext() == NULL)
			{
				rpWalker->SetNext(rpNew); //���� ����Ʈ �������� ���ο� ��� ����
				break;
			}
			rpWalker = rpWalker->GetNext();
		}
	}
	else return; //����Ʈ ���� �ߺ��Ǵ� ��尡 �����ϸ� ����Ʈ�� �������� �ʰ� ����

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

		if (strcmp(epNew->GetRegionCode(), rpWalker->GetRegionCode()) == 0) //������ ����Ʈ�� ������ȣ�� ���� ���, ������ ����
		{

			if (rpWalker->GetDown() == NULL) //���� ����� �Ʒ��� ����Ʈ�� ���� ���
			{
				rpWalker->SetDown(epNew);
				break;
			}
			else //���� ����Ʈ�� �����ϴ� ���
			{
				epWalker = rpWalker->GetDown(); //���� ����Ʈ�� ó�� ���� ����

				//ó��
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
		else //������ ����Ʈ�� ������ȣ�� �ٸ� ���, �������� ���� ���� �̵�
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
				//������ ��� ã����
				if (strcmp(epWalker->GetCompany(), pNode->GetCompany()) == 0)
				{					
					//��尡 ó���� �ִ� ���
					if (epPrev == NULL)
					{
						rpWalker->SetDown(epWalker->GetDown());
						return true;
					}
					//��尡 ���� �ִ� ���
					else if (epPrev != NULL && epWalker->GetDown() == NULL)
					{
						epPrev->SetDown(NULL);
						return true;
					}

					//��尡 �߰��� �ִ� ���
					else
					{
						epPrev->SetDown(epWalker->GetDown());
						return true;
					}

					//��尡 �� ���� �ִ� ���, ���� ��嵵 ����Ʈ���� �����ؾ� ��
					if (epWalker->GetDown() == NULL && epPrev == NULL)
					{
						//������ ���� ��尡 ����� ��
						if (rpPrev == NULL)
						{
							pHead = rpWalker->GetNext();
							return true;
						}
						//������ ���� ��尡 �������� ���
						else if (rpPrev != NULL && rpWalker->GetNext() == NULL)
						{
							rpPrev->SetNext(NULL);
							return true;
						}
						//������ ���� ��尡 �߰��� ���
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

