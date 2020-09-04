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
  -  In Terminal run this command: ```/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"```.
  -  Use brew to install basic tools.
  -  Write into terminal window: ```brew install git svn mercurial```.
  -  (optional) brew cask install atom.
2.  Install XCode.
  -  Install Command Line Tools by writing this into the terminal: ```xcode-select --install```.
3.  Clone repository
  -  In Terminal, make a working directory (can also be on cloud) and then move into the directory using: ```cd <YourProjFolder>```.
  -  from in the directory run the git clone command ```git clone <url>```
4.  setup
  -  using `cd` go to the directory location: ```splashkit/coresdk/external```
  -  Run setup.sh with  ```./setup.sh```
  -  Go to the ```coresdk/project``` folder and open in XCode.
  -  Build and Run from in XCode.  

### Windows
1. If an issue, potentially consider **temporarily** disabling antivirus software.
2. Install [MSYS2](https://www.msys2.org/) subsystem and follow fairly self-explanatory installer instructions &ndash; use defaults if unsure, **DO NOT INSTALL TO DIRECTORY WITH SPACES!**
3. Install core Splashkit SDK
    - Go into MSYS2 terminal emulator and install [Git](https://git-scm.com/) over MSYS2 subsystem by typing : ```pacman -S git --noconfirm --disable-download-timeout```
    - Now clone and install Splashkit via install-scripts: ```bash <(curl -s https://raw.githubusercontent.com/splashkit/skm/master/install-scripts/skm-install.sh)```
    - Restart terminal, type ```skm``` in terminal after restarting to verify successful install.
4. Install [VSCode](https://code.visualstudio.com/).
5. Install language tools (compilers / libs):
    - For C#, install the DotNet core sdk.
    - For C++, install GNU Compiler Collection (GCC) - g++ and clang++ in MSYS2.
      - Run the following command in terminal: ```pacman --disable-download-timeout -S mingw-w64-{x86_64,i686}-gcc mingw-w64-{i686,x86_64}-gdb```
      - Do not run compiler from main MSYS2 MSYS terminal, instead run from MSYS2 MinGW32 or MinGW64 terminals.
6. Install  remaining tools to build Splashkit:
    - Install cmake: ```pacman -S mingw-w64-x86_64-cmake```8
    - install make: ```pacman -S mingw-w64-x86_64-make```
7. Build the test project:
    - Go into the cloned directory of your Splashkit fork, open a MinGw-W64 MSYS2 shell and type: ```cd projects/cmake``` ```cmake -G "Unix Makefiles" .``` ```make```
    - Note: if the above does not work, try using the actual unix make and cmake installations, rather than the MinGw-specific ones; but do not try a combination of both. Remove packages with ```pacman -Rs <package>``` and ```pacman -S cmake make```
8. Run the test program by executing ```cd ../../bin``` ```./sktest```
9. Add features to code in ```./coresdk```
10. Add test code into ```coresdk/src/test```
Now you should be good to go.