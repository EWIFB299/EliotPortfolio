package asgn2Tests;

import static org.junit.Assert.*;

import java.time.LocalTime;

import org.junit.Test;

import asgn2Exceptions.PizzaException;
import asgn2Pizzas.Pizza;
import asgn2Pizzas.PizzaFactory;

/** 
 * A class that tests the asgn2Pizzas.PizzaFactory class.
 * 
 * @author Thiline Widanagamage N9185691
 * 
 */
public class PizzaFactoryTests {
	
	private String Margherita = "Margherita";
	private String MeatLovers = "Meat Lovers";
	private String Vegetarian = "Vegetarian";
	private String margheritaPizzaCode = "PZM";
	private String meatLoversPizzaCode = "PZL";
	private String vegetarianPizzaCode = "PZV";
	private String invalidCode = "IWJ";
	private int quantityOfFive = 5;
	LocalTime orderTime = LocalTime.parse("19:10:00");
	LocalTime deliveryTime = LocalTime.parse("19:30:00");
	
	
	@Test
	public void shouldMakeMargheritaPizzaOrderWhenUsingPZMCode() throws PizzaException {
		Pizza pizza = PizzaFactory.getPizza(margheritaPizzaCode, quantityOfFive, orderTime, deliveryTime);
		assertEquals(Margherita, pizza.getPizzaType());
	}
	
	@Test
	public void shouldMakeMeatLoversPizzaOrderWhenUsingPZLCode() throws PizzaException {
		Pizza pizza = PizzaFactory.getPizza(meatLoversPizzaCode, quantityOfFive, orderTime, deliveryTime);
		assertEquals(MeatLovers, pizza.getPizzaType());
	}

	@Test
	public void shouldMakeVegetarianPizzaOrderWhenUsingPZVCode() throws PizzaException {
		Pizza pizza = PizzaFactory.getPizza(vegetarianPizzaCode, quantityOfFive, orderTime, deliveryTime);
		assertEquals(Vegetarian, pizza.getPizzaType());
	}

	@Test(expected = PizzaException.class)
	public void shouldThrowExceptionWhenPizzaCodeIsInvalid() throws PizzaException {
		PizzaFactory.getPizza(invalidCode, quantityOfFive, orderTime, deliveryTime);
	}

	
	
	
}
