auxProPath=../_script/aux_pro

#include($$auxProPath/mkLib.pro)
#include($$auxProPath/mkDll.pro)

include($$auxProPath/auxPro.pro)

include($$auxProPath/yesQt.pro)
#
include("_testProj.pro")
TARGET = _testProj

win32:
{
INCLUDEPATH +=	..\calcCore\include
LIBS += ../calcCore/bin/$$PC/calcCore.lib
}
