#include <iostream>
#include <STDARG.H>

using namespace std;
void OutputInfo(int num, ...)
{
	va_list arguments;
	va_start(arguments, num);
	while (num--)
	{
		char* pchData = va_arg(arguments, char*);		
		int iData = va_arg(arguments, int);
		cout << pchData << endl;
		cout << iData << endl;
	}
	va_end(arguments);
}