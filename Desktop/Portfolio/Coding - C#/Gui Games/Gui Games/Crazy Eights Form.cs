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
    public partial class Crazy_Eights_Form : Form
    {
        public int turn_count = 0;
        PictureBox[] cards;

        public Crazy_Eights_Form()
        {
            cards = new PictureBox[13];
            InitializeComponent();
            pictureBox1.Image = Gui_Games.Images.GetBackOfCardImage();
            InstructionsLabel.Text = "Click Deal Button!";
        }

        private void Crazy_Eights_Form_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void TitleLabel2_Click_1(object sender, EventArgs e)
        {

        }

        private void DealButton_Click(object sender, EventArgs e)
        {
            SortPlayerHandButton.Enabled = true;
            pictureBox1.Enabled = true;
            pictureBox2.Enabled = true;
            Crazy_Eight_Game.Setup_Game();
            turn_count=1;
            pictureBox2.Image = Gui_Games.Images.GetCardImage(Crazy_Eight_Game.PlayPile[1].GetLastCardInPile());
            TableLayoutPanelPlayer.Controls.Clear();
            TableLayoutPanelComp.Controls.Clear();
            RefreshPlayerHand();
            RefreshCompHand();
            InstructionsLabel.Text = "Your turn Yugi-Boy. Click on a card to play.";
        }

        private void TitleLabel_Click(object sender, EventArgs e)
        {

        }

        private void SortPlayerHandButton_Click(object sender, EventArgs e)
        {
            TableLayoutPanelPlayer.Controls.Clear();
            Crazy_Eight_Game.PlayHand[0].SortHand();

            RefreshPlayerHand();
        }

        private void CancelGameButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void TableLayoutPanelPlayer_Paint(object sender, PaintEventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            int labeldisplay = Crazy_Eight_Game.Play_Check();
            if (labeldisplay == 1)
            {
                InstructionsLabel.Text = "You have a card you can play! You cannot draw Yugi-Boy!";
            }
            if (labeldisplay == 0)
            {
                if (turn_count > 0)
                {
                    int temp = Crazy_Eight_Game.PlayHand[0].GetCount();
                    if (temp > 0 && temp < 13)
                    {
                        Card tempCard = Crazy_Eight_Game.PlayPile[0].DealOneCard();
                        TableLayoutPanelPlayer.Controls.Clear();
                        Crazy_Eight_Game.PlayHand[0].AddCard(tempCard);

                       RefreshPlayerHand();
                       Crazy_Eight_Game.Computer_Turn();
                       RefreshCompHand();
                    }
                    if (temp == 0)
                    {
                        pictureBox1.Image = null;
                    }
                }
            }
            pictureBox2.Image = Gui_Games.Images.GetCardImage(Crazy_Eight_Game.PlayPile[1].GetLastCardInPile());
            GameOverCheck();
        }


        private void Card_Click(object sender, EventArgs e){
        
        Card cardClicked;
        PictureBox pBoxCard = (PictureBox)sender;
        cardClicked = (Card)pBoxCard.Tag;
        int check = Crazy_Eight_Game.Check_Card(cardClicked);
        if (check == 1)
        {
            InstructionsLabel.Text = "Yugi-Boy, that card won't play!";
        }
        int check1 = Crazy_Eight_Game.PlayHand[0].GetCount();
        Crazy_Eight_Game.Player_Turn(cardClicked);

        int checkint = Crazy_Eight_Game.Check_Eight();
        int quickcheck = Crazy_Eight_Game.PlayHand[1].GetCount();
        if (checkint == 1)
        {
            if (quickcheck > 0)
            {
                new ChooseSuitForm().ShowDialog();
            }
        }

        TableLayoutPanelPlayer.Controls.Clear();

        RefreshPlayerHand();
        int check2 = Crazy_Eight_Game.PlayHand[0].GetCount();

        if(check1 > check2)
        {
          Crazy_Eight_Game.Computer_Turn();
           int tempcomp = Crazy_Eight_Game.PlayHand[1].GetCount();
           TableLayoutPanelComp.Controls.Clear();
           for (int i = 0; i < tempcomp; i++)
           {
               PictureBox picturecomp = new PictureBox();
               picturecomp.Image = Gui_Games.Images.GetCardImage(Crazy_Eight_Game.PlayHand[1].GetCard(i));
               TableLayoutPanelComp.Controls.Add(picturecomp, i, 0);
               picturecomp.Dock = DockStyle.Fill;
               picturecomp.Margin = new Padding(1);
           }
            Delay();
        }

        pictureBox2.Image = Gui_Games.Images.GetCardImage(Crazy_Eight_Game.PlayPile[1].GetLastCardInPile());
        GameOverCheck();
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
           
        }

        private void GameOverCheck()
        {
            int gamecount = Crazy_Eight_Game.Check_Score();

            if (Crazy_Eight_Game.Return_Score() == 2)
            {
                MessageBox.Show("Tie!");
                this.Close();
            }

            if (gamecount == 1)
            {
                MessageBox.Show("You Win, Yugi-Boy!");
                this.Close();
            }
            if (gamecount == -1)
            {
                MessageBox.Show("Computer Wins!");
                this.Close();
            }
        }

        private void RefreshPlayerHand()
        {
            int templength = Crazy_Eight_Game.PlayHand[0].GetCount();
            for (int i = 0; i < templength; i++)
            {
                PictureBox picture = new PictureBox();
                picture.Image = Gui_Games.Images.GetCardImage(Crazy_Eight_Game.PlayHand[0].GetCard(i));
                TableLayoutPanelPlayer.Controls.Add(picture, i, 0);
                picture.Dock = DockStyle.Fill;
                picture.Margin = new Padding(1);
                cards[i] = picture;
                cards[i].Click += new EventHandler(Card_Click);
                picture.Tag = Crazy_Eight_Game.PlayHand[0].GetCard(i);
            } 
        }

        private void Delay()
        {
            System.Threading.Thread.Sleep(500);
        }

        private void RefreshCompHand()
        {
            int templength = Crazy_Eight_Game.PlayHand[1].GetCount();
            TableLayoutPanelComp.Controls.Clear();
            for (int i = 0; i < templength; i++)
            {
                PictureBox comppicture = new PictureBox();
                comppicture.Image = Gui_Games.Images.GetCardImage(Crazy_Eight_Game.PlayHand[1].GetCard(i));
                TableLayoutPanelComp.Controls.Add(comppicture, i, 0);
                comppicture.Dock = DockStyle.Fill;
                comppicture.Margin = new Padding(1);
            }
        }
    }
}
