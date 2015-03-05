#ifndef _STRINGUTIL
#define _STRINGUTIL
#include <string>
using namespace std;

System::String^ stdToSystem(string os);
System::String^ stdToSystem(char *os);
void systemStringtoString(System::String ^ s, string &os);
string systemToStd(System::String ^ s);
#endif