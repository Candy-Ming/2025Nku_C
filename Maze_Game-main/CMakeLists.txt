cmake_minimum_required(VERSION 3.5)

project(maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

# 所有源代码与资源
set(PROJECT_SOURCES
    main.cpp
    maze.h
    maze.cpp
    mazeWidget.h
    mazeWidget.cpp
    mazeWidget.ui
    StartScreen.h
    StartScreen.cpp
    resource.qrc
)

# Qt6：推荐使用 qt_add_executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(maze
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(maze SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(maze
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# 链接 Qt 模块
target_link_libraries(maze PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)

# 设置应用属性（macOS/iOS 可选）
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.maze)
endif()

set_target_properties(maze PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 安装配置（可选）
include(GNUInstallDirs)
install(TARGETS maze
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Qt6 特有处理
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(maze)
endif()
