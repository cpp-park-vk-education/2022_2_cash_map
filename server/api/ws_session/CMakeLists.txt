project(ws_session)

file(GLOB SOURCES "src/*")
add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC room serializer db_client)
