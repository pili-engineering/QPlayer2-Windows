#include "PlayerUrlListModel.h"

PlayerUrlListModel::PlayerUrlListModel(QMedia::QMediaModel* pmodel, const std::string& name) :mpModel(pmodel), mName(name)
{
}

PlayerUrlListModel::~PlayerUrlListModel()
{
	if (mpModel != nullptr)
	{
		delete mpModel;
		mpModel = nullptr;
	}
}

QMedia::QMediaModel* PlayerUrlListModel::get_media_model() {
	return mpModel;
}

std::string PlayerUrlListModel::get_name() {
	return mName;
}