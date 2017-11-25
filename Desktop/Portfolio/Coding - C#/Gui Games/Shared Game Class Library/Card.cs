using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shared_Game_Class_Library
{
    public enum Suit { Clubs, Diamonds, Hearts, Spades }

    public enum FaceValue
    {
        Two, Three, Four, Five, Six, Seven, Eight, Nine,
        Ten, Jack, Queen, King, Ace
    }

    /// <summary>
    /// Card class is the basis for the Hand and Card Pile classes and, when initiated, contains different properties
    /// equating to the enumarated value above. The Card Class will be used to play the game by equating values and 
    /// then running the functions as necessary.
    /// </summary>
    /// <remarks>
    /// Primarily, the methods within the Card Class are for checking values and equivilancies of the cards.
    /// </remarks>

    public class Card : IEquatable<Card>, IComparable<Card>
    {
        private FaceValue faceValue;
        private Suit suit;

        public Card()
        {
        }

        /*Initialises card based on the input suit and input facevalue
         * 
         * Precondition: Suit and Facevalue
         * Postcondition: Initialises card with properties Suit and Facevalue
         * */
        public Card(Suit s, FaceValue f)
        {
            this.suit = s;
            this.faceValue = f;

        }

    /*Returns suit of the specific card
     * 
     * Precondition: none
     * Postcondition: returns Suit
     * */
        public Suit GetSuit()
        {
            return suit;
        }

    /*Returns facevalue of the specific card
     * 
     * Precondition: none
     * Postcondition: returns Facevalue
     * */
        public FaceValue GetFaceValue()
        {
            return faceValue;
        }

    /*Checks if Card is equal to other specified card
     * 
     * Precondition: Card card
     * Postcondition: returns true or false
     * */
        public bool Equals(Card c)
        {
            if (this.suit == c.suit && this.faceValue == c.faceValue)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

   /*Checks if Card is equal to other specified card in multiple ways
    * 
    * -1 if suit or facevalue is lesser than card
    * 0 if both are equal
    * 1 if suit or facevalue are greater than card
    * 
    * Precondition: Card card
    * Postcondition: returns -1, -1, 0, 1, 1, or 0
    * */
       public int CompareTo(Card c){
           if (this.suit < c.suit)
           {
               return -1;
           }

           else if (this.suit == c.suit)
           {
               if (this.faceValue < c.faceValue)
               {
                   return -1;
               }

               else if (this.faceValue == c.faceValue)
               {
                    return 0;
               }

               else if (this.faceValue > c.faceValue)
               {
                   return 1;
               }
           }

           else if (this.suit > c.suit)
           {
               return 1;
           }

           return 0;
       }

    }
}