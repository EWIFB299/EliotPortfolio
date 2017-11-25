package asgn2Customers;

import asgn2Exceptions.CustomerException;

/** An abstract class to represent a customer at the Pizza Palace restaurant.
 *  The Customer class is used as a base class of PickUpCustomer, 
 *  DriverDeliveryCustomer and DroneDeliverCustomer. Each of these subclasses overwrites
 *  the abstract method getDeliveryDistance. A description of the class's
 * fields and their constraints is provided in Section 5.2 of the Assignment Specification.  
 * 
 * @author Thiline Widanagamage N9185691
*/
public abstract class Customer {


	/**
	 *  This class represents a customer of the Pizza Palace restaurant.  A detailed description of the class's fields
	 *  and parameters is provided in the Assignment Specification, in particular in Section 5.2. 
	 *  A CustomerException is thrown if the any of the constraints listed in Section 5.2 of the Assignment Specification
	 *  are violated. 
	 *  
  	 * <P> PRE: True
  	 * <P> POST: All field values are set
  	 * 
	 * @param name - The Customer's name 
	 * @param mobileNumber - The customer mobile number
	 * @param customerLocationX - The customer x location relative to the Pizza Palace Restaurant measured in units of 'blocks' 
	 * @param customerLocationY - The customer y location relative to the Pizza Palace Restaurant measured in units of 'blocks' 
	 * @param type - A human understandable description of this Customer type
	 * @throws CustomerException if supplied parameters are invalid 
	 * 
	 */
	
	private String customerName;
	private String customerMobileNumber;
	private String customerType;
	private int customerLocationX;
	private int customerLocationY;
	private int maxLocationXDistance = 10;
	private int maxLocationYDistance = 10;
	private int invalidDeliveryDistance = 0;
	private final int maxNameLength = 20;
	private final int minNameLength = 1;
	private final int mobileNumberLength = 10;
	private final String mobileNumberPrefix = "0";
	protected final int restaurantPositionX = 0;
	protected final int restaurantPositionY = 0;

	
	
	public Customer(String name, String mobileNumber, int locationX, int locationY, String type) throws CustomerException{
		validateCustomerName(name);
		validateCustomerMobileNumber(mobileNumber);
		customerType = type;
		validateDeliveryDistance(locationX, locationY);
		customerName = name;
		customerMobileNumber = mobileNumber;
		customerLocationX = locationX;
		customerLocationY = locationY;
		
	}
	
	/**
	 * Returns the Customer's name.
	 * @return The Customer's name.
	 */
	public final String getName() {
		return customerName;
	}
	
	/**
	 * Returns the Customer's mobile number.
	 * @return The Customer's mobile number.
	 */
	public final String getMobileNumber() {
		return customerMobileNumber;
	}

	/**
	 * Returns a human understandable description of the Customer's type. 
	 * The valid alternatives are listed in Section 5.2 of the Assignment Specification. 
	 * @return A human understandable description of the Customer's type.
	 */
	public final String getCustomerType() {
		return customerType;
	}
	
	/**
	 * Returns the Customer's X location which is the number of blocks East or West 
	 * that the Customer is located relative to the Pizza Palace restaurant. 
	 * @return The Customer's X location
	 */
	public final int getLocationX() {
		return customerLocationX;
	}

	/**
	 * Returns the Customer's Y location which is the number of blocks North or South 
	 * that the Customer is located relative to the Pizza Palace restaurant. 
	 * @return The Customer's Y location
	 */
	public final int getLocationY() {
		return customerLocationY;
	}

	/**
	 * An abstract method that returns the distance between the Customer and 
	 * the restaurant depending on the mode of delivery. 
	 * @return The distance between the restaurant and the Customer depending on the mode of delivery.
	 */
	public abstract double getDeliveryDistance();
	

	/**
	 * Compares *this* Customer object with an instance of an *other* Customer object and returns true if  
	 * if the two objects are equivalent, that is, if the values exposed by public methods are equal.
	 *  You do not need to test this method.
	 * 
	 * @return true if *this* Customer object and the *other* Customer object have the same values returned for 	
	 * getName(),getMobileNumber(),getLocationX(),getLocationY(),getCustomerType().
	 */
	@Override
	public boolean equals(Object other){
		Customer otherCustomer = (Customer) other;

		return ( (this.getName().equals(otherCustomer.getName()))  &&
			(this.getMobileNumber().equals(otherCustomer.getMobileNumber())) && 
			(this.getLocationX() == otherCustomer.getLocationX()) && 
			(this.getLocationY() == otherCustomer.getLocationY()) && 
			(this.getCustomerType().equals(otherCustomer.getCustomerType())) );			
	}
	
	//Validates Customer Name
	private void validateCustomerName(String name) throws CustomerException {
		
		if (name.trim().isEmpty()) {
			throw new CustomerException();
		}
		
		if (name.length() > maxNameLength) {
			throw new CustomerException();	
		}
	
	}
	
	//Validates Customer Mobile Number
	private void validateCustomerMobileNumber(String mobileNumber) throws CustomerException {
		if (mobileNumber.length() != mobileNumberLength) {
			throw new CustomerException();
		}
		
		if (!mobileNumber.startsWith(mobileNumberPrefix)) {
			throw new CustomerException();
		}
		
	}
	
	//Validates Delivery Distance 
	private void validateDeliveryDistance(int locationX, int locationY) throws CustomerException {
		if (locationX > maxLocationXDistance) {
			throw new CustomerException();
		}
		
		if (locationY > maxLocationYDistance) {
			throw new CustomerException();
		}
		
		if (locationX < -maxLocationXDistance) {
			throw new CustomerException();
		}
		
		if (locationY < -maxLocationYDistance) {
			throw new CustomerException();
		}
		
		if (itsADelivery()) {
			if (locationX == invalidDeliveryDistance && locationY == invalidDeliveryDistance) {
				throw new CustomerException();
			}		
		}
	}
	
	//Checks if delivery type is Driver or Drone
	private boolean itsADelivery() {
		if (this instanceof DriverDeliveryCustomer) return true;
		if (this instanceof DroneDeliveryCustomer) return true;
		return false;
	}
	

}
