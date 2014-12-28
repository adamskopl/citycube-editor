# everything
HEADERS += glwidget.h \
    paintwidget.h \
    mainwindow.h \
    welcomewindow.h \
    primitives/field.h \
    vector.h \
    world.h \
    texture.h \
    object.h \
    node.h \
    md2.h \
    error.h \
    engine.h \
    clock.h \
    camera.h \
    being.h \
    lucidbeaver.h \
    globalcontainer.h \
    primitives/floor.h \
    primitives/lbstairs.h \
    primitives/lbpassage.h \
    lbwallhelper.h \
    lbmathhelper.h \
    counter.h \
    lbstairshelper.h \
    lbhelpersbase.h \
    primitives/lbwindow.h \
    designwidgetmini.h \
    lbxmlmanager.h
SOURCES += glwidget.cpp \
    paintwidget.cpp \
    mainwindow.cpp \
    main.cpp \
    welcomewindow.cpp \
    primitives/field.cpp \
    world.cpp \
    texture.cpp \
    object.cpp \
    node.cpp \
    md2.cpp \
    error.cpp \
    engine.cpp \
    clock.cpp \
    camera.cpp \
    being.cpp \
    lucidbeaver.cpp \
    globalcontainer.cpp \
    primitives/floor.cpp \
    primitives/lbstairs.cpp \
    primitives/lbpassage.cpp \
    lbwallhelper.cpp \
    lbmathhelper.cpp \
    lbstairshelper.cpp \
    lbhelpersbase.cpp \
    primitives/lbwindow.cpp \
    designwidgetmini.cpp \
    lbxmlmanager.cpp
QT += opengl
LIBS += `sdl-config \
    --libs \
    --cflags` \
    -lSDL \
    -lSDL_image \
    -I/usr/X11R6/include \
    -L/usr/X11R6/lib \
    -lGL \
    -lGLU \
    -lmxml
