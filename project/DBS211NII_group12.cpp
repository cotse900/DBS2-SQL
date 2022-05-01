// DBS211 Project – Milestone 3
// Group 12
// Members:
// Ryan Locke (ID: 034748129) - table CUSTOMER (options 7-12)
// 
// Chung On Tse (ID: 154928188) - table CARD (options 13-18)
// 
// Stephen Suresh (ID: 117916213) - table PAYMENT (options 19-24)
// Class: DBS211 NII

#include <iostream>
#include <iomanip>
#include <occi.h>
#include <string>
#include <cstring>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

struct Employee
{
	int employeeNumber;
	string lastName;
	string firstName;
	string email;
	string extension;
	string jobTitle;
	string city;
	int reportsTo;
	int officeCode;
	string phone;
};

//Ryan Locke 034748129
struct Customer
{
	int custId;
	string custName;
	string custEmail;
	string custPhoneNum;
	string custAddress;
};
//Chungon Tse 154928188
struct Card
{
	string card_num;
	string card_type;
	string card_exp;
	int cust_id;
	double interest_rate;
};
//Stephen Suresh 117916213
struct Payment
{
	int paymentReceipt; //pk
	int payerID; //fk
	int receiverID;
	string description;
	string payTime;
	double payAmount;
};

//Stephen Suresh 117916213
//don't even need this since not dealing with this table
struct Account
{
	int accountID;
	int custID;
	string accountType;
	double balance;
	double interest;
};

string commaspace = ", ";
int menu(void);
//HR menu funcs
int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp);
void displayEmployee(Connection* conn, struct Employee emp);
void displayAllEmployees(Connection* conn);
void getEmployee(Connection* conn, struct Employee* emp);
void insertEmployee(Connection* conn, struct Employee emp);
void updateEmployee(Connection* conn, int employeeNumber);
void deleteEmployee(Connection* conn, int employeeNumber);
int findOffice(Connection* conn, int officecode);
//banking app funcs

//Ryan Locke 034748129
int findCustomer(Connection* conn, int cust_id, Customer* cust);
void displayCustomer(Connection* conn, struct Customer cust);
void displayAllCustomers(Connection* conn);
void getCustomer(Connection* conn, struct Customer* cust);
void insertCustomer(Connection* conn, struct Customer cust);
void deleteCustomer(Connection* conn, int custId);
void updateCustomer(Connection* conn, int  custId);
//Chungon Tse 154928188
int findCard(Connection* conn, string card_num, Card* crd);
void displayCard(Connection* conn, struct Card crd);
void displayAllCards(Connection* conn);
void getCard(Connection* conn, struct Card* crd);
void insertCard(Connection* conn, struct Card crd);
void updateCard(Connection* conn, string card_num);
void deleteCard(Connection* conn, string card_num);

//Stephen Suresh 117916213
int findPayment(Connection* conn, int payment_receipt, Payment* pay);
void displayPayment(Connection* conn, struct Payment pay);
void displayAllPayments(Connection* conn);
int findAccount(Connection* conn, int accountID, struct Account* account);//to find the account
int insertPayment(Connection* conn, struct Payment pay);
void updatePayment(Connection* conn, int paymentReceipt, struct Payment* pay);
void deletePayment(Connection* conn, int paymentID);

