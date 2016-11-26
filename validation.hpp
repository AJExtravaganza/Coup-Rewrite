#pragma once

#include <vector>

inline bool getSelection(std::istream& uiIn, std::ostream& uiOut);
inline int getSelection(int lowerBound, int upperBound, std::istream& uiIn, std::ostream& uiOut);

inline bool getSelection(std::istream& uiIn, std::ostream& uiOut)
{
    uiOut << "[y/n]: ";
    char input = ' ';
    bool choice = false;
    uiIn >> input;
    input = tolower(input);
    if (uiIn.fail() || !(input == 'y' || input == 'n'))
    {
        uiOut << "Invalid Selection.\n";
        uiIn.clear();
        uiIn.ignore(INT_MAX, '\n');
        choice = getSelection(uiIn, uiOut);
    }
    else if (input == 'y')
    {
        choice = true;
    }
    else if (input == 'n')
    {
        choice = false;
    }

    return choice;
}

inline int getSelection(int lowerBound, int upperBound, std::istream& uiIn, std::ostream& uiOut)
{
    int input = 0;
    uiIn >> input;
    if (uiIn.fail() || input < lowerBound || input > upperBound)
    {
        uiOut << "Invalid Selection.  Please input [" << lowerBound << "-" << upperBound << "]: ";
        uiIn.clear();
        uiIn.ignore(INT_MAX, '\n');
        input = getSelection(lowerBound, upperBound, uiIn, uiOut);
    }

    return input;
}
