cmake_minimum_required(VERSION 3.23)
project(Qt1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(client client/MainWindow.cpp client/MainWindow.h client/client.cpp)
add_executable(server  server/server.cpp)

target_link_libraries(client
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

