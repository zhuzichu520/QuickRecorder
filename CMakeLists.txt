cmake_minimum_required(VERSION 3.14)

project(QuickRecorder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    message("Window System")
    if(CMAKE_CL_64)
        message("build 64")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/win64)
        include_directories(./third/win64/ffmpeg/include)
    else()
        message("build 32")
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/win32)
    endif()
else()
    message("Linux System")
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools REQUIRED)

set(TS_FILES res/QuickRecorder_zh_CN.ts)

set(PROJECT_SOURCES
    src/main.cpp
    src/tool.h
    src/tool.cpp
    src/ScreenImageProvider.cpp
    src/ScreenImageProvider.h
    src/aencode.cpp
    src/aencode.h
    src/gdigrab.cpp
    src/gdigrab.h
    res/qml.qrc
    ${TS_FILES}
    )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QuickRecorder
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET QuickRecorder APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(QuickRecorder SHARED
            ${PROJECT_SOURCES}
            )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QuickRecorder
            ${PROJECT_SOURCES}
            )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

if(WIN32)
    if(CMAKE_CL_64)
        set(FFMPEG_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third/win64/ffmpeg/lib/)
        target_link_libraries(QuickRecorder PRIVATE
            ${FFMPEG_LIB_PATH}/avcodec.lib
            ${FFMPEG_LIB_PATH}/avdevice.lib
            ${FFMPEG_LIB_PATH}/avfilter.lib
            ${FFMPEG_LIB_PATH}/avformat.lib
            ${FFMPEG_LIB_PATH}/avutil.lib
            ${FFMPEG_LIB_PATH}/postproc.lib
            ${FFMPEG_LIB_PATH}/swresample.lib
            ${FFMPEG_LIB_PATH}/swscale.lib
            )
    else()
    endif()
else()
endif()


target_compile_definitions(QuickRecorder
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QuickRecorder
    PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

set_target_properties(QuickRecorder PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(QuickRecorder)
    qt_finalize_executable(QuickRecorder)
endif()
