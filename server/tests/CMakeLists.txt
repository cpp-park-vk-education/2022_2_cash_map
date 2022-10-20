project(test_server)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} server_lib GTest::gtest_main)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

if (BUILD_COVERAGE)
    add_coverage(${PROJECT_NAME})
endif()
