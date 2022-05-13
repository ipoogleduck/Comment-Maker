#include "string.h"
#include <iostream>
#include <fstream>

using namespace std;

bool isPositiveInt(string str) {
    if (str.length() == 0) //False if nothing in string
        return false;
    for (int i = 0; i < str.length(); i++)
        if (!(str[i] >= 48 && str[i] <= 57)) //If not number in ascii chart return false
            return false;
    return true;
}

int promptUserInt(string prompt, int low, int high, string lowError = "Invalid input. ", string highError = "Invalid input. ") {
    string tempString;
    int tempInt;
    do {
        cout << prompt << endl;
        cin >> tempString;

        tempInt = atoi(tempString.c_str()); //Convert string to int

        if (!isPositiveInt(tempString)) {
            cout << "Please enter a valid integer number. ";
        } else if (tempInt < low) //Output low error
            cout << lowError;
        else if (tempInt > high) //Output high error
            cout << highError;
    } while (tempInt < low || tempInt > high || !isPositiveInt(tempString));
    return tempInt;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Incorrect number of args, please input filename(s) separated by space" << endl;
        return 1;
    }

    cout << "Welcome to Comment Maker v1.0. Make sure to put @ before your functions." << endl;
    cout << "Would you like to include Description: in the function headers for descriptions that need to be manually added by you?" << endl;
    cout << "Hint: If you're lazy or in a rush press 0" << endl;
    bool alwaysIncludeDescription = promptUserInt("Input: (0-no or 1-yes)", 0, 1);
    

    for (int i = 1; i < argc; i++) {
        string filename = argv[i];
        ifstream fileIn;
        fileIn.open(filename);

        string allOfFile = "";

        while (!fileIn.eof()) {
            char c = 'h';
            while(c != '@' && !fileIn.eof()) {
                fileIn.get(c);
                if (c != '@' && !fileIn.eof()) {
                    allOfFile += c;
                }
            }
            if (fileIn.eof()) {
                break;
            }
            string functionLine;
            getline(fileIn, functionLine);
            // cout << functionLine << endl;


            string functionName = "";

            string description = "";
            string className = "";
            
            string parameters = "";
            string returnType = "";

            bool constructor = false;
            bool destructor = false;

            string preConditions = "";
            
            int index = 0;

            //Get rid of virtual
            while (functionLine[index] != ' ' && functionLine[index] != ':') {
                returnType += functionLine[index];
                index++;
            }
            index++;
            if (returnType != "virtual") {
                index = 0;
            }
            returnType = "";

            while (functionLine[index] != ' ' && functionLine[index] != ':') {
                returnType += functionLine[index];
                index++;
            }
            index++;
            if (functionLine[index] == ':') {
                className = returnType;
                if (functionLine[index+1] == '~') {
                    returnType = "destructor";
                    destructor = true;
                } else {
                    returnType = "constructor";
                    constructor = true;
                }
                index++;
            } else {
                int index2 = index;
                string tempString = "";
                while (functionLine[index2] != '(' && functionLine[index2] != ':') {
                    if (!constructor && !destructor) {
                        className += functionLine[index2];
                    }
                    index2++;
                }
                if (functionLine[index2] == ':') {
                    index = index2+2;
                }
            }
            while (functionLine[index] != '(') {
                functionName += functionLine[index];
                index++;
            }
            if (constructor || destructor) {
                functionName = className + " class " + returnType;
            }
            if (functionName == "operator=") {
                functionName = "Assignment Operator Overload";
                description = "Copies values of " + className + " from one instance to another already existing instance";
            }
            index++;
            while (functionLine[index] != ')') {
                parameters += functionLine[index];
                index++;
            }

            if (constructor) {
                if (parameters == "") {
                    description = "Default constructor for " + className + " class";
                } else {
                    description = "Constructs " + className + " class with parameters listed below";
                }
            } else if (destructor) {
                description = "Destructs " + className + " class and frees all dynamic memory";
            }

            if (parameters == "") {
                if (destructor) {
                    preConditions = "Function will be called by class when class is out of scope";
                } else {
                    preConditions = "Function must be called with no parameters";
                }
            } else {
                string type = "";
                string name = "";
                bool isOnType = true;
                for (int i = 0; i < parameters.length(); i++) {
                    if (parameters[i] == ',') {
                        preConditions.append(name + " must be of type " + type + ", ");
                        type = "";
                        name = "";
                        isOnType = true;
                        i++;
                    } else {
                        if (parameters[i] == ' ') {
                            if (type != "const") {
                                isOnType = false;
                            } else {
                                type = "";
                            }
                        } else if (isOnType) {
                            type += parameters[i];
                        } else {
                            name += parameters[i];
                        }
                    }
                }
                preConditions.append(name + " must be of type " + type);
            }

            string output = "";
            output += "/********************************************************************\n";
            output += "** Function: " + functionName + "\n";
            if (description != "" || alwaysIncludeDescription) {
                output += "** Description: " + description + "\n";
            }
            output += "** Parameters: ";
            if (parameters == "") {
                output += "N/A\n";
            } else {
                output += parameters + "\n";
            }
            output += "** Pre-Conditions: " + preConditions + "\n";
            output += "** Post-Conditions: ";
            if (returnType == "void") {
                output += "Does not return a value\n";
            } else if (constructor) {
                output += "Class is constructed\n";
            } else if (destructor) {
                output += "Class is destructed\n";
            } else {
                output += "Function returns value of type " + returnType + "\n";
            }
            output += "********************************************************************/\n";
            
            allOfFile += output;
            allOfFile += functionLine + "\n";
        }
        ofstream fileOut;
        fileOut.open(filename, ios::trunc);
        fileOut << allOfFile;
        cout << "Wrote function headers to " + filename << endl;
    }
}