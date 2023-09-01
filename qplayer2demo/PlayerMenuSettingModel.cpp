#include "PlayerMenuSettingModel.h"

PlayerMenuSettingModel::PlayerMenuSettingModel()
{
}

PlayerMenuSettingModel::~PlayerMenuSettingModel()
{
	if (mpChildMenu)
	{
		delete mpChildMenu;
	}
}