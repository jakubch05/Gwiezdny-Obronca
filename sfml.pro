TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        src/bonus.cpp \
        src/boss.cpp \
        src/egg.cpp \
        src/enemy.cpp \
        src/gameobject.cpp \
        src/hud.cpp \
        src/laser.cpp \
        src/main.cpp \
        src/menu.cpp \
        src/player.cpp \
        src/projectile.cpp \
        src/scoremanager.cpp
        INCLUDEPATH += "C:/SFML-2.5.1/include"

        LIBS += -L"C:/SFML-2.5.1/lib"
        CONFIG(debug, debug|release){
            LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
        } else {
            LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
        }

HEADERS += \
    src/GameConfig.h \
    src/bonus.h \
    src/boss.h \
    src/egg.h \
    src/enemy.h \
    src/gameobject.h \
    src/hud.h \
    src/laser.h \
    src/menu.h \
    src/player.h \
    src/projectile.h \
    src/scoremanager.h
