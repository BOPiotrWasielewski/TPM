cmake_minimum_required(VERSION 3.26)
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v5.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

project(tpm)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES src/main.cpp
        src/Panel.cpp
        src/Panel.h
        src/Passwords.cpp
        src/Passwords.h
)

add_executable(tpm ${SOURCE_FILES})
target_include_directories(tpm PRIVATE src)
target_link_libraries(tpm
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
)