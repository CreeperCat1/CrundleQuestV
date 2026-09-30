cmake_minimum_required(VERSION 3.20)

project(CrundleQuestV VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(SDL3_mixer CONFIG REQUIRED)

add_executable(CrundleQuestV WIN32
	Scripts/renderCrundle.cpp
	Scripts/LTexture.cpp
	Scripts/gameManager.cpp
)

target_link_libraries(CrundleQuestV PRIVATE
	SDL3::SDL3
	SDL3_image::SDL3_image
	SDL3_ttf::SDL3_ttf
	SDL3_mixer::SDL3_mixer
)

add_custom_command(TARGET CrundleQuestV POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/Assets"
	"$<TARGET_FILE_DIR:CrundleQuestV>/Assets"
)