int main(void)
{
	Environment* env = nullptr;
	Connection* conn = nullptr;
	string str;
	string usr = "";
	string pass = "";
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

	struct Employee emp;
	struct Customer cust;
	struct Card crd;
	struct Payment pay;
	struct Account account;

	try
	{
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);
		cout << "Database Connection is successful!" << endl;
		cout << "Project Milestone 3" << endl;

		struct Employee employee;
		struct Customer customer;
		struct Card crd;
		struct Payment pay;
		bool keepgoing = false;
		bool valid = true;
		int input = 0;
		int num = 0;
		string card_num;
		int custId;
		do
		{
			input = menu();

			switch (input)
			{
			case 1:
				keepgoing = true;
				cout << "Enter Employee Number: ";
				cin >> num;
				if (findEmployee(conn, num, &employee) == 1)
				{
					cout << endl << "Valid Employee" << endl << endl;
				}
				else
				{
					cout << "Employee " << num << " does not exist." << endl << endl;
				}
				break;
			case 2:
				keepgoing = true;
				cout << "Enter Employee Number to display an employee: ";
				cin >> num;
				if (findEmployee(conn, num, &employee) == 1)
				{
					displayEmployee(conn, employee);
				}
				else
				{
					cout << "Employee " << num << " does not exist." << endl << endl;
				}
				break;
			case 3:
				keepgoing = true;
				displayAllEmployees(conn);
				break;
			case 4:
				keepgoing = true;
				getEmployee(conn, &employee);
				insertEmployee(conn, employee);
				break;
			case 5:
				keepgoing = true;
				cout << "Employee Number: ";
				cin >> num;
				updateEmployee(conn, num);
				break;
			case 6:
				keepgoing = true;
				cout << "Employee Number: ";
				cin >> num;
				deleteEmployee(conn, num);
				break;
				//Ryan Locke 034748129
			case 7:
				keepgoing = true;
				cout << "Enter Customer ID: ";
				cin >> num;
				if (findCustomer(conn, num, &cust) == 1)
				{
					cout << endl << "Valid Customer" << endl << endl;
				}
				else
				{
					cout << "Customer " << num << " does not exist." << endl << endl;
				}
				break;
			case 8:
				keepgoing = true;
				cout << "Enter customer ID to display a customer: ";
				cin >> num;
				if (findCustomer(conn, num, &cust) == 1)
				{
					cout << endl << "Valid Customer" << endl;
				}
				else
				{
					cout << "Customer " << num << " does not exist." << endl << endl;
				}
				if (findCustomer(conn, num, &cust) == 1) displayCustomer(conn, cust);
				break;
			case 9:
				keepgoing = true;
				displayAllCustomers(conn);
				break;
			case 10:
				keepgoing = true;
				getCustomer(conn, &cust);
				insertCustomer(conn, cust);
				break;
			case 11:
				keepgoing = true;
				cout << "Enter Customer Number to change the customer phone number: ";
				cin >> num;
				updateCustomer(conn, num);
				break;
			case 12:
				keepgoing = true;
				cout << "Enter Customer Number to delete a customer: ";
				cin >> custId;
				deleteCustomer(conn, custId);
				break;
				//Chungon Tse 154928188 (13-18)
			case 13:
				keepgoing = true;
				cout << "Enter Card Number to find a card: ";
				cin >> card_num;
				if (findCard(conn, card_num, &crd) == 1)
				{
					cout << endl << "Valid Card" << endl << endl;
				}
				else
				{
					cout << "Card numbered " << card_num << " does not exist." << endl << endl;
				}
				break;
			case 14:
				keepgoing = true;
				cout << "Enter Card Number to display a card: ";
				cin >> card_num;
				if (findCard(conn, card_num, &crd) == 1)
				{
					cout << endl << "Valid Card" << endl << endl;
				}
				else
				{
					cout << "Card numbered " << card_num << " does not exist." << endl << endl;
				}
				if (findCard(conn, card_num, &crd) == 1) displayCard(conn, crd);
				break;
			case 15:
				keepgoing = true;
				displayAllCards(conn);
				break;
			case 16:
				keepgoing = true;
				getCard(conn, &crd);
				insertCard(conn, crd);
				break;
			case 17:
				keepgoing = true;
				cout << "Enter Card Number to change the interest rate: ";
				cin >> card_num;
				updateCard(conn, card_num);
				break;
			case 18:
				keepgoing = true;
				cout << "Enter Card Number to delete a card: ";
				cin >> card_num;
				deleteCard(conn, card_num);
				break;
				//Stephen Suresh 117916213
			case 19:
				keepgoing = true;
				cout << "Enter a Payment ID: ";
				cin >> num;
				if (findPayment(conn, num, &pay) == 1)
				{
					cout << endl << "Valid Payment ID" << endl << endl;
				}
				else
				{
					cout << "Payment ID " << num << " does not exist." << endl << endl;
				}
				break;
				//Stephen Suresh 117916213
			case 20: //displayPayment(conn, pay);
				keepgoing = true;
				cout << "Enter a Payment ID to Display a Payment: ";
				cin >> num;
				if (findPayment(conn, num, &pay) == 1)
				{
					cout << endl << "Valid Payment ID" << endl << endl;
				}
				else
				{
					cout << "Payment ID " << num << " does not exist." << endl << endl;
					cin.clear();
					cin.ignore(1000, '\n');
				}
				if (findPayment(conn, num, &pay) == 1) displayPayment(conn, pay);
				break;
				//Stephen Suresh 117916213
			case 21:
				keepgoing = true;
				displayAllPayments(conn);
				break;
			case 22:
				keepgoing = true;
				valid = true;
				do
				{
					cout << "Enter a Payment ID to Insert: ";
					cin >> num;
					cin.clear();
					cin.ignore(100, '\n');
					if (findPayment(conn, num, &pay) == 1)
					{ //check if payment PK already exists
						cout << "This Payment ID Already Exists" << endl;
						valid = false;
					}
					else
					{
						valid = true;
					}
				} while (!valid);
				pay.paymentReceipt = num;

				do
				{
					valid = true;
					cout << "Enter the Payer's Account Number: ";
					cin >> num;
					if (findAccount(conn, num, &account) == 1)
					{ //Check if the Payer Account ID is in the DB since it's an FK
						pay.payerID = num;
						valid = true;
						//removed all this validation
						/*
						string debit = "debit";
						if (account.accountType == debit) {
							valid = true;
						}
						else {
							cout << "This Account Cannot Make Payments." << endl; //only debit accounts can make payments
							valid = false;
						}*/
					}
					else
					{
						cout << "Invalid Account Number." << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = false;
					}
				} while (!valid);


				do
				{
					valid = true;
					cout << "Enter the Receiver's ID: ";
					cin >> pay.receiverID;
					cin.clear();
					cin.ignore(1000, '\n');
					if (pay.receiverID <= 0)
					{
						cout << "Please Enter a Valid Receiver ID" << endl;
						valid = false;
					}
				} while (!valid);
				do
				{
					valid = true;
					cout << "Enter the Payment's Description:";
					getline(cin, pay.description, '\n');
					if (pay.description.size() == 0 || pay.description.find('\'') < pay.description.length())
					{
						cout << "Please Enter a Valid Description (You cannot leave this blank or have a description that includes a (') character)" << endl;
						valid = false;
					}
				} while (!valid);

				cout << "Enter The Date the Payment Was Made (format: dd-MMM-yyyy, such as 31-DEC-2020): ";
				//did not validate the date
				//do {
				//	cout >> "Enter the day (dd):"
				//}
				cin >> pay.payTime;

				do
				{
					valid = true;
					cout << "Enter The Amount Paid: ";
					cin >> pay.payAmount;
					if (pay.payAmount <= 0)
					{
						cout << "Invalid Payment Amount" << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = false;
					}
				} while (!valid);

				num = insertPayment(conn, pay);
				if (num != 0)
				{ //shouldn't even include this since the sql errors are caught
					cout << endl << "Payment Insertion Failed. Please Try Again." << endl << endl;
				}
				else
				{
					cout << endl << "Payment Insertion Successful. Inserted Payment Details:" << endl << endl;
					displayPayment(conn, pay);
				}
				break;
				//Stephen Suresh 117916213
			case 23:
				keepgoing = true;
				do
				{
					cout << "Enter a Payment ID to Update: ";
					cin >> pay.paymentReceipt;
					if (findPayment(conn, pay.paymentReceipt, &pay) == 1)
					{
						valid = true;
					}
					else
					{
						cout << "This Payment ID is not in the Database" << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = false;
					}
				} while (!valid);
				cout << endl << "Payment Details: " << endl << endl;
				displayPayment(conn, pay);
				cout << endl;
				do
				{
					valid = true;
					cout << "Enter the Payer's Account Number: ";
					cin >> num;
					if (findAccount(conn, num, &account) == 1)
					{ //Check if the Payer Account ID is in the DB since it's an FK
						pay.payerID = num;
						valid = true;
					}
					else
					{
						cout << "Invalid Account Number." << endl;
						valid = false;
					}
				} while (!valid);

				do
				{
					valid = true;
					cout << "Enter the Receiver's ID: ";
					cin >> pay.receiverID;
					cin.clear();
					cin.ignore(100, '\n');
					if (pay.receiverID <= 0)
					{
						cout << "Please Enter a Valid Receiver ID" << endl;
						valid = false;
					}
				} while (!valid);

				do
				{
					valid = true;
					cout << "Enter the Payment's Description:";
					getline(cin, pay.description, '\n');
					if (pay.description.size() == 0 || pay.description.find('\'') < pay.description.length())
					{
						cout << "Please Enter a Valid Description (You cannot leave this blank or have a description that includes a (') character)" << endl;
						valid = false;
					}
				} while (!valid);
				cout << "Enter The Date the Payment Was Made (format: dd-MMM-yyyy, such as 31-DEC-2020): ";
				//did not validate the date
				cin >> pay.payTime;
				do
				{
					valid = true;
					cout << "Enter The Amount Paid: ";
					cin >> pay.payAmount;
					if (pay.payAmount <= 0)
					{
						cout << "Please Enter a Valid Amount" << endl;
						cin.clear();
						cin.ignore(100, '\n');
						valid = false;
					}
				} while (!valid);
				updatePayment(conn, pay.paymentReceipt, &pay);
				cout << endl << "The Updated Payment Details:" << endl << endl;
				displayPayment(conn, pay);
				break;
				//Stephen Suresh 117916213
			case 24:
				keepgoing = true;
				do
				{
					cout << "Enter a Payment ID to Delete: ";
					cin >> pay.paymentReceipt;
					if (findPayment(conn, pay.paymentReceipt, &pay) == 1)
					{
						valid = true;
					}
					else
					{
						cout << "This Payment ID is not in the Database" << endl;
						cin.clear();
						cin.ignore(1000, '\n');
						valid = false;
					}
				} while (!valid);
				deletePayment(conn, pay.paymentReceipt);
				cout << endl << "The Payment Transaction Has Been Deleted" << endl << endl;
				break;
			case 0:
				cout << endl << "Thank You and Goodbye!" << endl;
				keepgoing = false;
				break;
				//	default:
					//	keepgoing = true;
					//	cout << "Invalid Entry" << endl;
			}
		} while (keepgoing);

		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp)
	{
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return 0;
}

