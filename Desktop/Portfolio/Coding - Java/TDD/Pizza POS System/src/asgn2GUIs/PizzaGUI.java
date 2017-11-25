package asgn2GUIs;

import java.awt.event.ActionEvent;


import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.text.DecimalFormat;

import javax.swing.text.DefaultCaret;

import asgn2Customers.Customer;
import asgn2Exceptions.CustomerException;
import asgn2Exceptions.LogHandlerException;
import asgn2Exceptions.PizzaException;
import asgn2Pizzas.Pizza;
import asgn2Restaurant.PizzaRestaurant;

import java.awt.*;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;


/**
 * This class is the graphical user interface for the rest of the system. 
 * Currently it is a ‘dummy’ class which extends JFrame and implements Runnable and ActionLister. 
 * It should contain an instance of an asgn2Restaurant.PizzaRestaurant object which you can use to 
 * interact with the rest of the system. You may choose to implement this class as you like, including changing 
 * its class signature – as long as it  maintains its core responsibility of acting as a GUI for the rest of the system. 
 * You can also use this class and asgn2Wizards.PizzaWizard to test your system as a whole
 * 
 * 
 * @author Eliot Wilson n9175504 and Thiline Widanagamage N9185691
 *
 */
public class PizzaGUI extends javax.swing.JFrame implements Runnable, ActionListener {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -1658564567605117128L;
	private JPanel mainDisplay, functionPanel, alertPanel;
	private JLabel costLabel, distanceLabel, alertLabel;
	private JFileChooser fileSelect;
	private JButton load, display, calculate, reset;
	private JTable displayTable;
	private DefaultTableModel model;
	private JScrollPane viewBox;
	private DecimalFormat stringConvert = new DecimalFormat("0.00");
	
	public static final int WIDTH = 1100; 
	public static final int HEIGHT = 500;
	private PizzaRestaurant restaurant;
	private double totalCost = 0;
	private double totalDistance = 0;
	private File selectedFile;
	private String fileName;
	
