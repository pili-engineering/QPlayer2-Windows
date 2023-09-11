#pragma once
#include "CurrentDataModel.h"
#include <list>
class CurrentDataModelManager
{
public:
	static CurrentDataModelManager* get_instance();

	void set_duration_time(long time);

	long get_duration_time();

	void set_player_state(QMedia::QPlayerState state);

	QMedia::QPlayerState get_player_state();

	void set_first_frame_time(long  elapsed_time);

	long get_first_frame_time();


	void set_is_seeking(bool is_seeking);

	bool get_is_seeking();



private:
	CurrentDataModelManager();
	~CurrentDataModelManager();

private:

	static CurrentDataModelManager* instance;

	CurrentDataModel* mpCurrentDataModel;

};