int menu(void)
{
	//6 HR menu funcs
	cout << "------------- HR Menu -------------" << endl;
	cout << "1. Find Employee" << endl;
	cout << "2. Employees Report" << endl;
	cout << "3. Display All Employees" << endl;
	cout << "4. Add Employee" << endl;
	cout << "5. Update Employee" << endl;
	cout << "6. Delete Employee" << endl;
	//18 banking app funcs and 1 exit
	cout << "7. Find Customer" << endl;
	cout << "8. Customer Report" << endl;
	cout << "9. Display All Customers" << endl;
	cout << "10. Add Customer " << endl;
	cout << "11. Update Customer" << endl;
	cout << "12. Delete Customer" << endl;
	cout << "13. Find Card" << endl;
	cout << "14. Card Report" << endl;
	cout << "15. Display All Cards" << endl;
	cout << "16. Add Card" << endl;
	cout << "17. Update Interest Rate" << endl;
	cout << "18. Delete Card" << endl;
	cout << "19. Find a Payment Transaction" << endl;
	cout << "20. Payment Transaction Report" << endl;
	cout << "21. Display All Payment Transactions" << endl;
	cout << "22. Create a New Payment Transaction" << endl;
	cout << "23. Update an Existing Payment Transaction" << endl;
	cout << "24. Delete an Existing Payment Transaction" << endl;
	cout << "0. Exit" << endl;

	cout << "\nEnter your choice: ";

	int choice;
	char newline;
	bool done;
	do
	{
		cin >> choice;
		newline = cin.get();
		if (cin.fail() || newline != '\n')
		{
			done = false;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid. Enter an option from 0 to 24: ";
		}
		else
		{
			done = choice >= 0 && choice <= 24;
			if (!done)
			{
				cout << "Invalid. Enter an option from 0 to 24: ";
			}
		}
	} while (!done);
	return choice;
}

