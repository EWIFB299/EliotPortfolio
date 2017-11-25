using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Gui_Games {
    public partial class Start_Game_Form : Form {
        public Start_Game_Form() {
            InitializeComponent();
        }

        private void ChooseGameLabel_Click(object sender, EventArgs e)
        {

        }

        private void ChooseGameComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            StartGameButton.Enabled = true;
         
           

            

        }

        private void StartGameButton_Click(object sender, EventArgs e)
        {
            if (ChooseGameComboBox.SelectedIndex == 0)
            {
                new Crazy_Eights_Form().Show();
            }
            else if (ChooseGameComboBox.SelectedIndex == 1)
            {
                new SolitaireForm().Show();
            }

        }

        private void ExitGameButton_Click(object sender, EventArgs e)
        {
            Environment.Exit(0);
        }
    }
}
