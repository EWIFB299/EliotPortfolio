using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Game_Class_Library;
using Shared_Game_Class_Library;

namespace Gui_Games
{
    public partial class ChooseSuitForm : Form
    {
        public static int choice;

        public ChooseSuitForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {            
            Crazy_Eight_Game.Suit_Choice(choice);
            this.Close();
        }

        private void ClubsRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            choice = 0;
        }

        private void DiamondsRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            choice = 1;
        }

        private void HeartsRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            choice = 2;
        }

        private void SpadesRadioButton_CheckedChanged(object sender, EventArgs e)
        {
            choice = 3;
        }
    }
}
