# dear_spdlog

ImGui window that acts as sink for spdlog.

### Semi-working example

```cpp
#include <dear_sink.h>
#include <spdlog/spdlog.h>
#include <imgui.h>

int main() {
    // setup sink
    sink = dear_sink_mt();

    spdlog::debug("this is a debug message");
    spdlog::info("this is an info message");
    spdlog::error("this is an error message");

    // setup the graphics context and imgui
    /* ... */

    while(!close_main_loop) {
        // start imgui frame
        ImGui::NewFrame();

        // finally tell the sink to render itself
        sink->draw_imgui(/*possibly control position and size*/);

        // render imgui frame (in this example using the OpenG: Backend)
        ImGui::Render();
        Imgui_ImplOpenGl3_RenderDrawData(ImGui::GetDrawData());
    }
}
```