int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT e.employeenumber, e.lastname, e.firstname, e.email, o.phone, e.extension, e.reportsto, e.jobtitle, o.city	FROM employees e FULL OUTER JOIN offices o on e.officecode = o.officecode WHERE employeenumber = " + to_string(employeeNumber));


	if (!rs->next())
	{
		return 0;
	}
	else
	{
		emp->employeeNumber = rs->getInt(1);
		emp->lastName = rs->getString(2);
		emp->firstName = rs->getString(3);
		emp->email = rs->getString(4);
		emp->phone = rs->getString(5);
		emp->extension = rs->getString(6);
		emp->reportsTo = rs->getInt(7);
		emp->jobTitle = rs->getString(8);
		emp->city = rs->getString(9);
		return 1;
	}
}
void displayEmployee(Connection* conn, struct Employee emp)
{
	cout << "\n-------------- Employee Information -------------" << endl;
	cout << "employeeNumber = " << emp.employeeNumber << endl;
	cout << "lastName = " << emp.lastName << endl;
	cout << "firstName = " << emp.firstName << endl;
	cout << "email = " << emp.email << endl;
	cout << "phone = " << emp.phone << endl;
	cout << "extension = " << emp.extension << endl;
	cout << "reportsTo = " << emp.reportsTo << endl;
	cout << "jobTitle = " << emp.jobTitle << endl;
	cout << "city = " << emp.city << endl << endl;
}
void displayAllEmployees(Connection* conn)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT a.employeenumber, a.firstname ||' '|| a.lastname, a.email, phone, a.extension, b.firstname || ' ' || b.lastname FROM employees a FULL OUTER JOIN employees b ON a.reportsto = b.employeenumber JOIN offices ON a.officecode = offices.officecode ORDER BY offices.officecode, a.employeenumber, phone");
	if (!rs->next())
	{
		cout << "There is no employees' information to be displayed." << endl;
	}
	else
	{
		cout.setf(ios::left);
		cout.width(10);
		cout << "\nE";
		cout.width(18);
		cout << "Employee Name";
		cout.width(35);
		cout << "Email";
		cout.width(18);
		cout << "Phone";
		cout.width(11);
		cout << "Ext";
		cout << "Manager" << endl;

		cout << "------------------------------------------------------------------------------------------------------------" << endl;
		do
		{
			cout.setf(ios::left);
			cout.width(9);
			cout << rs->getInt(1);
			cout.width(18);
			cout << rs->getString(2);
			cout.width(35);
			cout << rs->getString(3);
			cout.width(18);
			cout << rs->getString(4);
			cout.width(11);
			cout << rs->getString(5);
			cout << rs->getString(6) << endl;

		} while (rs->next());
		cout << endl;
	}
}
void getEmployee(Connection* conn, struct Employee* emp)
{
	bool valid = true;
	cout << "\n-------------- New Employee Information -------------" << endl;
	cout << "Employee Number: ";
	cin >> emp->employeeNumber;
	cout << "Last Name: ";
	cin >> emp->lastName;
	cout << "First Name: ";
	cin >> emp->firstName;
	cout << "Email: ";
	cin >> emp->email;
	cout << "Extension: ";
	cin >> emp->extension;
	cout << "Job Title: ";
	cin >> emp->jobTitle;
	do
	{
		valid = true;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Office Code: ";
		cin >> emp->officeCode;
		if (emp->officeCode == 1 || emp->officeCode == 2 || emp->officeCode == 3 || emp->officeCode == 4 || emp->officeCode == 5 || emp->officeCode == 6 || emp->officeCode == 7)
		{
			valid = true;
		}
		else
		{
			cout << "Invalid Office Code" << endl;
			valid = false;
		}
	} while (!valid);
	do
	{
		cout << "Manager ID: ";
		cin >> emp->reportsTo;
		if (emp->reportsTo != 1002 && emp->reportsTo != 1056 && emp->reportsTo != 1143 && emp->reportsTo != 1102 && emp->reportsTo != 1088 && emp->reportsTo != 1621)
		{
			cout << "Please Enter a Valid Manager ID" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			valid = false;
		}
		else {
			valid = true;
		}
	} while (!valid);
}
void insertEmployee(Connection* conn, struct Employee emp)
{
	if (findEmployee(conn, emp.employeeNumber, &emp) == 1)
	{
		cout << "\nAn employee with the same employee number exists." << endl;
	}
	else
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("INSERT INTO employees VALUES(:1,:2,:3,:4,:5,:6,:7,:8)");
		stmt->setInt(1, emp.employeeNumber);
		stmt->setString(2, emp.lastName);
		stmt->setString(3, emp.firstName);
		stmt->setString(4, emp.extension);
		stmt->setString(5, emp.email);
		stmt->setInt(6, emp.officeCode);
		stmt->setInt(7, emp.reportsTo);
		stmt->setString(8, emp.jobTitle);
		stmt->executeUpdate();
		conn->commit();
		conn->terminateStatement(stmt);

		cout << "The new employee is added successfully. " << endl;
	}
}
void updateEmployee(Connection* conn, int employeeNumber)
{
	struct Employee temp;
	string ext;
	if (findEmployee(conn, employeeNumber, &temp) == 1)
	{
		cout << "Last Name: " << temp.lastName << endl;
		cout << "First Name: " << temp.firstName << endl;
		cout << "New Extension (format: x9999): ";
		cin >> ext;

		Statement* stmt = conn->createStatement();
		stmt->setSQL("UPDATE employees SET extension=:1 WHERE employeenumber=:2");
		stmt->setString(1, ext);
		stmt->setInt(2, employeeNumber);
		stmt->executeUpdate();
		conn->commit();
		conn->terminateStatement(stmt);

		cout << "The employee's extension is updated successfully." << endl;
	}
	else
	{
		cout << "The employee with ID " << employeeNumber << " does not exist." << endl;
	}
}
void deleteEmployee(Connection* conn, int employeeNumber)
{
	struct Employee temp;
	if (findEmployee(conn, employeeNumber, &temp) == 1)
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("DELETE FROM employees WHERE employeenumber=:1");

		stmt->setInt(1, employeeNumber);
		stmt->executeUpdate();
		conn->commit();
		conn->terminateStatement(stmt);

		cout << "The employee with ID " << employeeNumber << " is deleted successfully." << endl;
	}
	else
	{
		cout << "The employee with ID " << employeeNumber << " does not exist." << endl;
	}
}
int findOffice(Connection* conn, int officecode)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT * FROM offices WHERE officecode =" + to_string(officecode));

	if (!rs->next())
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
//Ryan Locke 034748129
int findCustomer(Connection* conn, int cust_id, Customer* cust)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT * FROM customer WHERE cust_id =" + to_string(cust_id));

	if (!rs->next())
	{
		return 0;
	}
	else
	{

		cust->custId = rs->getInt(1);
		cust->custName = rs->getString(2);
		cust->custAddress = rs->getString(5);
		cust->custEmail = rs->getString(3);
		cust->custPhoneNum = rs->getString(4);
		return 1;
	}

}
void displayCustomer(Connection* conn, struct Customer cust)
{
	cout << "\n------------------- Customer Information ------------------" << endl;
	cout << "Customer ID = " << cust.custId << endl;
	cout << "Customer Name = " << cust.custName << endl;
	cout << "Customer Email = " << cust.custEmail << endl;
	cout << "Customer Phone Number = " << cust.custPhoneNum << endl;
	cout << "Customer Address = " << cust.custAddress << endl << endl;

}
void displayAllCustomers(Connection* conn)
{
	Statement* stmt = conn->createStatement();

	ResultSet* rs = stmt->executeQuery("SELECT * FROM customer");

	cout << endl << "All Customers" << endl << endl;
	cout << "ID  Name" << setw(22) << "Email" << setw(26) << "Phone Num" << setw(14) << "Address" << endl;
	cout.width(107);
	cout.fill('-');
	cout << '-' << endl;
	cout.fill(' ');

	while (rs->next())
	{
		int custId = rs->getInt(1);
		string custName = rs->getString(2);
		string custEmail = rs->getString(3);
		string custPhone = rs->getString(4);
		string custAddress = rs->getString(5);
		cout << custId << " ";
		cout.width(20);
		cout.setf(ios::left);
		cout << custName << " ";
		cout.width(21);
		cout << custEmail << " ";
		cout.width(15);
		cout << custPhone << " ";
		cout << custAddress << endl;
	}
	cout << endl;
}

