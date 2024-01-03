#pragma once
#include "../framework.h"
#include <string>
#include <list>
#include "PlayerMenuSettingModel.h"
#include "../PlayerWindow.h"
#include "CurrentDataModelManager.h"

#define ID_PLAY_CHONTROL									 1000
#define ID_RESUME_BUTTON									 1001
#define ID_PAUSE_BUTTON										 1002
#define ID_STOP_BUTTON										 1003
#define ID_RELEASE_BUTTON									 1004

#define ID_DECODER   										 1100
#define ID_AUTO_DECODER_BUTTON								 1101
#define ID_HARD_DECODER_BUTTON								 1102
#define ID_SOFT_DECODER_BUTTON								 1103

#define ID_SEEK												 1200
#define ID_SEEK_NORMAL_BUTTON								 1201
#define ID_SEEK_ACCURATE_BUTTON								 1202

#define ID_SEEK_START										 1300
#define ID_SEEK_START_PLAYING_BUTTON						 1301
#define ID_SEEK_START_PAUSE_BUTTON							 1302

#define ID_AURHENTICATION									 1400
#define ID_AURHENTICATION_BUTTON							 1401

#define ID_RENDER_RADIO										 1500
#define ID_RENDER_RADIO_AUTO_BUTTON							 1501
#define ID_RENDER_RADIO_STRETCH_BUTTON						 1502
#define ID_RENDER_RADIO_FULL_SCREEN_BUTTON					 1503
#define ID_RENDER_RADIO_16_9_BUTTON							 1504
#define ID_RENDER_RADIO_4_3_BUTTON							 1505

#define ID_BLIND											 1600
#define ID_BLIND_NONE_BUTTON								 1601
#define ID_BLIND_RED_BUTTON									 1602
#define ID_BLIND_GREEN_BUTTON								 1603
#define ID_BLIND_BLUE_BUTTON								 1604

#define ID_SEI												 1700
#define ID_SEI_OPEN_BUTTON									 1701
#define ID_SEI_CLOSE_BUTTON									 1702
	
#define ID_QUALITY_CHANGE									 1900
#define ID_QUALITY_CHANGE_IMMEDIATYLY_TRUE_BUTTON			 1901
#define ID_QUALITY_CHANGE_IMMEDIATYLY_FALSE_BUTTON			 1902
#define ID_QUALITY_CHANGE_IMMEDIATYLY_CUSTOM_BUTTON			 1903

#define ID_SUBTITLE											 2000
#define ID_SUBTITLE_CLOSE_BUTTON							 2001
#define ID_SUBTITLE_CHINESE_BUTTON							 2002
#define ID_SUBTITLE_ENGLISH_BUTTON							 2003

#define ID_PLAY_SPEED										 2100
#define ID_PLAY_SPEED_2_0_BUTTON							 2101
#define ID_PLAY_SPEED_1_5_BUTTON							 2102
#define ID_PLAY_SPEED_1_2_5_BUTTON							 2103
#define ID_PLAY_SPEED_1_0_BUTTON							 2104
#define ID_PLAY_SPEED_0_7_5_BUTTON							 2105
#define ID_PLAY_SPEED_0_5_BUTTON							 2106

#define ID_MUTE												 2200
#define ID_MUTE_OPEN_BUTTON									 2201
#define ID_MUTE_CLOSE_BUTTON								 2202

#define ID_SHOOT_IMAGE										 2300
#define ID_SHOOT_IMAGE_BUTTON								 2301

#define ID_PLAY_START_POSITION								 2400
#define ID_PLAY_START_POSITION_BUTTON						 2401

#define ID_RECORD										     2500
#define ID_RECORD_BUTTON									 2501
class PlayerMenuSettingModelManager
{
public:
	PlayerMenuSettingModelManager(HWND hwnd, PlayerWindow* pplayer_window, CurrentDataModelManager* pcurrent_data_model_manager);
	~PlayerMenuSettingModelManager();

	std::list<PlayerMenuSettingModel*>* get_menu_setting_model();

	HMENU get_child_menu_for_name(const std::string& name);

	void update_subtitle_menu_text(QMedia::QMediaModel* pmodel, HMENU subtitle_hmenu);

	void update_play_start_position_menu_text(long start_position, HMENU position_hmenu);

private:
	void add_setting_model(const std::string& menu_name,int id);

	void add_setting_child_model(std::list<ChildMenu*>* pchild_menu, int parent_menu_id);

	ChildMenu* create_child_menu(const std::string& name, int id, bool is_selected);

	std::list<ChildMenu*>* create_play_control_list();

	std::list<ChildMenu*>* create_decoder_list();

	std::list<ChildMenu*>* create_seek_list();

	std::list<ChildMenu*>* create_start_seek_list();

	std::list<ChildMenu*>* create_authentication_list();

	std::list<ChildMenu*>* create_render_radio_list();

	std::list<ChildMenu*>* create_blind_list();

	std::list<ChildMenu*>* create_sei_list();

	std::list<ChildMenu*>* create_quality_change_list();

	std::list<ChildMenu*>* create_subtitle_list();

	std::list<ChildMenu*>* create_play_speed_list();

	std::list<ChildMenu*>* create_mute_list();

	std::list<ChildMenu*>* create_shoot_list();

	std::list<ChildMenu*>* create_player_start_list();

	std::list<ChildMenu*>* create_player_record_list();


private:
	HWND mHwnd;
	PlayerWindow* mpPlayerWindow;
	std::list<PlayerMenuSettingModel*>* mpMenuSettingModels;
	CurrentDataModelManager* mpCurrentDataModelManager;
};

