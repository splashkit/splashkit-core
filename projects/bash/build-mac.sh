#!/bin/sh
#
rm libsplashkit.a

LIBSRC_DIR="../../coresdk/src/coresdk"

for file in `find ${LIBSRC_DIR} | grep [.]cpp$` ; do
  name=${file##*/} # ## = delete longest match for */... ie all but file name
  name=${name%%.cpp} # %% = delete longest match from back, i.e. extract .cpp
  out_file="./out/${name}.o"

  clang++ -arch x86_64 --std=c++1y -stdlib=libc++ -O0 -Werror -Wno-missing-field-initializers -Wno-missing-prototypes -Werror=return-type -Wunreachable-code -Werror=deprecated-objc-isa-usage -Werror=objc-root-class -Wnon-virtual-dtor -Woverloaded-virtual -Wno-exit-time-destructors -Wno-missing-braces -Wparentheses -Wswitch -Wunused-function -Wno-unused-label -Wno-unused-parameter -Wunused-variable -Wunused-value -Wempty-body -Wconditional-uninitialized -Wno-unknown-pragmas -Wshadow -Wfour-char-constants -Wno-conversion -Wconstant-conversion -Wint-conversion -Wbool-conversion -Wenum-conversion -Wshorten-64-to-32 -Wno-newline-eof -Wc++11-extensions -DDEBUG=1 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk -fasm-blocks -fstrict-aliasing -Wdeprecated-declarations -Winvalid-offsetof -mmacosx-version-min=10.11 -g -Wno-sign-conversion  -I../../coresdk/external/mongoose -I../../coresdk/external/SDL/include -I../../coresdk/external/SDL_ttf -I../../coresdk/external/SDL_mixer -I../../coresdk/external/SDL_gfx -I../../coresdk/external/SDL_image -I../../coresdk/external/SDL_net -I../../coresdk/external/SDL_image/external/libpng-1.6.2 -I../../coresdk/src/backend -I../../coresdk/src/coresdk  -Wall -c $file -o $out_file
done

LIBSRC_DIR="../../coresdk/src/backend"

for file in `find ${LIBSRC_DIR} | grep [.]cpp$` ; do
  name=${file##*/} # ## = delete longest match for */... ie all but file name
  name=${name%%.cpp} # %% = delete longest match from back, i.e. extract .cpp
  out_file="./out/${name}.o"

  clang++ -arch x86_64 --std=c++1y -stdlib=libc++ -O0 -Werror -Wno-missing-field-initializers -Wno-missing-prototypes -Werror=return-type -Wunreachable-code -Werror=deprecated-objc-isa-usage -Werror=objc-root-class -Wnon-virtual-dtor -Woverloaded-virtual -Wno-exit-time-destructors -Wno-missing-braces -Wparentheses -Wswitch -Wunused-function -Wno-unused-label -Wno-unused-parameter -Wunused-variable -Wunused-value -Wempty-body -Wconditional-uninitialized -Wno-unknown-pragmas -Wshadow -Wfour-char-constants -Wno-conversion -Wconstant-conversion -Wint-conversion -Wbool-conversion -Wenum-conversion -Wshorten-64-to-32 -Wno-newline-eof -Wc++11-extensions -DDEBUG=1 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk -fasm-blocks -fstrict-aliasing -Wdeprecated-declarations -Winvalid-offsetof -mmacosx-version-min=10.11 -g -Wno-sign-conversion  -I../../coresdk/external/SDL/include -I../../coresdk/external/SDL_ttf -I../../coresdk/external/SDL_mixer -I../../coresdk/external/mongoose -I../../coresdk/external/SDL_gfx -I../../coresdk/external/SDL_image -I../../coresdk/external/SDL_net -I../../coresdk/external/SDL_image/external/libpng-1.6.2 -I../../coresdk/src/backend -I../../coresdk/src/coresdk  -Wall -c $file -o $out_file
done

libtool -static -framework AudioToolbox -framework AudioUnit -framework CoreAudio -framework CoreVideo -framework IOKit -framework OpenGL -framework Carbon -framework ForceFeedback -framework Cocoa -L../../coresdk/lib/mac -lbz2 -lFLAC -lSDL2_mixer -lsmpeg2 -lvorbis -lz -lpng16 -lvorbisfile -lSDL2 -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lmikmod -logg -lwebp -lSDL2_net -lfreetype -arch_only x86_64 out/*.o -o libsplashkit.a
