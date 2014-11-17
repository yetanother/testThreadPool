#
win32:
{
	#PC = $(PlatformName)/$(ConfigurationName)
	PC = $(Platform)/$(Configuration)
	INCLUDEPATH += $$quote(./include) \
					 $$quote(./build)
}

#unix:INCLUDEPATH += $$quote(/home/user/extra headers)

#output dir
DESTDIR = ./bin/$$PC
#intermediate dir
OBJECTS_DIR = ./build/$$PC
#
MOC_DIR = $$OBJECTS_DIR
RCC_DIR = $$OBJECTS_DIR
UI_DIR  = $$OBJECTS_DIR
#