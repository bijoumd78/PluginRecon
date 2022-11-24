#pragma once
#include "configuration.h"
#include <spdlog/spdlog.h>
#include <spdlog/async_logger.h>
//#include <memory>


namespace pluginrecon {

    class Logger
    {
     public:
        Logger() = delete;
        // Dependency injection
        explicit Logger(std::string_view config, std::string_view name);

        template<typename T>         static void info(T&& msg)           { p_logger->info(std::forward<T>(msg));           }
        template <typename ...Args>  static void info(Args&& ...msg)     { p_logger->info(std::forward<Args>(msg)...);     }

        template<typename T>         static void debug(T&& msg)          { p_logger->debug(std::forward<T>(msg));          }
        template <typename ...Args>  static void debug(Args&& ...msg)    { p_logger->debug(std::forward<Args>(msg)...);    }

        template<typename T>         static void warn(T&& msg)           { p_logger->warn(std::forward<T>(msg));           }
        template <typename ...Args>  static void warn(Args&& ...msg)     { p_logger->warn(std::forward<Args>(msg)...);     }

        template<typename T>         static void error(T&& msg)          { p_logger->error(std::forward<T>(msg));          }
        template <typename ...Args>  static void error(Args&& ...msg)    { p_logger->error(std::forward<Args>(msg)...);    }

        template<typename T>         static void critical(T&& msg)       { p_logger->critical(std::forward<T>(msg));       }
        template <typename ...Args>  static void critical(Args&& ...msg) { p_logger->critical(std::forward<Args>(msg)...); }

     private:
            spdlog::level::level_enum convertStringToLoggingLevel(const std::string& level)const;
            std::unique_ptr<Configuration> p_config;
            inline static std::shared_ptr<spdlog::logger> p_logger {nullptr};
    };
}