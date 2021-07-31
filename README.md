GiraffeMoor
===========

**Table of contents**

- [Introduction](#introduction)
- [Dependencies](#dependencies)
- [Building and compiling](#building-and-compiling)
- [Executing](#executing)
- [User defined language for Notepad++](#user-defined-language-for-notepad)
- [Some disclaimers...](#some-disclaimers)

#  Introduction

**GiraffeMoor** is a preprocessor tool for the FEM platform **Giraffe** (acronym of “Generic Interface Readily Accessible for Finite Elements”), 
started by [Prof. Alfredo Gay Neto](http://sites.poli.usp.br/p/alfredo.gay/#me-section) at the [University of São Paulo](https://www5.usp.br/#english), Brazil. 
The main goal of **GiraffeMoor** is to generate FEM models of mooring systems with very few information and invoke Giraffe to solve it. 
**GiraffeMoor** also provides a summary of the mooring system, based on its statics. :anchor:


# Dependencies

**GiraffeMoor** only depends on [Intel oneMKL](https://software.intel.com/content/www/us/en/develop/documentation/get-started-with-mkl-for-dpcpp/top.html), 
which is part of the [Intel oneAPI](https://software.intel.com/content/www/us/en/develop/tools/oneapi.html#gs.409kvt).

Just make sure to get **`version 2021.3.0`**  or later.  There is no need to install the plugin for Visual Studio, the linking will be done by the CMake file. 


# Building and compiling

You can build the solution with [CMake](https://cmake.org/) and the auxiliary batch files. Thus, install the current CMake before proceeding.

:warning: Do not forget to get **oneMKL**: [download](https://software.intel.com/content/www/us/en/develop/tools/oneapi/base-toolkit/download.html) 
and install `version 2021.3.0` or later. Earlies versions do not include the `Config.cmake` file.

Then, follow these steps:
  1. Clone [this repository](https://github.com/G-R-Martins/GiraffeMoor)

```cmd
git clone https://github.com/G-R-Martins/GiraffeMoor.git
```

  2. Run the batch file according to your desire. You have 4 options: 
     1. `gen_and_build.bat`: generate and build the solution without open Visual Studio
     2. `build.bat`: build, by default, Debug solution
     3. `openVS.bat`: open Visual Studio solution (I guess the lazy one, like me, doesn't like to get the .sln in ./build folder)
     4. `all_actions.bat`: generate and build (debug) the solution, then open Visual Studio

And that's it! :grin: :tada:


# Executing 

As **oneMKL** creates environment variables, its DLLs are accessible  after compiling the code or download the GiraffeMoor executable (see [releases](https://github.com/G-R-Martins/GiraffeMoor/releases)) 
you can move the executable `GiraffeMoor.exe` to any desirable directory on your computer.

```cmd
<exe_dir>
├─────Giraffe.exe
└─────<inp_name>
      └─────<inp_name>.inp
```

1. from command line:
   ```cmd
   cd <executable dir>
   giraffe <input name>
   ```
2. opening the executable and typing the `<input name>` when asked for it. 



# User defined language for Notepad++

Despite the fact the input file is designed to be short and comprehensive, it is provided a defined language for [Notepad++](https://notepad-plus-plus.org/downloads/) to help you identify possible typos and invalid keywords in the GiraffeMoor input file - with the extension `.gmr`.


# Some disclaimers...

  - IDE and OS supported: 
    
    Currently, GiraffeMoor is build and test only with [Microsoft Visual Studio](https://visualstudio.microsoft.com/) and Windows platform. 
    I plan to expand to Linux and Mac, support other compilers, and do other stuff, but this is far from being the priority at this moment - also because Giraffe is available only for Windows at this moment.
  
  - Coding style:
    
    The code is an academic program and nowadays maintained only by me - a civil engineer and MSc student, not exactly a brilliant programmer, 
    and that has had the first contact with the C/C++ languages for this project. 
    Also, the first scratch of GiraffeMoor had a huge influence of the C language, thus there are still lots of raw pointers and unsafe functions (like fscanf), for example.
    
    Of course, I'm still studying the language/tools and I plan to "update the code" to modern C++ 
    ~~depending on my free time~~, not because *"I must write in a C++ style"* as some StackOverflow users say, but to learn and
    practice different things. 
    
    Check the [projects](https://github.com/G-R-Martins/GiraffeMoor/projects) and **don't hesitate to make suggestions and corrections, please!**
  