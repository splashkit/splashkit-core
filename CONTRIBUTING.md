# SplashKit development

## macOS

### Install prerequisites

1. `git` and `make` are installed by default.
2. Install `XCode` and Command Line Tools

   ```sh
   xcode-select --install
   ```

### Build & test

1. [Create a fork](https://guides.github.com/activities/forking/) of SplashKit.
2. Clone the forked repository into your preferred location.

   ```sh
   git clone --recursive -j2 https://github.com/<username>/splashkit-core.git
   ```

3. Build the test project:

   - In a terminal application, go into the cloned directory of your SplashKit
     fork, and type:

     ```sh
     cd projects/cmake
     cmake .
     make
     ```

4. Run the test program by executing

   ```sh
   cd ../../bin
   ./sktest
   ```

5. Add features to code in

   ```sh
   ./coresdk
   ```

6. Add test code into `coresdk/src/test`. Now you should be good to go.

## Linux

### Install prerequisites

1.  Update your system

    ```sh
    sudo apt-get update
    sudo apt-get upgrade -y
    ```

2.  Install the packages

    ```sh
    sudo apt-get install -y \
      git build-essential cmake g++ libpng-dev libcurl4-openssl-dev libsdl2-dev \
      libsdl2-mixer-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-net-dev libsdl2-ttf-dev \
      libmikmod-dev libbz2-dev libflac-dev libvorbis-dev libwebp-dev libfreetype6-dev
    ```

### Build & test

1.  [Create a fork](https://guides.github.com/activities/forking/) of SplashKit.
2.  Clone the forked repository into your preferred location.

    ```sh
    git clone --recursive -j2 https://github.com/<username>/splashkit-core.git
    ```

3.  Build the test project:

    - In a terminal application, go into the cloned directory of your SplashKit
      fork, and type:

      ```sh
      cd projects/cmake
      cmake .
      make
      ```

4.  Run the test program by executing

    ```sh
    cd ../../bin
    ./sktest
    ```

5.  Add features to code in

    ```sh
    ./coresdk
    ```

6.  Add test code into `coresdk/src/test`. Now you should be good to go.

## Windows

### Install prerequisites

1. Install [MSYS2](https://www.msys2.org/) subsystem and follow installer
   instructions - use defaults if unsure, **DO NOT INSTALL TO DIRECTORY WITH SPACES!**
2. Install SplashKit SDK

   - Go into MSYS2 terminal emulator and install [Git](https://git-scm.com/) over MSYS2 subsystem by typing:
     ```sh
     pacman -S git --noconfirm --disable-download-timeout
     ```
   - Now clone and install SplashKit via install-scripts:
     ```sh
     bash <(curl -s https://raw.githubusercontent.com/splashkit/skm/master/install-scripts/skm-install.sh)
     ```
   - Restart terminal, type the following command in terminal to verify successfully installation.
     ```sh
     skm
     ```

3. Install language tools (compilers / libs):

   - For C#, install the DotNet core SDK.
   - For C++, install GNU Compiler Collection (GCC) - g++ and clang++ in MSYS2.
     - Run the following command in terminal:
       ```sh
       pacman --disable-download-timeout -S mingw-w64-{x86_64,i686}-gcc mingw-w64-{i686,x86_64}-gdb
       ```
     - Do not run compiler from main MSYS2 MSYS terminal, instead run from MSYS2 MinGW32 or MinGW64 terminals.

4. Install remaining tools to build Splashkit:

   - Install `cmake`
     ```sh
     pacman -S mingw-w64-x86_64-cmake
     ```
   - Install `make`
     ```sh
     pacman -S mingw-w64-x86_64-make
     ```

### Build & test

1. [Create a fork](https://guides.github.com/activities/forking/) of SplashKit.
2. Clone the forked repository into your preferred location.

   ```sh
   git clone --recursive -j2 https://github.com/<username>/splashkit-core.git
   ```

3. Build the test project:

   - Go into the cloned directory of your SplashKit fork, open a MinGw-W64 MSYS2 shell and type:
     ```sh
     cd projects/cmake
     cmake -G "Unix Makefiles" .
     make
     ```
   - Note: if the above does not work, try using the actual Unix `make` and `cmake`
     installations, rather than the MinGw-specific ones; but do not try a
     combination of both. Remove packages using the following command

     ```sh
     pacman -Rs <package>
     pacman -S cmake make
     ```

4. Run the test program by executing

   ```sh
   cd ../../bin
   ./sktest
   ```

5. Add features to code in

   ```sh
   ./coresdk
   ```

6. Add test code into `coresdk/src/test`. Now you should be good to go.
