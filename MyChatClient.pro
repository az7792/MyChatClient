QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chat/chatwebsocket.cpp \
    entity/group.cpp \
    entity/message.cpp \
    entity/user.cpp \
    main.cpp \
    formmanager.cpp \
    manager/usergroupmanager.cpp \
    smallWidget/loginform.cpp \
    smallWidget/messagebox.cpp \
    smallWidget/recvbox.cpp \
    smallWidget/registerform.cpp \
    smallWidget/resetpasswordform.cpp \
    smallWidget/sendbox.cpp \
    window/userauthwindow.cpp

HEADERS += \
    chat/chatwebsocket.h \
    entity/group.h \
    entity/message.h \
    entity/user.h \
    formmanager.h \
    manager/usergroupmanager.h \
    smallWidget/loginform.h \
    smallWidget/messagebox.h \
    smallWidget/recvbox.h \
    smallWidget/registerform.h \
    smallWidget/resetpasswordform.h \
    smallWidget/sendbox.h \
    window/userauthwindow.h

FORMS += \
    formmanager.ui \
    smallWidget/loginform.ui \
    smallWidget/messagebox.ui \
    smallWidget/recvbox.ui \
    smallWidget/registerform.ui \
    smallWidget/resetpasswordform.ui \
    smallWidget/sendbox.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
    smallWidget/resources.qrc
