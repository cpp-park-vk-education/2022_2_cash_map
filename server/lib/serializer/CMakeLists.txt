project(serializer)

file(GLOB SOURCES "src/*")
find_package(nlohmann_json 3.10.5 REQUIRED)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
