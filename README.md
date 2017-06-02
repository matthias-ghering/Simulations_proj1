# Prerequisites
- [MinGW (32 bit)](https://sourceforge.net/projects/mingw/files/latest/download)
- Clion

When installing MinGW, select the base package and c++ package. When installing CLion, select MinGW, not Cygwin, when
asked to do so. For all options not included in MinGW (for example a debugger), select the default CLion options.
Import the project in CLion, and the CMakeLists.txt file should do the rest.

## Static Linking of freeglut
We were not able to statically link freeglut during compilation.
Although there are several posts out there that specify how to solve this problem([here](http://mattfife.com/?p=226) and [here](http://www.transmissionzero.co.uk/computing/using-glut-with-mingw/))
Therefore, the resulting binary requires `freeglut.dll` to be present on the system.
In our *CmakeLists.txt* file, we have included a post build command that copies this required dll to the `cmake-build-debug` folder
after building has been done. This is the location in which the binary will also be placed after compilation, so this is quite handy.

