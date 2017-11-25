using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Currency_Convertor_GUI {
    
    public partial class Form1 : Form {

        private int inputConvert = 0;
        private int outputConvert = 0;

        /*
 *  GUI to calculate currency conversions for a set number of currencies.
 *  Takes input value and currencies selected from various gui items
 *  and prints the calculated values.
 *  Author: Eliot Wilson, n9175504
 *  Date: April 2015
 *  
 */


        public Form1() {
            InitializeComponent();
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void inputSelect_SelectedIndexChanged(object sender, EventArgs e)
        {
            inputConvert = inputSelect.SelectedIndex;
            EnableSecondInput();
        }


        private void inputBox_TextChanged(object sender, EventArgs e)
        {
            EnableFourthInput();
        }

        private void outputSelect_SelectedIndexChanged(object sender, EventArgs e)
        {
            outputConvert = outputSelect.SelectedIndex;
            EnableThirdInput();
        }


        private void buttonConvert_Click(object sender, EventArgs e)
        {
            double temp, result= 0.00;

            if (!double.TryParse(inputBox.Text, out temp))
            {
                MessageBox.Show("Please enter in numerical form.");
                inputBox.Text = "";
                inputBox.Focus();
                return;
            }

            result = Currency_Exchange.convertCurrency(temp, inputConvert, outputConvert);

            EnableFinalInput();
            OutputResult(result);
        }

        private void OutputResult(double amount)
        {
            outputBox.Text = amount.ToString("F5");
        }

        private void EnableSecondInput()
        {
            outputSelect.Enabled = true;
        }

        private void EnableThirdInput()
        {
            inputBox.Enabled = true;
            inLab.Text = Currency_Exchange.cNames[inputConvert];
        }
        private void EnableFourthInput()
        {
            buttonConvert.Enabled = true;
        }
        private void EnableFinalInput()
        {
            outLab.Text = Currency_Exchange.cNames[outputConvert];
            inputSelect.Enabled = false;
            inputBox.Enabled = false;
            outputSelect.Enabled = false;
            buttonConvert.Enabled = false;
            outputSelect.Enabled = false;
            converBox.Visible = true;
        }

        private void ResetInput()
        {
            inputSelect.Enabled = true;
            outputSelect.Enabled = false;
            converBox.Visible = false;
            conTrue.Checked = false;
            inputBox.Enabled = false;
            inputBox.Text = "";
            outputBox.Text = "";
            inLab.Text = "";
            outLab.Text = "";
        }

        private void conTrue_CheckedChanged(object sender, EventArgs e)
        {
            ResetInput();
        }

        private void conFalse_CheckedChanged(object sender, EventArgs e)
        {
            Environment.Exit(0);
        }


         
    }//end class 
}
