package asgn2Pizzas;

import java.awt.Window.Type;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.EnumSet;

import asgn2Exceptions.PizzaException;


/**
 * An abstract class that represents pizzas sold at the Pizza Palace restaurant. 
 * The Pizza class is used as a base class of VegetarianPizza, MargheritaPizza and MeatLoversPizza. 
 * Each of these subclasses have a different set of toppings. A description of the class's fields
 * and their constraints is provided in Section 5.1 of the Assignment Specification. 
 * 
 * @author Eliot Wilson n9175504
 *
 */
public abstract class Pizza  {

	/**
	 *  This class represents a pizza produced at the Pizza Palace restaurant.  A detailed description of the class's fields
	 *  and parameters is provided in the Assignment Specification, in particular in Section 5.1. 
	 *  A PizzaException is thrown if the any of the constraints listed in Section 5.1 of the Assignment Specification
	 *  are violated. 
	 *
	 *  PRE: TRUE
	 *  POST: All field values except cost per pizza are set
	 * 
	 * @param quantity - The number of pizzas ordered 
	 * @param orderTime - The time that the pizza order was made and sent to the kitchen 
	 * @param deliveryTime - The time that the pizza was delivered to the customer
	 * @param type -  A human understandable description of this Pizza type
	 * @param price - The price that the pizza is sold to the customer
	 * @throws PizzaException if supplied parameters are invalid 
	 * 
	 */

	private int pizzaQuantity;
	private String pizzaType;
	private double pizzaPrice;
	protected double pizzaCost;
	protected ArrayList<PizzaTopping> toppings;
	private LocalTime openingTime = LocalTime.of(19, 00, 00, 00000);
	private LocalTime closingTime = LocalTime.of(23, 00, 00, 00000);

	public Pizza(int quantity, LocalTime orderTime, LocalTime deliveryTime, String type, double price) throws PizzaException{
		if(!(type.equals("Meat Lovers")) && !(type.equals("Vegetarian")) && !(type.equals("Margherita"))){
			throw new PizzaException("Not Valid Pizza Type");
		}
		if(quantity < 1 || quantity > 10){
			throw new PizzaException("Invalid Quantity");
		}
		if(orderTime.getHour() < openingTime.getHour() 
				|| (orderTime.getHour() > closingTime.getHour()) 
				|| ((orderTime.getHour() == closingTime.getHour()) && (orderTime.getMinute()>0)) 
				|| (deliveryTime.getHour() < orderTime.getHour())
				|| ((deliveryTime.getHour() >= orderTime.getHour()+1) && (deliveryTime.getMinute() >= orderTime.getMinute()))
				|| ((deliveryTime.getHour() == orderTime.getHour()) && (deliveryTime.getMinute() < orderTime.getMinute() +10)) ){
			throw new PizzaException("Invalid Timeframe");
		}
		this.pizzaQuantity = quantity;
		this.pizzaType = type;
		this.pizzaPrice = price;		
	}


	/**
	 * Calculates how much a pizza would could to make calculated from its toppings.
	 *  
	 * <P> PRE: TRUE
	 * <P> POST: The cost field is set to sum of the Pizzas's toppings
	 */
	public final void calculateCostPerPizza(){
		double totalCost = 0;
		for (PizzaTopping tempTopping : toppings) {
			totalCost += tempTopping.getCost();
		}
		this.pizzaCost = totalCost;
	}

	/**
	 * Returns the amount that an individual pizza costs to make.
	 * @return The amount that an individual pizza costs to make.
	 */
	public final double getCostPerPizza(){
		return this.pizzaCost;		
	}

	/**
	 * Returns the amount that an individual pizza is sold to the customer.
	 * @return The amount that an individual pizza is sold to the customer.
	 */
	public final double getPricePerPizza(){
		return this.pizzaPrice;
	}

	/**
	 * Returns the amount that the entire order costs to make, taking into account the type and quantity of pizzas. 
	 * @return The amount that the entire order costs to make, taking into account the type and quantity of pizzas. 
	 */
	public final double getOrderCost(){
		return (this.getCostPerPizza() * this.pizzaQuantity);
	}

	/**
	 * Returns the amount that the entire order is sold to the customer, taking into account the type and quantity of pizzas. 
	 * @return The amount that the entire order is sold to the customer, taking into account the type and quantity of pizzas. 
	 */
	public final double getOrderPrice(){
		return (this.pizzaPrice * this.pizzaQuantity);
	}


	/**
	 * Returns the profit made by the restaurant on the order which is the order price minus the order cost. 
	 * @return  Returns the profit made by the restaurant on the order which is the order price minus the order cost.
	 */
	public final double getOrderProfit(){
		return(this.getOrderPrice()-this.getOrderCost());
	}


	/**
	 * Indicates if the pizza contains the specified pizza topping or not. 
	 * @param topping -  A topping as specified in the enumeration PizzaTopping
	 * @return Returns  true if the instance of Pizza contains the specified topping and false otherwise.
	 */
	public final boolean containsTopping(PizzaTopping topping){
		if(toppings.contains(topping)){
			return true;
		}
		else return false;
	}

	/**
	 * Returns the quantity of pizzas ordered. 
	 * @return the quantity of pizzas ordered. 
	 */
	public final int getQuantity(){
		return this.pizzaQuantity;
	}

	/**
	 * Returns a human understandable description of the Pizza's type. 
	 * The valid alternatives are listed in Section 5.1 of the Assignment Specification. 
	 * @return A human understandable description of the Pizza's type.
	 */
	public final String getPizzaType(){
		return this.pizzaType;
	}


	/**
	 * Compares *this* Pizza object with an instance of an *other* Pizza object and returns true if  
	 * if the two objects are equivalent, that is, if the values exposed by public methods are equal.
	 * You do not need to test this method.
	 *  
	 * @return true if *this* Pizza object and the *other* Pizza object have the same values returned for 	
	 * getCostPerPizza(), getOrderCost(), getOrderPrice(), getOrderProfit(), getPizzaType(), getPricePerPizza() 
	 * and getQuantity().
	 *   
	 */
	@Override
	public boolean equals(Object other){
		Pizza otherPizza = (Pizza) other;
		return ((this.getCostPerPizza()) == (otherPizza.getCostPerPizza()) &&
				(this.getOrderCost()) == (otherPizza.getOrderCost())) &&				
				(this.getOrderPrice()) == (otherPizza.getOrderPrice()) &&
				(this.getOrderProfit()) == (otherPizza.getOrderProfit()) &&
				(this.getPizzaType() == (otherPizza.getPizzaType()) &&
				(this.getPricePerPizza()) == (otherPizza.getPricePerPizza()) &&
				(this.getQuantity()) == (otherPizza.getQuantity()));
	}


}
