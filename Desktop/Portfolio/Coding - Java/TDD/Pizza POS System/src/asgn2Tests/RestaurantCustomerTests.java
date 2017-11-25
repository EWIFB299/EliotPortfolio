package asgn2Tests;

import static org.junit.Assert.*;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import org.junit.Before;
import org.junit.Test;

import asgn2Customers.Customer;
import asgn2Exceptions.CustomerException;
import asgn2Exceptions.LogHandlerException;
import asgn2Exceptions.PizzaException;
import asgn2Restaurant.PizzaRestaurant;

/**
 * A class that that tests the methods relating to the handling of Customer objects in the asgn2Restaurant.PizzaRestaurant
 * class as well as processLog and resetDetails.
 * 
 * @author Eliot Wilson n9175504
 */
public class RestaurantCustomerTests {
	
	PizzaRestaurant testRestaurant;
	Customer testCustomer;
	private File testFile;
	private File emptyTestFile;
	private String testString =  "19:00:00,19:20:00,Casey Jones,0123456789,DVC,5,5,PZV,2";
	private String invalidString = " , , , , , , , , ";
	private String nullLogString = null;
	
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
	
	@Before @Test
	public void setUpPizzaResterauntTest(){
		testRestaurant = new PizzaRestaurant();
		
	}
	
	@Test
	public void customerProcessLogTest() throws CustomerException, PizzaException, LogHandlerException{
		String tempPath = testFile.getPath();
		assertTrue(testRestaurant.processLog(tempPath));
	}
	
	@Test
	public void customerIndexTest() throws CustomerException, PizzaException, LogHandlerException{
		String tempPath = testFile.getPath();
		testRestaurant.processLog(tempPath);
		assertNotNull(testRestaurant.getCustomerByIndex(0));
	}
	
	@Test
	public void getCustomerSizeTest() throws CustomerException, PizzaException, LogHandlerException{
		String tempPath = testFile.getPath();
		assertTrue(testRestaurant.processLog(tempPath));
		assertEquals(1,testRestaurant.getNumCustomerOrders());
	}
	
	@Test
	public void totalDeliveryDistanceTest() throws CustomerException, PizzaException, LogHandlerException{
		String tempPath = testFile.getPath();
		testRestaurant.processLog(tempPath);
		assertEquals(10,testRestaurant.getTotalDeliveryDistance(),0);
	}
	
	@Test
	public void resetCustomerDetailsTest() throws CustomerException, PizzaException, LogHandlerException{
		String tempPath = testFile.getPath();
		testRestaurant.processLog(tempPath);
		testRestaurant.resetDetails();
		assertEquals(0,testRestaurant.getNumCustomerOrders());
	}
	
	@Test (expected = LogHandlerException.class)
	public void processInvalidDetailsLogTest() throws CustomerException, PizzaException, LogHandlerException{
		String tempPath = emptyTestFile.getPath();
		assertTrue(testRestaurant.processLog(tempPath));
	}
	
	@Test (expected = LogHandlerException.class)
	public void processNullLogTest() throws CustomerException, PizzaException, LogHandlerException{
		assertTrue(testRestaurant.processLog(nullLogString));
	}
	
	@Test (expected = CustomerException.class)
	public void customerNegativeIndexTest() throws CustomerException{
		testCustomer = testRestaurant.getCustomerByIndex(-1);
		
	}
	
	@Test (expected = CustomerException.class)
	public void customerBoundaryIndexTest() throws CustomerException{
		testCustomer = testRestaurant.getCustomerByIndex(testRestaurant.getNumCustomerOrders());
		
	}
	
	@Test (expected = CustomerException.class)
	public void customerBoundaryBreakIndexTest() throws CustomerException{
		testCustomer = testRestaurant.getCustomerByIndex(testRestaurant.getNumCustomerOrders()+1);
		
	}

}
