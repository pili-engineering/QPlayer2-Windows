#include "CurrentDataModelManager.h"
#include "../FileOfWriteAndRead.h"
#include <iostream>
#include <sstream>
#include <iomanip>

#define SETTING_LOCAL_FILE_NAME "Setting.json"
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
	mpCurrentDataModel = FileOfWriteAndRead::read_setting_local_file(SETTING_LOCAL_FILE_NAME);

}

CurrentDataModelManager::~CurrentDataModelManager()
{
	if (mpCurrentDataModel != nullptr) {
		delete mpCurrentDataModel;
		mpCurrentDataModel = nullptr;
	}
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

void CurrentDataModelManager::set_duration_time(long time) {
	mpCurrentDataModel->set_duration_time(time);
}

long CurrentDataModelManager::get_duration_time() {
	return mpCurrentDataModel->get_duration_time();
}
void CurrentDataModelManager::set_player_state(QMedia::QPlayerState state) {
	mpCurrentDataModel->set_player_state(state);
}

QMedia::QPlayerState CurrentDataModelManager::get_player_state() {
	return mpCurrentDataModel->get_player_state();
}

void  CurrentDataModelManager::set_first_frame_time(long  elapsed_time) {
	mpCurrentDataModel->set_first_frame_time(elapsed_time);
}

long CurrentDataModelManager::get_first_frame_time() {
	return mpCurrentDataModel->get_first_frame_time();
}
void CurrentDataModelManager::set_is_seeking(bool is_seeking) {
	mpCurrentDataModel->set_is_seeking(is_seeking);
}

bool CurrentDataModelManager::get_is_seeking() {
	return mpCurrentDataModel->get_is_seeking();
}

void CurrentDataModelManager::set_decoder(QMedia::QPlayerSetting::QPlayerDecoder decoder) {
	mpCurrentDataModel->set_decoder(decoder);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

QMedia::QPlayerSetting::QPlayerDecoder CurrentDataModelManager::get_decoder() {
	return mpCurrentDataModel->get_decoder();
}

void CurrentDataModelManager::set_seek_mode(QMedia::QPlayerSetting::QPlayerSeek seek_mode) {
	mpCurrentDataModel->set_seek_mode(seek_mode);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

QMedia::QPlayerSetting::QPlayerSeek CurrentDataModelManager::get_seek_mode() {
	return mpCurrentDataModel->get_seek_mode();
}

void CurrentDataModelManager::set_player_start(QMedia::QPlayerSetting::QPlayerStart player_start) {
	mpCurrentDataModel->set_player_start(player_start);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

QMedia::QPlayerSetting::QPlayerStart CurrentDataModelManager::get_player_start() {
	return mpCurrentDataModel->get_player_start();
}

void CurrentDataModelManager::set_render_ratio(QMedia::QPlayerSetting::QPlayerRenderRatio render_ratio) {
	mpCurrentDataModel->set_render_ratio(render_ratio);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

QMedia::QPlayerSetting::QPlayerRenderRatio CurrentDataModelManager::get_render_ratio() {
	return mpCurrentDataModel->get_render_ratio();
}

void CurrentDataModelManager::set_blind(QMedia::QPlayerSetting::QPlayerBlind blind) {
	mpCurrentDataModel->set_blind(blind);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

QMedia::QPlayerSetting::QPlayerBlind CurrentDataModelManager::get_blind() {
	return mpCurrentDataModel->get_blind();
}

void CurrentDataModelManager::set_sei_enable(bool sei_enable) {
	mpCurrentDataModel->set_sei_enable(sei_enable);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

bool CurrentDataModelManager::get_sei_enable() {
	return mpCurrentDataModel->get_sei_enable();
}

void CurrentDataModelManager::set_background_enable(bool background_enable) {
	mpCurrentDataModel->set_background_enable(background_enable);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

bool CurrentDataModelManager::get_background_enable() {
	return mpCurrentDataModel->get_background_enable();
}

void CurrentDataModelManager::set_quality_immediatyly(QualityImmediatyly quality_immediatyly) {
	mpCurrentDataModel->set_quality_immediatyly(quality_immediatyly);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

QualityImmediatyly CurrentDataModelManager::get_quality_immediatyly() {
	return mpCurrentDataModel->get_quality_immediatyly();
}

void CurrentDataModelManager::set_subtitle_enable(bool subtitle_enable) {
	mpCurrentDataModel->set_subtitle_enable(subtitle_enable);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

bool CurrentDataModelManager::get_subtitle_enable() {
	return mpCurrentDataModel->get_subtitle_enable();
}

void CurrentDataModelManager::set_subtitle_name(const std::string& subtitle_name) {
	mpCurrentDataModel->set_subtitle_name(subtitle_name);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

std::string CurrentDataModelManager::get_subtitle_name() {
	return mpCurrentDataModel->get_subtitle_name();
}

void CurrentDataModelManager::set_play_speed(float play_speed) {
	mpCurrentDataModel->set_play_speed(play_speed);
	//保留两位小数
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << play_speed;
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

float CurrentDataModelManager::get_play_speed() {
	return mpCurrentDataModel->get_play_speed();
}

void CurrentDataModelManager::set_mute_enable(bool mute_enable) {
	mpCurrentDataModel->set_mute_enable(mute_enable);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

bool CurrentDataModelManager::get_mute_enable() {
	return mpCurrentDataModel->get_mute_enable();
}

void CurrentDataModelManager::set_player_start_position(long player_start_position) {
	mpCurrentDataModel->set_player_start_position(player_start_position);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

long CurrentDataModelManager::get_player_start_position() {
	return mpCurrentDataModel->get_player_start_position();
}

void CurrentDataModelManager::set_force_authentication_enable(bool force_authentication_enable) {
	mpCurrentDataModel->set_force_authentication_enable(force_authentication_enable);
	FileOfWriteAndRead::write_setting_local_file(SETTING_LOCAL_FILE_NAME, mpCurrentDataModel);
}

bool CurrentDataModelManager::get_force_authentication_enable() {
	return mpCurrentDataModel->get_force_authentication_enable();
}

QMedia::QMediaModel* CurrentDataModelManager::get_media_model() {
	return mpCurrentDataModel->get_model();
}

void CurrentDataModelManager::set_media_model(QMedia::QMediaModel* pmodel) {
	 mpCurrentDataModel->set_model(pmodel);
}
int CurrentDataModelManager::get_quality() {
	return mpCurrentDataModel->get_quality();
}

void CurrentDataModelManager::set_quality(int quality) {
	mpCurrentDataModel->set_quality(quality);
}