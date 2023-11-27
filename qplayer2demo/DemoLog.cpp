#include "demoLog.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <windows.h>
using namespace std;
DemoLog::DemoLog()
{

}

DemoLog::~DemoLog()
{

}
void DemoLog::log_string(const char* pclass_name, int line , char* plog) {
	chrono::system_clock::time_point now_date = chrono::system_clock::now();
	time_t current_date = chrono::system_clock::to_time_t(now_date);
	tm local_date = {};
	localtime_s(&local_date, &current_date);
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "[%d-%02d-%02d %d:%d:%d] \\%s %d %s \n",local_date.tm_year + 1900,local_date.tm_mon,local_date.tm_mday,local_date.tm_hour,local_date.tm_min,local_date.tm_sec, pclass_name, line, plog);

	OutputDebugStringA(buffer);
}

void DemoLog::log_string(const char* pclass_name, int line, const char* plog) {
	chrono::system_clock::time_point now_date = chrono::system_clock::now();
	time_t current_date = chrono::system_clock::to_time_t(now_date);
	tm local_date = {};
	localtime_s(&local_date, &current_date);
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "[%d-%02d-%02d %d:%d:%d] \\%s %d %s \n", local_date.tm_year + 1900, local_date.tm_mon, local_date.tm_mday, local_date.tm_hour, local_date.tm_min, local_date.tm_sec, pclass_name, line, plog);

	OutputDebugStringA(buffer);
}