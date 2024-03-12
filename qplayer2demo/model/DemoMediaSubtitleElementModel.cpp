#include "DemoMediaSubtitleElementModel.h"

DemoMediaSubtitleElementModel::DemoMediaSubtitleElementModel():
	mIsSelected(false),
	mUrl(""),
	mName("")
{
}

DemoMediaSubtitleElementModel::~DemoMediaSubtitleElementModel()
{
}


void DemoMediaSubtitleElementModel::set_is_selected(bool is_selected) {
	mIsSelected = is_selected;
}

bool DemoMediaSubtitleElementModel::get_is_selected() {
	return mIsSelected;
}

void DemoMediaSubtitleElementModel::set_url(const std::string& url) {
	mUrl = url;
}

std::string DemoMediaSubtitleElementModel::get_url() {
	return mUrl;
}

void DemoMediaSubtitleElementModel::set_name(const std::string& name) {
	mName = name;
}

std::string DemoMediaSubtitleElementModel::get_name() {
	return mName;
}