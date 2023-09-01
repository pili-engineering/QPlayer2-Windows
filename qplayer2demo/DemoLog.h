#pragma once

#include <iostream>
#include <string>
class DemoLog
{
public:
	DemoLog();
	~DemoLog();

	static void log_string(const char* class_name, int line, char* log);

	static void log_string(const char* class_name, int line, const char* log);
private:

};

