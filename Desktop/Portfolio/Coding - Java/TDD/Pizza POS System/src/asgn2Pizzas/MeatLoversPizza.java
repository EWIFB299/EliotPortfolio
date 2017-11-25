package asgn2Pizzas;

import java.time.LocalTime;
import java.util.ArrayList;

import asgn2Exceptions.PizzaException;

/**
 * 
 *  A class that represents a meat lovers pizza made at the Pizza Palace restaurant. 
 *  The meat lovers pizza has certain toppings listed in Section 5.1 of the Assignment Specification Document.  
 *  A description of the class's fields and their constraints is provided in Section 5.1 of the Assignment Specification.
 * 
 * @author Eliot Wilson n9175504
 *
 */
public class MeatLoversPizza extends Pizza {
	
	
	private final static double meatloversPrice = 12;
	private int toppingCount = 5;

	/**
	 * 
	 *  This class represents a meat lovers pizza made at the  Pizza Palace restaurant. The meat lovers pizza has certain
	 *  toppings listed in Section 5.1 of the Assignment Specification Document.  A description of the class's
	 *  fields and their constraints is provided in Section 5.1 of the Assignment Specification.
	 *  A PizzaException is thrown if the any of the constraints listed in Section 5.1 of the Assignment Specification are violated. 
	 * 
 	 * <P> PRE: TRUE
 	 * <P> POST: All field values including the cost per pizza are set
     *
	 * @param quantity - The number of pizzas ordered 
	 * @param orderTime - The time that the pizza order was made and sent to the kitchen 
	 * @param deliveryTime - The time that the pizza was delivered to the customer
	 * @throws PizzaException if supplied parameters are invalid 
	 *
	 */
	
	public MeatLoversPizza(int quantity, LocalTime orderTime, LocalTime deliveryTime) throws PizzaException {
		super(quantity, orderTime, deliveryTime, "Meat Lovers", meatloversPrice);
		toppings = new ArrayList<PizzaTopping>(toppingCount);
		this.toppings.add(PizzaTopping.CHEESE);
		this.toppings.add(PizzaTopping.TOMATO);
		this.toppings.add(PizzaTopping.BACON);
		this.toppings.add(PizzaTopping.PEPPERONI);
		this.toppings.add(PizzaTopping.SALAMI);
		this.calculateCostPerPizza();
	}

}
