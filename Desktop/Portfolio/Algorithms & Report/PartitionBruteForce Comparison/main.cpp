#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <windows.h>


int length = 500 ;


int counter2nd = 0;
int counter = 0;
int numsmaller;
int numequal;
double k;
LARGE_INTEGER frequency1;
LARGE_INTEGER timerstart1, timerend1;
LARGE_INTEGER frequency2;
LARGE_INTEGER timerstart2, timerend2;
double elapsedTime2nd;
double elapsedTime;
using namespace std;

int static fillThenShuffle(unsigned long long randArray[]){

    for(int i=0; i < length; i++){
        randArray[i] = i + 1;
    }
    random_shuffle(&randArray[0], &randArray[length-1] );

}

int static printArray(unsigned long long randArray[]){
        for(int x = 0; x < length;x++){
            cout<<randArray[x]<<" ";
        }
        cout<<endl;
}
unsigned long long BruteForceMedian(unsigned long long theArray[]){
    k = ceil(length / 2.0);
    for(int i = 0; i < length;i++ ){

        numsmaller = 0;
        numequal = 0;
        for(int j = 0; j < length; j++){
            counter++;
            if(theArray[j] < theArray[i]){
                numsmaller = numsmaller + 1;
            }
            else if(theArray[j] == theArray[i]){
                numequal = numequal + 1;
            }
        }
        if(numsmaller < k && k <=(numsmaller + numequal)){
            return theArray[i];
        }
    }
}

unsigned long long Partition(unsigned long long testArray[], int start, int fin){
    int pivotval = testArray[start];
    int pivotlocal = start;

    for(int j = start + 1; j <= fin; j++){
        if(testArray[j] < pivotval){
            counter2nd++;
            pivotlocal = pivotlocal+1;
            swap(testArray[pivotlocal], testArray[j]);
        }
    }
    swap(testArray[start],testArray[pivotlocal]);
    return pivotlocal;
}

unsigned long long Select(unsigned long long testArray[], int start, int middle, int fin){
    int pos = Partition(testArray, start, fin);
    if(pos == middle){
        return testArray[pos];
    }
    else if(pos > middle){
        return Select(testArray, start, middle, pos-1);
    }
    else if(pos < middle){
        return Select(testArray, pos+1, middle, fin);
    }
}

unsigned long long Median(unsigned long long testArray[]){
    double floorvar = floor(length/2.0);
    if (length == 1){
        return testArray[0];
    }
    else{
        Select(testArray, 0, floorvar, length - 1);

    }
}

int main()
{

    ofstream BrutebasicOperation;
    BrutebasicOperation.open("brutebasic.csv", ios_base::app);
    ofstream BrutetimeTaken;
    BrutetimeTaken.open("brutetime.csv", ios_base::app);
    ofstream partitionbasicOperation;
    partitionbasicOperation.open("partitionbasic.csv", ios_base::app);
    ofstream partitiontimeTaken;
    partitiontimeTaken.open("partitiontime.csv", ios_base::app);
    srand(time(NULL));
    for(int j = 0; j < 20; j++){
    for(int i = 0; i < 10;i++){
        unsigned long long testArray[length];
        fillThenShuffle(testArray);

        printArray(testArray);
        QueryPerformanceFrequency(&frequency1);
        QueryPerformanceCounter(&timerstart1);

        int med = BruteForceMedian(testArray);

        QueryPerformanceCounter(&timerend1);
        elapsedTime = (timerend1.QuadPart - timerstart1.QuadPart) * 1000000.0 / frequency1.QuadPart;

        QueryPerformanceFrequency(&frequency2);
        QueryPerformanceCounter(&timerstart2);

        int med2 = Median(testArray);

        QueryPerformanceCounter(&timerend2);
        elapsedTime2nd = (timerend2.QuadPart - timerstart2.QuadPart) * 1000000.0 / frequency2.QuadPart;

        cout << "Test" << i << endl;
        cout << " Brute Median: " << med << endl;
        cout <<"Basic operations: "<< counter<< endl;
        cout <<"Execution time: "<< elapsedTime<<" Microseconds"<< endl;
        cout << "Partition Median: " << med2 << endl;
        cout <<"Basic operations: "<< counter2nd<< endl;
        cout <<"Execution time: "<< elapsedTime2nd<<" Microseconds"<< endl;


      
       // file out for brute
        BrutetimeTaken << elapsedTime << endl;
        BrutebasicOperation << counter <<endl;

       // file out for partition
        partitionbasicOperation << counter2nd << endl;
        partitiontimeTaken << elapsedTime2nd << endl;

        elapsedTime2nd = 0;
        elapsedTime = 0;
        counter2nd = 0;
        counter = 0;



    }
    length = length + 500;
    }
    BrutetimeTaken.close();
    BrutebasicOperation.close();
    partitionbasicOperation.close();
    partitiontimeTaken.close();

    return 0;
}
