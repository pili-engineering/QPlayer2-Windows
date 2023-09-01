#include "PlayerUrlListModel.h"

PlayerUrlListModel::PlayerUrlListModel(QMedia::QMediaModel* model, const std::string name) :mpModel(model), mName(name)
{
}

PlayerUrlListModel::~PlayerUrlListModel()
{
}
