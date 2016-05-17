# BenchPimpl
# (C) Copyright 2016 HicknHack Software GmbH
#
# The original code can be found at:
#    https://github.com/hicknhack-software/BenchPimpl
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
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

