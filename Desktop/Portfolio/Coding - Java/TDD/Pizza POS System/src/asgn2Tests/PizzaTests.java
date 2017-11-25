package asgn2Tests;

import static org.junit.Assert.*;

import java.time.LocalTime;

import org.junit.Before;
import org.junit.Test;


import asgn2Exceptions.PizzaException;
import asgn2Pizzas.MargheritaPizza;
import asgn2Pizzas.MeatLoversPizza;
import asgn2Pizzas.Pizza;
import asgn2Pizzas.PizzaTopping;
import asgn2Pizzas.VegetarianPizza;

/**
 * A class that that tests the asgn2Pizzas.MargheritaPizza, asgn2Pizzas.VegetarianPizza, asgn2Pizzas.MeatLoversPizza classes. 
 * Note that an instance of asgn2Pizzas.MeatLoversPizza should be used to test the functionality of the 
 * asgn2Pizzas.Pizza abstract class. 
 * 
 * @author Thiline Widanagamage N9185691
 *
 */
public class PizzaTests {
	
	private int minPizzaQuantity = 1;
	private int midPizzaQuantity = 5;
	private int limitPizzaQuantity = 10;
	private int boundaryBreakQuantity = 11;
	
	LocalTime time_1859 = LocalTime.parse("18:59:00");	
	LocalTime time_1900 = LocalTime.parse("19:00:00");
	LocalTime time_1909 = LocalTime.parse("19:09:00");
	LocalTime time_2001 = LocalTime.parse("20:01:00");
	LocalTime time_2300 = LocalTime.parse("23:00:00");
	LocalTime time_0000 = LocalTime.parse("00:00:00");
	
	
	
	Pizza testMeatPizza;
	Pizza testVegPizza;
	Pizza testMargPizza;
	Pizza testPizzaWithNoType;
	Pizza testPizza;
	
	@Before
	public void setUp() throws PizzaException {
		setUpMeatPizza();
		setUpVegPizza();
		setUpMargPizza();
	}

	private void setUpMeatPizza() throws PizzaException{
		testMeatPizza = new MeatLoversPizza(midPizzaQuantity, time_2001, time_2300);
	}
	
	private void setUpVegPizza() throws PizzaException{
		testVegPizza = new VegetarianPizza(midPizzaQuantity, time_2001, time_2300);
	}
	
	private void setUpMargPizza() throws PizzaException{
		testMargPizza = new MargheritaPizza(midPizzaQuantity, time_2001, time_2300);
	}
		
	@Test
	public void shouldHaveCorrectToppingsOnAMargheritaOrder() throws PizzaException {
		//Should have these toppings
		assertTrue(testMargPizza.containsTopping(PizzaTopping.TOMATO));
		assertTrue(testMargPizza.containsTopping(PizzaTopping.CHEESE));
		
		//Should not have these toppings
		assertFalse(testMargPizza.containsTopping(PizzaTopping.BACON));
		assertFalse(testMargPizza.containsTopping(PizzaTopping.SALAMI));
		assertFalse(testMargPizza.containsTopping(PizzaTopping.PEPPERONI));
		assertFalse(testMargPizza.containsTopping(PizzaTopping.CAPSICUM));
		assertFalse(testMargPizza.containsTopping(PizzaTopping.MUSHROOM));
		assertFalse(testMargPizza.containsTopping(PizzaTopping.EGGPLANT));
		
	}
	
	@Test
	public void shouldHaveCorrectToppingsOnAMeatloversOrder() throws PizzaException {
		// Should have these toppings
		
		assertTrue(testMeatPizza.containsTopping(PizzaTopping.TOMATO));
		assertTrue(testMeatPizza.containsTopping(PizzaTopping.CHEESE));
		assertTrue(testMeatPizza.containsTopping(PizzaTopping.BACON));
		assertTrue(testMeatPizza.containsTopping(PizzaTopping.PEPPERONI));
		assertTrue(testMeatPizza.containsTopping(PizzaTopping.SALAMI));

		// Should not have these toppings
		
		assertFalse(testMeatPizza.containsTopping(PizzaTopping.CAPSICUM));
		assertFalse(testMeatPizza.containsTopping(PizzaTopping.EGGPLANT));
		assertFalse(testMeatPizza.containsTopping(PizzaTopping.MUSHROOM));

	}
	
	@Test
	public void shouldHaveCorrectToppingsOnAVegetarianOrder() throws PizzaException {
		// Should have these toppings
		assertTrue(testVegPizza.containsTopping(PizzaTopping.TOMATO));
		assertTrue(testVegPizza.containsTopping(PizzaTopping.CHEESE));
		assertTrue(testVegPizza.containsTopping(PizzaTopping.EGGPLANT));
		assertTrue(testVegPizza.containsTopping(PizzaTopping.CAPSICUM));
		assertTrue(testVegPizza.containsTopping(PizzaTopping.MUSHROOM));
		
		// Should not have these toppings
		assertFalse(testVegPizza.containsTopping(PizzaTopping.BACON));
		assertFalse(testVegPizza.containsTopping(PizzaTopping.SALAMI));
		assertFalse(testVegPizza.containsTopping(PizzaTopping.PEPPERONI));
	}
	
	@Test
	public void shouldGetPizzaQuantity() throws PizzaException {
		assertEquals(midPizzaQuantity, testMeatPizza.getQuantity());
	}
	
	@Test
	public void shouldGetPizzaTypeForMargherita() throws PizzaException {
		assertEquals("Margherita", testMargPizza.getPizzaType());
	}
	
