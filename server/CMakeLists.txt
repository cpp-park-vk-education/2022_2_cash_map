project(server)

file(GLOB SOURCES "src/*.cpp")

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}_lib PUBLIC include)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (BUILD_COVERAGE)
    add_coverage(${PROJECT_NAME})
    add_coverage(${PROJECT_NAME}_lib)
endif()
