package asgn2Tests;

import static org.junit.Assert.assertEquals;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import org.junit.Before;
import org.junit.Test;

import asgn2Customers.Customer;
import asgn2Exceptions.CustomerException;
import asgn2Exceptions.LogHandlerException;
import asgn2Exceptions.PizzaException;
import asgn2Pizzas.Pizza;
import asgn2Restaurant.LogHandler;

/** A class that tests the methods relating to the creation of Pizza objects in the asgn2Restaurant.LogHander class.
* 
* @author Thiline Widanagamage N9185691
* 
*/
public class LogHandlerPizzaTests {
	
	private String testString = 
			"19:00:00,19:20:00,Test One,0123456789,DVC,5,5,PZV,1\n" +
			"19:00:00,19:20:00,Test Two,0123456789,DVC,5,5,PZM,5\n" +
			"19:00:00,19:20:00,Test Three,0123456789,DVC,5,5,PZL,5";
	
	
	private String invalidString = " , , , , , , , , ";
	private String nullString = null;
	private String invalidPath = "InvalidPath";
	private Customer testCustomer;
	private ArrayList<Pizza> testList = new ArrayList<Pizza>();
	private File testFile;
	private File emptyTestFile;
	
	@Before //Not a Test. Creates temporary File with the testString.
	public void setUpTestFile(){
		try {
			testFile = File.createTempFile("tempFile", ".txt");
			BufferedWriter writer = new BufferedWriter(new FileWriter(testFile));
			writer.write(testString);
			writer.close();
    	    emptyTestFile = File.createTempFile("invalidTempFile", ".txt");
			BufferedWriter invalidWriter = new BufferedWriter(new FileWriter(emptyTestFile));
			invalidWriter.write(invalidString);
			invalidWriter.close();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Test
	public void populateDataSetTest() throws LogHandlerException, PizzaException{
		String tempPath = testFile.getPath();
		testList = LogHandler.populatePizzaDataset(tempPath);
		assertEquals(testList.get(0).getPizzaType(),"Vegetarian");
		assertEquals(testList.get(1).getPizzaType(),"Margherita");
		assertEquals(testList.get(2).getPizzaType(),"Meat Lovers");
	}
	
	@Test (expected = LogHandlerException.class)
	public void checksIfPopulatePizzaFileExists() throws LogHandlerException, PizzaException{
		String tempPath = "nonexistentfile.txt";
		LogHandler.populatePizzaDataset(tempPath);
		
	}
	
	@Test (expected = LogHandlerException.class)
	public void checksIfFileNameIsEmpty() throws LogHandlerException, PizzaException{
		String tempPath = "";
		LogHandler.populatePizzaDataset(tempPath);
		
	}
	
	@Test (expected = LogHandlerException.class)
	public void ensuresLogLineIsntEmpty() throws PizzaException, LogHandlerException {
		String line = "";
		LogHandler.createPizza(line);
	}
	
	@Test (expected = LogHandlerException.class)
	public void ensuresSplitLineIsntEmpty() throws PizzaException, LogHandlerException {
		String line = " , , , , , , , , ";
		LogHandler.createPizza(line);
	}

	@Test (expected = LogHandlerException.class)
	public void ensuresSplitLineIsntEmptyWhenJustCommas() throws PizzaException, LogHandlerException {
		String line = ",,,,,,,,";
		LogHandler.createPizza(line);
	}
	
	@Test
	public void ensuresPizzaDetailsAreCorrect() throws PizzaException, LogHandlerException {
		String line = "20:00:00,20:20:00,Test Customer,0123456789,DVC,5,5,PZM,5";
		
		Pizza pizza = LogHandler.createPizza(line);
		
		assertEquals("Margherita", pizza.getPizzaType());
		assertEquals(5, pizza.getQuantity());
		
	}

	@Test (expected = LogHandlerException.class)
	public void throwsExceptionWhenQuantityIsntANumber() throws PizzaException, LogHandlerException {
		String line = "20:00:00,20:20:00,Test Customer,0123456789,DVC,5,5,PZM,ABC";
		LogHandler.createPizza(line);
	}

	@Test (expected = LogHandlerException.class)
	public void throwsExceptionWhenTimeIsntParsedCorrectly() throws PizzaException, LogHandlerException {
		String line = "25:WW:WW,20:20:00,Test Customer,0123456789,DVC,5,5,PZM,5";
		LogHandler.createPizza(line);
	}
	
	@Test (expected = PizzaException.class)
	public void throwsExceptionWhenPizzaTypeIsEmpty() throws PizzaException, LogHandlerException {
		String line = "20:00:00,20:20:00,Test Customer,0123456789,DVC,5,5,,5";
		LogHandler.createPizza(line);
	}
	
}
