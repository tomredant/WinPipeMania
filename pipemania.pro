QT       += core gui widgets
CONFIG += console
TARGET = pipemania
RESOURCES = pipemania.qrc
TEMPLATE = app
TRANSLATIONS = pipemania_nl.ts
CONFIG+=static
QMAKE_LFLAGS+=-static -static-libgcc -static-libstdc++ -lstdc++
DEFINES+=STATIC
CONFIG += c++11
SOURCES += \
    main.cpp \
    src/Board.cpp \
    src/Button.cpp \
    src/Controller.cpp \
    src/Log.cpp \
    src/Menu.cpp \
    src/Pipe.cpp \
    src/Splash.cpp \
    src/Text.cpp
FORMS +=
INCLUDEPATH += include/
INCLUDEPATH +=$$(SDL_ROOT)/include/
INCLUDEPATH +=$$(SDL_TTF_ROOT)/include
INCLUDEPATH +=$$(SDL_IMAGE_ROOT)/include
INCLUDEPATH += $$(SDL_MIXER_ROOT)/include
LIBS +=$$(SDL_ROOT)/lib/libSDL.a
LIBS +=$$(SDL_TTF_ROOT)/lib/libSDL_ttf.a
LIBS +=$$(SDL_MIXER_ROOT)/lib/libSDL_mixer.a
LIBS +=$$(SDL_IMAGE_ROOT)/lib/libsdl_image.a
LIBS +=$$(FREETYPE_ROOT)/lib/libttf.a
LIBS +=$$(MINGW_ROOT)/lib/libimm32.a
LIBS +=$$(MINGW_ROOT)/lib/libsetupapi.a
LIBS +=$$(MINGW_ROOT)/lib/libhid.a
LIBS +=$$(MINGW_ROOT)/lib/libole32.a
LIBS +=$$(MINGW_ROOT)/lib/liboleaut32.a
LIBS +=$$(MINGW_ROOT)/lib/libversion.a
LIBS +=$$(MINGW_ROOT)/lib/libgdi32.a
LIBS +=$$(MINGW_ROOT)/lib/libwinmm.a
LIBS +=$$(MINGW_ROOT)/lib/libws2_32.a
LIBS +=$$(MINGW_ROOT)/lib/libz.a
