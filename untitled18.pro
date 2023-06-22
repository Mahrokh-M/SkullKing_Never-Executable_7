QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    avatar.cpp \
    edit_information.cpp \
    forgotpassword.cpp \
    globals.cpp \
    login.cpp \
    main.cpp \
    mainmenu.cpp \
    signup.cpp \
    user.cpp

HEADERS += \
    avatar.h \
    edit_information.h \
    forgotpassword.h \
    globals.h \
    login.h \
    mainmenu.h \
    signup.h \
    user.h

FORMS += \
    avatar.ui \
    edit_information.ui \
    forgotpassword.ui \
    login.ui \
    mainmenu.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc
