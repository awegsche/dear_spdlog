#include "dear_sink.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>

const dear_sink_mt_t dear_sink_mt() {
	auto llog = spdlog::create<dear_spdlog::dear_sink<std::mutex>>(std::string("llog"));

	// I don't understand this step, shouldn't it log to all registered loggers?
	spdlog::set_default_logger(llog);

	return std::dynamic_pointer_cast<dear_spdlog::dear_sink<std::mutex>>(llog->sinks()[0]);
}
