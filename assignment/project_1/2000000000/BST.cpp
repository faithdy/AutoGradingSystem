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
		if (strcmp(rNode->GetRegionCode(), rpWalker->GetRegionCode()) == 0)  //지역 코드가 같은 노드가 이미 존재하면 삽입하지 않음
		{
			return false;
		}

		if (strcmp(rNode->GetRegionCode(), rpWalker->GetRegionCode()) < 0) rpWalker = rpWalker->GetLeft(); //삽입할 노드가 더 작으면 왼쪽 자식 노드로
		else rpWalker = rpWalker->GetRight(); //삽입할 노드가 더 크면 오른쪽 자식 노드로
	}

	if (root == NULL) root = rNode; //리스트가 없으면 삽입할 노드가 리스트의 첫번째 노드
	else if (strcmp(rNode->GetRegionCode(), pPrev->GetRegionCode()) < 0) pPrev->SetLeft(rNode); //삽입할 노드 값이 부모 노드보다 작으면 왼쪽으로
	else pPrev->SetRight(rNode); //삽입할 노드 값이 부모 노드보다 크면 오른쪽으로
	return true;
}

bool BST::Delete(Region* pNode)
{
	Region* pTemp = new Region();
	Region* pPrev = NULL;
	Region* ptr_1 = NULL, *ptr_2 = NULL, *ptr_3 = NULL;
	int check = 0;

	pTemp = root;
	while (pTemp && check == 0) //삭제할 노드 위치 탐색
	{
		if (strcmp(pNode->GetRegionCode(), pTemp->GetRegionCode()) == 0) check = 1; //지역 코드가 같으면 변수 체크 해줌
		else
		{
			pPrev = pTemp;
			if (strcmp(pNode->GetRegionCode(), pTemp->GetRegionCode()) < 0) pTemp = pTemp->GetLeft(); //삭제할 노드의 값이 더 작으면 왼쪽으로
			else pTemp = pTemp->GetRight(); //삭제할 노드의 값이 더 크면 오른쪽으로
		}
	}

	if (pTemp == NULL) return false; //삭제할 노드가 BST 내에 존재하지 않으면 false 반환
	if (pTemp->GetLeft() == NULL) ptr_1 = pTemp->GetLeft(); //왼쪽 자식 노드가 존재하지 않으면 삭제할 노드 가리키는 포인터를 왼쪽 자식 노드로 옮김
	else
	{
		ptr_3 = pTemp;
		ptr_1 = pTemp->GetLeft();
		ptr_2 = ptr_1->GetRight();

		while (ptr_2) //포인터 옮겨가며 왼쪽 서브트리에서 가장 큰 값을 갖는 노드 찾음
		{
			ptr_3 = ptr_1;
			ptr_1 = ptr_2;
			ptr_2 = ptr_1->GetRight();
		}

		if (ptr_3 != pTemp) //삭제할 노드가 헤드가 아닌 경우 이전에 연결되있던 자식 노드를 연결해줌
		{
			ptr_3->SetRight(ptr_1->GetLeft());
			ptr_1->SetLeft(pTemp->GetLeft());
		}
		ptr_1->SetRight(pTemp->GetRight()); //대체 노드의 오른쪽 자식 노드를 삭제할 노드의 오른쪽 자식 노드로 연결해줌
	}

	if (pPrev == NULL) root = ptr_1; //부모 노드가 없으면 대체할 노드가 헤드가 됨
	else if (pTemp == pPrev->GetLeft()) pPrev->SetLeft(ptr_1); //삭제할 노드가 그 부모 노드의 왼쪽 자식 노드였던 경우
	else pPrev->SetRight(ptr_1); //삭제할 노드가 그 부모 노드의 오른쪽 자식 노드였던 경우
	return true;

}

Employment* BST::Search(char* region_code)
{
	Region* rpWalker = this->root;
	
	while (rpWalker)
	{
		if (strcmp(rpWalker->GetRegionCode(), region_code) == 0) return rpWalker->GetDown(); //지역 코드 같은 경우 연결된 운송장 노드 반환
		if (strcmp(rpWalker->GetRegionCode(), region_code) > 0) rpWalker = rpWalker->GetLeft(); //찾을 노드의 값이 더 작으면 왼쪽 자식 노드로
		else rpWalker = rpWalker->GetRight(); //찾을 노드의 값이 더 크면 오른쪽 자식 노드로
	}

	if (rpWalker == NULL)
		return NULL;
}
