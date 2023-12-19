#include "CurrentDataModel.h"


CurrentDataModel::CurrentDataModel() :
	mMuteEnable(false),
	mPlayerStart(QMedia::QPlayerSetting::QPlayerStart::QPLAYER_START_SETTING_PLAYING),
	mBackgroundEnable(false),
	mBlind(QMedia::QPlayerSetting::QPlayerBlind::QPLAYER_BLIND_SETTING_NONE),
	mDecoder(QMedia::QPlayerSetting::QPlayerDecoder::QPLAYER_DECODER_SETTING_AUTO),
	mDownSpeed(0),
	mDurationTime(0),
	mFirstFrameTime(0),
	mIsSeeking(false),
	mpModel(nullptr),
	mPlaySpeed(1),
	mPlayState(QMedia::QPlayerState::NONE),
	mQualityImmediatyly(QualityImmediatyly::IMMEDIATYLY_TRUE),
	mRenderRatio(QMedia::QPlayerSetting::QPlayerRenderRatio::QPLAYER_RATIO_SETTING_AUTO),
	mSeekMode(QMedia::QPlayerSetting::QPlayerSeek::QPLAYER_SEEK_SETTING_NORMAL),
	mSEIEnable(false),
	mSubtitleEnable(false),
	mFPS(0),
	mProgressTime(0),
	mForceAuthenticationEnable(false),
	mPlayStartPosition(0),
	mQuality(0)
{
}

CurrentDataModel::~CurrentDataModel()
{
	if (mpModel != nullptr)
	{
		delete mpModel;
		mpModel = nullptr;
	}
}
void CurrentDataModel::set_progress_time(long progress) {
	mProgressTime = progress;
}

long CurrentDataModel::get_progress_time() {
	return mProgressTime;
}

void CurrentDataModel::set_duration_time(long duration) {
	mDurationTime = duration;
}

long CurrentDataModel::get_duration_time() {
	return mDurationTime;
}

void CurrentDataModel::set_model(QMedia::QMediaModel* pmodel) {
	mpModel = pmodel;
}

QMedia::QMediaModel* CurrentDataModel::get_model() {
	return mpModel;
}

void CurrentDataModel::set_player_state(QMedia::QPlayerState state) {
	mPlayState = state;
}

QMedia::QPlayerState CurrentDataModel::get_player_state() {
	return mPlayState;
}

void CurrentDataModel::set_fps(int fps) {
	mFPS = fps;
}

int CurrentDataModel::get_fps() {
	return mFPS;
}

void CurrentDataModel::set_first_frame_time(int first_frame_time) {
	mFirstFrameTime = first_frame_time;
}

int CurrentDataModel::get_first_frame_time() {
	return mFirstFrameTime;
}

void CurrentDataModel::set_down_speed(int down_speed) {
	mDownSpeed = down_speed;
}

int CurrentDataModel::get_down_speed() {
	return mDownSpeed;
}

void CurrentDataModel::set_is_seeking(bool is_seeking) {
	mIsSeeking = is_seeking;
}

bool CurrentDataModel::get_is_seeking() {
	return mIsSeeking;
}

void CurrentDataModel::set_decoder(QMedia::QPlayerSetting::QPlayerDecoder decoder) {
	mDecoder = decoder;
}

QMedia::QPlayerSetting::QPlayerDecoder CurrentDataModel::get_decoder() {
	return mDecoder;
}

void CurrentDataModel::set_seek_mode(QMedia::QPlayerSetting::QPlayerSeek seek_mode) {
	mSeekMode = seek_mode;
}

QMedia::QPlayerSetting::QPlayerSeek CurrentDataModel::get_seek_mode() {
	return mSeekMode;
}

void CurrentDataModel::set_player_start(QMedia::QPlayerSetting::QPlayerStart player_start) {
	mPlayerStart = player_start;
}

QMedia::QPlayerSetting::QPlayerStart CurrentDataModel::get_player_start() {
	return mPlayerStart;
}

void CurrentDataModel::set_render_ratio(QMedia::QPlayerSetting::QPlayerRenderRatio render_ratio) {
	mRenderRatio = render_ratio;
}

QMedia::QPlayerSetting::QPlayerRenderRatio CurrentDataModel::get_render_ratio() {
	return mRenderRatio;
}

void CurrentDataModel::set_blind(QMedia::QPlayerSetting::QPlayerBlind blind) {
	mBlind = blind;
}

QMedia::QPlayerSetting::QPlayerBlind CurrentDataModel::get_blind() {
	return mBlind;
}

void CurrentDataModel::set_sei_enable(bool sei_enable) {
	mSEIEnable = sei_enable;
}

bool CurrentDataModel::get_sei_enable() {
	return mSEIEnable;
}

void CurrentDataModel::set_background_enable(bool background_enable) {
	mBackgroundEnable = background_enable;
}

bool CurrentDataModel::get_background_enable() {
	return mBackgroundEnable;
}

void CurrentDataModel::set_quality_immediatyly(QualityImmediatyly quality_immediatyly) {
	mQualityImmediatyly = quality_immediatyly;
}

QualityImmediatyly CurrentDataModel::get_quality_immediatyly() {
	return mQualityImmediatyly;
}

void CurrentDataModel::set_subtitle_enable(bool subtitle_enable) {
	mSubtitleEnable = subtitle_enable;
}

bool CurrentDataModel::get_subtitle_enable() {
	return mSubtitleEnable;
}

void CurrentDataModel::set_subtitle_name(const std::string& subtitle_name) {
	mSubtitleName = subtitle_name;
}

std::string CurrentDataModel::get_subtitle_name() {
	return mSubtitleName;
}

void CurrentDataModel::set_play_speed(float play_speed) {
	mPlaySpeed = play_speed;
}

float CurrentDataModel::get_play_speed() {
	return mPlaySpeed;
}

void CurrentDataModel::set_mute_enable(bool mute_enable) {
	mMuteEnable = mute_enable;
}

bool CurrentDataModel::get_mute_enable() {
	return mMuteEnable;
}
void CurrentDataModel::set_player_start_position(long player_start_position) {
	mPlayStartPosition = player_start_position;
}

long CurrentDataModel::get_player_start_position() {
	return mPlayStartPosition;
}
void CurrentDataModel::set_force_authentication_enable(bool force_authentication_enable) {
	mForceAuthenticationEnable = force_authentication_enable;
}

bool CurrentDataModel::get_force_authentication_enable() {
	return mForceAuthenticationEnable;
}

int CurrentDataModel::get_quality() {
	return mQuality;
}

void CurrentDataModel::set_quality(int quality) {
	mQuality = quality;
}