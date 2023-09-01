#pragma once
#include <string>
#include "QMediaModel.h"

class PlayerUrlListModel
{
public:
	QMedia::QMediaModel* mpModel;

	const std::string mName;
public:
	PlayerUrlListModel(QMedia::QMediaModel* model, const std::string name);
	~PlayerUrlListModel();

private:

};

