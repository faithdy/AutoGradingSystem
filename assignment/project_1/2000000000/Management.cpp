#include "Management.h"

Management::Management()
{
	this->m_2DLL = new List_2D();
	this->m_Circular = new List_Circular();
	this->m_BST = new BST();

	//Clear existing out file contents
	ofstream fout1, fout2, fout3;
	fout1.open("OUT_FIND.txt", ios::trunc);
	fout2.open("OUT_DELETE.txt", ios::trunc);
	fout3.open("OUT_PRINT.txt", ios::trunc);
	fout1.close();
	fout2.close();
	fout3.close();
}

Management::~Management()
{
	delete m_2DLL;
	delete m_Circular;
	delete m_BST;
}

bool Management::ReadCommand()
{
	char* command = NULL; //파싱한 명령어 저장하기 위한 포인터
	char* pToken = NULL;
	char* context = NULL; //문자열 파싱하기 위한 포인터
	char buf[512] = {};

	ifstream fin;
	fin.open("IN_Command.txt",ios::in);
	if (!fin.is_open())
	{
		cout << "Input file (command.txt) open error" << endl;
		return false;
	}		

	while (1)
	{
		if (fin.eof()) //파일이 끝날 때까지
			break;

		fin.getline(buf, sizeof(buf));
		pToken = strtok(buf, " \n" );

		if (strcmp(pToken, "LOAD") == 0) //명령어가 'LOAD'인 경우
		{
			pToken = strtok(NULL, " \n" );
			cout << "LOAD" << endl;
			LOAD(pToken);
		}
		else if (strcmp(pToken, "PRINT") == 0) //명령어가 'PRINT'인 경우
		{
			cout << "PRINT" << endl;
			PRINT();
		}
		else if (strcmp(pToken, "FIND") == 0) //명령어가 'FIND'인 경우
		{
			pToken = strtok(NULL, " \n" );
			cout << "FIND" << endl;
			FIND(pToken);
		}
		else if (strcmp(pToken, "UPDATE") == 0) //명령어가 'UPDATE'인 경우
		{
			pToken = strtok(NULL, " \n" );
			cout << "UPDATE" << endl;
			UPDATE(pToken);
		}
		else if (strcmp(pToken, "DELETE") == 0) //명령어가 'DELETE'인 경우
		{
			pToken = strtok(NULL, " \n" );
			cout << "DELETE" << endl;
			DELETE(pToken);
		}
		else if (strcmp(pToken, "EXIT") == 0) //명령어가 'EXIT'인 경우
		{
			EXIT();
			break;
		}
		else //주어진 명령어 외에 다른 경우
		{
			cout << "Command error." << endl;
			return false;
		}

		pToken = NULL; //토큰 포인터 초기화
	}
	

	if (fin.is_open() == true)
	{
		fin.close();
	}

	return true;
}

bool Management::LOAD(char* filename)
{
	char* pToken = NULL, *context = NULL;
	char buf[512] = {};
	ifstream fin;
	fin.open(filename);

	if (!fin.is_open())
	{
		cout << "'" << filename << "' file open error" << endl;
		return false;
	}

	//정보와 관련 없는 문자열 받아옴
	fin.getline(buf, 512);
	fin.getline(buf, 512);
	fin.getline(buf, 512);

	/////////////////////////////////////////////////////////////////2D 링크드리스트 연결
	while (1)
	{
		if (fin.eof())
			break;		
		
		memset(buf, 0, 512);
		fin.getline(buf, sizeof(buf));

		Employment* epNew = new Employment;
		Region* rpNew = new Region;

		////////////파싱
		pToken = strtok(buf, "," );
		epNew->SetRegionCode(pToken);
		rpNew->SetRegionCode(pToken);

		pToken = strtok(NULL, "," );
		epNew->SetRegionName(pToken);
		rpNew->SetRegionName(pToken);

		pToken = strtok(NULL, "," );
		epNew->SetCompany(pToken);
		
		pToken = strtok(NULL, "," );
		epNew->SetQualification(pToken);

		pToken = strtok(NULL, "," );
		epNew->SetWorkingCondition(pToken);

		pToken = strtok(NULL, "," );
		epNew->SetTo(pToken);

		if (strcmp(epNew->GetTo(),"E") == 0)
		{
			m_2DLL->Insert(rpNew); //2D-Linked list 가로에 삽입
			m_2DLL->Insert(epNew); //2D-Linked list 세로에 삽입

		}
		else 
		{ 
			m_Circular->Insert(epNew);
		}

	}

	Region* rpWalker = m_2DLL->GetHead();
	while (rpWalker) //2D 링크드리스트 구성한 후 같은 노드로 BST 구성함
	{
		m_BST->Insert(rpWalker);
		rpWalker = rpWalker->GetNext();
	}

	return true;
}


