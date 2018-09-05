TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    websocketclient.cpp \
    client/MessageType.pb.cc \
    Login.pb.cc \
    Robot.pb.cc

LIBS += -lasan -luWS -lssl -lcrypto -lz -lpthread -luv -lboost_system -L/usr/local/lib -lprotobuf
QMAKE_CXXFLAGS += -DUWS_THREADSAFE -fsanitize=address -Wno-unused-parameter
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3 -g


INCLUDEPATH += /usr/include/uWS

HEADERS += \
    websocketclient.h \
    client/MessageType.pb.h \
    Login.pb.h \
    Robot.pb.h

