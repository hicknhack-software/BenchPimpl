TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

# your local path where libraries reside
LIB_BASE = C:/C/Lib

# Find GCC major version
*-g++: {
    GCC_VERSION = $$system("gcc -dumpversion")
    GCC_VERSION2 = $$split(GCC_VERSION, .)
    GCC_MAJOR = $$first(GCC_VERSION2)
    CONFIG += g++$$GCC_MAJOR
}

# Google Benchmark Library
# https://github.com/google/benchmark
INCLUDEPATH += $${LIB_BASE}/benchmark/include
win32-g++:g++4: LIBS += -L$${LIB_BASE}/benchmark/mingw4/lib
win32-g++:g++5: LIBS += -L$${LIB_BASE}/benchmark/mingw5/lib
win32-msvc2015: LIBS += -L$${LIB_BASE}/benchmark/VS2015/lib
LIBS += -lbenchmark

SOURCES += main.cpp \
    UniquePimplPoint.cpp \
    UniquePimplRect.cpp \
    PlainPoint.cpp \
    PlainRect.cpp \
    SharedPimplPoint.cpp \
    SharedPimplRect.cpp \
    ChainedPimplPoint.cpp \
    ChainedPimplRect.cpp \
    ChainedDeleterPimplPoint.cpp \
    ChainedDeleterPimplRect.cpp

HEADERS += \
    UniquePimplPoint.h \
    UniquePimplRect.h \
    UniquePimplBase.h \
    PlainPoint.h \
    PlainRect.h \
    SharedPimplBase.h \
    SharedPimplPoint.h \
    SharedPimplRect.h \
    ChainedPimplBase.h \
    ChainedPimplPoint.h \
    ChainedPimplRect.h \
    SharedPimplPoint_p.h \
    SharedPimplRect_p.h \
    UniquePimplPoint_p.h \
    UniquePimplRect_p.h \
    ChainedDeleterPimplPoint.h \
    ChainedDeleterPimplPoint_p.h \
    ChainedDeleterPimplRect.h \
    ChainedDeleterPimplRect_p.h