bool Management::FIND(char* region_code)
{
	Employment* eTemp = new Employment();
	char result[512];
	char *pToken = NULL, *context = NULL;
	int len = 0;
	int i = 0;
	ofstream fout;
	fout.open("OUT_FIND.txt", ios::out | ios::binary | ios::app); //이어서 파일에 쓰기 위해 'ios::app' 파일 모드로 텍스트 열기(텍스트 없으면 새로 생성)

	memset(result, 0, sizeof(char) * 512);
	
	eTemp = m_BST->Search(region_code); //BST에서 주어진 지역 코드를 갖는 노드가 존재하는지 탐색

	if (eTemp == NULL)
	{
		fout << "해당 지역에 채용정보가 없습니다.";
		fout << "\n";
	}
	else
	{

		fout << "====OUT_FIND - "<<region_code<<" 지역의 채용중인 기업=========================\n";
		fout << "지역코드,지역명,기업명,지원자격,근무조건,TO\n";
		fout << "===============================================================\n";

		while (eTemp) //운송장 번호 갖는 노드가 없을 때까지
		{
			fout << eTemp->GetRegionCode() << "," << eTemp->GetRegionName()
				<< "," << eTemp->GetCompany() << "," << eTemp->GetQualification()
				<< "," << eTemp->GetWorkingCondition() << "," << eTemp->GetTo() << endl;

			cout << eTemp->GetRegionCode() << "," << eTemp->GetRegionName()
				<< "," << eTemp->GetCompany() << "," << eTemp->GetQualification()
				<< "," << eTemp->GetWorkingCondition() << "," << eTemp->GetTo() << endl;

			eTemp = eTemp->GetDown();

		}

		fout << "\n";

	}

	if (fout.is_open() == true)
	{
		fout.close();
	}

	return true;
}

bool Management::UPDATE(char* filename)
{
	char* pToken = NULL, *context = NULL;
	char buf[512] = {};
	ifstream fin;
	fin.open(filename);


	if (!fin.is_open())
	{
		cout << "'" << filename << "' file open error" << endl;
		return false;
	}

	//정보와 관련 없는 문자열 받아옴
	fin.getline(buf, 512);
	fin.getline(buf, 512);
	fin.getline(buf, 512);
	while (1)
	{
		if (fin.eof())
			break;

		memset(buf, 0, 512);
		fin.getline(buf, sizeof(buf));

		
		Employment* epNew = new Employment;
		Region* rpNew = new Region;
		Region* rpHead = new Region;
		rpHead = m_BST->GetRoot();

		////////////파싱
		pToken = strtok(buf, "," );
		epNew->SetRegionCode(pToken);
		rpNew->SetRegionCode(pToken);

		pToken = strtok(NULL, "," );
		epNew->SetRegionName(pToken);
		rpNew->SetRegionName(pToken);

		pToken = strtok(NULL, "," );
		epNew->SetCompany(pToken);

		pToken = strtok(NULL, "," );
		epNew->SetQualification(pToken);

		pToken = strtok(NULL, "," );
		epNew->SetWorkingCondition(pToken);

		pToken = strtok(NULL, "," );
		epNew->SetTo(pToken);
	
		////////////////////////////////////////
		
		if (strcmp(epNew->GetTo(), "NE") == 0)
		{
			m_2DLL->Delete(epNew); //BST까지 지워짐
			m_Circular->Insert(epNew);
		}
		else if(strcmp(epNew->GetTo(), "E") == 0)
		{
			m_2DLL->Insert(epNew); //BST까지 삽입됨
			m_Circular->Delete(epNew);
		}		
		
	}

	if (fin.is_open() == true)
	{
		fin.close();
	}

	return true;
}


