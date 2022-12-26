project(server_core)

file(GLOB SOURCES "src/*")

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC ws_session)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
