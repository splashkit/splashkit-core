# SplashKit


## Building SplashKit

Requires
- clang Compiler
- git
- mac
  - XCode
- Windows
  - MSys2


##  Steps for setting up
### Mac

1. Install brew.
1.1  In Terminal run this command: ```/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"```.
1.2  Use brew to install basic tools.
1.3  Write into terminal window: ```brew install git svn mercurial```.
1,4  (optional) brew cask install atom.
2.  Install XCode.
2.1  Install Command Line Tools by writing this into the terminal: ```xcode-select --install```.
3.  Clone repositry
3.1  In Terminal, make a working directory (can also be on cloud) and then move into the directory using: ```cd <YourProjFolder>```.
3.2  from in the directory run the git clone command ```git clone <url>```
4.  setup
4.1  using `cd` go to the directory location: ```splashkit/coresdk/external```
4.2  Run setup.sh with  ```./setup.sh```
4.3  Go to the ```coresdk/project``` folder and open in XCode.
4.4  Build and Run from in XCode.

 
### Windows

1. MSys2
1.1  
