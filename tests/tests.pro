QT += core

CONFIG += c++17

TEMPLATE = app

include(gtest_dependency.pri)

INCLUDEPATH += ../VRPSPD_solver/

HEADERS += \
        ../VRPSPD_solver/inc/core/Client.h \
        ../VRPSPD_solver/inc/core/ClientList.h \
        ../VRPSPD_solver/inc/core/Route.h \
        ../VRPSPD_solver/inc/core/Saving.h \
        ../VRPSPD_solver/inc/service/ComputingService.h \
        ../VRPSPD_solver/inc/service/RouteService.h

SOURCES += \
        ../VRPSPD_solver/src/core/Client.cpp \
        ../VRPSPD_solver/src/core/ClientList.cpp \
        ../VRPSPD_solver/src/core/Route.cpp \
        ../VRPSPD_solver/src/core/Saving.cpp \
        ../VRPSPD_solver/src/service/ComputingService.cpp \
        ../VRPSPD_solver/src/service/RouteService.cpp \
        core/tst_ClientListTests.cpp \
        core/tst_RouteTests.cpp \
        main.cpp \
        service/tst_ComputingServiceTests.cpp \
        service/tst_RouteService.cpp
