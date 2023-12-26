#pragma once
#include "CurrentDataModel.h"
#include <list>
class CurrentDataModelManager
{
public:
	//static CurrentDataModelManager* get_instance();
	CurrentDataModelManager();
	~CurrentDataModelManager();

	void set_duration_time(long time);

	long get_duration_time();

	void set_player_state(QMedia::QPlayerState state);

	QMedia::QPlayerState get_player_state();

	void set_first_frame_time(long  elapsed_time);

	long get_first_frame_time();


	void set_is_seeking(bool is_seeking);

	bool get_is_seeking();

	//void release();

	void set_decoder(QMedia::QPlayerSetting::QPlayerDecoder decoder);

	QMedia::QPlayerSetting::QPlayerDecoder get_decoder();

	void set_seek_mode(QMedia::QPlayerSetting::QPlayerSeek seek_mode);

	QMedia::QPlayerSetting::QPlayerSeek get_seek_mode();

	void set_player_start(QMedia::QPlayerSetting::QPlayerStart player_start);

	QMedia::QPlayerSetting::QPlayerStart get_player_start();

	void set_render_ratio(QMedia::QPlayerSetting::QPlayerRenderRatio render_ratio);

	QMedia::QPlayerSetting::QPlayerRenderRatio get_render_ratio();

	void set_blind(QMedia::QPlayerSetting::QPlayerBlind blind);

	QMedia::QPlayerSetting::QPlayerBlind get_blind();

	void set_sei_enable(bool sei_enable);

	bool get_sei_enable();

	void set_background_enable(bool background_enable);

	bool get_background_enable();

	void set_quality_immediatyly(QualityImmediatyly quality_immediatyly);

	QualityImmediatyly get_quality_immediatyly();

	void set_subtitle_enable(bool subtitle_enable);

	bool get_subtitle_enable();

	void set_subtitle_name(const std::string& subtitle_name);

	std::string get_subtitle_name();

	void set_play_speed(float play_speed);

	float get_play_speed();

	void set_mute_enable(bool mute_enable);

	bool get_mute_enable();

	void set_player_start_position(long player_start_position);

	long get_player_start_position();

	void set_force_authentication_enable(bool force_authentication_enable);

	bool get_force_authentication_enable();

	QMedia::QMediaModel* get_media_model();

	void set_media_model(QMedia::QMediaModel* pmodel);

	int get_quality();

	void set_quality(int quality);

private:

	//static CurrentDataModelManager* instance;

	CurrentDataModel* mpCurrentDataModel;

};

