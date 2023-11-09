#include "PlayerChildMenuModel.h"

PlayerChildMenuModel::PlayerChildMenuModel():mpMenus(new std::list<ChildMenu *>),mHmenu(nullptr)
{
}

PlayerChildMenuModel::~PlayerChildMenuModel()
{
	if (mpMenus != nullptr)
	{
		delete mpMenus;
		mpMenus = nullptr;
	}
}

void PlayerChildMenuModel::set_child_menus_list(std::list<ChildMenu*>* menu_list) {
	mpMenus = menu_list;
}


std::list<ChildMenu*>* PlayerChildMenuModel::get_child_menus_list() {
	return mpMenus;
}

void PlayerChildMenuModel::set_menu(HMENU menu) {
	mHmenu = menu;
}

HMENU PlayerChildMenuModel::get_menus() {
	return mHmenu;
}

ChildMenu::ChildMenu():mName(""),mId(0),mIsSelected(false)
{
}

ChildMenu::~ChildMenu()
{
}
void ChildMenu::set_name(const std::string& name) {
	mName = name;
}

std::string ChildMenu::get_name() {
	return mName;
}

void ChildMenu::set_id(int id) {
	mId = id;
}

int ChildMenu::get_id() {
	return mId;
}

void ChildMenu::set_is_selected(bool is_selected) {
	mIsSelected = is_selected;
}

bool ChildMenu::get_is_selected() {
	return mIsSelected;
}

