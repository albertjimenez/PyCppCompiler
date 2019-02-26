'''
Created by Albert Sendros Jimenez for MSc in Artificial Intelligence.
Automator script to compile and execute c++ code using gecode library.
'''
import sys
from platform import system
import subprocess
import os

# MAC
MAC_COMPILER = "g++ -framework gecode -std=c++11 -o {0} {1}"
# LINUX
LINUX_COMPILER_1 = "g++ -I/usr/local/include –c {0}"  # {0} is the filename
LINUX_COMPILER_2 = "g++ -o {0} -L/usr/local/lib {1} –lgecodesearch –lgecodeminimodel –lgecodeint -lgecodekernel " \
                   "-lgecodesupport "  # {0} is the filename and {1} is the target executable


def get_parameters() -> str:
    if len(sys.argv) != 2:
        print("USAGE: python3 compiler.py FILE.CPP")
        print("EXITING...")
        exit(1)
    return sys.argv[1]


def compile_cpp(filename: str):
    if system() == "Darwin":
        print("Compiling for Mac")
        compile_mac(filename)
    elif system() == "Windows":
        print("Compiling for Windows")
        compile_windows(filename)
    else:
        print("Compiling for Linux")
        compile_linux(filename)


def run(output_file: str):
    subprocess.run(output_file)


def compile_mac(filename: str):
    output_name = filename[:-4]
    compiled_out = subprocess.getoutput(MAC_COMPILER.format(output_name, filename))
    if compiled_out == "":
        print("Compiled successfully\n EXECUTING {0}:\n".format(output_name))
        print("===============================================")
        run(output_name)
    else:
        print("Check the results of the compilation {0}\n".format(output_name), compiled_out)


def compile_linux(filename: str):
    output_name = filename[:-4]
    compiled_out_1, compiled_out_2 = subprocess.getoutput(LINUX_COMPILER_1.format(filename)), subprocess.getoutput(
        LINUX_COMPILER_2.format(filename, output_name))
    if os.path.isfile(output_name):
        print("Compiled successfully... Running\n")
        print("===============================================")
        run(output_name)
    else:
        print("SOMETHING WENT WRONG...Printing the output")
        print("FIRST COMMAND:\n", compiled_out_1)
        print("SECOND COMMAND:\n", compiled_out_2)


def compile_windows(filename: str):
    pass


def main():
    filename = get_parameters()
    compile_cpp(filename)


if __name__ == '__main__':
    main()
