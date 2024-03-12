#pragma once
#include <string>
#include <QMediaModel.h>
class DemoMediaSubtitleElementModel
{
public:
	DemoMediaSubtitleElementModel();
	~DemoMediaSubtitleElementModel();
	void set_is_selected(bool is_selected);

	bool get_is_selected();

	void set_url(const std::string& url);

	std::string get_url();

	void set_name(const std::string& name);

	std::string get_name();
private:

	std::string mUrl;

	bool mIsSelected;

	std::string mName;
};

