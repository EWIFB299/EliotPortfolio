using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace Advanced_Gold_Lotto_Checker {

    /*
     *  Calculates matching numbers in a mutltidimensional array to a
     *  seperate array and then increments seperate value counters to display those
     *  numbers in multiple print statements.
     *  Author: Eliot Wilson, n9175504
     *  Date: March 2015
     *  
     */

    class Program {

        static Random randomGen = new Random();
       
        static void Main() {

        
            const int NUMBER_OF_ROWS = 12;
            int numcount = 0;
            int supcount = 0;
            int game = 1;

            int[][] lottoNumbers ={ 
                             new int [6],
                             new int [6],
                             new int [6],
                             new int [6],
                             new int [6],
                             new int [6],
                             new int [6],
                             new int [6],
                             new int [6],
                             new int [6],
                             new int [6],
                             new int [6] 
                              };

            int[] drawNumbers = new int[8];


            for (int rowcount = 0; rowcount < NUMBER_OF_ROWS; rowcount++)
            {
                LottoAssign(lottoNumbers[rowcount]);
            }
            WinAssign(drawNumbers);
            
            for (int rowcount = 0; rowcount < NUMBER_OF_ROWS; rowcount++)
            {
                PrintLottoNumbers(lottoNumbers[rowcount], rowcount);
            }
            PrintDrawNumbers(drawNumbers);
            for (int gamenum = 0; gamenum < NUMBER_OF_ROWS; gamenum++)
            {
                numcount = NumCalc(lottoNumbers[gamenum], drawNumbers);
                supcount = SupCalc(lottoNumbers[gamenum], drawNumbers);
                PrintResults(numcount, supcount, game);
                game++;
            }
            ExitProgram();
        }//end Main/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        /*
* Assigns a random value to each value location in the array.
* precondition: Requires the drawNumbers array
* postcondition: assigns varies random integer values below 45 to the array
*/

        static void WinAssign(int[] array){
            for (int i = 0; i < array.Length; i++)
            {
                int random = randomGen.Next(0,45);
                array[i] = random;
            }
          
            for (int position = 0; position < array.Length; position++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    int random = randomGen.Next(0, 45);
                    if (array[position] == array[j])
                    {
                        array[position] = random;
                    }
                }
            }

        }

        /*
* Assigns a random value to each value location in the array and then aranges them in ascending order.
* precondition: Requires the lottoNumber array
* postcondition: assigns varies random integer values below 45 to the array
*/

        static void LottoAssign(int[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                int random = randomGen.Next(0,45);
                array[i] = random;
            }
            Array.Sort(array);

            for (int position = 1; position < array.Length; position++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    int random = randomGen.Next(0, 45);
                    if (array[position - 1] == array[j])
                    {
                        array[position] = random;
                    }
                }
            }
            Array.Sort(array); 
        }

        /*
* Calculates which numbers in the arrays match and then increments the couting
* value by one for each that matches.
* precondition: Requires the lottoNumber array and the drawNumber array
* postcondition: returns the number of matching values in the lottoNumber array
*/

        static int NumCalc(int[] array, int[] winningarray)
        {
            int numcount = 0;

            for (int j = 0; j < array.Length; j++)
            {
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

        static int SupCalc(int[] array, int[] winningarray)
        {
            int supcount = 0;

            for (int x = 0; x < winningarray.Length; x++)
            {
                for (int j = 0; j < array.Length; j++)
                {
                    if (x > winningarray.Length - 3)
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
            Console.Write("\n\n Game {0}:", game);
            foreach (int i in arr)
            {
                Console.Write(" \t {0} ", i);
                game++;
            }
        }

        /*
* Takes the values found in previous methods and prints them in
* a single line.
* precondition: Requires number of matching values, supplementary values and game values
* postcondition: Prints the numbers in a single line
*/

        static void PrintResults(int numcount, int supcount, int gamenum)
        {

            Console.Write("\n\n Found {0} winning numbers and {1} supplementary numbers in Game {2}", numcount, supcount, gamenum);
        }

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
