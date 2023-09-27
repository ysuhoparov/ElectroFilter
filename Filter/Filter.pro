QT += widgets sql
requires(qtConfig(treeview))
qtHaveModule(printsupport): QT += printsupport
#unix:qtHaveModule(dbus): QT += dbus widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
	
SOURCES += \
    MVC/abstractlogmodel.cpp \
    MVC/abstractlogview.cpp \
    MVC/catalogchoiceview.cpp \
    MVC/catalogmodel.cpp \
    MVC/catalogview.cpp \
    MVC/operativelogmodel.cpp \
    MVC/operativelogview.cpp \
    MVC/repairlogmodel.cpp \
    MVC/repairlogview.cpp \
    MVC/servicelogmodel.cpp \
    MVC/servicelogview.cpp \
    channel.cpp \
    checkup.cpp \
    config.cpp \
    datedialog.cpp \
    diagram.cpp \
    field.cpp \
    main.cpp \
    mainwindow.cpp \
    MVC/model.cpp \
    operationallog.cpp \
    report.cpp \
    printview.cpp

HEADERS += \
    MVC/abstractlogmodel.h \
    MVC/abstractlogview.h \
    MVC/catalogchoiceview.h \
    MVC/catalogmodel.h \
    MVC/catalogview.h \
    MVC/operativelogmodel.h \
    MVC/operativelogview.h \
    MVC/repairlogmodel.h \
    MVC/repairlogview.h \
    MVC/servicelogmodel.h \
    MVC/servicelogview.h \
    about.h \
    channel.h \
    checkup.h \
    color.h \
    config.h \
    datedialog.h \
    diagram.h \
    enums.h \
    field.h \
    MVC/model.h \
    netinfo.h \
    mainwindow.h \
    operationallog.h \
    report.h \
    printview.h
	
FORMS += \
    datedialog.ui \
    mainwindow.ui \
    operationalLog.ui

RESOURCES += filter.qrc

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
