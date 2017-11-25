using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace Shared_Game_Class_Library
{
    /// <summary>
    /// Hand Class are the collection of cards primarily attributed to the the
    /// player and computer. 
    /// </summary>
    /// <remarks>
    /// The methods in Hand class are primarily used for 
    /// organising and changing the objects in hand.
    /// </remarks>
    public class Hand: IEnumerable
    {
        private List<Card> cards = new List<Card>();

        public Hand()
        {
        }

        /*Initialises a list of Card objects to the class Hand.
         * 
         * Precondition:
         * Postcondition:
         * */
        public Hand(List<Card> myHand)
        {
            this.cards = myHand;
        }

        /* Gets the length of the list for Hand
         * 
         * Precondition: none
         * Postcondition: returns length of Hand
         * */
        public int GetCount()
        {
            return cards.Count;
        }
              
        /* Gets the Card object at a certain position, specified by an integer
         * 
         * Precondition: integer "position"
         * Postcondition: returns Card at that position
         * */
        public Card GetCard(int cardPos)
        {
            return cards[cardPos];
        }

        /* Takes in a Card object and adds it to the list under Class Hand.
         * 
         * Precondition: Card card
         * Postcondition: Adds object Card to the list in Class Hand.
         * */
        public void AddCard(Card card)
        {
            cards.Add(card);
        }

        /* Checks if list contains specific Card object.
         * 
         * Precondition: Card card
         * Postcondition: returns true or returns false.
         * */
        public bool ContainsCard(Card card){
            if (cards.Contains(card))
            {
                return true;
            }
            return false;
        }

        /* Takes in a Card object and adds it to the list under Class Hand.
         * 
         * Precondition: Card card
         * Postcondition: Removes card and returns true, or returns false.
         * */
       public bool RemoveCard(Card card){
            if (cards.Contains(card))
            {
                cards.Remove(card);
                return true;
            }
            return false;
       }

       /* Removes card from list under Class Hand based on an integer position
       * 
       * Precondition: integer "position"
       * Postcondition: Removes card at integer position
       * */
       public void RemoveCardAt(int cardPos){
           cards.Remove(cards[cardPos]);
       }

      /*Sorts the cards in the list according to suit and facevalue.
      * 
      * Precondition: none
      * Postcondition: Sorts cards
      * */
       public void SortHand()
       {
           cards.Sort();
       }

     /*
      * 
      * Precondition: none
      * Postcondition: returns Enumaerated
      * */
        public IEnumerator GetEnumerator()
        {
            return cards.GetEnumerator();
        }
    }
}
