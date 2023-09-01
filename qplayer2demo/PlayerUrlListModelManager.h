#pragma once
#include "PlayerUrlListModel.h"
#include <string>
#include <list>
class PlayerUrlListModelManager
{
private:
	void create_url_models();
public:
	PlayerUrlListModelManager();
	~PlayerUrlListModelManager();

	void add_model(QMedia::QMediaModel* model,std::string name);

	std::list<PlayerUrlListModel*> get_url_models();

	int get_url_models_count();

	PlayerUrlListModel* get_url_model_for_index(int index);
private:
	std::list<PlayerUrlListModel*> mUrlModels;
};

