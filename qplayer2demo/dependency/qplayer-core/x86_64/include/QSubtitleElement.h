#pragma once

#include "QPlayerExport.h"
#include <string>
#include "QUrlType.h"
#include "QVideoRenderType.h"

namespace QMedia {
	class QPLAYER_API QSubtitleElement {


	private:
		QSubtitleElement(const std::string& name, const std::string& url, bool is_selected)
			:mName(name),
			mUrl(url),
			mIsSelected(is_selected) {}

		~QSubtitleElement() {}

		QSubtitleElement(const QSubtitleElement&) = delete;

		QSubtitleElement(QSubtitleElement&&) = delete;

		QSubtitleElement& operator=(const QSubtitleElement&) = delete;

		QSubtitleElement& operator=(QSubtitleElement&&) = delete;
		friend class QMediaModelBuilder;
		friend class QMediaModel;
	public:

		/// <summary>
		/// 获取当前字幕元素的名称
		/// </summary>
		/// <returns></returns>
		const std::string& get_name() const { return mName; }

		/// <summary>
		/// 获取当前字幕元素的地址
		/// </summary>
		/// <returns></returns>
		const std::string& get_url() const { return mUrl; }

		/// <summary>
		/// 获取当前字幕元素是非被选中
		/// </summary>
		/// <returns></returns>
		bool is_selected() const { return mIsSelected; }

	private:
		std::string mName;
		std::string mUrl;
		std::string mBackupUrl;
		bool mIsSelected;
	};
}