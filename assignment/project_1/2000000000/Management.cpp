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
	char* command = NULL; //�Ľ��� ��ɾ� �����ϱ� ���� ������
	char* pToken = NULL;
	char* context = NULL; //���ڿ� �Ľ��ϱ� ���� ������
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
		if (fin.eof()) //������ ���� ������
			break;

		fin.getline(buf, sizeof(buf));
		pToken = strtok(buf, " \n" );

		if (strcmp(pToken, "LOAD") == 0) //��ɾ 'LOAD'�� ���
		{
			pToken = strtok(NULL, " \n" );
			cout << "LOAD" << endl;
			LOAD(pToken);
		}
		else if (strcmp(pToken, "PRINT") == 0) //��ɾ 'PRINT'�� ���
		{
			cout << "PRINT" << endl;
			PRINT();
		}
		else if (strcmp(pToken, "FIND") == 0) //��ɾ 'FIND'�� ���
		{
			pToken = strtok(NULL, " \n" );
			cout << "FIND" << endl;
			FIND(pToken);
		}
		else if (strcmp(pToken, "UPDATE") == 0) //��ɾ 'UPDATE'�� ���
		{
			pToken = strtok(NULL, " \n" );
			cout << "UPDATE" << endl;
			UPDATE(pToken);
		}
		else if (strcmp(pToken, "DELETE") == 0) //��ɾ 'DELETE'�� ���
		{
			pToken = strtok(NULL, " \n" );
			cout << "DELETE" << endl;
			DELETE(pToken);
		}
		else if (strcmp(pToken, "EXIT") == 0) //��ɾ 'EXIT'�� ���
		{
			EXIT();
			break;
		}
		else //�־��� ��ɾ� �ܿ� �ٸ� ���
		{
			cout << "Command error." << endl;
			return false;
		}

		pToken = NULL; //��ū ������ �ʱ�ȭ
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

	//������ ���� ���� ���ڿ� �޾ƿ�
	fin.getline(buf, 512);
	fin.getline(buf, 512);
	fin.getline(buf, 512);

	/////////////////////////////////////////////////////////////////2D ��ũ�帮��Ʈ ����
	while (1)
	{
		if (fin.eof())
			break;		
		
		memset(buf, 0, 512);
		fin.getline(buf, sizeof(buf));

		Employment* epNew = new Employment;
		Region* rpNew = new Region;

		////////////�Ľ�
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
			m_2DLL->Insert(rpNew); //2D-Linked list ���ο� ����
			m_2DLL->Insert(epNew); //2D-Linked list ���ο� ����

		}
		else 
		{ 
			m_Circular->Insert(epNew);
		}

	}

	Region* rpWalker = m_2DLL->GetHead();
	while (rpWalker) //2D ��ũ�帮��Ʈ ������ �� ���� ���� BST ������
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
	fout.open("OUT_FIND.txt", ios::out | ios::binary | ios::app); //�̾ ���Ͽ� ���� ���� 'ios::app' ���� ���� �ؽ�Ʈ ����(�ؽ�Ʈ ������ ���� ����)

	memset(result, 0, sizeof(char) * 512);
	
	eTemp = m_BST->Search(region_code); //BST���� �־��� ���� �ڵ带 ���� ��尡 �����ϴ��� Ž��

	if (eTemp == NULL)
	{
		fout << "�ش� ������ ä�������� �����ϴ�.";
		fout << "\n";
	}
	else
	{

		fout << "====OUT_FIND - "<<region_code<<" ������ ä������ ���=========================\n";
		fout << "�����ڵ�,������,�����,�����ڰ�,�ٹ�����,TO\n";
		fout << "===============================================================\n";

		while (eTemp) //����� ��ȣ ���� ��尡 ���� ������
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

	//������ ���� ���� ���ڿ� �޾ƿ�
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

		////////////�Ľ�
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
			m_2DLL->Delete(epNew); //BST���� ������
			m_Circular->Insert(epNew);
		}
		else if(strcmp(epNew->GetTo(), "E") == 0)
		{
			m_2DLL->Insert(epNew); //BST���� ���Ե�
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
	fout.open("OUT_DELETE.txt", ios::out | ios::binary | ios::app); //�̾ ���Ͽ� ���� ���� 'ios::app' ���� ���� �ؽ�Ʈ ����(�ؽ�Ʈ ������ ���� ����)

	memset(result, 0, sizeof(char) * 512);

	Region* m_2DLL_head = m_2DLL->GetHead();
	Region* rpWalker = m_2DLL->GetHead();
	Region* rPrev = NULL;
	while (rpWalker) //2D ��ũ�帮��Ʈ ������ �� ���� ���� BST ������
	{
		if (strcmp(rpWalker->GetRegionCode(), region_code) == 0)
		{
			
			fout << "=======OUT_DELETE - " << region_code << " ������ ������ ä������ ���=============================\n";
			fout << "�����ڵ�,������,�����,�����ڰ�,�ٹ�����,TO\n";
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

			//BST ����
			m_BST->Delete(rpWalker);
			
			//2D Linked List ����
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
			

			fout << "=====OUT_DELETE - " << region_code << " ������ ������ ä�븶�� ���=============================\n";
			fout << "�����ڵ�,������,�����,�����ڰ�,�ٹ�����,TO\n";
			fout << "==================================================================\n";
			//Circular Linked List ����
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

	fout << "===============OUT_PRINT - ��� ������ ä������ ���===============\n";
	fout << "�����ڵ�,������,�����,�����ڰ�,�ٹ�����,TO\n";
	fout << "===================================================================\n";

	//////////////////////////////////////////////////////////////////////Inorder traversal 
	while (1)
	{
		while (rpWalker) //BST���� ���� ����Ʈ���� ��Ʈ�� ���ÿ� ����
		{
			S1.push(rpWalker);
			rpWalker = rpWalker->GetLeft();
		}
		if (S1.empty() == false) //������ ������� ������
		{
			rpWalker = S1.top(); //���ÿ��� ��� ������
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