	/**
	 * Creates a new Pizza GUI with the specified title 
	 * @param title - The title for the supertype JFrame
	 */
	public PizzaGUI(String title) {
		super(title);
		restaurant = new PizzaRestaurant();
		fileSelect = new JFileChooser("./logs");
		model = new DefaultTableModel(new Object[]{"Pizza Type","Pizza Quantity","Order Price","Order Cost","Order Profit","Name","Mobile","Delivery Type",
													"Location X, Y","Delivery Distance"},0);
		this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
	
	private void createGUI(){
		setSize(WIDTH, HEIGHT);
		setLayout(new BorderLayout());
		mainDisplay = createPanel(Color.WHITE);
		functionPanel = createPanel(Color.LIGHT_GRAY);
		costLabel = createLabel("Total Profit: " + stringConvert.format(totalCost));
		distanceLabel = createLabel("Total Distance: "  + stringConvert.format(totalDistance));
		alertLabel = createLabel("Load a File");
		alertPanel = createColourPanel();
		load = createButton("Place Order");
		display = createButton("Display Info");
		calculate = createButton("Calcualte");
		reset = createButton("Reset GUI");
		mainDisplay.setLayout(new BorderLayout());
		displayTable = createTable();
		viewBox = createPane(displayTable);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.getContentPane().add(mainDisplay,BorderLayout.CENTER);
		mainDisplay.add(viewBox,BorderLayout.CENTER);
		this.getContentPane().add(displayTable.getTableHeader(),BorderLayout.NORTH);
		this.getContentPane().add(functionPanel,BorderLayout.SOUTH);
		this.getContentPane().add(alertPanel,BorderLayout.NORTH);
		alertPanel.add(alertLabel);
		layoutFunctionPanel();
		repaint();
		this.setVisible(true);
		display.setEnabled(false);
		calculate.setEnabled(false);
		reset.setEnabled(false);
	}
	
	private JTable createTable() {
		JTable tempTable = new JTable();
		tempTable.setModel(model);
		tempTable.setSize(WIDTH, HEIGHT);
		tempTable.getTableHeader().setReorderingAllowed(false);
		return tempTable;
	}
	
	private JButton createButton(String description) {
		JButton tempButton = new JButton();
		tempButton.setText(description);
		tempButton.addActionListener(this);
		return tempButton;
	}

	private JLabel createLabel(String description) {
		JLabel tempLabel=  new JLabel(description);
		return tempLabel; 
	}
	
	private JPanel createColourPanel() {
		JPanel tempPanel=  new JPanel();
		tempPanel.setBackground(Color.CYAN);
		return tempPanel;
	}

	private JPanel createPanel(Color c){
		JPanel tempPanel=  new JPanel();
		tempPanel.setBackground(c);
		return tempPanel; 

	}
	
	private JScrollPane createPane(JComponent component){
		JScrollPane tempPane = new JScrollPane(component);
		tempPane.setSize(WIDTH, HEIGHT*2);
		tempPane.setVisible(true);
		tempPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		return tempPane;
	}
	
	private void layoutFunctionPanel(){
		GridBagLayout layout = new GridBagLayout();
		functionPanel.setLayout(layout);	
		GridBagConstraints constraints = new GridBagConstraints();
		constraints.fill = GridBagConstraints.NONE;
		constraints.anchor = GridBagConstraints.CENTER;
		constraints.weightx = 200;
		constraints.weighty = 200;
		addToPanel(functionPanel, load,constraints,0,0,2,1);
		addToPanel(functionPanel, display,constraints,0,2,2,1); 
		addToPanel(functionPanel, calculate,constraints,4,2,2,1);
		addToPanel(functionPanel, reset,constraints,4,0,2,1); 
		addToPanel(functionPanel, distanceLabel,constraints,2,0,2,1); 
		addToPanel(functionPanel, costLabel,constraints,2,2,2,1); 
		
	}
	
	private void addToPanel(JPanel jp,Component c, GridBagConstraints constraints,int x, int y, int w, int h) { 
		constraints.gridx = x; 
		constraints.gridy = y; 
		constraints.gridwidth = w; 
		constraints.gridheight = h; 
		jp.add(c, constraints); 
	}
	
	
	@Override
	public void run() {
		createGUI();
	}


	@Override
	public void actionPerformed(ActionEvent evt) {
		Object src=evt.getSource(); 
		if (src==load) { 
			int returnValue = fileSelect.showOpenDialog(null);
	        if (returnValue == JFileChooser.APPROVE_OPTION) {
	        	selectedFile = fileSelect.getSelectedFile();
	        	fileName = selectedFile.getPath();
	        }
	        try {
				restaurant.processLog(fileName);
				alertPanel.setBackground(Color.GREEN);
				alertLabel.setText("File has been loaded. Display info?");
			} catch (CustomerException | PizzaException | LogHandlerException e) {
				e.printStackTrace();
				alertPanel.setBackground(Color.RED);
				alertLabel.setText("Error Detected: " + e.getMessage() +". Please Select a Valid Log to Continue");
				return;
			}
	        display.setEnabled(true);
		} 
		if (src==display) { 
			load.setEnabled(false);
			calculate.setEnabled(true);
			fillTable();
			display.setEnabled(false);
			alertLabel.setText("Info Displayed. Calculate the math?");
		}
		if (src==calculate) { 
			reset.setEnabled(true);
			calculate.setEnabled(false);
			totalCost = restaurant.getTotalProfit();
			totalDistance = restaurant.getTotalDeliveryDistance();
			costLabel.setText("Total Profit: " + stringConvert.format(totalCost));
			distanceLabel.setText("Total Distance: " + stringConvert.format(totalDistance));
			alertLabel.setText("Price and Distance Calulated. Ready for a new order?");
		}
		if (src==reset) { 
			reset.setEnabled(false);
			model.setRowCount(0);
			restaurant.resetDetails();
			totalCost = 0;
			totalDistance = 0;
			load.setEnabled(true);
			costLabel.setText("Total Profit: " + stringConvert.format(totalCost));
			distanceLabel.setText("Total Distance: " + stringConvert.format(totalDistance));
			alertPanel.setBackground(Color.CYAN);
			alertLabel.setText("Load a File");
		}
		
	}
	
	
	private void fillTable(){
		int numOrders, tempQuantity, locationX, locationY;
		double orderPrice, orderProfit, orderCost, customerDistance;
		String pizzaType, customerName, mobileNumber, deliveryType;
		Pizza testPizza;
		Customer testCustomer;
		numOrders = restaurant.getNumPizzaOrders();			
		for (int i = 0; i < numOrders; i++){
			try {
				testCustomer= restaurant.getCustomerByIndex(i);
				testPizza= restaurant.getPizzaByIndex(i);
				tempQuantity = testPizza.getQuantity();
				pizzaType = testPizza.getPizzaType();
				orderCost = testPizza.getOrderCost();
				orderPrice = testPizza.getOrderPrice();
				orderProfit = testPizza.getOrderProfit();
				if(pizzaType.equals("PZM")){
					pizzaType = "Margherita";
				}
				else if (pizzaType.equals("PZB")){
					pizzaType = "Vegetarian";
				}
				else if (pizzaType.equals("PZL")){
					pizzaType = "Meat Lovers";
				}
				locationX = testCustomer.getLocationX();
				locationY = testCustomer.getLocationY();
				mobileNumber = testCustomer.getMobileNumber();
				deliveryType = testCustomer.getCustomerType();
				customerName = testCustomer.getName();
				customerDistance = testCustomer.getDeliveryDistance();
				model.addRow(new Object[] {pizzaType, Integer.toString(tempQuantity),stringConvert.format(orderPrice),stringConvert.format(orderCost),
						stringConvert.format(orderProfit),customerName,mobileNumber,deliveryType,Integer.toString(locationX) +", " + Integer.toString(locationY),stringConvert.format(customerDistance)});
			} catch (PizzaException | CustomerException e) {
				e.printStackTrace();
			}
		}
	}

}
