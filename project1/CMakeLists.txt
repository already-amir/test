cmake_minimum_required(VERSION 3.16)

project(project1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(PahoMqttCpp REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(project1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET project1 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(project1 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        find_package(Qt5 REQUIRED COMPONENTS Core)

        add_executable(project1
          ${PROJECT_SOURCES}

          res/control/wifi.h res/control/wifi.cpp
          res/3d/P3d.qml res/boiler/Boiler.qml res/control/wifi.cpp res/control/wifi.h res/home/Cl1.qml res/home/Cl2.qml res/home/Cl3.qml res/home/Home.qml res/home/Left_side.qml res/home/Right_side.qml res/img/ab.jpg res/img/boiler.png res/img/grc.jpg res/img/home.png res/img/loading.gif res/img/P3d.png res/img/ping.png res/img/ross.png res/img/scan.png res/img/settings.png res/img/wifi_off.png res/img/wifi_on.png res/setting/Left_side.qml res/setting/Right_side.qml res/setting/Setting.qml res/setting/Wifi_Bottom.qml res/setting/Wifi_panel.qml res/setting/Wifi_Top.qml res/Glassy.qml res/Icon.qml res/Page_start.qml


          res/control/bluetooth.h res/control/bluetooth.cpp
          res/control/mqttclient.h res/control/mqttclient.cpp










        )
    endif()
endif()

target_link_libraries(project1
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
target_link_libraries(project1 PRIVATE Qt5::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(project1 PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include)
target_link_libraries(${PROJECT_NAME} PRIVATE PahoMqttCpp::paho-mqttpp3)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.project1)
endif()
set_target_properties(project1 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS project1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(project1)
    qt_finalize_executable(project1)
endif()
