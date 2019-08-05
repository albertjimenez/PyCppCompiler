'''
Created by Albert Sendros Jimenez for MSc in Artificial Intelligence.
Automator script to compile and execute c++ code using gecode library.
'''
import sys
from platform import system
import subprocess
import os

# MAC
MAC_COMPILER = "g++ -F/Library/Frameworks -std=c++11 -o {0} -framework gecode {1}"
# LINUX
LINUX_COMPILER_1 = "g++ -I/usr/local/include –c {0}"  # {0} is the filename
LINUX_COMPILER_2 = "g++ -o {0} -L/usr/local/lib {1} –lgecodesearch –lgecodeminimodel –lgecodeint -lgecodekernel " \
                   "-lgecodesupport "  # {0} is the filename and {1} is the target executable
# Gecode examples folder
CODE_EXAMPLES = "gecode_examples"


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
    output_name = filename[:-4] + ".o"
    compiled_out = subprocess.getoutput(MAC_COMPILER.format(output_name, filename))
    if compiled_out == "":
        print("Compiled successfully\n EXECUTING {0}:\n".format(output_name))
        print("===============================================")
        run("./" + output_name)
    else:
        print("Check the results of the compilation {0}\n".format(output_name), compiled_out)


def compile_linux(filename: str):
    output_name = filename[:-4] + ".o"
    compiled_out_1, compiled_out_2 = subprocess.getoutput(LINUX_COMPILER_1.format(filename)), subprocess.getoutput(
        LINUX_COMPILER_2.format(filename, output_name))
    if os.path.isfile(output_name):
        print("Compiled successfully... Running\n")
        print("===============================================")
        run("./" + output_name)
    else:
        print("SOMETHING WENT WRONG...Printing the output")
        print("FIRST COMMAND:\n", compiled_out_1)
        print("SECOND COMMAND:\n", compiled_out_2)


def compile_windows(filename: str):
    output_name = filename[:-4] + ".exe"
    pass


def is_cpp_file(filename: str) -> bool:
    if len(filename) < 5:
        return False
    return filename[-4:] == ".cpp"


def test_gecode_examples():
    if os.path.exists(CODE_EXAMPLES):
        current_files = os.listdir(CODE_EXAMPLES)
        cpp_files = list(filter(is_cpp_file, current_files))
        for file in cpp_files:
            compile_cpp("{}/{}".format(CODE_EXAMPLES, file))
        print("\n"
              "If you see this, everything was tested properly and you can use freely this script with any .cpp file")
    else:
        print("Directory {} does not exists, please clone the entire repository if you want to perform test".format(
            CODE_EXAMPLES))
        exit(1)


def main():
    filename = get_parameters()
    if filename != "-t":
        compile_cpp(filename)
    else:
        test_gecode_examples()


if __name__ == '__main__':
    main()
