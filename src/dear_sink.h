#include <vector>
#include <iostream>

#include <spdlog/sinks/base_sink.h>
#include <imgui.h>

//constexpr ImColor make_col(float r, float g, float b) {
//	return ImColor(r, g, b, 1.0f);
//}

namespace dear_spdlog {
	const ImColor TXT_DBG_CLR{ 0.5f, 0.5f, 0.5f, 1.0f };

	const ImColor LVL_DBG_CLR{ 0.0f, 1.0f, 0.8f, 1.0f };
	const ImColor LVL_LOG_CLR{ 0.65f, 0.2f, 1.0f, 1.0f };
	const ImColor LVL_ERR_CLR{ 1.0f, 0.0f, 0.0f, 1.0f };
	const ImColor LVL_WRN_CLR{ 1.0f, 0.5f, 0.0f, 1.0f };

	template<typename Mutex>
	class dear_sink : public spdlog::sinks::base_sink<Mutex>
	{

	public:
		dear_sink() {
			std::cout << "creating" << std::endl;
		}
		void draw_imgui() const {
			ImGui::Begin("Log", nullptr);
			for (auto const& msg : messages_) {

				switch (msg.level) {
				case spdlog::level::debug:
					ImGui::TextColored(LVL_DBG_CLR, "DBG");
					ImGui::SameLine();
					ImGui::Text("|");
					ImGui::SameLine();
					ImGui::TextColored(LVL_DBG_CLR, "%s", msg.payload.data());
					break;
				case spdlog::level::warn:
					ImGui::TextColored(LVL_WRN_CLR, "WRN");
					ImGui::SameLine();
					ImGui::Text("|");
					ImGui::SameLine();
					ImGui::Text("%s", msg.payload.data());
					break;
				case spdlog::level::err:
					ImGui::TextColored(LVL_ERR_CLR, "ERR");
					ImGui::SameLine();
					ImGui::Text("|");
					ImGui::SameLine();
					ImGui::Text("%s", msg.payload.data());
					break;
				default:
					ImGui::TextColored(LVL_LOG_CLR, "LOG");
					ImGui::SameLine();
					ImGui::Text("|");
					ImGui::SameLine();
					ImGui::Text("%s", msg.payload.data());
					break;
				}
			}
			ImGui::End();
		}

	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override {
			messages_.push_back(msg);
		}
		void flush_() override {}

	protected:
		std::vector<spdlog::details::log_msg> messages_;
	};
}

const std::shared_ptr<dear_spdlog::dear_sink<std::mutex>> dear_sink_mt() {
	auto llog = spdlog::create<dear_spdlog::dear_sink<std::mutex>>(std::string("llog"));

	// I don't understand this step, shouldn't it log to all registered loggers?
	spdlog::set_default_logger(llog);

	return std::dynamic_pointer_cast<dear_spdlog::dear_sink<std::mutex>>(llog->sinks()[0]);
}
