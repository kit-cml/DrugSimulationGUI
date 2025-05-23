cmake_minimum_required(VERSION 3.5)

project(DrugSimulationGUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable dynamic linking of Qt
set(QT_BUILD_SHARED_LIBS OFF)
set(BUILD_SHARED_LIBS OFF)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Pdf)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PdfWidgets)

set(PROJECT_SOURCES
        browsewidget.cpp
        browsewidget.h
        centralwidget.cpp
        centralwidget.h
        comboboxdelegate.cpp
        comboboxdelegate.h
        guiconstants.cpp
        guiconstants.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        parametermodel.cpp
        parametermodel.h
        parameterviewer.cpp
        parameterviewer.h
        pdfviewer.cpp
        pdfviewer.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DrugSimulationGUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DrugSimulationGUI APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DrugSimulationGUI SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DrugSimulationGUI
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DrugSimulationGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PdfWidgets)

set_target_properties(DrugSimulationGUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS DrugSimulationGUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DrugSimulationGUI)
endif()
