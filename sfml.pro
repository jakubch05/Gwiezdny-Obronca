TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bonus.cpp \
        boss.cpp \
        egg.cpp \
        enemy.cpp \
        gameobject.cpp \
        hud.cpp \
        laser.cpp \
        main.cpp \
        menu.cpp \
        player.cpp \
        projectile.cpp \
        scoremanager.cpp
        INCLUDEPATH += "C:/SFML-2.5.1/include"

        LIBS += -L"C:/SFML-2.5.1/lib"
        CONFIG(debug, debug|release){
            LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
        } else {
            LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
        }

HEADERS += \
    GameConfig.h \
    bonus.h \
    boss.h \
    egg.h \
    enemy.h \
    gameobject.h \
    hud.h \
    laser.h \
    menu.h \
    player.h \
    projectile.h \
    scoremanager.h
