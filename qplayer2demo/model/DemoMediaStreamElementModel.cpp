#include "DemoMediaStreamElementModel.h"

DemoMediaStreamElementModel::DemoMediaStreamElementModel() :
	mBackupUrl(""),
	mHlsDrm(""),
	mIsSelected(false),
	mMp4Drm(""),
	mMp4QNDrmComkey(""),
	mMp4QNDrmFilekey(""),
	mQuality(0),
	mReferer(""),
	mUrl(""),
	mUrlType(QMedia::QUrlType::NONE),
	mUserType(""),
	mVideoType(QMedia::QVideoRenderType::NONE),
	mUrlMethod(QMedia::QUrlMethod::NORMAL)
{
}

DemoMediaStreamElementModel::~DemoMediaStreamElementModel()
{
	
}

void DemoMediaStreamElementModel::set_user_type(const std::string& user_type) {
	mUserType = user_type;
}

std::string DemoMediaStreamElementModel::get_user_type() {
	return mUserType;
}

void DemoMediaStreamElementModel::set_url(const std::string& url) {
	mUrl = url;
}

std::string DemoMediaStreamElementModel::get_url() {
	return mUrl;
}

void DemoMediaStreamElementModel::set_quality(int quality) {
	mQuality = quality;
}

int DemoMediaStreamElementModel::get_quality() {
	return mQuality;
}

void DemoMediaStreamElementModel::set_url_type(QMedia::QUrlType url_type) {
	mUrlType = url_type;
}

QMedia::QUrlType DemoMediaStreamElementModel::get_url_type() {
	return mUrlType;
}

void DemoMediaStreamElementModel::set_is_selected(bool is_selected) {
	mIsSelected = is_selected;
}

bool DemoMediaStreamElementModel::get_is_selected() {
	return mIsSelected;
}

void DemoMediaStreamElementModel::set_backup_url(const std::string& backup_url) {
	mBackupUrl = backup_url;
}

std::string DemoMediaStreamElementModel::get_backup_url() {
	return mBackupUrl;
}

void DemoMediaStreamElementModel::set_referer(const std::string& referer) {
	mReferer = referer;
}

std::string DemoMediaStreamElementModel::get_referer() {
	return mReferer;
}

void DemoMediaStreamElementModel::set_hls_drm(const std::string& hls_drm) {
	mHlsDrm = hls_drm;
}

std::string DemoMediaStreamElementModel::get_hls_drm() {
	return mHlsDrm;
}

void DemoMediaStreamElementModel::set_mp4_drm(const std::string& mp4_drm) {
	mMp4Drm = mp4_drm;
}

std::string DemoMediaStreamElementModel::get_mp4_drm() {
	return mMp4Drm;
}

void DemoMediaStreamElementModel::set_mp4_qn_drm_com_key(const std::string& mp4_qn_drm_com_key) {
	mMp4QNDrmComkey = mp4_qn_drm_com_key;
}

std::string DemoMediaStreamElementModel::get_mp4_qn_drm_com_key() {
	return mMp4QNDrmComkey;
}

void DemoMediaStreamElementModel::set_mp4_qn_drm_file_key(const std::string& mp4_qn_drm_file_key) {
	mMp4QNDrmFilekey = mp4_qn_drm_file_key;
}

std::string DemoMediaStreamElementModel::get_mp4_qn_drm_file_key() {
	return mMp4QNDrmFilekey;
}
void DemoMediaStreamElementModel::set_video_type(QMedia::QVideoRenderType video_type) {
	mVideoType = video_type;
}

QMedia::QVideoRenderType DemoMediaStreamElementModel::get_video_type() {
	return mVideoType;
}

void DemoMediaStreamElementModel::set_url_methond(QMedia::QUrlMethod url_methond) {
	mUrlMethod = url_methond;
}

QMedia::QUrlMethod DemoMediaStreamElementModel::get_url_methond() {
	return mUrlMethod;
}