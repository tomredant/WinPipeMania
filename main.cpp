#ifdef __cplusplus
    #include <cstdlib>
    #include <ctime>
#else
    #include <stdlib.h>
    #include <time.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "Log.h"
#include "Controller.h"
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QTranslator>
#include "showlicense.h"
#define FRAMES_PER_SECOND 25

const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
#undef main
int main ( int argc, char** argv )
{

    QApplication a(argc, argv);
    QTranslator *translator = new QTranslator();
    QString language = "nl";
    QString translatorFile =(":/pipemania_" + language + ".qm");
    translator->load(translatorFile);
    a.installTranslator(translator);

    std::vector<std::string> libs;

    libs.push_back(R"MYSTRING(WinPipeMania#Dutch translation by Tom Redant of the Original Game pipemania made by Fabio Kreusch. Source files can be obtained from: https://github.com/tomredant/WinPipeMania.#gpl-3.0)MYSTRING");

    libs.push_back(R"MYSTRING(PipeMania#Original Game pipemania made by Fabio Kreusch. https://github.com/fabiokr/pipemania
Originally licensed under conditions of the MIT License.

The MIT License (MIT)

Copyright (c) 2014 Fabio Kreusch

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.#)MYSTRING");

    libs.push_back(R"MYSTRING(Freetype 1.3.1#The FreeType Project LICENSE
                   ----------------------------

                      Copyright 1996-1999 by
         David Turner, Robert Wilhelm, and Werner Lemberg



Introduction
============

 The FreeType  Project is distributed in  several archive packages;
 some of them may contain, in addition to the FreeType font engine,
 various tools and  contributions which rely on, or  relate to, the
 FreeType Project.

 This  license applies  to all  files found  in such  packages, and
 which do not  fall under their own explicit  license.  The license
 affects  thus  the  FreeType   font  engine,  the  test  programs,
 documentation and makefiles, at the very least.

 This  license   was  inspired  by  the  BSD,   Artistic,  and  IJG
 (Independent JPEG  Group) licenses, which  all encourage inclusion
 and  use of  free  software in  commercial  and freeware  products
 alike.  As a consequence, its main points are that:

   o We don't promise that this software works.  However, we are be
     interested in any kind of bug reports. (`as is' distribution)

   o You can  use this software for whatever you  want, in parts or
     full form, without having to pay us. (`royalty-free' usage)

   o You may not pretend that  you wrote this software.  If you use
     it, or  only parts of it,  in a program,  you must acknowledge
     somewhere in your documentation  that you've used the FreeType
     code. (`credits')

 We  specifically  permit  and  encourage  the  inclusion  of  this
 software,  with  or without modifications, in commercial products,
 provided that all warranty or  liability claims are assumed by the
 product vendor.


Legal Terms
===========

0. Definitions
--------------

 Throughout this license,  the terms `package', `FreeType Project',
 and  `FreeType  archive' refer  to  the  set  of files  originally
 distributed  by the  authors  (David Turner,  Robert Wilhelm,  and
 Werner Lemberg) as the `FreeType project', be they named as alpha,
 beta or final release.

 `You' refers to  the licensee, or person using  the project, where
 `using' is a generic term including compiling the project's source
 code as  well as linking it  to form a  `program' or `executable'.
 This  program is  referred to  as  `a program  using the  FreeType
 engine'.

 This  license applies  to all  files distributed  in  the original
 FreeType  archive,   including  all  source   code,  binaries  and
 documentation,  unless  otherwise  stated   in  the  file  in  its
 original, unmodified form as  distributed in the original archive.
 If you are  unsure whether or not a particular  file is covered by
 this license, you must contact us to verify this.

 The FreeType  project is copyright (C) 1996-1999  by David Turner,
 Robert Wilhelm, and Werner Lemberg.  All rights reserved except as
 specified below.

1. No Warranty
--------------

 THE FREETYPE ARCHIVE  IS PROVIDED `AS IS' WITHOUT  WARRANTY OF ANY
 KIND, EITHER EXPRESSED OR  IMPLIED, INCLUDING, BUT NOT LIMITED TO,
 WARRANTIES  OF  MERCHANTABILITY   AND  FITNESS  FOR  A  PARTICULAR
 PURPOSE.  IN NO EVENT WILL ANY OF THE AUTHORS OR COPYRIGHT HOLDERS
 BE LIABLE  FOR ANY DAMAGES CAUSED  BY THE USE OR  THE INABILITY TO
 USE, OF THE FREETYPE PROJECT.

 As  you have  not signed  this license,  you are  not  required to
 accept  it.   However,  as  the FreeType  project  is  copyrighted
 material, only  this license, or  another one contracted  with the
 authors, grants you  the right to use, distribute,  and modify it.
 Therefore,  by  using,  distributing,  or modifying  the  FreeType
 project, you indicate that you understand and accept all the terms
 of this license.

2. Redistribution
-----------------

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

   o Redistribution  of source code  must retain this  license file
     (`licence.txt') unaltered; any additions, deletions or changes
     to   the  original   files  must   be  clearly   indicated  in
     accompanying  documentation.   The  copyright notices  of  the
     unaltered, original  files must be preserved in  all copies of
     source files.

   o Redistribution in binary form must provide a  disclaimer  that
     states  that  the software is based in part of the work of the
     FreeType Team,  in  the  distribution  documentation.  We also
     encourage you to put an URL to the FreeType web page  in  your
     documentation, though this isn't mandatory.

 These conditions  apply to any  software derived from or  based on
 the FreeType code, not just  the unmodified files.  If you use our
 work, you  must acknowledge us.  However,  no fee need  be paid to
 us.

3. Advertising
--------------

 The names of  FreeType's authors and contributors may  not be used
 to endorse or promote  products derived from this software without
 specific prior written permission.

 We suggest,  but do not require, that  you use one or  more of the
 following phrases to refer  to this software in your documentation
 or advertising  materials: `FreeType Project',  `FreeType Engine',
 `FreeType library', or `FreeType Distribution'.

4. Contacts
-----------

 There are two mailing lists related to FreeType:

   o freetype@freetype.org

     Discusses general use and applications of FreeType, as well as
     future and  wanted additions to the  library and distribution.
     If  you are looking  for support,  start in  this list  if you
     haven't found anything to help you in the documentation.

   o devel@freetype.org

     Discusses bugs,  as well  as engine internals,  design issues,
     specific licenses, porting, etc.

   o http://www.freetype.org

     Holds the current  FreeType web page, which will  allow you to
     download  our  latest  development  version  and  read  online
     documentation.

 You can also contact us individually at:

   David Turner      <david.turner@freetype.org>
   Robert Wilhelm    <robert.wilhelm@freetype.org>
   Werner Lemberg    <werner.lemberg@freetype.org>


--- end of license.txt ---
)MYSTRING");



    libs.push_back(R"MYSTRING(SDL 1.2.15#
                   Simple DirectMedia Layer

                            (SDL)

                          Version 1.2

---
http://www.libsdl.org/

This is the Simple DirectMedia Layer, a general API that provides low
level access to audio, keyboard, mouse, joystick, 3D hardware via OpenGL,
and 2D framebuffer across multiple platforms.

The current version supports Linux, Windows CE/95/98/ME/XP/Vista, BeOS,
MacOS Classic, Mac OS X, FreeBSD, NetBSD, OpenBSD, BSD/OS, Solaris, IRIX,
and QNX.  The code contains support for Dreamcast, Atari, AIX, OSF/Tru64,
RISC OS, SymbianOS, Nintendo DS, and OS/2, but these are not officially
supported.

SDL is written in C, but works with C++ natively, and has bindings to
several other languages, including Ada, C sharp, Eiffel, Erlang, Euphoria,
Guile, Haskell, Java, Lisp, Lua, ML, Objective C, Pascal, Perl, PHP,
Pike, Pliant, Python, Ruby, and Smalltalk.

This library is distributed under GNU LGPL version 2, which can be
found below.  This license allows you to use SDL
freely in commercial programs as long as you link with the dynamic
library.

The best way to learn how to use SDL is to check out the header files in
the "include" subdirectory and the programs in the "test" subdirectory.
The header files and test programs are well commented and always up to date.
More documentation is available in HTML format in "docs/index.html", and
a documentation wiki is available online at:
http://www.libsdl.org/cgi/docwiki.cgi

The test programs in the "test" subdirectory are in the public domain.

Frequently asked questions are answered online:
http://www.libsdl.org/faq.php

If you need help with the library, or just want to discuss SDL related
issues, you can join the developers mailing list:
http://www.libsdl.org/mailing-list.php

Enjoy!
Sam Lantinga				(slouken@libsdl.org)#lgpl-2.0)MYSTRING");




libs.push_back(R"MYSTRING(SDL_mixer 1.2.12##/*
               SDL_mixer:  An audio mixer library based on the SDL library
               Copyright (C) 1997-2012 Sam Lantinga <slouken@libsdl.org>

               This software is provided 'as-is', without any express or implied
               warranty.  In no event will the authors be held liable for any damages
               arising from the use of this software.

               Permission is granted to anyone to use this software for any purpose,
               including commercial applications, and to alter it and redistribute it
               freely, subject to the following restrictions:

               1. The origin of this software must not be misrepresented; you must not
                  claim that you wrote the original software. If you use this software
                  in a product, an acknowledgment in the product documentation would be
                  appreciated but is not required.
               2. Altered source versions must be plainly marked as such, and must not be
                  misrepresented as being the original software.
               3. This notice may not be removed or altered from any source distribution.
             */)MYSTRING");



libs.push_back(R"MYSTRING(SDL_ttf 1.2.2#This library is a wrapper around the excellent FreeType 1.2 library, available at: http://www.freetype.org/#lgpl-2.0)MYSTRING");


libs.push_back(R"MYSTRING(SDL_image 1.2.12##/*
               SDL_image:  An example image loading library for use with SDL
               Copyright (C) 1997-2012 Sam Lantinga <slouken@libsdl.org>

               This software is provided 'as-is', without any express or implied
               warranty.  In no event will the authors be held liable for any damages
               arising from the use of this software.

               Permission is granted to anyone to use this software for any purpose,
               including commercial applications, and to alter it and redistribute it
               freely, subject to the following restrictions:

               1. The origin of this software must not be misrepresented; you must not
                  claim that you wrote the original software. If you use this software
                  in a product, an acknowledgment in the product documentation would be
                  appreciated but is not required.
               2. Altered source versions must be plainly marked as such, and must not be
                  misrepresented as being the original software.
               3. This notice may not be removed or altered from any source distribution.
             */

)MYSTRING");

    libs.push_back("Qt5.15.3#Source files can be obtained from http://www.qt.io.#lgpl-3.0");
    libs.push_back("MinGW-W64-builds-4.3.5##MinGW-w64");
    libs.push_back("libstdc++-6##gpl-3.0_runtime_exception");
    showLicenseDialog(libs);
    if(!waitLicenseDialogAccepted())
        return 0;



    /* seed pseudo random numbers generator */
    srand(time(NULL));

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return EXIT_FAILURE;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // initialize TTF library
    if ( TTF_Init() < 0 ) {
        fprintf(stderr, "Unable to initialize SDL_ttf: %s \n", TTF_GetError());
        return EXIT_FAILURE;
    }

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(1024, 768, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    char* windowTitleHeap;
    {
        const char* windowTitle = QObject::tr("WinPipeMania").toStdString().c_str();
        char ch = 0;
        int strSize = strcspn(windowTitle, &ch);
        windowTitleHeap = new char [strSize+1];
        memcpy(windowTitleHeap,windowTitle,sizeof(char)*(strSize+1));
    }

    char* iconTextHeap;
    {
        const char* iconText = QObject::tr("WinPipeMania").toStdString().c_str();
        char ch = 0;
        int strSize = strcspn(iconText, &ch);
        iconTextHeap = new char [strSize+1];
        memcpy(iconTextHeap,iconText,sizeof(char)*(strSize+1));
    }
    SDL_WM_SetCaption(windowTitleHeap, iconTextHeap);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // load an image
    QFile backgroundPath(":/background.gif");
    QString backgroundPathTemp = QDir::temp().absolutePath() + "/" + backgroundPath.fileName().split("/").last();
    backgroundPath.copy(backgroundPathTemp);
    SDL_Surface* background = IMG_Load(backgroundPathTemp.toUtf8());
    if (!background)
    {
        printf("Unable to load background: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    QFile pipesPath(":/pipes.gif");
    QString pipesPathTemp = QDir::temp().absolutePath() + "/" + pipesPath.fileName().split("/").last();
    pipesPath.copy(pipesPathTemp);
    SDL_Surface* pipes_sprite = IMG_Load(pipesPathTemp.toUtf8());
    if (!pipes_sprite)
    {
        printf("Unable to load pipesSprite: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    QFile pipes2Path(":/pipes2.gif");
    QString pipes2PathTemp = QDir::temp().absolutePath() + "/" + pipes2Path.fileName().split("/").last();
    pipes2Path.copy(pipes2PathTemp);
    SDL_Surface* pipes_sprite_2 = IMG_Load(pipes2PathTemp.toUtf8());
    if (!pipes_sprite_2)
    {
        printf("Unable to load pipesSprite2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    QFile splashPath(":/kct_logo.gif");
    QString splashPathTemp = QDir::temp().absolutePath() + "/" + splashPath.fileName().split("/").last();
    splashPath.copy(splashPathTemp);
    SDL_Surface* splash = IMG_Load(splashPathTemp.toUtf8());
    if (!splash)
    {
        printf("Unable to load kct logo: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (screen->w - background->w) / 2;
    dstrect.y = (screen->h - background->h) / 2;

    LOG(logINFO) << "Game started !";

    Controller controller = Controller(screen, &dstrect, background, pipes_sprite, pipes_sprite_2, splash);

    // program main loop
    bool done = false;
    unsigned int ticks_now, next_game_tick = SDL_GetTicks();
    while (!done)
    {
        controller.Update();

        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }

            case SDL_MOUSEBUTTONDOWN:
                {
                    if(event.button.button == SDL_BUTTON_LEFT) {
                        int x, y;
                        SDL_GetMouseState(&x, &y);
                        controller.mouseClick(x, y);
                        break;
                    }
                }
            }

            // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        controller.Draw();
        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);

        // sleep until next frame
        next_game_tick += SKIP_TICKS;
        ticks_now = SDL_GetTicks();
        SDL_Delay(( next_game_tick > ticks_now ) ? next_game_tick - ticks_now : 0);
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(background);
    SDL_FreeSurface(pipes_sprite);
    SDL_FreeSurface(pipes_sprite_2);

    delete[] windowTitleHeap;
    delete[] iconTextHeap;
    // all is well ;)
    printf("Exited cleanly\n");
    return EXIT_SUCCESS;
}
