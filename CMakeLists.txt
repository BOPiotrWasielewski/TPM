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

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.2
)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

project(tpm)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(SOURCE_FILES src/main.cpp
        src/classes/Panel.cpp
        src/headers/Panel.h
        src/classes/PasswordManager.cpp
        src/headers/PasswordManager.h
        src/classes/Files.cpp
        src/headers/Files.h
        src/classes/Encrypt.cpp
        src/headers/Encrypt.h
)

add_executable(tpm ${SOURCE_FILES})
target_include_directories(tpm PRIVATE src)
target_link_libraries(tpm
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)
target_link_libraries(tpm
    PRIVATE nlohmann_json::nlohmann_json
)