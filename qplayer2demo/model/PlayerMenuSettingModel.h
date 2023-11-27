#pragma once
#include "../framework.h"
#include <string>
#include "PlayerChildMenuModel.h"

class PlayerMenuSettingModel
{
public:
	PlayerMenuSettingModel();
	~PlayerMenuSettingModel();

	void set_name(const std::string& name);

	std::string get_name();

	void set_child_menu_model(PlayerChildMenuModel* pchild_menu_model);

	PlayerChildMenuModel* get_child_menu_model();

	void set_id(int id);

	int get_id();
private:

	std::string mName;

	PlayerChildMenuModel* mpChildMenu;

	int mId;
};