void getCustomer(Connection* conn, struct Customer* cust)
{
	char name[100];
	char address[100];
	cout << "New Customer Number (digits only): ";
	cin >> cust->custId;
	cout << "Customer Name: ";
	cin.ignore();
	cin.getline(name, 100, '\n');// >> cust->custName;
	cust->custName = name;
	//strcpy(cust->custName, name);
	cout << "Customer Email: ";
	cin >> cust->custEmail;
	cout << "Customer Phone Number: ";
	cin >> cust->custPhoneNum;
	cout << "Customer Address: ";
	cin.ignore();
	cin.getline(address, 100, '\n');// >> cust->custName;
	cust->custAddress = address;
	//cin >> cust->custAddress;
}

void insertCustomer(Connection* conn, struct Customer cust)
{
	if (findCustomer(conn, cust.custId, &cust) == 1)
	{
		cout << "\nA Customer with the same customer number exists." << endl;
	}
	else
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("INSERT INTO customer VALUES(:1,:2,:3,:4,:5)");

		stmt->setInt(1, cust.custId);
		stmt->setString(2, cust.custName);
		stmt->setString(3, cust.custEmail);
		stmt->setString(4, cust.custPhoneNum);
		stmt->setString(5, cust.custAddress);

		stmt->executeUpdate();
		conn->commit();
		conn->terminateStatement(stmt);

		cout << "\nThe new customer is added successfully. " << endl;
	}

}

