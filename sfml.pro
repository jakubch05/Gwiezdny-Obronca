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

win32 {
    # Znajdowanie SFML
    exists("C:/SFML-2.5.1/include/SFML/Graphics.hpp"):    SFML_PATH = "C:/SFML-2.5.1"
    exists("C:/SFML-2.6.1/include/SFML/Graphics.hpp"):    SFML_PATH = "C:/SFML-2.6.1"
    exists("C:/SFML/include/SFML/Graphics.hpp"):          SFML_PATH = "C:/SFML"

    INCLUDEPATH += "$$SFML_PATH/include"
    LIBS += -L"$$SFML_PATH/lib"

    CONFIG(debug, debug|release){
        LIBS += -lsfml-graphics-d -lsfml-window-d -lsfml-system-d

        copy_dlls.files = $$SFML_PATH/bin/sfml-graphics-d-2.dll \
                          $$SFML_PATH/bin/sfml-window-d-2.dll \
                          $$SFML_PATH/bin/sfml-system-d-2.dll
    } else {
        LIBS += -lsfml-graphics -lsfml-window -lsfml-system

        copy_dlls.files = $$SFML_PATH/bin/sfml-graphics-2.dll \
                          $$SFML_PATH/bin/sfml-window-2.dll \
                          $$SFML_PATH/bin/sfml-system-2.dll
    }

    # Wykonanie skryptu kopiującego
    copy_dlls.path = $$OUT_PWD
    COPIES += copy_dlls
}

unix {
    LIBS += -lsfml-graphics -lsfml-window -lsfml-system
}

copy_assets.files = $$files($$PWD/assets/*)
copy_assets.path = $$OUT_PWD
COPIES += copy_assets
