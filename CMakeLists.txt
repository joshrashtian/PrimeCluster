cmake_minimum_required(VERSION 3.21)
project(PriusCluster LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(QT_QML_GENERATE_QMLLS_INI ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8 REQUIRED COMPONENTS Bluetooth Quick SerialBus)
qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(prius-cluster
    main.cpp
    bluetoothbaseclass.h bluetoothbaseclass.cpp
    clusterdata.h clusterdata.cpp
    turnsignals.h
    canreader.h canreader.cpp
    cansimulator.h cansimulator.cpp
    decode_functions.h decode_functions.cpp
    bluetooth/mediadata.h bluetooth/mediadata.cpp
    bluetooth/ios/amsclient.h bluetooth/ios/amsclient.cpp
)

target_include_directories(prius-cluster PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth
    ${CMAKE_CURRENT_SOURCE_DIR}/bluetooth/ios
)

qt_add_qml_module(prius-cluster
    URI Cluster
    QML_FILES
        Main.qml
        Background.qml
        components/Header.qml
        components/Speedometer.qml
        components/Gears.qml
        components/ButtonSelect.qml
        components/TurnSignals.qml
        components/Music.qml
    RESOURCES
        assets/fonts/GeistMonoBold.otf
        assets/fonts/ClashDisplay-Variable.ttf
        assets/fonts/DMSans.ttf
        assets/fonts/Nippo.ttf
        assets/fonts/lucide.ttf
)

target_link_libraries(prius-cluster PRIVATE Qt6::Quick Qt6::Bluetooth Qt6::SerialBus)
