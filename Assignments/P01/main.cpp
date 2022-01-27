//////////////////////////////////////////////////////////
//
// Author:           Josh Cupp
// Email:            joshcupp14@gmail.com
// Label:            P01
// Title:            Program 1 - Resizing Stack
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//        This program resizes a stack by either growing 
//        or shrinking based on a ratio that decides if  
//        the stack is too full or too empty.
// 
// Files: 
//      main.cpp
//
//////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack {
private:
    int *A;   // pointer to array of int's
    int size; // current max stack size
    int top;  // top of stack

    int commands = 0;
    int maxSize = 0;
    int resizeCount = 0; // number of times stack resizes

    double tooFull = .85; // when to enlarge stack
    double tooEmpty = .15; // when to shrink stack
    double Enlarge = 2; // how much to enlarge stack 
    double Shrink = .5; // how much to shrink stack

    // top = number of items in the stack + 1
    // size = array size

    // size = 100
    // (top + 1) / size

public:
    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack() {
        size = 10;
        A = new int[size];
        top = -1;
    }

    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(int s) {
        size = s;
        A = new int[s];
        top = -1;
      
    }

    /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
    bool Empty() {
        return (top <= -1);
    }

    /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Peek() {
        if (!Empty()) {
            return A[top];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Pop() {

        checkResize();
        if (!Empty()) {
            commands++;
            return A[top--];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      ofstream outfile
  * 
  * Returns:
  *      NULL
  */
    void Print(ofstream& outfile) {
        outfile << "#################################################" << endl;

        outfile << " Assignment 4 - Resizing the Stack\n";
        outfile << " CMPS 3013\n";
        outfile << " Josh Cupp\n\n";

        outfile << "Config Params:\n";
        outfile << " Full Threshold: " << tooFull << endl;
        outfile << " Shrink Threshold: " << tooEmpty <<     endl;
        outfile << " Grow Ratio: " << Enlarge << endl;
        outfile << " Shrink Ratio: " << Shrink << endl;
        outfile << endl;

        outfile << "Processed " << commands <<  " commands" << endl << endl;

        outfile << "Max Stack Size: " << maxSize << endl;
        outfile << "End Stack Size: " << size << endl;
        outfile << "Stack Resized: " <<  resizeCount <<   " times" << endl;
        outfile << "#################################################" << endl;


    }

    /**
  * Public void: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *       NULL
  */
    void Push(int x) {
        
            
        checkResize();
        A[++top] = x;
        commands++;

    }

    /**
  * Public void: ContainerGrow
  * 
  * Description:
  *      Resizes the container for the stack by doubling
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void ContainerGrow() {

        int newSize = size * Enlarge;   // double size of original

        if(newSize > maxSize) // update max size of stack
        {
          maxSize = newSize;
        }
        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
    }


 /**
  * Public void: ContainerShrink
  * 
  * Description:
  *      Resizes the container for the stack by shrinking
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void ContainerShrink()
    {

      int newSize = size * Shrink;
      int *C = new int[newSize];

      for(int i = 0; i < top; i++)
      {
        C[i] = A[i];
      }

      delete[] A;

      size = newSize;

      A = C;

    }

 /**
  * Public void: checkResize
  * 
  * Description:
  *      checks to see if the stack needs to be resized
  *
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void checkResize()
    {
        double resizeThresh = double(top)/double(size);

        // if stack is too full enlarge it
        if(resizeThresh > tooFull)
        {
          ContainerGrow();
          resizeCount++;
        }
        else if(resizeThresh < tooEmpty && !(size <= 10))
        {
          ContainerShrink();
          resizeCount++;
        }
    }
};

/**
  * Function: checkEvenOdd
  * 
  * Description:
  *      checks to see if the number from the input file
  *       is even or odd
  *
  * 
  * Params:
  *      ArrayStack
  *      int num
  * 
  * Returns:
  *      NULL
  */
void checkEvenOdd(ArrayStack &Stack,int num);

/**
  * Function: openFiles
  * 
  * Description:
  *      opens input and output files
  *       
  * Params:
  *      ifstream
  *      ofstream
  *      
  * 
  * Returns:
  *      NULL
  */
void openFiles(ifstream& infile, ofstream& outfile);

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main() {
    ifstream infile;
	  ofstream outfile;

    openFiles(infile, outfile);
    
    ArrayStack stack;
    int num; 

    while (!infile.eof()){
        infile >> num; // read in from infile
        checkEvenOdd(stack,num);
        
    }
    stack.Print(outfile);
}


void openFiles(ifstream& infile, ofstream& outfile)
{

	char inFileName[40];
	char outFileName[40];


	cout << "Enter the input file name: ";
	cin >> inFileName;
	infile.open(inFileName);
	cout << endl;

	cout << "Enter the output file name: ";
	cin >> outFileName;
	outfile.open(outFileName);
}

void checkEvenOdd(ArrayStack &Stack,int num)
{
  // checks if number is even
  if(num % 2 == 0){
    Stack.Push(num);
  }
  else
    Stack.Pop();
}
