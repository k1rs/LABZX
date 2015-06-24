extern "C"
{
	#include "first.h"
} 

class LN_Class
{
	BigSize num;

	public:

		LN_Class();
		~LN_Class();
		LN_Class(unsigned int);
		LN_Class(char*);
		LN_Class(const LN_Class& t);

		const LN_Class operator= (const LN_Class& right); 
		const LN_Class operator+ (const LN_Class&);
		const LN_Class operator- (const LN_Class&);
		const LN_Class operator* (const LN_Class&);
		const LN_Class operator/ (const LN_Class&);
		const LN_Class operator% (const LN_Class&);
		const LN_Class operator+ (const unsigned int&);
		const LN_Class operator- (const unsigned int&);
		const LN_Class operator* (const unsigned int&);
		const LN_Class operator/ (const unsigned int&);
		const LN_Class operator% (const unsigned int&);

		const LN_Class PowMod (const LN_Class& b, const LN_Class& c);
		const LN_Class PowMod (const unsigned int& t, const LN_Class& c);
		const LN_Class PowMod (const unsigned int& t1, const unsigned int& t2);

		void ReadText (const char* filename);
		void WriteText (const char* filename);
		void ReadBin (const char* longNumFileName);
		void WriteBin (const char* longNumFileName);
		char* Print();

	private:
		void ClearMemory();
};
