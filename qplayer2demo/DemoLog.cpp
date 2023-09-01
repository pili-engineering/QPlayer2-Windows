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
void DemoLog::log_string(const char* class_name, int line , char* log) {
	chrono::system_clock::time_point now_date = chrono::system_clock::now();
	time_t currentDate = chrono::system_clock::to_time_t(now_date);
	tm localDate = {};
	localtime_s(&localDate, &currentDate);
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "[%d-%02d-%02d %d:%d:%d] \\%s %d %s \n",localDate.tm_year + 1900,localDate.tm_mon,localDate.tm_mday,localDate.tm_hour,localDate.tm_min,localDate.tm_sec, class_name, line, log);

	OutputDebugStringA(buffer);
}

void DemoLog::log_string(const char* class_name, int line, const char* log) {
	chrono::system_clock::time_point now_date = chrono::system_clock::now();
	time_t currentDate = chrono::system_clock::to_time_t(now_date);
	tm localDate = {};
	localtime_s(&localDate, &currentDate);
	char buffer[256];
	snprintf(buffer, sizeof(buffer), "[%d-%02d-%02d %d:%d:%d] \\%s %d %s \n", localDate.tm_year + 1900, localDate.tm_mon, localDate.tm_mday, localDate.tm_hour, localDate.tm_min, localDate.tm_sec, class_name, line, log);

	OutputDebugStringA(buffer);
}