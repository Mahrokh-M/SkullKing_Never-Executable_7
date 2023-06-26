QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    avatar.cpp \
    each_game_history.cpp \
    edit_information.cpp \
    forgotpassword.cpp \
    globals.cpp \
    history.cpp \
    login.cpp \
    main.cpp \
    mainmenu.cpp \
    selection.cpp \
    signup.cpp \
    user.cpp

HEADERS += \
    avatar.h \
    each_game_history.h \
    edit_information.h \
    forgotpassword.h \
    globals.h \
    history.h \
    login.h \
    mainmenu.h \
    selection.h \
    signup.h \
    user.h

FORMS += \
    avatar.ui \
    each_game_history.ui \
    edit_information.ui \
    forgotpassword.ui \
    history.ui \
    login.ui \
    mainmenu.ui \
    selection.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc
