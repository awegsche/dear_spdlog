# CMakeList.txt : CMake project for dear_spdlogger, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)

project ("dear_spdlogger" LANGUAGES CXX)

find_package(spdlog CONFIG REQUIRED)

# gl window
find_package(glew REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# --------------------------------------------------------------------------------------------------
# ---- Test executable -----------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------------
add_executable (test_dear_spdlogger "dear_spdlogger.cpp" "dear_spdlogger.h")

target_link_libraries(test_dear_spdlogger
	PRIVATE
	spdlog::spdlog
	glfw
	GLEW::GLEW
	imgui::imgui
)

# --------------------------------------------------------------------------------------------------
# ---- Library -------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------------
add_library (dear_spdlogger "src/dear_sink.h")

target_link_libraries(dear_spdlogger
	PRIVATE
	spdlog::spdlog
	imgui::imgui
)

# TODO: Add tests and install targets if needed.
