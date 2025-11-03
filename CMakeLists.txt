cmake_minimum_required(VERSION 3.16)

project(test_1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(apptest_1
    main.cpp
)

qt_add_qml_module(apptest_1
    URI test_1
    QML_FILES
        Main.qml
        QML_FILES App.qml
        RESOURCES Resource.qrc



)

qt_add_resources(apptest_1 "icons" PREFIX "/res"
    FILES img/openai.png img/TickTick.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apptest_1 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apptest_1
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptest_1
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS apptest_1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
