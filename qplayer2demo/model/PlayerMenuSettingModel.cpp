#include "PlayerMenuSettingModel.h"

PlayerMenuSettingModel::PlayerMenuSettingModel():mName(""),mId(0),mpChildMenu()
{
}

PlayerMenuSettingModel::~PlayerMenuSettingModel()
{
	if (mpChildMenu)
	{
		delete mpChildMenu;
	}
}

void PlayerMenuSettingModel::set_name(const std::string& name) {
	mName = name;
}

std::string PlayerMenuSettingModel::get_name() {
	return mName;
}

void PlayerMenuSettingModel::set_child_menu_model(PlayerChildMenuModel* pchild_menu_model) {
	mpChildMenu = pchild_menu_model;
}

PlayerChildMenuModel* PlayerMenuSettingModel::get_child_menu_model() {
	return mpChildMenu;
}

void PlayerMenuSettingModel::set_id(int id) {
	mId = id;
}

int PlayerMenuSettingModel::get_id() {
	return mId;
}