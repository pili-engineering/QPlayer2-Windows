#pragma once
#include "QPlayerExport.h"
#include "QMediaModel.h"
#include <list>
namespace QMedia {
	/// <summary>
	/// 创建视频数据模型
	/// </summary>
	class QPLAYER_API QMediaModelBuilder {

	friend class PlayerControlHandlerImpl;
	public:
		QMediaModelBuilder();

		~QMediaModelBuilder();

		QMediaModelBuilder(const QMediaModelBuilder&) = delete;

		QMediaModelBuilder(QMediaModelBuilder&&) = delete;

		QMediaModelBuilder& operator=(const QMediaModelBuilder&) = delete;

		QMediaModelBuilder& operator=(QMediaModelBuilder&&) = delete;

		/// <summary>
		/// 添加 steramElement
		/// </summary>
		/// <param name="user_type">用户自定义Type</param>
		/// <param name="url_type">媒体的资源属性 只包含视频/只包含音频/同时有视频音频</param>
		/// <param name="quality_index">清晰度</param>
		/// <param name="url">视频地址</param>
		/// <param name="is_default">是否起播时播放该流</param>
		/// <param name="referer">http/https 协议的地址 支持该属性</param>
		/// <param name="backup_url">备用地址</param>
		/// <param name="video_render_type"> 视频的渲染类型</param>
		/// <param name="url_method">播放地址类型</param>
		void add_stream_element(const std::string& user_type, QUrlType url_type, uint32_t  quality_index,
			const std::string& url, bool is_default, const std::string& referer, const std::string& backup_url,
			QVideoRenderType video_render_type, QUrlMethod url_method);

		/// <summary>
		/// 添加 steramElement
		/// </summary>
		/// <param name="user_type">用户自定义Type</param>
		/// <param name="url_type">媒体的资源属性 只包含视频/只包含音频/同时有视频音频</param>
		/// <param name="quality_index">清晰度</param>
		/// <param name="url">视频地址</param>
		/// <param name="is_default">是否起播时播放该流</param>
		/// <param name="referer">http/https 协议的地址 支持该属性</param>
		/// <param name="backup_url">备用地址</param>
		/// <param name="video_render_type"> 视频的渲染类型</param>
		/// <param name="mp4_drm_key"> MP4 drm aes-ctr解密秘钥</param>
		/// <param name="url_method">播放地址类型</param>
		void add_stream_element_mp4_drm(const std::string& user_type, QUrlType url_type, uint32_t  quality_index,
			const std::string& url, bool is_default, const std::string& referer = "", const std::string& backup_url = "",
			QVideoRenderType video_render_type = QVideoRenderType::PLANE, 
			const std::string& mp4_drm_key = "", QUrlMethod url_method = QUrlMethod::NORMAL);
		
		/// <summary>
		/// 添加 steramElement
		/// </summary>
		/// <param name="user_type">用户自定义Type</param>
		/// <param name="url_type">媒体的资源属性 只包含视频/只包含音频/同时有视频音频</param>
		/// <param name="quality_index">清晰度</param>
		/// <param name="url">视频地址</param>
		/// <param name="is_default">是否起播时播放该流</param>
		/// <param name="referer">http/https 协议的地址 支持该属性</param>
		/// <param name="backup_url">备用地址</param>
		/// <param name="video_render_type"> 视频的渲染类型</param>
		/// <param name="mp4_qn_drm_com_key">七牛私有 MP4 drm 解密 comkey 秘钥</param>
		/// <param name="mp4_qn_drm_file_key">七牛私有 MP4 drm 解密 filekey 秘钥</param>
		/// <param name="url_method">播放地址类型</param>
		void add_stream_element_qn_mp4_drm(const std::string& user_type, QUrlType url_type, uint32_t  quality_index,
			const std::string& url, bool is_default, const std::string& referer = "", const std::string& backup_url = "",
			QVideoRenderType video_render_type = QVideoRenderType::PLANE, const std::string& mp4_qn_drm_com_key = "",
			const std::string& mp4_qn_drm_file_key = "" , QUrlMethod url_method = QUrlMethod::NORMAL);

		/// <summary>
		/// 添加 steramElement
		/// </summary>
		/// <param name="user_type">用户自定义Type</param>
		/// <param name="url_type">媒体的资源属性 只包含视频/只包含音频/同时有视频音频</param>
		/// <param name="quality_index">清晰度</param>
		/// <param name="url">视频地址</param>
		/// <param name="is_default">是否起播时播放该流</param>
		/// <param name="referer">http/https 协议的地址 支持该属性</param>
		/// <param name="backup_url">备用地址</param>
		/// <param name="video_render_type"> 视频的渲染类型</param>
		/// <param name="hls_drm_key">hls 解密秘钥</param>
		/// <param name="url_method">播放地址类型</param>
		void add_stream_element_hls_drm(const std::string& user_type, QUrlType url_type, uint32_t  quality_index,
			const std::string& url, bool is_default, const std::string& referer = "", const std::string& backup_url = "",
			QVideoRenderType video_render_type = QVideoRenderType::PLANE,
			const std::string& hls_drm_key = "", QUrlMethod url_method = QUrlMethod::NORMAL);
		/**
		 * 添加 subtitleElement
		 * @param name 用户自定义Type
		 * @param url 视频地址
		 * @param isSelected 是否起播时使用该字幕
		 */
		void add_subtitle_element(const std::string& name, const std::string& url, bool is_default);

		/**
		 * 构造QMediaModel 实例
		 * @param is_live 是否是直播
		 * @return 如果返回null 说明builder 已经用过了，无法再次调用该方法
		 */
		QMediaModel* build(bool is_live, bool is_reconstruct_time_line = false);
	private:
		//内部使用的添加stream函数
		void add_stream_element_inner(const std::string& user_type, QUrlType url_type, uint32_t  quality_index,
			const std::string& url, bool is_default, const std::string& referer = "", const std::string& backup_url = "",
			QVideoRenderType video_render_type = QVideoRenderType::PLANE,
			const std::string& hls_drm_key = "", const std::string& mp4_drm_key = "", const std::string& mp4_qn_drm_com_key = "",
			const std::string& mp4_qn_drm_file_key = "", QUrlMethod url_method = QUrlMethod::NORMAL);


		std::list<QStreamElement*> mStreamElements;
		std::list<QSubtitleElement*> mSubtitleElements;
		bool mIsBuild;

	};
}