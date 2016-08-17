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
  -  In Terminal run this command: ```/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"```.
  -  Use brew to install basic tools.
  -  Write into terminal window: ```brew install git svn mercurial```.
  -  (optional) brew cask install atom.
2.  Install XCode.
  -  Install Command Line Tools by writing this into the terminal: ```xcode-select --install```.
3.  Clone repositry
  -  In Terminal, make a working directory (can also be on cloud) and then move into the directory using: ```cd <YourProjFolder>```.
  -  from in the directory run the git clone command ```git clone <url>```
4.  setup
  -  using `cd` go to the directory location: ```splashkit/coresdk/external```
  -  Run setup.sh with  ```./setup.sh```
  -  Go to the ```coresdk/project``` folder and open in XCode.
  -  Build and Run from in XCode.


### Windows

1. MSys2
1.1  
