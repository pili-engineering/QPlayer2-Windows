#pragma once
#include <string>
#include <QMediaModel.h>
class DemoMediaStreamElementModel
{
public:
	DemoMediaStreamElementModel();
	~DemoMediaStreamElementModel();

	void set_user_type(const std::string& user_type);

	std::string get_user_type();

	void set_url(const std::string& url);

	std::string get_url();

	void set_quality(int quality);

	int get_quality();

	void set_url_type(QMedia::QUrlType url_type);

	QMedia::QUrlType get_url_type();

	void set_is_selected(bool is_selected);

	bool get_is_selected();

	void set_backup_url(const std::string& backup_url);

	std::string get_backup_url();

	void set_referer(const std::string& referer);

	std::string get_referer();

	void set_hls_drm(const std::string& hls_drm);

	std::string get_hls_drm();

	void set_mp4_drm(const std::string& mp4_drm);

	std::string get_mp4_drm();

	void set_video_type(QMedia::QVideoRenderType video_type);

	QMedia::QVideoRenderType get_video_type();

	void set_url_methond(QMedia::QUrlMethod url_methond);

	QMedia::QUrlMethod get_url_methond();
private:
	std::string mUserType;
	std::string mUrl;
	int mQuality;
	QMedia::QUrlType mUrlType;
	bool mIsSelected;
	std::string mBackupUrl;
	std::string mReferer;
	std::string mHlsDrm;
	std::string mMp4Drm;
	QMedia::QVideoRenderType mVideoType;
	QMedia::QUrlMethod mUrlMethod;
};

