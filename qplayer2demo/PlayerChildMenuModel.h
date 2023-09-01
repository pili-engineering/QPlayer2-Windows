#pragma once
#include "framework.h"
#include <string>
#include <list>

class ChildMenu;
class PlayerChildMenuModel
{
public:
	PlayerChildMenuModel();
	~PlayerChildMenuModel();


public:
	HMENU mHmenu;

	std::list<ChildMenu*>* mpMenus;

};

class ChildMenu
{
public:
	ChildMenu();
	~ChildMenu();
public:
	std::string mName;
	
	int mId;

	bool mIsSelected;
};

