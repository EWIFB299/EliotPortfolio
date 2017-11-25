#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>


using namespace std;
double duration;
int Length= 1000;
int operationcount=0;
int value, tempvalue, basecount;
 LARGE_INTEGER frequency;
    LARGE_INTEGER timerstart, timerend;
    double elapsedTime;


void print(int numlist[]){
        for (int printcount = 0; printcount < Length; printcount++)
{
     cout << numlist[printcount] << ", ";
}
     cout << " With" << operationcount << "Operations" << "\n";
}

int main()
{
            ofstream myfile;
  myfile.open ("test.txt");
 // myfile << "Length of Array" << " | " << "Time(Microseconds)" <<"\n";
    srand(time(NULL));
    for (int i = 1; i < 1001; i++){
    int numlist[Length];

    for(int i = 0; i < Length; i++ ){
     numlist[i]= rand() % 120;
    }
     QueryPerformanceFrequency(&frequency);
         QueryPerformanceCounter(&timerstart);

    for(int i = 1; i < Length; i++ ){
        value = numlist[i];
        tempvalue = i-1;
         while(tempvalue >= 0 && numlist[tempvalue] > value){  //inequality performed n^2/4 times
                operationcount++;
                numlist[tempvalue+1] = numlist[tempvalue];
                tempvalue--;
         }
         numlist[tempvalue+1] = value;

    }

       QueryPerformanceCounter(&timerend);
        elapsedTime = (timerend.QuadPart - timerstart.QuadPart) * 1000000.0 / frequency.QuadPart;

       myfile << operationcount <<"\n";
       operationcount=0;
       Length++;
    }
    myfile.close();
}
