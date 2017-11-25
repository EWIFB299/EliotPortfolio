using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gold_Lotto_Checker {

    /*
 *  Calculates matching numbers in a mutltidimensional array to a
 *  seperate array and then increments seperate value counters to display those
 *  numbers in multiple print statements.
 *  Author: Eliot Wilson, n9175504
 *  Date: March 2015
 *  
 */
    
    class Program {

        /*
* Calculates which numbers in the arrays match and then increments the couting
* value by one for each that matches.
* precondition: Requires the lottoNumber array and the drawNumber array
* postcondition: returns the number of matching values in the lottoNumber array
*/
        static int NumCalc(int[] array, int[] winningarray){ 
            int numcount=0;

            for(int j = 0; j<array.Length;j++){
                for (int x = 0; x < winningarray.Length; x++)
                {
                    if (x < winningarray.Length-2)
                    {
                        if (array[j] == winningarray[x])
                        {
                            numcount = numcount + 1;
                        }
                    }
                }
            }
            return numcount;

        }

        /*
* Calculates which supplemantary numbers in the arrays match and then increments 
* the couting value by one for each that matches.
* precondition: Requires the lottoNumber array and the drawNumber array
* postcondition: returns the number of matching supplementary values in the lottoNumber array
*/
        static int SupCalc(int[] array, int[] winningarray){
            int supcount=0;

            for(int x=0; x<winningarray.Length;x++){
                for(int j = 0; j<array.Length;j++){
                    if (x > winningarray.Length-3)
                    {
                        if (array[j] == winningarray[x])
                        {
                            supcount = supcount + 1;
                        }
                    }
                }
            }
            return supcount;
        }

        /*
* For each element in the array, print that element and then incrememnt
* game number by 1.
* 
* precondition: Requires the drawNumber array
* postcondition: Prints the game number and then the Draw Numbers
*/
        static void PrintDrawNumbers(int[] arr)
        {
            Console.Write("\n\n Lotto Draw Numbers");
            foreach (int i in arr)
            {
                Console.Write(" {0} ", i);
            }
        }

                /*
      * For each element in the array, print that element and then incrememnt
      * game number by 1.
      * 
      * precondition: Requires the desired printing array
      * postcondition: Prints the game number and then the Array
      */

                static void PrintLottoNumbers(int[] arr, int rowcount)
        {
            int game = rowcount + 1;
            Console.Write("\n\n Game {0}: ", game);
            foreach (int i in arr)
            {
                Console.Write("\t {0} ", i);
                game++;
            }
        }

                /*
      * Takes the values found in previous methods and prints them in
      * a single line.
      * precondition: Requires number of matching values, supplementary values and game values
      * postcondition: Prints the numbers in a single line
      */

        static void PrintResults(int numcount,int supcount,int gamenum){

            Console.Write("\n\n Found {0} winning numbers and {1} supplementary numbers in Game {2}",numcount,supcount,gamenum);
        }

        static void Main(){
            const int NUMBER_OF_ROWS = 9;
            int numcount = 0;
            int supcount = 0;
            int game = 1;

            int[][] lottoNumbers ={ 
                             new int [] { 4, 7, 19, 23, 28, 36},
                             new int [] { 14, 18, 26, 34, 38, 45},
                             new int [] { 8, 10,11, 19, 28, 30},
                             new int [] {15, 17, 19, 24, 43, 44},
                             new int [] { 10, 27, 29, 30, 32, 41},
                             new int [] {9, 13, 26, 32, 37,  43},
                             new int [] {1, 3, 25, 27, 35, 41},
                             new int [] {7, 9, 17, 26, 28, 44},
                             new int [] {17, 18, 20, 28, 33, 38}
                              };

            int[] drawNumbers = new int[] { 44, 9, 17, 43, 26, 7, 28, 19 };

            //WRITE PROGRAM CALL FUNCTIONS HERE//

            for (int rowcount = 0; rowcount < NUMBER_OF_ROWS; rowcount++)
            {
                PrintLottoNumbers(lottoNumbers[rowcount], rowcount);
            }

            PrintDrawNumbers(drawNumbers);
            for (int gamenum = 0; gamenum < NUMBER_OF_ROWS; gamenum++){
                numcount = NumCalc(lottoNumbers[gamenum],drawNumbers);
                supcount = SupCalc(lottoNumbers[gamenum], drawNumbers);
                PrintResults(numcount, supcount, game);
                game++;
            }
            ExitProgram();
        }//end Main


        /*
* Takes the values found in previous methods and prints them in
* a single line.
* precondition:
* postcondition: Exits program
*/

        static void ExitProgram() {
            Console.Write("\n\nPress any key to exit program: ");
            Console.ReadKey();
        }//end ExitProgram


    } //end class Program
}
