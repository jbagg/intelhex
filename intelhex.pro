QT = core

include($$PWD/intelhex.pri)

#VERSION = 1.0

TEMPLATE = lib
TARGET = $$qtLibraryTarget(IntelHex$$QT_LIBINFIX)
CONFIG += module create_prl
DEFINES+= QT_BUILD_INTELHEX_LIB
mac:QMAKE_FRAMEWORK_BUNDLE_NAME = $$TARGET

target.path = $$PREFIX/lib

INSTALLS += target
