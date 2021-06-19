set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=address")

add_executable(
    ${PROJECT_NAME}
    ${TRADING_BOT_SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME}
    pqxx
    pq
)
