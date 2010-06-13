# everything
HEADERS += glwidget.h \
    paintwidget.h \
    mainwindow.h \
    welcomewindow.h \
    field.h \
    vector.h \
    vector2.h \
    world.h \
    texture.h \
    object.h \
    node.h \
    md2.h \
    hero.h \
    error.h \
    engine.h \
    clock.h \
    camera.h \
    being.h \
    lucidbeaver.h \
    globalcontainer.h \
    floor.h
SOURCES += glwidget.cpp \
    paintwidget.cpp \
    mainwindow.cpp \
    main.cpp \
    welcomewindow.cpp \
    field.cpp \
    world.cpp \
    texture.cpp \
    object.cpp \
    node.cpp \
    md2.cpp \
    hero.cpp \
    error.cpp \
    engine.cpp \
    clock.cpp \
    camera.cpp \
    being.cpp \
    lucidbeaver.cpp \
    globalcontainer.cpp \
    floor.cpp
QT += opengl
LIBS += `sdl-config \
    --libs \
    --cflags` \
    -lSDL \
    -lSDL_image \
    -I/usr/X11R6/include \
    -L/usr/X11R6/lib \
    -lGL \
    -lGLU
