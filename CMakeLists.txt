cmake_minimum_required(VERSION 3.23)
project(Qt1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(server/dependencies/cds/include)

find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(client client/LogInInterface/MainWindow.cpp
        client/LogInInterface/MainWindow.h
        client/client.cpp
        client/InApp/AppHomeWidget.cpp
        client/InApp/AppHomeWidget.h
        client/LogInInterface/LoginWidget.cpp
        client/LogInInterface/LoginWidget.h
        client/Posts/FeedWidget.cpp
        client/Posts/FeedWidget.h
        client/InApp/ActionsWidget.cpp
        client/InApp/ActionsWidget.h
        client/InApp/NotNormalUser.cpp client/InApp/NotNormalUser.h
       common/common.cpp common/common.h
        client/ServerConnection.cpp
        client/ServerConnection.h
        client/Friends/FriendsMenuWidget.cpp
        client/Friends/FriendsMenuWidget.h
        client/Friends/AddFriendsWidget.cpp
        client/Friends/AddFriendsWidget.h
        client/InApp/SettingsWidget.cpp
        client/InApp/SettingsWidget.h
        common/errors.cpp
        common/errors.h
        client/Friends/FriendsList.cpp
        client/Friends/FriendsList.h
        client/Friends/FriendItem.cpp
        client/Friends/FriendItem.h
        client/InApp/SettingsWidget.cpp
        client/InApp/SettingsWidget.h
        client/Messenger/MessagesWidget.cpp
        client/Messenger/MessagesWidget.h
        client/Messenger/NewMessageWidget.cpp
        client/Messenger/NewMessageWidget.h
        client/Messenger/ChatWidget.cpp
        client/Messenger/ChatWidget.h
        client/Messenger/AllMessagesWidget.cpp
        client/Messenger/AllMessagesWidget.h
        client/Posts/NewPostWidget.cpp client/Posts/NewPostWidget.h client/Posts/PostWidget.cpp client/Posts/PostWidget.h client/Friends/FriendRequestsWidget.cpp client/Friends/FriendRequestsWidget.h client/Friends/RequestItem.cpp client/Friends/RequestItem.h)
add_executable(server server/Server.cpp
        server/Server.h
        server/ClientThread.cpp
        server/ClientThread.h
        server/server_main.cpp
        common/common.cpp
        common/common.h
        common/errors.cpp
        common/errors.h
        server/RequestHandler.h
        server/RequestHandler.cpp)



target_link_libraries(client
  Qt::Core
  Qt::Gui
  Qt::Widgets
)

