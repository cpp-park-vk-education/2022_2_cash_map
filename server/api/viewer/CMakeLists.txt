project(viewer)

file(GLOB SOURCES "src/*")


add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC room serializer ws_session user_session response)

