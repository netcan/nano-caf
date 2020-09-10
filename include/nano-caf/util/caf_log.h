//
// Created by Darwin Yuan on 2020/9/11.
//

#ifndef NANO_CAF_CAF_LOG_H
#define NANO_CAF_CAF_LOG_H

#if DEBUG
#include <spdlog/spdlog.h>

#define CAF_DEBUG(str, ...) \
spdlog::debug("{}:{}: " str, __FILE__, __LINE__, ##__VA_ARGS__)

#define CAF_INFO(str, ...) \
spdlog::info("{}:{}: " str, __FILE__, __LINE__, ##__VA_ARGS__)

#define CAF_WARN(str, ...) \
spdlog::warn("{}:{}: " str, __FILE__, __LINE__, ##__VA_ARGS__)

#define CAF_ERROR(str, ...) \
spdlog::error("{}:{}: " str, __FILE__, __LINE__, ##__VA_ARGS__)

#define CAF_CRITICAL(str, ...) \
spdlog::critical("{}:{}: " str, __FILE__, __LINE__, ##__VA_ARGS__)

#else
#define CAF_DEBUG(str, ...)
#define CAF_INFO(str, ...)
#define CAF_ERROR(str, ...)
#define CAF_WARN(str, ...)
#define CAF_CRITICAL(str, ...)
#endif

#endif //NANO_CAF_CAF_LOG_H
