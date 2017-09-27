#include "Employment.h"

Employment::Employment()
{
	memset(this->rCodeName.first, 0, sizeof(char) * STR_MAX);
	memset(this->rCodeName.second, 0, sizeof(char) * STR_MAX);
	memset(this->company, 0, sizeof(char) * STR_MAX);
	memset(this->qualification, 0, sizeof(char) * STR_MAX);
	memset(this->working_condition, 0, sizeof(char) * STR_MAX);
	memset(this->to, 0, sizeof(char) * STR_MAX);
	this->pDown = NULL;
	this->pNext = NULL;
}

Employment::~Employment()
{

}

void Employment::SetRegionCode(char* region_code)
{
	strcpy(rCodeName.first, region_code);

}

void Employment::SetRegionName(char* region_name)
{
	strcpy(rCodeName.second, region_name);
}

void Employment::SetCompany(char* company)
{
	
	strcpy(this->company, company);

}

void Employment::SetQualification(char* qualification)
{
	strcpy(this->qualification, qualification);

}

void Employment::SetWorkingCondition(char* working_condition)
{
	strcpy(this->working_condition, working_condition);

}

void Employment::SetTo(char* to)
{
	strcpy(this->to, to);

}

void Employment::SetDown(Employment* pDown)
{
	this->pDown = pDown;
}

void Employment::SetNext(Employment* pNext)
{
	this->pNext = pNext;
}

char* Employment::GetRegionCode()
{
	return rCodeName.first;
}

char* Employment::GetRegionName()
{
	return rCodeName.second;
}

char* Employment::GetCompany()
{
	return company;
}

char* Employment::GetQualification()
{
	return qualification;
}

char* Employment::GetWorkingCondition()
{
	return working_condition;
}

char* Employment::GetTo()
{
	return to;
}

Employment* Employment::GetDown()
{
	return pDown;
}

Employment* Employment::GetNext()
{
	return pNext;
}



