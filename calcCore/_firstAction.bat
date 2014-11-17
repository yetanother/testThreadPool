echo off

rem set ROOT=..\..\..\addLibs

rem set rootQt=%ROOT%\rawQt
rem set QTDIR=%rootQt%
rem set QTINCLUDE=%rootQt%\include
rem set binQt=%rootQt%\bin
rem set QMAKESPEC=%QTDIR%\mkspecs\win32-msvc2008

rem echo QTDIR=%QTDIR%

rem set QT_INSTALL_BINS=%binQt%

del bin /s /q 
del build /s /q 

rem %binQt%\
qmake -project
rem %binQt%\
qmake _.pro -t vclib
