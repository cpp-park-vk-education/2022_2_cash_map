project(test_client)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} client_lib GTest::gtest_main)

#add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
gtest_discover_tests(${PROJECT_NAME})

