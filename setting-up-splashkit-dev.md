# SplashKit Development
<!--Original author: @ClancyLight (GitHub username), committed by Andrew Cain (GitHub @macite <macite@gmail.com>
Modified by Nathaniel Schmidt <schmidty2244@gmail.com> (GitHub @njsch) on 04/09/2020-->

## Building SplashKit

Requires
- Base-level reqs
  - clang Compiler
  - git
- OS-specific reqs
  - mac
    - XCode
  - Windows
    - MSYS2

If you are reading this then you have probably already found the Splashkit-core Git repo, at least via the web client interface.  To Follow these instructions you will need to [fork and clone](https://guides.github.com/activities/forking/) the Splashkit core SDK.

##  Steps for setting up
### Mac

1. Install brew.
  -  In Terminal run this command:   ```/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"  ```.
  -  Use brew to install basic tools.
  -  Write into terminal window:   ```brew install git svn mercurial  ```.
  -  (optional) brew cask install atom.
2.  Install XCode.
  -  Install Command Line Tools by writing this into the terminal:   ```xcode-select --install  ```.
3.  Clone repository
  -  In Terminal, make a working directory (can also be on cloud) and then move into the directory using:   ```cd <YourProjFolder>  ```.
  -  from in the directory run the git clone command   ```git clone <url>  ```
4.  setup
  -  using `cd` go to the directory location:   ```splashkit/coresdk/external  ```
  -  Run setup.sh with    ```./setup.sh  ```
  -  Go to the   ```coresdk/project  ``` folder and open in XCode.
  -  Build and Run from in XCode.  

### Windows
* If an issue, potentially consider **temporarily** disabling antivirus software.
* Install [MSYS2](https://www.msys2.org/) subsystem and follow fairly self-explanatory installer instructions &ndash; use defaults if unsure, **DO NOT INSTALL TO DIRECTORY WITH SPACES!**
* Install core Splashkit SDK
    - Go into MSYS2 terminal emulator and install [Git](https://git-scm.com/) over MSYS2 subsystem by typing :
      ```
    pacman -S git --noconfirm --disable-download-timeout
      ```
    - Now clone and install Splashkit via install-scripts:
      ```
    bash <(curl -s https://raw.githubusercontent.com/splashkit/skm/master/install-scripts/skm-install.sh)
      ```
    - Restart terminal, type
      ```
    skm
      ```
    in terminal after restarting to verify successful install.
* Install [VSCode](https://code.visualstudio.com/).
* Install language tools (compilers / libs):
    - For C#, install the DotNet core sdk.
    - For C++, install MinGW-W64: a Windows port of GNU Compiler Collection (GCC) - g++ and clang++ in MSYS2.
      - Run the following command in terminal:
        ```
      pacman --disable-download-timeout -S mingw-w64-{x86_64,i686}-gcc mingw-w64-{i686,x86_64}-gdb
        ```
      - Do not run compiler from main MSYS2 MSYS terminal, instead run from MSYS2 MinGW32 or MinGW64 terminals.
* Install  remaining tools to build Splashkit:
    - Install cmake:
      ```
    pacman -S mingw-w64-x86_64-cmake
      ```
    - install make:
      ```
    pacman -S mingw-w64-x86_64-make
      ```
* Build the test project:
    - Go into the cloned directory of your Splashkit fork, open a MinGw-W64 MSYS2 shell and type:
      ```
    cd projects/cmake
     ```
      ```
    cmake -G "Unix Makefiles" .
      ```
      ```
    make
      ```
    - Note: if the above does not work, try using the actual unix make and cmake installations, rather than the MinGw-specific ones; but do not try a combination of both. Remove packages with
      ```
    pacman -Rs <package>
      ```
    and
      ```
    pacman -S cmake make
      ```
* Run the test program by executing
    ```
    cd ../../bin
    ```
    ```
    ./sktest
      ```
* Add features to code in
    ```
    ./coresdk
    ```
* Add test code into
    ```
    coresdk/src/test
    ```
Now you should be good to go.

## Developing and building extension and test code for Splashkit
Although concise instructions are contained above, further substantiation may be required for a beginner as to precisely how to write (and implement the appropriate test) code for the Splashkit backend and / or core SDK.  This information is provided in the hope that one no will longer necessarily need to search the code to figure out how to do this by oneself.

If you have gotten this far then it is assumed that you already know how to recursively Git clone your already-created fork of the splashkit-core repository on GitHub.  Being keen to start working, you can do the following:

1. From your cloned fork, you can add your new coded extensions into ```./coresdk```.
  -  If you are writing backend code such as a driver for a core module, you can add source and header files into ```coresdk/src/backend```.
  -  If you are writing a module or extension that will be used by other third-party applications using Splashkit, you can add it directly into ```coresdk/src/coresdk```.
  -  When writing the code, ensure that callable types, procedures and functions are placed directly into the Splashkit library namespace.  You can do this in one of two ways:
    -    Utilise global access in your source file by typing
    ```using namespace splashkit_lib;```
    -    To be more flexable, identify which components of the file you want included by creating a splashkit_lib scope i.e.
    ```namespace splashkit_lib
    {
    ...
    }```
2. Once you think you may have the code working, you can add the test code by placing it into coresdk/src/test.
  -  First, Create a ```test_<ext>``` file, where ```<ext>``` is the name of the extension i.e. ```animations```.
  -  Ensure this file globally uses the splashkit_lib namespace.
  -  Within the same file, declare a ```run_<ext>_test``` procedure (void function) and place in a sequence(s) to test your new code.
  -  Next, edit ```coresdk/src/test/test_main.cpp```, move to its declared ```setup_tests()``` procedure, call the ```add_test``` procedure and pass in
 (a) the test's name as a string i.e. ```"animations"```; and (b) pass in the function running the test i.e. ```run_animation_test```.
3. Re-build the test project contained in ```./projects/cmake``` (See Windows build instructions for immediate help if unsure from the line staring with &ldquo;Run the test program&rdquo;, should work on any platform from that point) and you're done.