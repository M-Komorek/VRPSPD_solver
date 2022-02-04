QT += quick qml core

CONFIG += c++17

TARGET = VRPSPD_solver

HEADERS += \
        inc/core/Client.h \
        inc/core/ClientList.h \
        inc/core/Route.h \
        inc/core/Saving.h \
        inc/service/ComputingService.h \
        inc/service/RouteService.h \
        inc/solver/Solver.h

SOURCES += \
        main.cpp \
        src/core/Client.cpp \
        src/core/ClientList.cpp \
        src/core/Route.cpp \
        src/core/Saving.cpp \
        src/service/ComputingService.cpp \
        src/service/RouteService.cpp \
        src/solver/Solver.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
