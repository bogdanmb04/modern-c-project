cmake_minimum_required(VERSION 3.16)

project(BattleCityClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include CPR library via FetchContent
include(FetchContent)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.0 # Use a stable version of CPR
)
FetchContent_MakeAvailable(cpr)

# Find Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Define sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ClickableLabel.h
    loginwindow.h
    loginwindow.cpp
    registerwindow.h
    registerwindow.cpp
    map.txt
)

# Add executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BattleCityClient
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        httpmanager.h httpmanager.cpp
    )
else()
    add_executable(BattleCityClient
        ${PROJECT_SOURCES}
    )
endif()

# Link libraries
target_link_libraries(BattleCityClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets cpr::cpr)

add_custom_command(TARGET BattleCityClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/map.txt
    $<TARGET_FILE_DIR:BattleCityClient>/map.txt
)

# Set properties for macOS and iOS (optional)
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BattleCityClient)
endif()
set_target_properties(BattleCityClient PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Install rules
include(GNUInstallDirs)
install(TARGETS BattleCityClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BattleCityClient)
endif()
