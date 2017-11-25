package asgn2Restaurant;


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.time.LocalTime;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import asgn2Customers.Customer;
import asgn2Customers.CustomerFactory;
import asgn2Exceptions.CustomerException;
import asgn2Exceptions.LogHandlerException;
import asgn2Exceptions.PizzaException;
import asgn2Pizzas.Pizza;
import asgn2Pizzas.PizzaFactory;

/**
 *
 * A class that contains methods that use the information in the log file to return Pizza 
 * and Customer object - either as an individual Pizza/Customer object or as an
 * ArrayList of Pizza/Customer objects.
 * 
 * @author Eliot Wilson n9175504 and Thiline Widanagamage N9185691
 *
 */
public class LogHandler {
	
	private static int orderTimePos = 0;
	private static int deliveryTimePos = 1;
	private static int customerNamePos = 2;
	private static int mobileNumberPos = 3;
	private static int customerTypePos = 4;
	private static int customerXLocPos = 5;
	private static int customerYLocPos = 6;
	private static int pizzaTypePos = 7;
	private static int pizzaQuantityPos = 8;
	
	/**
	 * Returns an ArrayList of Customer objects from the information contained in the log file ordered as they appear in the log file.
	 * @param filename The file name of the log file
	 * @return an ArrayList of Customer objects from the information contained in the log file ordered as they appear in the log file. 
	 * @throws CustomerException If the log file contains semantic errors leading that violate the customer constraints listed in Section 5.3 of the Assignment Specification or contain an invalid customer code (passed by another class).
	 * @throws LogHandlerException If there was a problem with the log file not related to the semantic errors above
	 * 
	 */
	public static ArrayList<Customer> populateCustomerDataset(String filename) throws CustomerException, LogHandlerException{
		ArrayList <Customer> tempCustomerList = new ArrayList<Customer>();
		
		try{
			BufferedReader buffer = new BufferedReader(new FileReader(filename));
			String nextLine;
			while ((nextLine = buffer.readLine()) != null) {
				tempCustomerList.add(createCustomer(nextLine));
			}
		} catch(IOException e){
			throw new LogHandlerException("IO: " + e.getMessage());
		} catch(CustomerException e){
			throw new CustomerException("Invalid Customer Options");
		}			
	
		return tempCustomerList;
	}		

	/**
	 * Returns an ArrayList of Pizza objects from the information contained in the log file ordered as they appear in the log file. .
	 * @param filename The file name of the log file
	 * @return an ArrayList of Pizza objects from the information contained in the log file ordered as they appear in the log file. .
	 * @throws PizzaException If the log file contains semantic errors leading that violate the pizza constraints listed in Section 5.3 of the Assignment Specification or contain an invalid pizza code (passed by another class).
	 * @throws LogHandlerException If there was a problem with the log file not related to the semantic errors above
	 * 
	 */
	public static ArrayList<Pizza> populatePizzaDataset(String filename) throws PizzaException, LogHandlerException{
		ArrayList <Pizza> templist = new ArrayList<Pizza>();
		try{
		BufferedReader buffer = new BufferedReader(new FileReader(filename));
		String nextLine;
		while ((nextLine = buffer.readLine()) != null) {
			templist.add(createPizza(nextLine));
			}
		}catch(IOException e){
			throw new LogHandlerException("IO: " + e.getMessage());
		}catch(PizzaException e){
			throw new PizzaException("Invalid Pizza Options" + e.getMessage());
		}catch(NullPointerException e) {
			throw new LogHandlerException("Filename cannot be null" + e.getMessage());
		}
		return templist;
		
	}		

	
	/**
	 * Creates a Customer object by parsing the  information contained in a single line of the log file. The format of 
	 * each line is outlined in Section 5.3 of the Assignment Specification.  
	 * @param line - A line from the log file
	 * @return- A Customer object containing the information from the line in the log file
	 * @throws CustomerException - If the log file contains semantic errors leading that violate the customer constraints listed in Section 5.3 of the Assignment Specification or contain an invalid customer code (passed by another class).
	 * @throws LogHandlerException - If there was a problem parsing the line from the log file.
	 */
	public static Customer createCustomer(String line) throws CustomerException, LogHandlerException{
		Customer tempCustomer;
		try {
			String[] customerArray = line.split(",");
			if (customerArray.length != 9) throw new LogHandlerException("Invalid Field Length");
			String customerName = customerArray[customerNamePos];
			String customerMobileNumber = customerArray[mobileNumberPos];
			String customerType = customerArray[customerTypePos];
			int locationX = Integer.parseInt(customerArray[customerXLocPos]);
			int locationY = Integer.parseInt(customerArray[customerYLocPos]);
			tempCustomer = (CustomerFactory.getCustomer(customerType, customerName, customerMobileNumber, locationX, locationY)); 
		} catch (CustomerException e) {
			throw new CustomerException("Invalid Customer Options");
		} catch (NumberFormatException | DateTimeParseException |ArrayIndexOutOfBoundsException e) {
			throw new LogHandlerException("Invalid Log");
		}
		return tempCustomer;
	}
	
	/**
	 * Creates a Pizza object by parsing the information contained in a single line of the log file. The format of 
	 * each line is outlined in Section 5.3 of the Assignment Specification.  
	 * @param line - A line from the log file
	 * @return- A Pizza object containing the information from the line in the log file
	 * @throws PizzaException If the log file contains semantic errors leading that violate the pizza constraints listed in Section 5.3 of the Assignment Specification or contain an invalid pizza code (passed by another class).
	 * @throws LogHandlerException - If there was a problem parsing the line from the log file.
	 */
	public static Pizza createPizza(String line) throws PizzaException, LogHandlerException{
		Pizza tempPizza;
		try{
   	    String[] pizzaArray = line.split(",");
   	    LocalTime orderTime = LocalTime.parse((pizzaArray[orderTimePos]));
   	    LocalTime deliveryTime = LocalTime.parse((pizzaArray[deliveryTimePos]));
   	    String pizzaType = pizzaArray[pizzaTypePos];
   	    int pizzaQuantity = Integer.parseInt(pizzaArray[pizzaQuantityPos]);
   	    tempPizza = (PizzaFactory.getPizza(pizzaType, pizzaQuantity, orderTime, deliveryTime));	
   	    } catch(PizzaException e){
   	    	throw new PizzaException("Invalid Pizza Options");
   	    }catch(NumberFormatException | DateTimeParseException |ArrayIndexOutOfBoundsException e){
   	    	throw new LogHandlerException("Invalid Log");
   	    }
   	    return tempPizza;
	}

}