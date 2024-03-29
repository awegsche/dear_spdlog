#ifndef __DEAR_SINK_H
#define __DEAR_SINK_H
#include <iostream>
#include <mutex>
#include <vector>

#include <imgui.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>

// constexpr ImColor make_col(float r, float g, float b) {
//	return ImColor(r, g, b, 1.0f);
// }

struct log_item {
    std::string message;
    spdlog::level::level_enum level;
};

namespace dear_spdlog {
const ImColor TXT_DBG_CLR{0.5f, 0.5f, 0.5f, 1.0f};

const ImColor LVL_DBG_CLR{0.0f, 1.0f, 0.8f, 1.0f};
const ImColor LVL_LOG_CLR{0.65f, 0.2f, 1.0f, 1.0f};
const ImColor LVL_ERR_CLR{1.0f, 0.0f, 0.0f, 1.0f};
const ImColor LVL_WRN_CLR{1.0f, 0.5f, 0.0f, 1.0f};

template <typename Mutex> class dear_sink : public spdlog::sinks::base_sink<Mutex> {

  public:
    dear_sink() {}

    void draw_imgui(float posx = 5.0f, float posy = 5.0f, float width = 200.0f,
                    float height = 1000.0f) {
        ImGui::SetNextWindowPos({posx, posy});
        ImGui::SetNextWindowSize({width, height});
        ImGui::Begin("Log", nullptr,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoCollapse);

        for (size_t i = messages_.size() > max_shown_ ? messages_.size() - max_shown_ : 0; i < messages_.size(); ++i) {
            auto const &msg = messages_[i];

            switch (msg.level) {
            case spdlog::level::debug:
                ImGui::TextColored(LVL_DBG_CLR, "DBG");
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextColored(LVL_DBG_CLR, "%s", msg.message.c_str());
                break;
            case spdlog::level::warn:
                ImGui::TextColored(LVL_WRN_CLR, "WRN");
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::Text("%s", msg.message.c_str());
                break;
            case spdlog::level::err:
                ImGui::TextColored(LVL_ERR_CLR, "ERR");
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::Text("%s", msg.message.c_str());
                break;
            default:
                ImGui::TextColored(LVL_LOG_CLR, "LOG");
                ImGui::SameLine();
                ImGui::Text("|");
                ImGui::SameLine();
                ImGui::TextUnformatted(msg.message.c_str());
                break;
            }
        }
        if (scroll_) {
            ImGui::SetScrollHereY();
            scroll_ = false;
        }
        ImGui::End();
    }

    /// <summary>
    /// Sets the maximum number of messages that are shown.
    /// </summary>
    /// <param name="max_shown"></param>
    void set_max_shown_messages(size_t max_shown) { max_shown_ = max_shown; }

  protected:
    void sink_it_(const spdlog::details::log_msg &msg) override {
        log_item it;
        it.message = std::string(msg.payload.data(), msg.payload.size());
        it.level   = msg.level;
        messages_.push_back(it);
        scroll_ = true;
    }
    void flush_() override {}

  protected:
    std::vector<log_item> messages_ = {};
    bool scroll_                    = true;
    size_t max_shown_               = 1024;
};
} // namespace dear_spdlog

typedef std::shared_ptr<dear_spdlog::dear_sink<std::mutex>> dear_sink_mt_t;

const dear_sink_mt_t dear_sink_mt();
#endif // __DEAR_SINK_H