bool Management::DELETE(char* region_code)
{
	Employment* eTemp = new Employment();
	char result[512];
	char *pToken = NULL, *context = NULL;
	int len = 0;
	int i = 0;
	ofstream fout;
	fout.open("OUT_DELETE.txt", ios::out | ios::binary | ios::app); //이어서 파일에 쓰기 위해 'ios::app' 파일 모드로 텍스트 열기(텍스트 없으면 새로 생성)

	memset(result, 0, sizeof(char) * 512);

	Region* m_2DLL_head = m_2DLL->GetHead();
	Region* rpWalker = m_2DLL->GetHead();
	Region* rPrev = NULL;
	while (rpWalker) //2D 링크드리스트 구성한 후 같은 노드로 BST 구성함
	{
		if (strcmp(rpWalker->GetRegionCode(), region_code) == 0)
		{
			
			fout << "=======OUT_DELETE - " << region_code << " 지역의 삭제된 채용중인 기업=============================\n";
			fout << "지역코드,지역명,기업명,지원자격,근무조건,TO\n";
			fout << "==================================================================\n";
			
			Employment* eTemp = rpWalker->GetDown();

			while (eTemp)
			{
				fout << eTemp->GetRegionCode() << "," << eTemp->GetRegionName()
					<< "," << eTemp->GetCompany() << "," << eTemp->GetQualification()
					<< "," << eTemp->GetWorkingCondition() << "," << eTemp->GetTo() << endl;

				eTemp = eTemp->GetDown();

			}
			fout << "\n";

			//BST 삭제
			m_BST->Delete(rpWalker);
			
			//2D Linked List 삭제
			if (rPrev == NULL)  
			{
				m_2DLL->SetHead(rpWalker->GetNext());
			}
			else if (rPrev != NULL && rpWalker->GetNext() == NULL)
			{
				rPrev->SetNext(NULL);
			}
			else
			{
				rPrev->SetNext(rpWalker->GetNext());
			}
			

			fout << "=====OUT_DELETE - " << region_code << " 지역의 삭제된 채용마감 기업=============================\n";
			fout << "지역코드,지역명,기업명,지원자격,근무조건,TO\n";
			fout << "==================================================================\n";
			//Circular Linked List 삭제
			Employment* eTemp2 = new Employment;
			eTemp2 = m_Circular->GetHead();
			while (eTemp2->GetNext() != m_Circular->GetHead())
			{
				if (strcmp(eTemp2->GetRegionCode(), region_code) == 0)
				{
					fout << eTemp2->GetRegionCode() << "," << eTemp2->GetRegionName()
						 << "," << eTemp2->GetCompany() << "," << eTemp2->GetQualification()
						 << "," << eTemp2->GetWorkingCondition() << "," << eTemp2->GetTo() << endl;
										
					m_Circular->Delete(eTemp2);
				}
					

				eTemp2 = eTemp2->GetNext();
			}

			break;
		}
		rPrev = rpWalker;
		rpWalker = rpWalker->GetNext();
	}
	
	if (fout.is_open() == true)
	{
		fout.close();
	}

	return true;
}

bool Management::PRINT()
{
	stack<Region*> S1;
	Region* rpWalker = m_2DLL->GetHead();
	Employment* epWalker = m_Circular->GetHead();
	Employment* epTemp = NULL;
	char result[512];
	//int len = 0;
	//int i = 0;
	
	memset(result, 0, 512);
	ofstream fout;
	fout.open("OUT_PRINT.txt", ios::out | ios::binary | ios::app);

	fout << "===============OUT_PRINT - 모든 지역의 채용중인 기업===============\n";
	fout << "지역코드,지역명,기업명,지원자격,근무조건,TO\n";
	fout << "===================================================================\n";

	//////////////////////////////////////////////////////////////////////Inorder traversal 
	while (1)
	{
		while (rpWalker) //BST에서 왼쪽 서브트리의 루트를 스택에 넣음
		{
			S1.push(rpWalker);
			rpWalker = rpWalker->GetLeft();
		}
		if (S1.empty() == false) //스택이 비어있지 않으면
		{
			rpWalker = S1.top(); //스택에서 노드 꺼내옴
			S1.pop();
			epTemp = rpWalker->GetDown();
			while (epTemp)
			{
				fout << epTemp->GetRegionCode() << "," << epTemp->GetRegionName()
					<< "," << epTemp->GetCompany() << "," << epTemp->GetQualification()
					<< "," << epTemp->GetWorkingCondition() << "," << epTemp->GetTo() << endl;

				cout << epTemp->GetRegionCode() << "," << epTemp->GetRegionName()
					<< "," << epTemp->GetCompany() << "," << epTemp->GetQualification()
					<< "," << epTemp->GetWorkingCondition() << "," << epTemp->GetTo() << endl;

				epTemp = epTemp->GetDown();
			}
			rpWalker = rpWalker->GetRight();
		}
		else
			break;
	}

	if (fout.is_open() == true)
	{
		fout.close();
	}
	return true;
}

bool Management::EXIT()
{
	return true;
}