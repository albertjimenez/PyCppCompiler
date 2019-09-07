# Python C++ gecode compiler
This is a workaround to use CLion and the library Gecode http://www.gecode.org.
The tutorial contains the section of **[Installation](#installation)**, **[Testing](#testing)** and a little **[Tip](#tip)**


## <a name="installation"><a/>Installation
The instructions to automate the build and compile execution are this ones:

- Go to Build settings right here

![1](https://i.imgur.com/Gwk08lC.png)
- Then edit the configuration by removing the build option. Select the build icon with the green hammer and then using 
the symbol '-' remove it from the list.
- Now is the time to add our own configuration script tool. Click the '+' button and select ``Run External Tool``.
- Again use the '+' to add a new external tool.
- Finally complete the fields; Name, Program and Arguments like this. Basically the program is where python
is located while the arguments will be the script ``compiler.py`` ABSOLUTE PATH and the CLion Macro called `$FilePath$` that is responsible
to detect the absolute route to the file that we are working. 
![2](https://i.imgur.com/GBGhgwM.png)
- As a demonstration, here it is the execution once we use this script. It can be used from the Build menu or even better, right click on the desired C++ file and then external tool - Python Compiler or the name you set on the external tool. As it is parametrized by the selected file, it can be compile and execute whatever file you want, say no more to the single `main.cpp` file
![3](https://i.imgur.com/2BRzpws.png)

## <a name="testing"><a/>Testing
Clone this repository and then use `python3 compile.py -t` to test the folder `gecode_examples`. It will compile and run every **.cpp** inside of it.
## <a name="tip"><a/>Tip

PS: If you want to trigger and active the autocomplete feature, in the Clion CMake file just type `include_directories(/Library/Frameworks/gecode.framework/Headers)` where this route may change on different O.S. (Mac only) you need to locate where are the libraries .h files. 