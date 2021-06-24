# GiraffeMoor

**GiraffeMoor** is a preprocessor tool for the FEM platform **Giraffe** (acronym of “Generic Interface Readily Accessible for Finite Elements”), 
started by [Prof. Alfredo Gay Neto](https://github.com/alfredogneto) at the [University of São Paulo](https://www5.usp.br/#english), Brazil. 
The main goal of **GiraffeMoor** is to generate FEM models of mooring systems with very few information and invoke **Giraffe** to solve it.

For more information about `Giraffe Project`, refer to [Prof. Alfredo Gay Neto's personal page](http://sites.poli.usp.br/p/alfredo.gay) and publications.
[Giraffe users' manual](http://sites.poli.usp.br/p/alfredo.gay/giraffe/GIRAFFE_Manual.pdf) 
and some [tutorials](http://sites.poli.usp.br/p/alfredo.gay/giraffe/GIRAFFE_Tutorials.pdf) are also available.


## Dependencies

**GiraffeMoor** only depends on [Intel oneMKL](https://software.intel.com/content/www/us/en/develop/documentation/get-started-with-mkl-for-dpcpp/top.html), 
which is part of the [Intel oneAPI](https://software.intel.com/content/www/us/en/develop/tools/oneapi.html#gs.409kvt).
Thus, it is very simple to setup it: 

  1. Download oneAPI [here](https://software.intel.com/content/www/us/en/develop/tools/oneapi/components/onemkl.html#gs.40957n);
  2. Install and make sure to mark `Intel® oneAPI Math Kernel Library` option.
  
And that is it!
If you aren't familiar with this tool, OneAPI known that oneAPI has an extension for Visual Studio that simplifies a lot its use! 
You don't have to explicitly link the lib/dll to your projects, all you have to do is tell VS you are using oneMKL and include the headers in your source files.


## Building

You can build the solution with [CMake](https://cmake.org/) following these steps:

  1. Clone [this repository](https://github.com/G-R-Martins/GiraffeMoor);
  
   - For example, from command line, go to desirable directory and type: 
  
  ```
  git clone https://github.com/G-R-Martins/GiraffeMoor
  ```
  3. Open the command prompt and go to the repository root folder; 
  5. Create a folder to build the solution and invoke CMake from there:
  ```cmd
  mkdir build
  cd build 
  cmake ..\
  ```
  4. Now, you have to include oneMKL:
  - In the Visual Studio solution explorer, rigt click in the `GiraffeMoor project` and hit `properties` (or select this project in the VS solution explorer 
    and type `Alt+Enter`)
  - Go to `Intel Libraries for oneAPI -> Intel oneAPI Math Kernel Library (oneMKL)` and set `Parallel` for use oneMKL option 
  5. Finally, just go to `Build -> Build solution` (or type `Ctrl+Shift+B`).

  
## Some disclaimers...

  - IDE and OS supported: 
    
    Currently, **GiraffeMoor** is build and test only with [Microsoft Visual Studio](https://visualstudio.microsoft.com/) and Windows platform. 
    I plan to expand to Linux and Mac, support other compilers, and do other stuff, but this is far from be the priority at this moment.
  
  - Coding style:
    
    The code is an academic program and nowadays maintained only by me - a civil engineer and MSc student, not exactly a brilliant programmer, 
    and that has had the first contact with the C/C++ languages with this program. Of course, I'm still studying the language/tools and I 
    plan to "update the code" to modern C++ style, not because it's "better" or "I must write in a C++ style" as some StackOverflow users say, but to learn and
    practice different things. 
    
    *PS: Actually, I've been doing this for some time ~depending on my free time~. Check the [projects](https://github.com/G-R-Martins/GiraffeMoor/projects) 
    in this repository and **don't hesitate to make suggestions and corrections, please!***
  
  - External dependencies:
  
    Although _~~for now~~_ **GiraffeMoor** performs considerable simple operations (such as "small" matrix multiplication and inversion) it uses a powerful 
    and fast library, which one may think is a little overkill and/or prefer other simpler libraries (like [Armadillo](http://arma.sourceforge.net)), or even a personal implementation.
    Of course, it would be simpler to build and link the program without external dependencies, but **GiraffeMoor** may - and probably will - have other features, 
    and have a library like MKL on hand can be helpful. 

