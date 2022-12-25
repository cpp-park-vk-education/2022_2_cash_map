cmake_minimum_required(VERSION 3.5)

project(WatchUpApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network WebSockets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network WebSockets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS WebEngineWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS WebEngineWidgets)
find_package(Qt6 REQUIRED COMPONENTS Test)

set(CMAKE_AUTOUIC_SEARCH_PATHS static/ui)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")


add_library(WatchUpApp_lib STATIC ${HEADERS} ${SOURCES} ${UI} )

add_executable(WatchUpApp
    "main.cpp" "./static/resources.qrc"
)

target_link_libraries(WatchUpApp PRIVATE WatchUpApp_lib)


target_link_libraries(${PROJECT_NAME}_lib PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME}_lib  PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(${PROJECT_NAME}_lib  PRIVATE Qt${QT_VERSION_MAJOR}::WebSockets)
target_link_libraries(${PROJECT_NAME}_lib PRIVATE  Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
target_link_libraries(${PROJECT_NAME}_lib PRIVATE Qt6::Test)



set_target_properties(WatchUpApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS WatchUpApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(WatchUpApp)
endif()
