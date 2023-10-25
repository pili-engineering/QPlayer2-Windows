#pragma once

#include <iostream>
#include <string>
class DemoLog
{
public:
	DemoLog();
	~DemoLog();

	static void log_string(const char* pclass_name, int line, char* plog);

	static void log_string(const char* pclass_name, int line, const char* plog);
private:

};

