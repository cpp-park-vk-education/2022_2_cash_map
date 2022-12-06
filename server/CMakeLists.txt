project(server)

file(GLOB SOURCES "src/*")

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}_lib PUBLIC include)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)


if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (BUILD_COVERAGE)
    add_coverage(${PROJECT_NAME})
    add_coverage(${PROJECT_NAME}_lib)
endif()
