package asgn2Pizzas;

import java.time.LocalTime;
import java.util.ArrayList;

import asgn2Exceptions.PizzaException;


/**
 * 
 *  A class that represents a vegetarian pizza made at the Pizza Palace restaurant. 
 *  The vegetarian pizza has certain toppings listed in Section 5.1 of the Assignment Specification Document.  
 *  A description of the class's fields and their constraints is provided in Section 5.1 of the Assignment Specification.
 * 
 * @author Eliot Wilson n9175504
 *
 */
public class VegetarianPizza extends Pizza {
	
	private final static double vegetarianPrice = 10;
	private int toppingCount = 5;

	/**
	 * 
	 *  This class represents a vegetarian pizza made at the  Pizza Palace restaurant. The vegetarian pizza has certain
	 *  toppings listed in Section 5.1 of the Assignment Specification Document.  A description of the class's
	 *  fields and their constraints is provided in Section 5.1 of the Assignment Specification.
	 *  A PizzaException is thrown if the any of the constraints listed in Section 5.1 of the Assignment Specification are violated. 
	 * 
     * <P> PRE: TRUE
	 * <P> POST: All field values including the cost per pizza are set
	 * @param quantity - The number of pizzas ordered 
	 * @param orderTime - The time that the pizza order was made and sent to the kitchen 
	 * @param deliveryTime - The time that the pizza was delivered to the customer
	 * @throws PizzaException if supplied parameters are invalid 
	 *
	 */
	public VegetarianPizza(int quantity, LocalTime orderTime, LocalTime deliveryTime) throws PizzaException {
		super(quantity, orderTime, deliveryTime, "Vegetarian", vegetarianPrice);
		toppings = new ArrayList<PizzaTopping>(toppingCount);
		this.toppings.add(PizzaTopping.CHEESE);
		this.toppings.add(PizzaTopping.TOMATO);
		this.toppings.add(PizzaTopping.CAPSICUM);
		this.toppings.add(PizzaTopping.EGGPLANT);
		this.toppings.add(PizzaTopping.MUSHROOM);
		this.calculateCostPerPizza();

	}

}
