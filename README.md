# WordCounter
A C++ application that counts the words which appear in the `.txt` file at least 2 times. Then it prints them, their frequency and the lines they appeared in into `result.txt`. The program also finds URLs and prints them as well.
This is the fifth assignment in the OOP module. Associative containers used: `std::map` and `std::set`.

## Installation and execution
1. Download the app.
2. If you haven't already, download and install the [GCC](https://gcc.gnu.org/) compiler.
3. Open a terminal window and navigate to the program directory on the disk.
4. Compile the program: `g++ main.cpp -o main`
5. Start the program by typing `./main` or `main`

## How do I use it?
- Move the `.txt` file that you want to analyze to the program directory (an exemplary `source.txt`  file is already in the directory). Enter the file name (with the extension `.txt`).
- *Voilà*, the process is done! Check the results in the `result.txt` file.
