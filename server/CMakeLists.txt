project(server)

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC server_core)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)


add_subdirectory(api)
add_subdirectory(lib)
add_subdirectory(core)


if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (BUILD_COVERAGE)
    add_coverage(${PROJECT_NAME})
    #add_coverage(${PROJECT_NAME}_lib)
endif()
