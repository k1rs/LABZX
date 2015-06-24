#include "second.h"

LN_Class::~LN_Class()
{	
    if(this->num.Number != NULL)
	{
    	ClearMemory();
	}
};

LN_Class::LN_Class()
{
	this->num.Number = NULL;
	this->num.Count = 0;
}

LN_Class::LN_Class(unsigned int t)
{
	this->num = Allocate((this->num), 1);
	this->num.Number[0] = t;
}

LN_Class::LN_Class(const LN_Class& t)
{
	this->num = Copy(t.num);
}

LN_Class::LN_Class(char* str)
{
	this->num = ReadFromString(str); 	
}

const LN_Class LN_Class::operator=(const LN_Class& right)
{
	this->num = Copy(right.num);
	return *this;
}

const LN_Class LN_Class::operator+(const LN_Class& right) 
{
	LN_Class res;
	res.num = SumBigSize(this->num, right.num);
	return res;
}

const LN_Class LN_Class::operator-(const LN_Class& right) 
{
	LN_Class res;
	res.num = SubBigSize(this->num, right.num, 4294967296);
	return res;
}

const LN_Class LN_Class::operator*(const LN_Class& right) 
{
	LN_Class res;
	res.num = MulBigSize(this->num, right.num);
	return res;
}

const LN_Class LN_Class::operator/(const LN_Class& right) 
{
	LN_Class res;
	res.num = DivModBigSize(this->num, right.num, 1, 4294967296);
	return res;
}

const LN_Class LN_Class::operator%(const LN_Class& right) 
{
	LN_Class res;
	res.num = DivModBigSize(this->num, right.num, 0, 4294967296);
	return res;
}

const LN_Class LN_Class::PowMod(const LN_Class& b,const LN_Class& c)
{
	LN_Class res;
	res.num = DegBigSize(this->num, b.num, c.num);
	return res;
}

const LN_Class LN_Class::operator+(const unsigned int& t) 
{
	LN_Class res;
	LN_Class right;
	right.num = Allocate(right.num, 1);
	right.num.Number[0] = t;
	res.num = SumBigSize(this->num, right.num);
	return res;
}

const LN_Class LN_Class::operator-(const unsigned int& t) 
{
	LN_Class res;
	LN_Class right;
	right.num = Allocate(right.num, 1);
	right.num.Number[0] = t;
	res.num = SubBigSize(this->num, right.num, 4294967296);
	return res;
}

const LN_Class LN_Class::operator*(const unsigned int& t) 
{
	LN_Class res;
	res.num = MulSimpleBigSize(this->num, t, 4294967296);
	return res;
}

const LN_Class LN_Class::operator/(const unsigned int& t) 
{
	LN_Class res;
	LN_Class right;
	right.num = Allocate(right.num, 1);
	right.num.Number[0] = t;
	res.num = DivModBigSize(this->num, right.num, 1, 4294967296);
	return res;
}

const LN_Class LN_Class::operator%(const unsigned int& t) 
{
	LN_Class res;
	LN_Class right;
	right.num = Allocate(right.num, 1);
	right.num.Number[0] = t;
	res.num = DivModBigSize(this->num, right.num, 0, 4294967296);
	return res;
}

const LN_Class LN_Class::PowMod(const unsigned int& t,const LN_Class& c)
{
	LN_Class res;
	LN_Class left;
	left.num = Allocate(left.num, 1);
	left.num.Number[0] = t;
	res.num = DegBigSize(this->num, left.num, c.num);
	return res;
}

const LN_Class LN_Class::PowMod(const unsigned int& t1, const unsigned int& t2)
{
	LN_Class res;
	LN_Class left;
	left.num = Allocate(left.num, 1);
	left.num.Number[0] = t1;
	LN_Class right;
	right.num = Allocate(right.num, 1);
	right.num.Number[0] = t2;
	res.num = DegBigSize(this->num, left.num, right.num);
	return res;
}

void LN_Class::ReadText(const char* filename)
{
	LN_Class res;
	res.num = ReadTextFile(filename);
	*this = res; 
}

void LN_Class::ReadBin(const char* longNumFileName)
{
	LN_Class res;
	res.num = ReadBinFile(longNumFileName);
	*this = res;
}

void LN_Class::WriteText(const char* filename)
{
	WriteTextFile(this->num, filename);
}

void LN_Class::WriteBin(const char* longNumFileName)
{	
	WriteBinFile(this->num, longNumFileName);
}

char* LN_Class::Print()
{
	return ToString(this->num);
}

void LN_Class::ClearMemory()
{
	Clear(&(this->num));
	this->num.Number = NULL;
}


