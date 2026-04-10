cmake_minimum_required(VERSION 3.20)
project(Game CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    code/main.cpp

    code/Attributes/Action.cpp
    code/Attributes/Attack.cpp
    code/Attributes/Item.cpp

    code/Entities/Enemy.cpp
    code/Entities/Entity.cpp
    code/Entities/Player.cpp

    code/FileManager/FileManager.cpp
    code/FileManager/stringConverter.cpp

    code/GameLogic/Bestiary.cpp
    code/GameLogic/Combat.cpp
    code/GameLogic/Game.cpp
    code/GameLogic/Menu.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    code/Attributes
    code/Entities
    code/FileManager
    code/GameLogic
)