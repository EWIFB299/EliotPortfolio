package asgn2Tests;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import asgn2Customers.Customer;
import asgn2Customers.CustomerFactory;
import asgn2Exceptions.CustomerException;

/**
 * A class the that tests the asgn2Customers.CustomerFactory class.
 * 
 * @author Eliot Wilson n9175504
 *
 */
public class CustomerFactoryTests {
	CustomerFactory testFactory;
	private String testName = "Tester";
	private String testMobileNumber = "0123456789";
	private String droneCustomerCode = "DNC";
	private String driverCustomerCode = "DVC";
	private String pickUpCustomerCode = "PUC";
	private String invalidCustomerCode = "AAA";
	private int testXLocation = 5;
	private int testYLocation = 5;
	Customer testDroneCustomer;
	Customer testDriverCustomer;
	Customer testPickUpCustomer;
	Customer exceptionCustomer;
	
	
	
	@Before @Test
	public void setUpCustomerFactoryTest(){
		testFactory = new CustomerFactory();
		
	}
	
	@Test
	public void getDroneCustomerTest() throws CustomerException{
		testDroneCustomer = CustomerFactory.getCustomer(droneCustomerCode, testName, testMobileNumber, testXLocation,  testYLocation);
		assertEquals("Drone Delivery", testDroneCustomer.getCustomerType());
		
	}
	
	@Test
	public void getDeliveryCustomerTest() throws CustomerException{
		testDriverCustomer = CustomerFactory.getCustomer(driverCustomerCode, testName, testMobileNumber, testXLocation,  testYLocation);
		assertEquals("Driver Delivery", testDriverCustomer.getCustomerType());
		
	}
	
	@Test
	public void getPickUpCustomerTest() throws CustomerException{
		testPickUpCustomer = CustomerFactory.getCustomer(pickUpCustomerCode, testName, testMobileNumber, testXLocation,  testYLocation);
		assertEquals("Pick Up", testPickUpCustomer.getCustomerType());
		
	}
	
	@Test (expected = CustomerException.class)
	public void getExceptionCustomerTest() throws CustomerException{
		exceptionCustomer = CustomerFactory.getCustomer(invalidCustomerCode, testName, testMobileNumber, testXLocation,  testYLocation);
		
	}
	
}
