using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shared_Game_Class_Library
{

    /// <summary>
    /// CardPile class is the basis for the decks used in games. Card Pile refers to the non player collections of the Card objects
    /// that encompass the games.
    /// </summary>
    /// <remarks>
    /// Primarily, the methods within the CardPile class are used for 
    /// distribution of objects oriented to the Card class amongst other 
    /// Card Pile classes or amongst Hand classes.
    /// </remarks>
   public class CardPile
    {
        private List<Card> pile = new List<Card>();
        public const int NUM_SUITS = 4;
        public const int NUM_CARDS_PER_SUIT = 13;
        
        public CardPile(){

        }

        /*Initialises a pile of cards. If the precondition is true, the pile will contain
         * 52 unique cards.
         * 
         * Precondition: true or false
         * Postcondition: Initialises pile of 52 cards or initilaises empty pile.
         * */
        public CardPile(bool fullpile)
        {
            if (fullpile)
            {
                
                for (int suitcount = 0; suitcount < NUM_SUITS; suitcount++)
                {
                    for (int facecount = 0; facecount < NUM_CARDS_PER_SUIT; facecount++)
                    {
                        Card nextCard =  new Card((Suit)suitcount, (FaceValue)facecount);
                        pile.Add(nextCard);
                    }
                }
            }

        }

        /*Adds a selected card to the selected pile
         * 
         * Precondition: Card card
         * Postcondition: Adds precondition card to pile
         * */
        public void AddCard(Card card)
        {
            pile.Add(card);
        }

         /*Gets the length of the list.
          * 
          * Precondition: none
          * Postcondition: returns int length of list
          * */
        public int GetCount()
        {
            return pile.Count;
        }

        /*Gets the last card in the list.
          * 
          * Precondition: none
          * Postcondition: returns card at position at end of list
          * */
        public Card GetLastCardInPile()
        {
            return pile.Last();
        }

        /*Gets the first card in the list.
           * 
           * Precondition: none
           * Postcondition: returns card at position 0
           * */
        public Card GetFirstCardInPile()
        {
            return pile.First();
        }

        /*Shuffles all cards in the pile.
           * 
           * Precondition: none
           * Postcondition: Randomly shuffles pile
           * */
        public void ShufflePile()
        {
            Random rPos = new Random();
            int pilePos = pile.Count;
            while (pilePos > 0)
            {
                pilePos--;
                int newPos = rPos.Next(pilePos + 1);
                Card card = pile[newPos];
                pile[newPos] = pile[pilePos];
                pile[pilePos] = card;
            }
        }

        /*Deals the first card in a pile.
           * 
           * Precondition: none
           * Postcondition: returns Card card and removes it from list.
           * */
        public Card DealOneCard()
        {
            Card tempcard = pile[0];
            pile.Remove(pile[0]);
            return tempcard;
        }

        /*Deals a set number of cards from the list.
           * 
           * Precondition: integer "number of cards"
           * Postcondition: returns the number of Card cards and removes them from list.
           * */
        public List<Card> DealCards(int numCards)
        {
            List<Card> newCards = new List<Card>();
            for (int swapcount = 0; swapcount < numCards; swapcount++ )
            {
                Card nextCard = pile[swapcount];
                pile.Remove(pile[swapcount]);
                newCards.Add(nextCard);
            }
            return newCards;
        }

    }
}
