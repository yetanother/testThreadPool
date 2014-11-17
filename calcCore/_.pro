auxProPath=../_script/aux_pro

include($$auxProPath/mkLib.pro)
#include($$auxProPath/mkDll.pro)

include($$auxProPath/auxPro.pro)

include($$auxProPath/noQt.pro)
#
include("calcCore.pro")
TARGET = calcCore

#
#ROOT=../../../addLibs
#
#rootQt=$$ROOT/rawQt
#QTDIR=$$(rootQt)
#binQt=$$(rootQt)/bin
#QTINCLUDE=$$(rootQt)/include
#QT_INSTALL_BINS=$$(binQt)
#
#QMAKE_MOC             = $$(QT_INSTALL_BINS)/moc
#QMAKE_UIC             = $$(QT_INSTALL_BINS)/uic
#
#include($$(ROOT)/_auxCALS/pro/auxLib.pri)
#include($$(ROOT)/_auxCALS/pro/auxFolderRule.pri)
#

#DEFINES += BUILD_DLL \
#			IPLIB

#INCLUDEPATH +=

#win32:INCLUDEPATH +=	$$(QTINCLUDE)/QtCore \
#						$$(QTINCLUDE)/QtGui \
#						$$(QTINCLUDE)/QtXml \
#						$$(QTINCLUDE) \
#						$$(ROOT)/Qt_Wrapper/include \
#						../../dep/source_TCE8/include \
#						../../dep/source_TCE8/include/tc \
#						../../epmHandler/include
#						\
#						$$quote($$Root/dlgProto/_aux)


#SOURCES += $$quote(../testDll/_aux/auxXml.cpp)

#HEADERS -= ../stubDBMS/stubDBMS.h
#HEADERS -= dep/aplCrypto/aplCryptographicManager.h

#SOURCES -=	testDlgProto/main.cpp \
#			../stubDBMS/stubDBMS.cpp

#RESOURCES += res.qrc
#LIBS += ../dlgConfigurator/bin/$$PC/dlgConfigurator.lib