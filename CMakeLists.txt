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

add_executable(client client/MainWindow.cpp
        client/MainWindow.h
        client/client.cpp
        client/AppHomeWidget.cpp
        client/AppHomeWidget.h
        client/LoginWidget.cpp
        client/LoginWidget.h
        client/FeedWidget.cpp
        client/FeedWidget.h
        client/ActionsWidget.cpp
        client/ActionsWidget.h
        NotLoggedIn.cpp NotLoggedIn.h
       common/common.cpp common/common.h
        client/ServerConnection.cpp
        client/ServerConnection.h
        client/FriendsMenuWidget.cpp
        client/FriendsMenuWidget.h
        client/FriendsListWidget.cpp
        client/FriendsListWidget.h
        client/AddFriendsWidget.cpp
        client/AddFriendsWidget.h
        common/errors.cpp
        common/errors.h)
add_executable(server server/Server.cpp
        server/Server.h
        server/ClientThread.cpp
        server/ClientThread.h
        server/server_main.cpp
        common/common.cpp
        common/common.h
        common/errors.cpp
        common/errors.h)


target_link_libraries(client
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

