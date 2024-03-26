#pragma once

#include "QPlayerExport.h"
#include <string>
#include "QUrlType.h"
#include "QVideoRenderType.h"
#include "QUrlMethod.h"
namespace QMedia {
	class QPLAYER_API QStreamElement {
	

	private:
		QStreamElement(const std::string& user_type, QUrlType url_type,
			int32_t quality_index, const std::string& url, bool is_selected,
			const std::string& back_url, const std::string& referer, 
			QVideoRenderType video_render_type,
			const std::string& hls_drm_key,
			const std::string& mp4_drm_key,
			const std::string& mp4_qn_drm_com_key,
			const std::string& mp4_qn_drm_file_key,
			QUrlMethod url_method)
			:mUserType(user_type),
			mUrlType(url_type),
			mQualityIndex(quality_index),
			mUrl(url),
			mIsSelected(is_selected),
			mBackupUrl(back_url),
			mReferer(referer),
			mVideoRenderType(video_render_type),
			mHlsDrmKey(hls_drm_key),
			mMp4DrmKey(mp4_drm_key),
			mMp4QNDrmComKey(mp4_qn_drm_com_key),
			mMp4QNDrmFileKey(mp4_qn_drm_file_key),
			mUrlMethod(url_method)
		{}

		~QStreamElement() {}

		QStreamElement(const QStreamElement&) = delete;

		QStreamElement(QStreamElement&&) = delete;

		QStreamElement& operator=(const QStreamElement&) = delete;

		QStreamElement& operator=(QStreamElement&&) = delete;
		friend class QMediaModelBuilder;
		friend class QMediaModel;
	public:
		/// <summary>
		/// ��ȡ��ǰԪ�ص� user_type
		/// </summary>
		/// <returns></returns>
		const std::string& get_user_type() const { return mUserType; }

		/// <summary>
		/// ��ȡ��ǰԪ�ص� url_type
		/// </summary>
		/// <returns></returns>
		QUrlType get_url_type() const { return mUrlType; }

		/// <summary>
		/// ��ȡ��ǰԪ�ص�������
		/// </summary>
		/// <returns></returns>
		int32_t get_quality_index() const { return mQualityIndex; }

		/// <summary>
		/// ��ȡ��ǰԪ�ص� url
		/// </summary>
		/// <returns></returns>
		const std::string& get_url() const { return mUrl; }

		/// <summary>
		/// ��ȡ��ǰԪ�صı��� url
		/// </summary>
		/// <returns></returns>
		const std::string& get_back_url() const { return mBackupUrl; }

		/// <summary>
		/// ��ȡ��ǰԪ�ص� referer
		/// </summary>
		/// <returns></returns>
		const std::string& get_referer() const { return mReferer; }

		/// <summary>
		/// ��ȡ��ǰԪ�ص� render type                                                                             
		/// </summary>
		/// <returns></returns>
		QVideoRenderType get_render_type() const { return mVideoRenderType; }

		/// <summary>
		/// ��ȡ��ǰԪ�ص� hls key
		/// </summary>
		/// <returns></returns>
		const std::string& get_hls_drm_key() const { return mHlsDrmKey; }

		/// <summary>
		/// ��ȡ��ǰԪ�ص� mp4 key
		/// </summary>
		/// <returns></returns>
		const std::string& get_mp4_drm_key() const { return mMp4DrmKey; }

		/// <summary>
		/// ��ȡ��ǰԪ�ص� url method
		/// </summary>
		/// <returns></returns>
		QUrlMethod get_url_method() const { return mUrlMethod; }

		/// <summary>
		/// ��ȡ��ǰԪ���Ƿ�ѡ��
		/// </summary>
		/// <returns></returns>
		bool is_selected() const { return mIsSelected; }

		/// <summary>
		/// ��ȡ��ǰԪ�ص���ţ˽�� MP4 drm comkey
		/// </summary>
		/// <returns></returns>
		const std::string& get_mp4_qn_drm_com_key() const { return mMp4QNDrmComKey; }

		/// <summary>
		/// ��ȡ��ǰԪ�ص���ţ˽�� MP4 drm filekey
		/// </summary>
		/// <returns></returns>
		const std::string& get_mp4_qn_drm_file_key() const { return mMp4QNDrmFileKey; }

	private:
		std::string mUserType;
		QUrlType mUrlType;
		int32_t mQualityIndex;
		std::string mUrl;
		std::string mBackupUrl;
		std::string mReferer;
		QVideoRenderType mVideoRenderType;
		std::string mHlsDrmKey;
		std::string mMp4DrmKey;
		std::string mMp4QNDrmComKey;
		std::string mMp4QNDrmFileKey;
		bool mIsSelected;
		QUrlMethod mUrlMethod;
	};
}