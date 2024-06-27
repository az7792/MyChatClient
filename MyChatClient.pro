QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boxList/boxlist.cpp \
    boxList/messageboxlist.cpp \
    chat/chatform.cpp \
    chat/chatwebsocket.cpp \
    entity/group.cpp \
    entity/message.cpp \
    entity/user.cpp \
    main.cpp \
    manager/usergroupmanager.cpp \
    smallWidget/loginform.cpp \
    smallWidget/messagebox.cpp \
    smallWidget/recvbox.cpp \
    smallWidget/registerform.cpp \
    smallWidget/resetpasswordform.cpp \
    smallWidget/sendbox.cpp \
    smallWidget/sidebar.cpp \
    window/mainwidow.cpp \
    window/userauthwindow.cpp

HEADERS += \
    boxList/boxlist.h \
    boxList/messageboxlist.h \
    chat/chatform.h \
    chat/chatwebsocket.h \
    entity/group.h \
    entity/message.h \
    entity/user.h \
    manager/usergroupmanager.h \
    smallWidget/boxlist.h \
    smallWidget/loginform.h \
    smallWidget/messagebox.h \
    smallWidget/recvbox.h \
    smallWidget/registerform.h \
    smallWidget/resetpasswordform.h \
    smallWidget/sendbox.h \
    smallWidget/sidebar.h \
    window/mainwidow.h \
    window/userauthwindow.h

FORMS += \
    chat/chatform.ui \
    smallWidget/loginform.ui \
    smallWidget/messagebox.ui \
    smallWidget/recvbox.ui \
    smallWidget/registerform.ui \
    smallWidget/resetpasswordform.ui \
    smallWidget/sendbox.ui \
    smallWidget/sidebar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc \
