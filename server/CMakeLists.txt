project(server)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC server_core)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
#target_link_libraries(${PROJECT_NAME} PUBLIC /usr/lib/x86_64-linux-gnu/libboost_date_time.a)


add_subdirectory(api)
add_subdirectory(lib)
add_subdirectory(core)
add_subdirectory(DB_client)


if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (BUILD_COVERAGE)
    add_coverage(${PROJECT_NAME})
    #add_coverage(${PROJECT_NAME}_lib)
endif()
