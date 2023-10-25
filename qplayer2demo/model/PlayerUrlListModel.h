#pragma once
#include <string>
#include "QMediaModel.h"

class PlayerUrlListModel
{
private:
	QMedia::QMediaModel* mpModel;

	const std::string mName;
public:
	PlayerUrlListModel(QMedia::QMediaModel* pmodel, const std::string& name);
	~PlayerUrlListModel();

	QMedia::QMediaModel* get_media_model();

	std::string get_name();
	

private:

};

