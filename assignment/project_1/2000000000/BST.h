#ifndef _BST_H_
#define _BST_H_

#include "Employment.h"
#include "Region.h"

class BST
{
public:
	Region* root;

public:
	BST();
	~BST();
		
	void SetRoot(Region*);
	Region* GetRoot();
	
	bool Insert(Region* rNode);
	bool Delete(Region* eNode);
	Employment* Search(char* region_code);
};
#endif