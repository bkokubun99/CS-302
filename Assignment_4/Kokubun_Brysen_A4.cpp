// @author Brysen Kokubn
// @date 09/30/2019
// @file Assignment #4 Multiplication in parallel using threads
//       Vasko CS-302-1003

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

//Mult function prototype
void mult(int n, int p);

mutex tLock;

/****************************************************************************************************************************
*                                                           Global Variables                                                                                          *
******************************************************************************************************************************/
vector<thread> threadResult;            //Vector threadResult type thread
vector<short> num1;                     //Vector num1         type short
vector<short> num2;                     //Vector num2         type short
vector<vector<short> > partial_result;  //2-D Vector          type short
vector<short> result;                   //Vector result       type short

//Start main
int main()
{

/****************************************************************************************************************************
*                                                           Variable Declaration                                                                                    *
******************************************************************************************************************************/
    string num_1;                   //String num_1 to read in input number 1
    string num_2;                   //String num_1 to read in input number 2
    int largest = 0;                //Integer to signify largest vector size
    short temp_val = 0;             //Temporary value for each column addition
    short carry_val = 0;            //Carry value for column addition
    
    //max threads that can run on this system at the same time
    int maxThreads = thread::hardware_concurrency();

/****************************************************************************************************************************
*                                                               User Input                                                                                                *
******************************************************************************************************************************/
    cout << endl;
    cout << "Enter number1: ";
    cin  >> num_1;
    
    cout << "Enter number2: ";
    cin  >> num_2;
    
    //Loop to convert 1st Number from a string to a vector of type short
    for (int i = 0; i < num_1.length(); i++)
    {
        num_1[i] = num_1[i] - '0';        //Converts string to integer by ASCII
        num1.push_back(num_1[i]);         //Puts integer value into short vector
    }
    
    //Loop to convert 2nd Number from a string to a vector of type short
    for (int i = 0; i < num_2.length(); i++)
    {
        num_2[i] = num_2[i] - '0';        //Converts string to integer by ASCII
        num2.push_back(num_2[i]);         //Puts integer value into short vector
    }

/****************************************************************************************************************************
*                                               Calculations/Computation                                                                                       *
******************************************************************************************************************************/
    //Loop to multiply number 2 to number 1
    for (int i = num2.size() - 1; i >= 0; i--)
    {
        //Call multiplication function
        threadResult.push_back(thread(mult,num2[i], i));
        
        //If the thread Amount is Equal to max threads then wait for all of them
        //to finish before we spawn more threads
        if(threadResult.size() == maxThreads)
        {
            //Loop to allow threads to spawn
            for (int j = 0; j < threadResult.size(); j++)
                threadResult[j].join();
            
            //Wipe out threadResult after all the threads are done running
            threadResult.clear();
        }
    }
    
    //Loop that waits for leftover threads that were spawned in the above loop
    for (int i = 0; i < threadResult.size(); i++)
    {
        threadResult[i].join();
    }
    
    //Wipe out threadResult after all threads are done running
    threadResult.clear();
    
    //Loop to find the largest size vector within the outer vector
    for (int i = 0; i < partial_result.size(); i++)
    {
        //Control enters if size of inner vector is larger than largest
        if(partial_result[i].size() > largest)
        {
            //Re-assign largest with size of inner vector
            largest = partial_result[i].size();
        }
        else
        {
            //Largest size vector is largest
            largest = largest;
        }
    }
    
    //Loop to insert leading zeros for column addition
    for (int i = 0; i < partial_result.size(); i++)
    {
        //Check to see if the size of the inner vector is the largest
        while(partial_result[i].size() != largest)
        {
            //Insert leading zeros into vector to match size of largest vector
            partial_result[i].insert(partial_result[i].begin(), 0);
        }
    }
    
    //Addition of vectors as columns
    for (int i = partial_result[0].size()-1; i >= 0; i--)
    {
        for (int j = 0; j < partial_result.size(); j++)
        {
            //Addition of each column
            temp_val += partial_result[j][i];
        }
        //Addition of the column value and carry amount
        temp_val += carry_val;
        //Determining carry value for next column addition
        carry_val = temp_val/10;
        //Determining value of the column after addition
        temp_val = temp_val%10;
        //Inserting the value of the column into result vector from the left
        result.insert(result.begin(), temp_val);
        //Re-initialize temporary value for next column addition
        temp_val = 0;
    }
    
    //Inserting the remaining carry value after addition to the front of result
    result.insert(result.begin(), carry_val);
    
    //If there is a 0 at the beginning of result vector then control enters
    while (result[0] == 0)
    {
        //Deletes leading zeros
        result.erase(result.begin());
    }
    
/****************************************************************************************************************************
*                                               Output                                                                                                                      *
******************************************************************************************************************************/
    cout << endl;
    cout << "The product is: ";
    
    //Loop through result vector
    for (int i = 0; i < result.size(); i++)
    {
        //Output result at position [i]
        cout << result[i];
    }
    cout << endl;
    cout << endl;
    
    return 0;
}
//End Main

/****************************************************************************************************************************
*                                               Functions                                                                                                                 *
******************************************************************************************************************************/
void mult(int n, int p)
{
    int temp_initial;                           //Temp initial value
    int carry_amount = 0;                       //Value for carry amount
    int temp_result;                            //Temporary result
    vector<short> temp_vect;                    //Temporary vector
    
    //Loop to multiply number2 to each value in number1
    for (int i = num1.size() - 1; i >= 0; i--)
    {
        //Calculates temporary initial value, including carry amount
        temp_initial = n * num1[i] + carry_amount;
        //Calculates temporary result value, w/o carry
        temp_result = temp_initial % 10;
        //Calculates the carry amount
        carry_amount = temp_initial /10;
        //Stores the value of temp_result into the beginning of temporary vector
        temp_vect.insert(temp_vect.begin(), temp_result);
    }
    
    //Control will enter if carry amount is not equal to 0
    if (carry_amount != 0)
    {
        //This will insert the carry amount to the front of the temporary vector
        temp_vect.insert(temp_vect.begin(), carry_amount);
    }
    
    //Will execute if the position is not equal to the size of number2
    while(p != num2.size() - 1)
    {
        //Pushes a 0 into the temporary vector from the back
        temp_vect.push_back(0);
        p++;                                //Increments the position
    }
    
    //Since each thread calculates its own result, then the threads need to
    //only insert into one portion of the vertor at one time, the lock
    //allows only one thread to be inserted into the vertor until it is done
    //then the unlock allows 1 thread that was waiting to insert into the vector
    tLock.lock();
    partial_result.insert(partial_result.begin(), temp_vect);
    tLock.unlock();

}