void updateCustomer(Connection* conn, int custId)
{
	struct Customer temp;
	string phone;
	if (findCustomer(conn, custId, &temp) == 1)
	{
		cout << "The current phone number is: " << temp.custPhoneNum << endl;
		cout << "Enter new phone number: ";
		cin >> phone;

		Statement* stmt = conn->createStatement();
		stmt->setSQL("UPDATE customer SET phone_num =:1 WHERE cust_id=:2");
		stmt->setString(1, phone);
		stmt->setInt(2, custId);
		stmt->executeUpdate();
		conn->commit();
		conn->terminateStatement(stmt);

		cout << "The customer phone number is updated successfully." << endl;
	}
	else
	{
		cout << "The customer numbered " << custId << " does not exist." << endl;
	}
}

void deleteCustomer(Connection* conn, int custId)
{
	struct Customer temp;
	if (findCustomer(conn, custId, &temp) == 1)
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("DELETE FROM customer WHERE cust_id =:1");

		stmt->setInt(1, custId);
		stmt->executeUpdate();
		conn->commit();
		conn->terminateStatement(stmt);

		cout << "The customer numbered " << custId << " is deleted successfully." << endl;
	}
	else
	{
		cout << "The customer numbered " << custId << " does not exist." << endl;
	}
}

//Chungon Tse 154928188
int findCard(Connection* conn, string card_num, Card* crd)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT card_num, upper(card_type), TO_CHAR(card_exp, 'FMMonth DD, YYYY'), cust_id, interest_rate FROM card WHERE card_num =" + card_num);

	if (!rs->next())
	{
		return 0;
	}
	else
	{

		crd->card_num = rs->getString(1);
		crd->card_type = rs->getString(2);
		crd->card_exp = rs->getString(3);
		crd->cust_id = rs->getInt(4);
		crd->interest_rate = rs->getDouble(5);
		return 1;
	}

}
void displayCard(Connection* conn, struct Card crd)
{
	cout << "------------- Card Information -------------" << endl;
	cout << "Card Number = " << crd.card_num << endl;
	cout << "Card Type = " << crd.card_type << endl;
	cout << "Card Expiry Date = " << crd.card_exp << endl;
	cout << "Customer ID = " << crd.cust_id << endl;
	cout << "Interest Rate = " << crd.interest_rate << "%" << endl << endl;
}
void displayAllCards(Connection* conn)
{
	Statement* stmt = conn->createStatement();

	ResultSet* rs = stmt->executeQuery("SELECT card_num, upper(card_type), TO_CHAR(card_exp, 'FMMonth DD, YYYY'), cust_id, interest_rate FROM card");

	cout << endl << "------------- All Cards -------------" << endl << endl;
	cout << "Card Number" << setw(12) << "Card Type" << setw(19) << "Card Expiry Date" << setw(15) << "Customer ID" << setw(16) << "Interest Rate" << endl;
	cout.width(75);
	cout.fill('-');
	cout << '-' << endl;
	cout.fill(' ');

	while (rs->next())
	{
		string card_num = rs->getString(1);
		string card_type = rs->getString(2);
		string card_exp = rs->getString(3);
		int cust_id = rs->getInt(4);
		double interest_rate = rs->getDouble(5);
		cout.setf(ios::left);
		cout.width(13);
		cout << card_num << " ";
		cout.width(11);
		cout << card_type << " ";
		cout.width(19);
		cout << card_exp << " ";
		cout.width(13);
		cout << cust_id << " ";
		cout.width(10);
		cout << interest_rate << endl;
	}
	cout << endl;
}
void getCard(Connection* conn, struct Card* crd)
{
	cout << "New Card Number (digits only): ";
	cin >> crd->card_num;
	cout << "Card Type (credit/debit): ";
	cin >> crd->card_type;
	cout << "Date of Expiry (format: dd-MMM-yyyy, such as 31-DEC-2020): ";
	cin >> crd->card_exp;
	cout << "Customer ID (digits only): ";
	cin >> crd->cust_id;
	cout << "Interest Rate (a positive number to 2 decimal places, such as 1.15): ";
	cin >> crd->interest_rate;
}
void insertCard(Connection* conn, struct Card crd)
{
	if (findCard(conn, crd.card_num, &crd) == 1)
	{
		cout << "\nA card with the same card number exists." << endl;
	}
	else
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("INSERT INTO card VALUES(:1,:2,:3,:4,:5)");

		stmt->setString(1, crd.card_num);
		stmt->setString(2, crd.card_type);
		stmt->setString(3, crd.card_exp);
		stmt->setInt(4, crd.cust_id);
		stmt->setDouble(5, crd.interest_rate);

		stmt->executeUpdate();
		conn->commit();
		conn->terminateStatement(stmt);

		cout << "\nThe new card is added successfully. " << endl;
	}
}
void updateCard(Connection* conn, string card_num)
{
	struct Card temp;
	double interest;
	if (findCard(conn, card_num, &temp) == 1)
	{
		cout << "The current interest rate is: " << temp.interest_rate << endl;
		cout << "Enter new interest rate: ";
		cin >> interest;

		Statement* stmt = conn->createStatement();
		stmt->setSQL("UPDATE card SET interest_rate=:1 WHERE card_num=:2");
		stmt->setDouble(1, interest);
		stmt->setString(2, card_num);
		stmt->executeUpdate();
		conn->commit();
		conn->terminateStatement(stmt);

		cout << "The card's interest rate is updated successfully." << endl;
	}
	else
	{
		cout << "The card numbered " << card_num << " does not exist." << endl;
	}
}
void deleteCard(Connection* conn, string card_num)
{
	struct Card temp;
	if (findCard(conn, card_num, &temp) == 1)
	{
		Statement* stmt = conn->createStatement();
		stmt->setSQL("DELETE FROM card WHERE card_num=:1");

		stmt->setString(1, card_num);
		stmt->executeUpdate();
		conn->commit();
		conn->terminateStatement(stmt);

		cout << "The card numbered " << card_num << " is deleted successfully." << endl;
	}
	else
	{
		cout << "The card numbered " << card_num << " does not exist." << endl;
	}
}

