using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Shared_Game_Class_Library;

namespace Game_Class_Library
{
    
    public static class Crazy_Eight_Game
    {

        private static CardPile pile;
        private static Hand myHand;
        public static Suit formsuit;
        public static int stalecount, suitselect = 1;
        static Card newCard;

        static  CardPile[] playPile = new CardPile[2];
        static  Hand[] playHand = new Hand[2];

        public static CardPile[] PlayPile{
            get
            {
                return playPile;
            }
        }

        public static Hand[] PlayHand{
            get
            {
                return playHand;
            }
        }

        /*Initialises two (Player and Computer) card piles
         * 
         * Precondition: None
         * Postcondition: Distributes the Card objects among Hand and Pile classes
         * */
        public static void Setup_Game()
        {
            playPile[0] = new CardPile(true);
            playPile[1] = new CardPile();

            playPile[0].ShufflePile();
            Card tempcard = playPile[0].DealOneCard();        
            playPile[1].AddCard(tempcard);
            for (int i = 0; i < 2; i++)
            {
                playHand[i] = new Hand(playPile[0].DealCards(8));
            }
        }

        /*Sorts the Player's hand of cards
          * 
          * Precondition: None
          * Postcondition: Sorts hand
          * */
        public static void Sort_Hand()
        {
            playHand[0].SortHand();
        }

        /*Changes the global variable suitselect according to the index integer
          * 
          * Precondition: index integer
          * Postcondition: Assigns value of global variable
          * */
        public static void Suit_Choice(int index)
        {
            suitselect = 2;
            if (index == 0)
            {
                formsuit = Suit.Clubs;

            }
            if (index == 1)
            {
                formsuit = Suit.Diamonds;

            }
            if (index == 3)
            {
                formsuit = Suit.Hearts;

            }
            if (index == 4)
            {
                formsuit = Suit.Hearts;

            }
        }

        /*Checks if a stalemate has occured
         * 
         * Precondition: None
         * Postcondition: Returns stalecount or returns zero
         * */
        public static int Return_Score()
        {
            if (stalecount == 2)
            {
                return stalecount;
            }
            return 0;
        }

        /*Checks the amount of cards left, if playlength is equal to zero, the person wins, if complength is equal to 0 the computer wins
         * 
         * Precondition: None
         * Postcondition: Returns 1 if the player wins, returns -1 if the computer wins.
         * */
        public static int Check_Score()
        {
            int complength = Crazy_Eight_Game.PlayHand[1].GetCount();
            int playlength = Crazy_Eight_Game.PlayHand[0].GetCount();

            if (playlength == 0)
            {
                return 1;
            }

            if (complength == 0)
            {
                return -1;
            }

            return 0;
        }

     /*Checks if the card at the top of the pile is an eight
      * 
      * Precondition: None
      * Postcondition: If card at the top of the pile is an eight, return 1.
      * */
        public static int Check_Eight()
        {
            Card check = PlayPile[1].GetLastCardInPile();
            int checkint = (int)check.GetFaceValue();
            if (checkint == 6)
            {
                return 1;
            }

            return 0;
        }

     /* Runs the functionality of the computer player
      * 
      * Precondition: None
      * Postcondition: Increments stalecount bothways as it moves a step towards stalemate, removes cards as applicable
      * */
        public static void Computer_Turn(){
            Suit currentsuit = 0;
            int incricount = 1;
            Card pilecard = playPile[1].GetLastCardInPile();
            if (suitselect == 1){
                currentsuit = pilecard.GetSuit();
            }
            else if (suitselect == 2){
                currentsuit = formsuit;
                suitselect = 1;}
            FaceValue currentvalue = pilecard.GetFaceValue();            
                int handsize=Crazy_Eight_Game.PlayHand[1].GetCount();
                for (int i = 0; i < handsize; i++){
                    Card swapcard = playHand[1].GetCard(i);
                    Suit swapsuit = swapcard.GetSuit();
                    FaceValue swapvalue = swapcard.GetFaceValue();                    
                    if (swapvalue == currentvalue){
                        stalecount = 0;
                        Crazy_Eight_Game.PlayHand[1].RemoveCardAt(i);
                        handsize = Crazy_Eight_Game.PlayHand[1].GetCount();
                        Crazy_Eight_Game.PlayPile[1].AddCard(swapcard);
                        incricount = 0;
                        break;
                    }
                    if (swapsuit == currentsuit){
                        stalecount = 0;
                        Crazy_Eight_Game.PlayHand[1].RemoveCardAt(i);
                        handsize = Crazy_Eight_Game.PlayHand[1].GetCount();
                        Crazy_Eight_Game.PlayPile[1].AddCard(swapcard);
                        incricount = 0;
                        break;
                    }
                }
            int templength = Crazy_Eight_Game.PlayHand[1].GetCount();
            if (templength > 0 && templength < 13){
                if (incricount > 0)                {
                    Card drawcard = Crazy_Eight_Game.PlayPile[0].DealOneCard();
                    Crazy_Eight_Game.PlayHand[1].AddCard(drawcard);
                    incricount = 1;
                }
            }
            if (templength == 13){
                stalecount++;
            }
        }

