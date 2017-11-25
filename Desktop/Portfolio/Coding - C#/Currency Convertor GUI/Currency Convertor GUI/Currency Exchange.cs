using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Currency_Convertor_GUI {

    /*
 *  Background implementations for then GUI.
 *  These include the various arrays with conversion rates, the types of currencies and strings of those currencies.
 *  Also included is the calculation function to be called by Form1.cs
 *  Author: Eliot Wilson, n9175504
 *  Date: March 2015
 *  
 */

    enum Currencies {AUD, CYN, DKK, EUR, INR, NZD, AED, UKP, USD, VND};

    static class Currency_Exchange{
        private static double[] xRates = {1, 4.2681, 5.0844, 0.6849, 43.5921, 0.9705, 2.7094, 0.4963, 0.7382, 19115.5547};
        public static string[] cNames = { "AUD", "CYN", "DKK", "EUR", "INR", "NZD", "AED", "UKP", "USD", "VND" };

        /* Takes the amount selected by a user and converts is based upon the rates selected.
         * These rates are taken from the list Xrates incremented to the position chosen by int j and int i.
         *
         * precondition : Amount in initial value, input value rate, output value rate.
         * postcondition: returns calculated value.
         */

        public static double convertCurrency(double amount,int inputConvert, int outputConvert)
        {
            double tempval = 0.0;
            for (int j = 0; j < 10; j = j + 1) {
                if (inputConvert == j)
                {
                    for (int i = 0; i < 10; i = i + 1)
                    {
                        if (outputConvert == i)
                        {
           
                        tempval= (((xRates[0]/xRates[j]) * amount )* xRates[i]);
                        }
                    }
                }
            }
            return tempval;
        }


    }//end class
}//end namespace
