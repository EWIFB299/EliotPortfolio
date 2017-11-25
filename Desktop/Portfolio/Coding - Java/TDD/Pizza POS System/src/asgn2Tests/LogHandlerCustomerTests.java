package asgn2Tests;

import static org.junit.Assert.*;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import org.junit.Before;
import org.junit.Test;

import asgn2Customers.Customer;
import asgn2Customers.CustomerFactory;
import asgn2Customers.DriverDeliveryCustomer;
import asgn2Exceptions.CustomerException;
import asgn2Exceptions.LogHandlerException;
import asgn2Restaurant.LogHandler;

/**
 * A class that tests the methods relating to the creation of Customer objects in the asgn2Restaurant.LogHander class.
 *
 * @author Eliot Wilson n9175504
 */
public class LogHandlerCustomerTests {

	private String testString =  "19:00:00,19:20:00,Test Test,0123456789,DVC,5,5,PZV,1";
	private String invalidDetailString =  "19:00:00,19:20:00,Test Test,12345678910,AAA,10,10,PZV,1";
	private String invalidString = " , , , , , , , , ";
	private String incompleteDetails =  "19:00:00,19:20:00, , , ,10,10,PZV,1";
	private String shortDetails =  "Test Test,0123456789,DVC,5,5";
	private String invalidPath = "InvalidPath";
	private Customer testCustomer;
	private ArrayList<Customer> testList = new ArrayList<Customer>();
	private File testFile, emptyTestFile, invalidTestFile;
	
	@Before //Not a Test. Creates temporary File with the testString.
	public void setUpTestFile(){
		try {
			testFile = File.createTempFile("tempFile", ".txt");
			BufferedWriter writer = new BufferedWriter(new FileWriter(testFile));
			writer.write(testString);
			writer.close();
    	    emptyTestFile = File.createTempFile("invalidTempFile", ".txt");
			BufferedWriter emptyWriter = new BufferedWriter(new FileWriter(emptyTestFile));
			emptyWriter.write(invalidString);
			emptyWriter.close();
    	    invalidTestFile = File.createTempFile("invalidDetailsFile", ".txt");
			BufferedWriter invalidWriter = new BufferedWriter(new FileWriter(invalidTestFile));
			invalidWriter.write(invalidDetailString);
			invalidWriter.close();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Test
	public void createCustomerTest() throws CustomerException, LogHandlerException{
		testCustomer = LogHandler.createCustomer(testString);
		assertEquals(testCustomer.getName(), "Test Test");
	}
	
	@Test
	public void populateDataSetTest() throws CustomerException, LogHandlerException{
		String tempPath = testFile.getPath();
		testList = LogHandler.populateCustomerDataset(tempPath);
		assertEquals(testList.get(0).getName(), "Test Test");
	}
	
	@Test (expected = CustomerException.class)
	public void incompleteCustomerDetailsDataSetTest() throws CustomerException, LogHandlerException{
		testCustomer = LogHandler.createCustomer(incompleteDetails);
	}
	
	@Test (expected = CustomerException.class)
	public void incorrectCustomerDetialsDataSetTest() throws CustomerException, LogHandlerException{
		String tempPath = invalidTestFile.getPath();
		testList = LogHandler.populateCustomerDataset(tempPath);
	}
	
	@Test (expected = LogHandlerException.class)
	public void customerOnlyDetailsDataSetTest() throws CustomerException, LogHandlerException{
		testCustomer = LogHandler.createCustomer(shortDetails);
	}
	
	@Test (expected = LogHandlerException.class)
	public void emptyStringPopulateDataSetTest() throws CustomerException, LogHandlerException{
		String tempPath = emptyTestFile.getPath();
		testList = LogHandler.populateCustomerDataset(tempPath);
	}
	
	@Test (expected = LogHandlerException.class)
	public void populateInvalidPathDataSetTest() throws CustomerException, LogHandlerException{
		testList = LogHandler.populateCustomerDataset(invalidPath);
	}
	
	@Test (expected = LogHandlerException.class)
	public void createInvalidStringCustomerTest() throws CustomerException, LogHandlerException{
		testCustomer = LogHandler.createCustomer(invalidString);
	}
	
}
