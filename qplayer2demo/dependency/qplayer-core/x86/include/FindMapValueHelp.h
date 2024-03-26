#pragma once
#include <string>
#include <map>
#include <any>
#include "LogInterface.h"
namespace QMedia {
	class FindMapValueHelp
	{
	public:
		FindMapValueHelp() = delete;
		~FindMapValueHelp() = delete;

		FindMapValueHelp(const FindMapValueHelp&) = delete;

		FindMapValueHelp(FindMapValueHelp&&) = delete;

		FindMapValueHelp& operator=(const FindMapValueHelp&) = delete;

		FindMapValueHelp& operator=(FindMapValueHelp&&) = delete;

		template <typename T>
		static T map_find_params_with_key(const std::string& key, const std::map<std::string, std::any>* pparams,LogInterface* plog_fucntion)
		{
			auto it = pparams->find(key);
			T value = T();
			try {
				value = std::any_cast<T>(it->second);
			}
			catch (const std::bad_any_cast& e) {
				// 类型转换失败，值的类型不匹配
				std::string log_str = "\\FindMapValueHelp.h : Type conversion failed, the type of the value does not match";
				plog_fucntion->log(QLogLevel::LOG_DEBUG, log_str);
			}

			return value;
		}
	};
}
