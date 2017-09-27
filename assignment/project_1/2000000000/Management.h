#ifndef _MANAGEMENT_H_
#define _MANAGEMENT_H_

#include "Employment.h"
#include "Region.h"
#include "List_2D.h"
#include "BST.h"
#include "List_Circular.h"
#include <stack>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

class Management
{
public:
	List_2D* m_2DLL;
	List_Circular* m_Circular;
	BST* m_BST;

public:
	Management();
	~Management();

	bool ReadCommand();
	bool LOAD(char* filename);
	bool UPDATE(char* filename);
	bool FIND(char* region_code);
	bool DELETE(char* region_code);
	bool PRINT();
	bool EXIT();
};
#endif