       /*Runs the functionality of the human player 
        * 
        * Precondition: None
        * Postcondition: Increments stalecount bothways as it moves a step towards stalemate, removes cards as applicable
        * */
        public static void Player_Turn(Card card)
        {
            Card pilecard = playPile[1].GetLastCardInPile();
            Suit currentsuit = pilecard.GetSuit();
            FaceValue currentvalue = pilecard.GetFaceValue();
            int handsize = Crazy_Eight_Game.PlayHand[0].GetCount();
            Suit swapsuit = card.GetSuit();
            FaceValue swapvalue = card.GetFaceValue();

                if (swapvalue == FaceValue.Eight)
                {
                    stalecount = 0;
                    Crazy_Eight_Game.PlayHand[0].RemoveCard(card);
                    handsize = Crazy_Eight_Game.PlayHand[0].GetCount();
                    Crazy_Eight_Game.PlayPile[1].AddCard(card);

                }
                if (swapvalue == currentvalue)
                {
                    stalecount = 0;
                    Crazy_Eight_Game.PlayHand[0].RemoveCard(card);
                    handsize = Crazy_Eight_Game.PlayHand[1].GetCount();
                    Crazy_Eight_Game.PlayPile[1].AddCard(card);
                }
                if (swapsuit == currentsuit)
                {
                    stalecount = 0;
                    Crazy_Eight_Game.PlayHand[0].RemoveCard(card);
                    handsize = Crazy_Eight_Game.PlayHand[1].GetCount();
                    Crazy_Eight_Game.PlayPile[1].AddCard(card);
                }
               
            int templength = Crazy_Eight_Game.PlayHand[0].GetCount();
            if (templength == 13)
            {
                stalecount++;
            }
        }

        /*Checks if Card is not equal to the card on top of the pile
       * 
       * Precondition: Card card
       * Postcondition: return 1 if card does not match or return 0
       * */
        public static int Check_Card(Card card)
        {
            Card pilecard = playPile[1].GetLastCardInPile();
            Suit currentsuit = pilecard.GetSuit();
            FaceValue currentvalue = pilecard.GetFaceValue();
            int handsize = Crazy_Eight_Game.PlayHand[0].GetCount();
            Suit swapsuit = card.GetSuit();
            FaceValue swapvalue = card.GetFaceValue();

           
            if (swapvalue != currentvalue)
            {
                if (swapsuit != currentsuit)
                {
                    return 1;
                }
            }

            return 0;

        }

      /*Checks if a playable Card is in the human players hand.
       * 
       * Precondition: None
       * Postcondition: Increments checkcounter and once it's more than 0, return 1. Else return 0.
       * */
        public static int Play_Check()
        {
            
            int checkcounter = 0;
            Card pilecard = playPile[1].GetLastCardInPile();
            Suit currentsuit = pilecard.GetSuit();
            FaceValue currentvalue = pilecard.GetFaceValue();

            int handsize = Crazy_Eight_Game.PlayHand[0].GetCount();

            for (int i = 0; i < handsize; i++)
            {
                Card swapcard = playHand[0].GetCard(i);
                Suit swapsuit = swapcard.GetSuit();
                FaceValue swapvalue = swapcard.GetFaceValue();

                if (swapvalue == currentvalue)
                {
                    checkcounter++;
                }

                if (swapsuit == currentsuit)
                {
                    checkcounter++;
                }

            }
            if (checkcounter > 0)
            {
                return 1;
            }
           
            return 0;
        }

        
    }//end class
}
