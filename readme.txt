About: Comment Maker auto generates function headers for all your functions, so you don't have to do it! The program conforms to the function header style required for EGR 103, CS 161 & CS 162. The program is only compatible with C/C++

To Use:
1. Drop this cpp file into the folder that contains your program files (cpp files)
2. Add an @ symbol to the beginning of every function in your program you want to add a function header for

ie:
void removeCardsAt() {

}

Would become:
@void removeCardsAt() {

}

Note: Only works on actual functions, doesn't support function prototypes

3. Compile this .cpp file with g++ or whatever you use
Ex: g++ commentMaker.cpp -o commentMaker

4. Run commentMaker with the name(s) of your c++ files
Ex: ./commentMaker filename.cpp

Or for multiple files: ./commentMaker filename.cpp filename2.cpp filename3.cpp