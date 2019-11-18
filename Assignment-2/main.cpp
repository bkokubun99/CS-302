///@author Brysen Kokubun
///@date   09/13/2019
///@file   Assignment #2 Selection Sort
///        Vasko CS-302-1003

#include <iostream>
#include <fstream>
#include <string>
#include "LL.h"
using namespace std;

int main()
{
    ifstream inFile;                    //Input stream inFile
    int read;                           //Temporary integer value for input
    LL<int> list;                       //Class list of LL
    LL<int>::iterator it_sort;          //Iterator of class LL
    LL<int>::iterator it_begin;         //Iterator of class LL
    LL<int>::iterator it_end;           //Iterator of class LL
    
/*******************************************************************************
*                   Reads in Contents of the File                              *
*******************************************************************************/
    inFile.open("numbers.txt");      //Open input file "numbers.txt"
    while(!inFile.eof())
    {
        inFile >> read;              //Reads in the integers in the file
        list.headInsert(read);       //Inserts the integers into the list
    }
    inFile.close();                  //Close input file
    
/*******************************************************************************
*                   Initializing Iterators Positions                           *
*******************************************************************************/
    it_begin = list.begin();         //Iterator Points to the first node in list
    it_end   = list.end();           //Iterator Points to last node in list
    it_sort  = list.begin();         //Iterator Points to the first node in list
    int current;                     //Hold current element of list
    
/*******************************************************************************
*                   Selection Sorting Contents of File                         *
*******************************************************************************/
//For loop will compare from the RIGHT to LEFT until it_end == list.begin()
    for(it_end = list.end(); it_end != list.begin(); it_end--)
    {
        //This integer variable largest holds the value in the iterator it_end
        int largest = *it_end;
        
//For loop will compare from LEFT to RIGHT until the iterator it_begin == it_end
        for(it_begin = list.begin(); it_begin != it_end; it_begin++)
        {
            //If the value at it_begin is larger than largest
            if(largest < *it_begin)
            {
                //Assign value within it_begin to largest
                largest = *it_begin;
                //Assign value within it_end to current
                current = *it_end;
                //Update the list to put the largest value @ the end of LL
                list.update(it_end, largest);
                //Update the list to put the current value @ the beginning of LL
                list.update(it_begin, current);
            }
        }
    }
/*******************************************************************************
*                   Printing the Sorted Contents of File                       *
*******************************************************************************/
//For loop will print out the sorted list of contents of the file but not last
    for(it_sort = list.begin(); it_sort != list.end(); it_sort++)
    {
        cout << *it_sort  << endl;  //Prints value within the node it points to
    }
    cout << *it_sort << endl;       //Prints the value within the last node 
    
    return 0;
}
//End main