	@Test
	public void shouldGetPizzaTypeForMeatlovers() throws PizzaException {
		assertEquals("Meat Lovers", testMeatPizza.getPizzaType());
	}
	
	@Test
	public void shouldGetPizzaTypeForVegetarian() throws PizzaException {
		assertEquals("Vegetarian", testVegPizza.getPizzaType());
	}
	
		
	
	@Test(expected = PizzaException.class)
	public void shouldThrowExceptionIfQuantityIsLessThanOne() throws PizzaException {
		new MeatLoversPizza(0, time_2001, time_2300);
		
	}

	@Test(expected = PizzaException.class)
	public void shouldThrowExceptionIfQuantityIsMoreThanTen() throws PizzaException {
		new MeatLoversPizza(boundaryBreakQuantity, time_2001, time_2300);
		
	}
	
	@Test
	public void shouldCreateAValidOrderWhenQuantityIsOne() throws PizzaException {
		Pizza validPizza = new MeatLoversPizza(minPizzaQuantity, time_2001, time_2300);
		assertNotNull(validPizza);
	}
	
	@Test
	public void shouldCreateAValidOrderWhenQuantityIsTen() throws PizzaException {
		Pizza validPizza = new MeatLoversPizza(limitPizzaQuantity, time_2001, time_2300);
		assertNotNull(validPizza);
	}
	
	@Test
	public void shouldGetPricePerMargheritaPizza() throws PizzaException {
		assertEquals(8, testMargPizza.getPricePerPizza(), 0);
	}

	@Test
	public void shouldGetPricePerMeatLoversPizza() throws PizzaException {
		assertEquals(12, testMeatPizza.getPricePerPizza(), 0);
	}
	
	@Test
	public void shouldGetPricePerVegetarianPizza() throws PizzaException {
		assertEquals(10, testVegPizza.getPricePerPizza(), 0);
	}

	@Test
	// Asserts that total topping cost equals $1.50
	public void shouldGetCostPerMargheritaPizza() throws PizzaException {
		assertEquals(1.5, testMargPizza.getCostPerPizza(), 0);
	}

	@Test
	// Asserts that total topping cost equals $5
	public void shouldGetCostPerMeatLoversPizza() throws PizzaException {
		assertEquals(5, testMeatPizza.getCostPerPizza(), 0);
	}
	
	@Test
	// Asserts that total topping cost equals $5.50
	public void shouldGetCostPerVegetarianPizza() throws PizzaException {
		assertEquals(5.5, testVegPizza.getCostPerPizza(), 0);
	}
	
	@Test
	public void shouldGetOrderPriceWhenOrderingMultipleMargheritaPizzas() throws PizzaException {
		assertEquals(40, testMargPizza.getOrderPrice(), 0);
	}
		
	@Test
	public void shouldGetOrderPriceWhenOrderingMultipleMeatloverPizzas() throws PizzaException {
		assertEquals(60, testMeatPizza.getOrderPrice(), 0);
	}
		
	@Test
	public void shouldGetOrderPriceWhenOrderingMultipleVegetarianPizzas() throws PizzaException {
		assertEquals(50, testVegPizza.getOrderPrice(), 0);
	}
	
	@Test
	public void shouldGetOrderCostWhenOrderingMultipleMargheritaPizzas() throws PizzaException {
		assertEquals(7.5, testMargPizza.getOrderCost(), 0);
	}

	@Test
	public void shouldGetOrderCostWhenOrderingMultipleMeatloversPizzas() throws PizzaException {
		assertEquals(25, testMeatPizza.getOrderCost(), 0);
	}		
	
	@Test
	public void shouldGetOrderCostWhenOrderingMultipleVegetarianPizzas() throws PizzaException {
		assertEquals(27.5, testVegPizza.getOrderCost(), 0);
	}
	
	@Test
	public void shouldGetOrderProfitWhenOrderingMultipleMargheritaPizzas() throws PizzaException {
		assertEquals(32.5, testMargPizza.getOrderProfit(), 0);
	}
	
	@Test
	public void shouldGetOrderProfitWhenOrderingMultipleMeatloversPizzas() throws PizzaException {
		assertEquals(35, testMeatPizza.getOrderProfit(), 0);
	}
	
	@Test
	public void shouldGetOrderProfitWhenOrderingMultipleVegetarianPizzas() throws PizzaException {
		assertEquals(22.5, testVegPizza.getOrderProfit(), 0);
	}
	
	@Test(expected = PizzaException.class)
	public void shouldThrowExceptionWhenPizzaCookAndDeliveryTimeIsUnderTenMins() throws PizzaException {
		new MeatLoversPizza(midPizzaQuantity, time_1900, time_1909);
	}
	
	@Test(expected = PizzaException.class)
	public void shouldThrowExceptionWhenPizzaCookAndDeliveryTimeIsOverAnHour() throws PizzaException {
		new MeatLoversPizza(midPizzaQuantity, time_1900, time_2001);
	}
	
	@Test(expected = PizzaException.class)
	public void shouldThrowExceptionWhenPizzaIsOrderedBeforeOpeningTime() throws PizzaException {
		testPizza = new MeatLoversPizza(midPizzaQuantity, time_1859, time_1909);
	}

	@Test(expected = PizzaException.class)
	public void shouldThrowExceptionWhenPizzaIsOrderedAfterClosingTime() throws PizzaException {
		new MeatLoversPizza(midPizzaQuantity, time_2300, time_0000);
	}
	
	

		
	
}
