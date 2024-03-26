#pragma once
#include "QPlayerExport.h"
#include "QMediaModel.h"
#include <list>
namespace QMedia {
	/// <summary>
	/// ������Ƶ����ģ��
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
		/// ��� steramElement
		/// </summary>
		/// <param name="user_type">�û��Զ���Type</param>
		/// <param name="url_type">ý�����Դ���� ֻ������Ƶ/ֻ������Ƶ/ͬʱ����Ƶ��Ƶ</param>
		/// <param name="quality_index">������</param>
		/// <param name="url">��Ƶ��ַ</param>
		/// <param name="is_default">�Ƿ���ʱ���Ÿ���</param>
		/// <param name="referer">http/https Э��ĵ�ַ ֧�ָ�����</param>
		/// <param name="backup_url">���õ�ַ</param>
		/// <param name="video_render_type"> ��Ƶ����Ⱦ����</param>
		/// <param name="url_method">���ŵ�ַ����</param>
		void add_stream_element(const std::string& user_type, QUrlType url_type, uint32_t  quality_index,
			const std::string& url, bool is_default, const std::string& referer, const std::string& backup_url,
			QVideoRenderType video_render_type, QUrlMethod url_method);

		/// <summary>
		/// ��� steramElement
		/// </summary>
		/// <param name="user_type">�û��Զ���Type</param>
		/// <param name="url_type">ý�����Դ���� ֻ������Ƶ/ֻ������Ƶ/ͬʱ����Ƶ��Ƶ</param>
		/// <param name="quality_index">������</param>
		/// <param name="url">��Ƶ��ַ</param>
		/// <param name="is_default">�Ƿ���ʱ���Ÿ���</param>
		/// <param name="referer">http/https Э��ĵ�ַ ֧�ָ�����</param>
		/// <param name="backup_url">���õ�ַ</param>
		/// <param name="video_render_type"> ��Ƶ����Ⱦ����</param>
		/// <param name="mp4_drm_key"> MP4 drm aes-ctr������Կ</param>
		/// <param name="url_method">���ŵ�ַ����</param>
		void add_stream_element_mp4_drm(const std::string& user_type, QUrlType url_type, uint32_t  quality_index,
			const std::string& url, bool is_default, const std::string& referer = "", const std::string& backup_url = "",
			QVideoRenderType video_render_type = QVideoRenderType::PLANE, 
			const std::string& mp4_drm_key = "", QUrlMethod url_method = QUrlMethod::NORMAL);
		
		/// <summary>
		/// ��� steramElement
		/// </summary>
		/// <param name="user_type">�û��Զ���Type</param>
		/// <param name="url_type">ý�����Դ���� ֻ������Ƶ/ֻ������Ƶ/ͬʱ����Ƶ��Ƶ</param>
		/// <param name="quality_index">������</param>
		/// <param name="url">��Ƶ��ַ</param>
		/// <param name="is_default">�Ƿ���ʱ���Ÿ���</param>
		/// <param name="referer">http/https Э��ĵ�ַ ֧�ָ�����</param>
		/// <param name="backup_url">���õ�ַ</param>
		/// <param name="video_render_type"> ��Ƶ����Ⱦ����</param>
		/// <param name="mp4_qn_drm_com_key">��ţ˽�� MP4 drm ���� comkey ��Կ</param>
		/// <param name="mp4_qn_drm_file_key">��ţ˽�� MP4 drm ���� filekey ��Կ</param>
		/// <param name="url_method">���ŵ�ַ����</param>
		void add_stream_element_qn_mp4_drm(const std::string& user_type, QUrlType url_type, uint32_t  quality_index,
			const std::string& url, bool is_default, const std::string& referer = "", const std::string& backup_url = "",
			QVideoRenderType video_render_type = QVideoRenderType::PLANE, const std::string& mp4_qn_drm_com_key = "",
			const std::string& mp4_qn_drm_file_key = "" , QUrlMethod url_method = QUrlMethod::NORMAL);

		/// <summary>
		/// ��� steramElement
		/// </summary>
		/// <param name="user_type">�û��Զ���Type</param>
		/// <param name="url_type">ý�����Դ���� ֻ������Ƶ/ֻ������Ƶ/ͬʱ����Ƶ��Ƶ</param>
		/// <param name="quality_index">������</param>
		/// <param name="url">��Ƶ��ַ</param>
		/// <param name="is_default">�Ƿ���ʱ���Ÿ���</param>
		/// <param name="referer">http/https Э��ĵ�ַ ֧�ָ�����</param>
		/// <param name="backup_url">���õ�ַ</param>
		/// <param name="video_render_type"> ��Ƶ����Ⱦ����</param>
		/// <param name="hls_drm_key">hls ������Կ</param>
		/// <param name="url_method">���ŵ�ַ����</param>
		void add_stream_element_hls_drm(const std::string& user_type, QUrlType url_type, uint32_t  quality_index,
			const std::string& url, bool is_default, const std::string& referer = "", const std::string& backup_url = "",
			QVideoRenderType video_render_type = QVideoRenderType::PLANE,
			const std::string& hls_drm_key = "", QUrlMethod url_method = QUrlMethod::NORMAL);
		/**
		 * ��� subtitleElement
		 * @param name �û��Զ���Type
		 * @param url ��Ƶ��ַ
		 * @param isSelected �Ƿ���ʱʹ�ø���Ļ
		 */
		void add_subtitle_element(const std::string& name, const std::string& url, bool is_default);

		/**
		 * ����QMediaModel ʵ��
		 * @param is_live �Ƿ���ֱ��
		 * @return �������null ˵��builder �Ѿ��ù��ˣ��޷��ٴε��ø÷���
		 */
		QMediaModel* build(bool is_live, bool is_reconstruct_time_line = false);
	private:
		//�ڲ�ʹ�õ����stream����
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