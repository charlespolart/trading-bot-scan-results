cmake_minimum_required(VERSION 3.2)

project(trading_bot_scan_results)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TRADING_BOT_HEADERS
${CMAKE_CURRENT_SOURCE_DIR}/include/Database.hpp
${CMAKE_CURRENT_SOURCE_DIR}/include/Results.hpp
)

set(TRADING_BOT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Database.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Results.cpp
)

add_subdirectory(src build)
