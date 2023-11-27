#pragma once
#include "../framework.h"
#include <string>
#include <list>

class ChildMenu;
class PlayerChildMenuModel
{
public:
	PlayerChildMenuModel();
	~PlayerChildMenuModel();
	

	void set_child_menus_list(std::list<ChildMenu*>* pmenu_list);

	std::list<ChildMenu*>* get_child_menus_list();

	void set_menu(HMENU menu);

	HMENU get_menus();;
private:
	HMENU mHmenu;

	std::list<ChildMenu*>* mpMenus;

};

class ChildMenu
{
public:
	ChildMenu();
	~ChildMenu();
	void set_name(const std::string& name);

	std::string get_name();

	void set_id(int id);

	int get_id();

	void set_is_selected(bool is_selected);

	bool get_is_selected();

private:
	std::string mName;
	
	int mId;

	bool mIsSelected;
};

