///@author Brysen Kokubun
///@date   08/28/2019
///@file   Assignment #1 Fun With Recursion
///        Vasko CS-302-1003

#include <iostream>
#include <string>
using namespace std;

/*******************************************************************************
*                        Function Prototypes                                   *
*******************************************************************************/
void printStarsUtil(int w);
void printStarsIncreasing(int w);
void printStarsDecreasing(int w);
bool isPalindrome(string s);
bool increasingDigits(unsigned long long num);

int main()
{
/*******************************************************************************
*                        Variable & Declaration                                *
*******************************************************************************/
    
    int    width = 0;                           //Variable for Width
    string str;                                 //Variable for String
    int    num   = 0;                           //Variable for Number
    
/*******************************************************************************
*                 Prompting & User Input For Stars Width                       *
*******************************************************************************/
//Do-While Loop that checks if user input width is greater than 0 (width >= 0)
    do
    {
        cout << endl;
        cout << "Enter the Width: ";
        cin  >> width;
//Control enters if statment if invalid input
        if (width <= 0 || (!width))
        {
            cin.clear();                            //Clears input error
            cin.ignore(1000, '\n');                 //Ignores/Discard input
            cout << "Seriously?! Wow!" << endl;
        }
    }while (width <= 0);
    
/*******************************************************************************
*                 Outputs & Displaying For Stars Width                         *
*******************************************************************************/
//Call Function to print stars in the size of width while Increasing
    printStarsIncreasing(width);
    cout << endl;
    
//Call Function to print stars in the size of width while Decreasing
    printStarsDecreasing(width);
    cout << endl;

/*******************************************************************************
*               Prompting & User Input For Palindrome String                   *
*******************************************************************************/
    cout << "Okay hopefully that worked"                      << endl;
    cout << "Enter a string: ";
    cin  >> str;

/*******************************************************************************
*               Outputs & Displaying For Palindrome String                     *
*******************************************************************************/
//Control enters if statement if the string is a true palindrome
    if (isPalindrome(str))
    {
        cout << str << " is a palindrome, nicely done"        << endl;
        cout << endl;
    }
//Control enters else if the string is not a palindrome
    else
    {
        cout << "Oh well, " << str << " is not a palindrome"  << endl;
        cout << endl;
    }
    
/*******************************************************************************
*         Prompting & User Input For Increasing Digit Left -> Right            *
*******************************************************************************/
    cout << "Hopefully we are still doing alright, last part" << endl;
    do
    {
        cout << "Enter a number: ";
        cin  >> num;
//Control enters if statement if invalid input
        if (num < 0 || (!num))
        {
            cin.clear();                            //Clears input error
            cin.ignore(1000, '\n');                 //Ignore/Discard input
            cout << "Can we just NOT do this again?!?!?!?!"   << endl;
            cout << endl;
        }
    }while (num < 0 || (!num));

/*******************************************************************************
*          Outputs & Displaying For Increasing Digits Left -> Right            *
*******************************************************************************/
//Control enters if statement if increasingDigits fct returns true
    if (increasingDigits(num))
    {
        cout << "Looks like the digits are increasing from left to right"
             << endl;
        cout << endl;
    }
    else
    {
        cout << "Digits do not increase from left to right, oh well"
             << endl;
        cout << endl;
    }
    
    return 0;
}//End main

/*******************************************************************************
*                         Recursion Functions                                  *
*******************************************************************************/

//Void Function that recursivly prints the set amount stars of size width
void printStarsUtil(int w)
{
    if (w == 0) return;                     //Base Case
    cout << '*';
    printStarsUtil(w-1);
}

//Void Function that calls printStarsUtil and recursivly prints the set amount
//of stars in an increasing order (ex. 1, 2, 3... , size width)
void printStarsIncreasing(int w)
{
    if (w == 0) return;                     //Base Case
    printStarsIncreasing(w-1);
    cout << endl;
    printStarsUtil(w);
}

//Void Function that calls printStarsUtil and recursivly prints the set amount
//of stars in a decreasing order (ex. size width, ..., 3, 2, 1)
void printStarsDecreasing(int w)
{
    if (w == 0) return;                     //Base Case
    printStarsUtil(w);
    cout << endl;
    printStarsDecreasing(w-1);
}

//Bool Function that will determine if the input string is a palindrome
//Will return true if it is palindrome, false if not palindrome
//(ex. racecar == racecar returns true, bobby != ybbob returns false)
bool isPalindrome(string s)
{
    //Checks if string is empty OR length of 1 OR first equal to last
    if ((s.empty()) || (s.length() == 1))
    {
        return true;
    }
    //Checks if string in 0 position is not equivalent to last
    if (s[0] != s[s.length()-1])
    {
        return false;
    }
    s.erase(0,1);
    s.erase(s.length()-1, -1);
    return true && isPalindrome(s);
}

//Bool Function that will determine if the input number is increasing from left
//to right (ex. 123 true, 2538 false)
bool increasingDigits(unsigned long long n)
{
    //Base Case
    if (n/10 == 0)
    {
        return true;
    }
    //Checks if 2nd to last number > last number
    if (((n/10)%10) > (n%10))
    {
        return false;
    }
    //Recursive function call, divides n/10 to get rid of last number in the input
    return true && increasingDigits(n/10);
}
