#include "CurrentDataModelManager.h"

CurrentDataModelManager* CurrentDataModelManager::instance = NULL;
CurrentDataModelManager* CurrentDataModelManager::get_instance() {
	if (instance == nullptr)
	{
		instance = new CurrentDataModelManager;
	}
	return instance;
}

CurrentDataModelManager::CurrentDataModelManager()
{
	mpCurrentDataModel = new CurrentDataModel;
}

CurrentDataModelManager::~CurrentDataModelManager()
{
	if (mpCurrentDataModel != nullptr) {
		delete mpCurrentDataModel;
		mpCurrentDataModel = nullptr;
	}
}

void CurrentDataModelManager::set_duration_time(long time) {
	mpCurrentDataModel->mDurationTime = time;
}

long CurrentDataModelManager::get_duration_time() {
	return mpCurrentDataModel->mDurationTime;
}
void CurrentDataModelManager::set_player_state(QMedia::QPlayerState state) {
	mpCurrentDataModel->mPlayState = state;
}

QMedia::QPlayerState CurrentDataModelManager::get_player_state() {
	return mpCurrentDataModel->mPlayState;
}

void  CurrentDataModelManager::set_first_frame_time(long  elapsed_time) {
	mpCurrentDataModel->mFirstFrameTime = elapsed_time;
}

long CurrentDataModelManager::get_first_frame_time() {
	return mpCurrentDataModel->mFirstFrameTime;
}
void CurrentDataModelManager::set_is_seeking(bool is_seeking) {
	mpCurrentDataModel->mIsSeeking = is_seeking;
}

bool CurrentDataModelManager::get_is_seeking() {
	return mpCurrentDataModel->mIsSeeking;
}