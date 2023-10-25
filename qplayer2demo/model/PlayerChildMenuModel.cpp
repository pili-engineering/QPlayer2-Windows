#include "PlayerChildMenuModel.h"

PlayerChildMenuModel::PlayerChildMenuModel()
{
}

PlayerChildMenuModel::~PlayerChildMenuModel()
{
	if (mpMenus != nullptr && !mpMenus->empty())
	{
		for (int i = 0; i < mpMenus->size();i++)
		{
			auto it = mpMenus->begin();
			std::advance(it, i);
			delete* it;
			*it = nullptr;
		}
	}
}



ChildMenu::ChildMenu()
{
}

ChildMenu::~ChildMenu()
{
}

