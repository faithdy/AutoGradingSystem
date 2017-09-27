#include"Region.h"

Region::Region()
{
	memset(this->rCodeName.first, 0, sizeof(char) * STR_MAX);
	memset(this->rCodeName.second, 0, sizeof(char) * STR_MAX);
	this->pNext = NULL;
	this->pLeft = NULL;
	this->pRight = NULL;
	this->pDown = NULL;
}

Region::~Region()
{

}

void Region::SetRegionCode(char* region_code)
{

	strcpy(rCodeName.first,region_code);
}

void Region::SetRegionName(char* region_name)
{
	strcpy(rCodeName.second, region_name);
}

void Region::SetNext(Region* rNext)
{
	this->pNext = rNext;
}

void Region::SetLeft(Region* rLeft)
{
	this->pLeft = rLeft;
}

void Region::SetRight(Region* rRight)
{
	this->pRight = rRight;
}

void Region::SetDown(Employment* rDown)
{
	this->pDown = rDown;
}

char* Region::GetRegionCode()
{

	//cout << "GetRegionCode" << "  " << region_code << endl;
	return rCodeName.first;
}

char* Region::GetRegionName()
{
	//cout << "GetRegionName" << "  " << region_name << endl;
	return rCodeName.second;
}

Region* Region::GetNext()
{
	return pNext;
}

Region* Region::GetLeft()
{
	return pLeft;
}

Region* Region::GetRight()
{
	return pRight;
}

Employment* Region::GetDown()
{
	return pDown;
}

