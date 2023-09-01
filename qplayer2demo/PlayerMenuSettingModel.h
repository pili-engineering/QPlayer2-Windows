#pragma once
#include "framework.h"
#include <string>
#include "PlayerChildMenuModel.h"

class PlayerMenuSettingModel
{
public:
	PlayerMenuSettingModel();
	~PlayerMenuSettingModel();

public:
	//HMENU mHmenu;

	std::string mName;

	PlayerChildMenuModel* mpChildMenu;

	int id;
};