//Stephen Suresh 117916213
int findPayment(Connection* conn, int payment_receipt, Payment* pay)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT payment_receipt, payer_id, receiver_id, pay_desc, TO_CHAR(pay_time, 'FMMonth DD, YYYY'), pay_amount FROM payamount WHERE payment_receipt =" + to_string(payment_receipt));

	if (!rs->next())
	{
		return 0;
	}
	else
	{
		pay->paymentReceipt = rs->getInt(1);
		pay->payerID = rs->getInt(2);
		pay->receiverID = rs->getInt(3);
		pay->description = rs->getString(4);
		pay->payTime = rs->getString(5);
		pay->payAmount = rs->getDouble(6);
		return 1;
	}
}
//Stephen Suresh 117916213
void displayPayment(Connection* conn, struct Payment pay)
{
	cout << "----------- Payment Transaction -----------" << endl;
	cout << "Payment Number = " << pay.paymentReceipt << endl;
	cout << "Payer ID = " << pay.payerID << endl;
	cout << "Receiver ID = " << pay.receiverID << endl;
	cout << "Description = " << pay.description << endl;
	cout << "Payment Date = " << pay.payTime << endl;
	cout << "Amount Paid = " << "$";
	cout.setf(ios::fixed);
	cout << std::setprecision(2);
	cout << pay.payAmount << endl;
	cout.unsetf(ios::fixed);
	cout << endl;
}
//Stephen Suresh 117916213
void displayAllPayments(Connection* conn)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT payment_receipt, payer_id, receiver_id, pay_desc, TO_CHAR(pay_time, 'FMMonth DD, YYYY'), pay_amount FROM payamount");
	cout << endl << "----------- Payment Transactions -----------" << endl << endl;
	cout << "Payment Number       " << "Payer ID        " << "Receiver ID     " << "Description          " << "Payment Date         " << "Amount Paid" << endl;
	cout.width(106);
	cout.fill('-');
	cout << '-' << endl;
	cout.fill(' ');

	while (rs->next())
	{
		int paymentReceipt = rs->getInt(1);
		int payerID = rs->getInt(2);
		int receiverID = rs->getInt(3);
		string description = rs->getString(4);
		string receiveTime = rs->getString(5);
		double receiveAmount = rs->getDouble(6);
		cout.setf(ios::left);
		cout.width(20);
		cout << paymentReceipt << " ";
		cout.width(15);
		cout << payerID << " ";
		cout.width(15);
		cout << receiverID << " ";
		cout.width(20);
		cout << description << " ";
		cout.width(20);
		cout << receiveTime << " ";
		cout.width(20);
		cout.setf(ios::fixed);
		cout << setprecision(2);
		cout << receiveAmount << endl;
		cout.unsetf(ios::fixed);
	}
	cout << endl;
}
//Stephen Suresh 117916213
int insertPayment(Connection* conn, struct Payment pay)
{
	//string commaspace = ", ";
	/*struct Payment {
	int paymentReceipt; //pk
	int payerID; //fk
	int receiverID;
	string description;
	string payTime;
	double payAmount;
	};*/
	//cout << pay.paymentReceipt << endl << pay.payerID << endl << pay.receiverID << endl << pay.description << endl << pay.payAmount << endl << pay.payTime << endl;
	Statement* stmt = conn->createStatement();

	/*
	ResultSet* rs = stmt->executeQuery("INSERT INTO payamount VALUES(" + to_string(pay.paymentReceipt) + ", " + to_string(pay.payerID) + ", " + to_string(pay.receiverID) + ", '" + pay.description + "', " + "DATE('" + pay.payTime + "'" + ", 'YYYY/MM/DD')" + ", " + to_string(pay.payAmount) + ")");
	*/
	//date format error

	stmt->setSQL("INSERT INTO payamount VALUES(:1,:2,:3,:4,:5,:6)");

	stmt->setInt(1, pay.paymentReceipt);
	stmt->setInt(2, pay.payerID);
	stmt->setInt(3, pay.receiverID);
	stmt->setString(4, pay.description);
	stmt->setString(5, pay.payTime);
	stmt->setDouble(6, pay.payAmount);

	stmt->executeUpdate();
	conn->commit();
	conn->terminateStatement(stmt);
	return 0;
}
//Stephen Suresh 117916213
int findAccount(Connection* conn, int accountID, struct Account* account)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT account_id, cust_id, account_type, balance, interest_rate FROM ACCOUNT WHERE account_id =" + to_string(accountID));

	if (!rs->next())
	{
		return 0;
	}
	else
	{
		account->accountID = rs->getInt(1);
		account->custID = rs->getInt(2);
		account->accountType = rs->getString(3);
		account->balance = rs->getDouble(4);
		account->interest = rs->getDouble(5);
		return 1;
	}
}
//Stephen Suresh 117916213
void updatePayment(Connection* conn, int paymentID, struct Payment* pay)
{
	Statement* stmt = conn->createStatement();
	stmt->setSQL("UPDATE payamount SET payer_id=:1, receiver_id=:2, pay_desc=:3, pay_time=:4, pay_amount=:5 WHERE payment_receipt=:6");
	stmt->setInt(1, pay->payerID);
	stmt->setInt(2, pay->receiverID);
	stmt->setString(3, pay->description);
	stmt->setString(4, pay->payTime);
	stmt->setDouble(5, pay->payAmount);
	stmt->setInt(6, pay->paymentReceipt);

	stmt->executeUpdate();
	conn->commit();
	conn->terminateStatement(stmt);
}
//Stephen Suresh 117916213
void deletePayment(Connection* conn, int paymentID)
{
	Statement* stmt = conn->createStatement();
	stmt->executeQuery("DELETE FROM payamount WHERE payment_receipt =" + to_string(paymentID));
	conn->commit();
}