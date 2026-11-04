set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

cmake_minimum_required(VERSION 3.21)
project(PriusCluster LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 6.8.2 REQUIRED COMPONENTS Bluetooth Quick SerialBus)
qt_standard_project_setup(REQUIRES 6.5)
# c files
qt_add_executable(prius-cluster main.cpp bluetoothbaseclass.cpp devicefinder.cpp clusterdata.cpp devicehandler.cpp deviceinfo.cpp canreader.cpp decode_functions.cpp cansimulator.cpp) 
# qml modules
qt_add_qml_module(prius-cluster URI Cluster QML_FILES Main.qml Background.qml components/Header.qml components/Speedometer.qml components/ButtonSelect.qml components/Music.qml assets/fonts/GeistMonoBold.otf assets/fonts/ClashDisplay-Variable.ttf assets/fonts/DMSans.ttf assets/fonts/Nippo.ttf assets/fonts/lucide.ttf)
target_link_libraries(prius-cluster PRIVATE Qt6::Quick Qt6::Bluetooth Qt6::SerialBus)

