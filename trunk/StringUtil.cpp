#include "stdafx.h"
#include "StringUtil.h"
#include <string>
using namespace std;
using namespace System;

System::String^ stdToSystem(string os){ //convierte de string a System::String
	using namespace Runtime::InteropServices;
	return Marshal::PtrToStringAnsi(static_cast<IntPtr>(const_cast<char *>(os.c_str())));
}
System::String^ stdToSystem(char *os){ //convierte de string a System::String
	using namespace Runtime::InteropServices;
	return Marshal::PtrToStringAnsi(static_cast<IntPtr>(const_cast<char *>(os)));
}
void systemStringtoString(System::String ^ s, string &os) { //convierte de System::String a string
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}
string systemToStd(System::String ^ s){
	string os;
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return os;
}