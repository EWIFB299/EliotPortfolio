package asgn2Tests;

import static org.junit.Assert.*;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.junit.Before;
import org.junit.Test;

import asgn2Exceptions.CustomerException;
import asgn2Exceptions.LogHandlerException;
import asgn2Exceptions.PizzaException;
import asgn2Pizzas.Pizza;
import asgn2Restaurant.PizzaRestaurant;

/**
 * A class that tests the methods relating to the handling of Pizza objects in the asgn2Restaurant.PizzaRestaurant class as well as
 * processLog and resetDetails.
 * 
 * @author Thiline Widanagamage N9185691
 *
 */
public class RestaurantPizzaTests {

	PizzaRestaurant pizzaRestaurant;
	final String testData = "21:08:00,21:30:00,Emma Chen,0678585543,DNC,-4,2,PZM,4\n" +
							"22:46:00,22:58:00,Jackson Taylor,0698979160,DVC,-5,-10,PZL,5\n" +
							"20:47:00,21:11:00,Caden Kumar,0862001010,PUC,0,0,PZV,9";
	
	final String invalidTestData = "29:08:00,20:30:00,Emma Chen,0678585543,DNC,-4,2,PZM,4\n" +
			"22:46:00,22:58:00,Jackson Taylor,0698979160,DVC,-5,-10,PZL,5\n" +
			"20:47:00,21:11:00,Caden Kumar,0862001010,PUC,0,0,PZV,9";
	
	final double expectedProfit = 101.5;
	
	@Before 
	public void setup() {
		pizzaRestaurant = new PizzaRestaurant();
	}
	
	@Test
	public void shouldProcessLogSuccessfully() throws CustomerException, PizzaException, LogHandlerException {
		String filename = createTestLogfile("test.txt", testData);
		boolean processed = pizzaRestaurant.processLog(filename);
		assertTrue(processed);
	}
	
	@Test
	public void shouldGetNumberOfPizzaOrders() throws CustomerException, PizzaException, LogHandlerException {
		String filename = createTestLogfile("test.txt", testData);
		pizzaRestaurant.processLog(filename);
		assertEquals(3, pizzaRestaurant.getNumPizzaOrders());		
	}

	@Test
	public void shouldGetPizzaByIndex() throws CustomerException, PizzaException, LogHandlerException {
		String filename = createTestLogfile("test.txt", testData);
		pizzaRestaurant.processLog(filename);
		
		Pizza actualPizza = pizzaRestaurant.getPizzaByIndex(1);
		assertEquals("Meat Lovers", actualPizza.getPizzaType());		
	}
	
	@Test (expected = PizzaException.class)
	public void shouldThrowExceptionWhenGetPizzaByIndexIsLessThanZero() throws CustomerException, PizzaException, LogHandlerException {
		String filename = createTestLogfile("test.txt", testData);
		pizzaRestaurant.processLog(filename);
		
		pizzaRestaurant.getPizzaByIndex(-1);	
	}
	
	@Test (expected = PizzaException.class)
	public void shouldThrowExceptionWhenGetPizzaByIndexIsOutOfRange() throws CustomerException, PizzaException, LogHandlerException {
		String filename = createTestLogfile("test.txt", testData);
		pizzaRestaurant.processLog(filename);
		pizzaRestaurant.getPizzaByIndex(3);
	}
	
	@Test (expected = PizzaException.class)
	public void shouldThrowExceptionWhenGetPizzaByIndexIsOutOfRange2() throws CustomerException, PizzaException, LogHandlerException {
		String filename = createTestLogfile("test.txt", testData);
		pizzaRestaurant.processLog(filename);
		pizzaRestaurant.getPizzaByIndex(4);
	}
	
	@Test
	public void shouldProcessFileWithNoOrders() throws CustomerException, PizzaException, LogHandlerException {
		assertEquals(0, pizzaRestaurant.getNumPizzaOrders());		
	}
	
	
	@Test
	public void shouldResetDetails() throws CustomerException, PizzaException, LogHandlerException {
		String filename = createTestLogfile("test.txt", testData);
		pizzaRestaurant.processLog(filename);
		assertEquals(3, pizzaRestaurant.getNumPizzaOrders());
		pizzaRestaurant.resetDetails();
		assertEquals(0, pizzaRestaurant.getNumPizzaOrders());		
	}
	
	@Test
	public void shouldGetTotalProfit() throws CustomerException, PizzaException, LogHandlerException {
		String filename = createTestLogfile("test.txt", testData);
		pizzaRestaurant.processLog(filename);
		
		double actualProfit = pizzaRestaurant.getTotalProfit();
		
		assertEquals(expectedProfit, actualProfit, 0);
	}
		
	private String createTestLogfile(String filename, String testData) {
		try {
			File tempFile = File.createTempFile(filename, ".txt");
			BufferedWriter writer = new BufferedWriter(new FileWriter(tempFile));
			writer.write(testData);
			writer.close();
			return tempFile.getPath();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return null;
	}
	
}
