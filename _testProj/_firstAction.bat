echo off

del bin /s /q 
del build /s /q 

qmake -project
qmake _.pro -t vcapp