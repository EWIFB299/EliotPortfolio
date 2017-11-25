package asgn2Tests;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import asgn2Customers.Customer;
import asgn2Customers.DriverDeliveryCustomer;
import asgn2Customers.DroneDeliveryCustomer;
import asgn2Customers.PickUpCustomer;
import asgn2Exceptions.CustomerException;

/**
 * A class that tests the that tests the asgn2Customers.PickUpCustomer, asgn2Customers.DriverDeliveryCustomer,
 * asgn2Customers.DroneDeliveryCustomer classes. Note that an instance of asgn2Customers.DriverDeliveryCustomer 
 * should be used to test the functionality of the  asgn2Customers.Customer abstract class. 
 * 
 * @author Eliot Wilson n9175504
 * 
 *
 */
public class CustomerTests {
	
	private int testXLocation = 4;
	private int testYLocation = 3;
	private int testNegativeXLocation = -4;
	private int testNegativeYLocation = -3;
	private int invalidXLocation = 11;
	private int invalidYLocation = 11;
	private double testEuclidianDeliveryDistance= 5;
	private double testManhattanDeliveryDistance= 7;
	private String customerName = "Tester";
	private String longName = "abcdefghijklmnopqrstuvwxyz";
	private String mobileNumber = "0123456789";
	private String shortNumber = "0123";
	private String invalidNumber = "1234567890";
	Customer testDroneCustomer;
	Customer testDriverCustomer;
	Customer testPickUpCustomer;
	Customer exceptionCustomer;
	Customer testCustomer;
	
	@Before @Test
	public void setUpDriverCustomer() throws CustomerException{
		testDriverCustomer = new DriverDeliveryCustomer(customerName, mobileNumber, testXLocation, testYLocation);
	}
	
	@Before @Test
	public void setUpPickUpCustomer() throws CustomerException{
		testPickUpCustomer = new PickUpCustomer(customerName, mobileNumber, 0, 0);
	}
	
	@Before @Test
	public void setUpDroneCustomer() throws CustomerException{
		testDroneCustomer = new DroneDeliveryCustomer(customerName, mobileNumber, testXLocation, testYLocation);
	}
	
	@Test
	public void getNameCustomer(){
		assertEquals(testDroneCustomer.getName(), customerName);
	}
	
	@Test
	public void getMobileCustomer(){
		assertEquals(testDroneCustomer.getMobileNumber(), mobileNumber);
	}
	
	@Test
	public void getLocationXCustomer(){
		assertEquals(testDroneCustomer.getLocationX(), testXLocation);
	}
	
	@Test
	public void getLocationYCustomer(){
		assertEquals(testDroneCustomer.getLocationY(), testYLocation);
	}
	
	@Test
	public void getDroneTypeCustomer(){
		assertEquals(testDroneCustomer.getCustomerType(), "Drone Delivery");
	}
	
	@Test
	public void getDriverTypeCustomer(){
		assertEquals(testDriverCustomer.getCustomerType(), "Driver Delivery");
	}
	
	@Test
	public void getPickUpTypeCustomer(){
		assertEquals(testPickUpCustomer.getCustomerType(), "Pick Up");
	}
	
	@Test
	public void getPickUpDistanceCustomer(){
		double testDistance = testPickUpCustomer.getDeliveryDistance();
		assertEquals(testDistance, 0,0);
	}
	
	@Test
	public void getDroneEuclidianDistanceCustomer(){
		double testDistance = testDroneCustomer.getDeliveryDistance();
		assertEquals(testDistance, testEuclidianDeliveryDistance,0);
		
	}
	
	@Test
	public void getDriverManhattanDistanceCustomer(){
		double testDistance = testDriverCustomer.getDeliveryDistance();
		assertEquals(testDistance, testManhattanDeliveryDistance,0);
	}
	
	@Test
	public void getDroneNegativeEuclidianDistanceCustomer() throws CustomerException{
		testCustomer = new DroneDeliveryCustomer(customerName, mobileNumber, testNegativeXLocation, testNegativeYLocation);
		double testDistance = testCustomer.getDeliveryDistance();
		assertEquals(testDistance, testEuclidianDeliveryDistance,0);
		
	}
	
	@Test
	public void getDriverNegativeEuclidianDistanceCustomer() throws CustomerException{
		testCustomer = new DriverDeliveryCustomer(customerName, mobileNumber, testNegativeXLocation, testNegativeYLocation);
		double testDistance = testCustomer.getDeliveryDistance();
		assertEquals(testDistance, testManhattanDeliveryDistance,0);
	}
	
	@Test (expected = CustomerException.class)
	public void blankNameCustomer() throws CustomerException{
		exceptionCustomer = new DriverDeliveryCustomer("     ", mobileNumber, testXLocation, testYLocation);
	}
	
	@Test (expected = CustomerException.class)
	public void longNameCustomer() throws CustomerException{
		exceptionCustomer = new DriverDeliveryCustomer(longName, mobileNumber, testXLocation, testYLocation);
	}
	
	@Test (expected = CustomerException.class)
	public void shortMobileCustomer() throws CustomerException{
		exceptionCustomer = new DriverDeliveryCustomer(customerName, shortNumber, testXLocation, testYLocation);
	}
	
	@Test (expected = CustomerException.class)
	public void invalidMobileCustomer() throws CustomerException{
		exceptionCustomer = new DriverDeliveryCustomer(customerName, invalidNumber, testXLocation, testYLocation);
	}
	
	@Test (expected = CustomerException.class)
	public void invalidDeliveryDistance() throws CustomerException{
		exceptionCustomer = new DriverDeliveryCustomer(customerName, mobileNumber, 0, 0);
	}
	
	@Test (expected = CustomerException.class)
	public void invalidDroneDistance() throws CustomerException{
		exceptionCustomer = new DroneDeliveryCustomer(customerName, mobileNumber, 0, 0);
	}
	
	@Test (expected = CustomerException.class)
	public void boundaryXDeliveryDistance() throws CustomerException{
		exceptionCustomer = new DriverDeliveryCustomer(customerName, mobileNumber, invalidXLocation, testYLocation);
	}
	
	@Test (expected = CustomerException.class)
	public void boundaryYDeliveryDistance() throws CustomerException{
		exceptionCustomer = new DriverDeliveryCustomer(customerName, mobileNumber, testXLocation, invalidYLocation);
	}
	
	@Test (expected = CustomerException.class)
	public void invalidPickUpLocationCustomer() throws CustomerException{
		exceptionCustomer = new PickUpCustomer(customerName, invalidNumber, testXLocation, testYLocation);
	}
	
	
	
}
