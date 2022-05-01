// DBS211 Project – Milestone 2
// Group 12
// Members:
// Ryan Locke (ID: 034748129) - table CUSTOMER (options 4,5,6)
// int findCustomer(Connection* conn, int cust_id, Customer* cust);
//void displayCustomer(Connection* conn, struct Customer cust);
//void displayAllCustomers(Connection* conn);
// 
// Chung On Tse (ID: 154928188) - table CARD (options 7,8,9)
// int findCard(Connection* conn, int card_num, Card* crd);
//void displayCard(Connection* conn, struct Card crd);
//void displayAllCards(Connection* conn);
// 
// Stephen Suresh (ID: 117916213) - table PAYMENT (options 10,11,12)
// int findPayment(Connection* conn, int payment_receipt, Payment* pay);
//void displayPayment(Connection* conn, struct Payment pay);
//void displayAllPayments(Connection* conn);
// Class: DBS211 NII

#include <iostream>
#include <iomanip>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

struct Employee
{
	int employeeNumber;
	string lastName;
	string firstName;
	string extension;
	string email;
	int reportsTo;
	string jobTitle;
	string phone;
	string city;
};

/*Ryan Locke 034748129
struct Customer
{
	int custId;
	string custName;
	string custEmail;
	string custPhoneNum;
	string custAddress;
};*/
//Chungon Tse 154928188
struct Card
{
	string card_num;
	string card_type;
	string card_exp;
	int cust_id;
	double interest_rate;
};
/*Stephen Suresh 117916213
struct Payment {
	int paymentReceipt; //pk
	int payerID; //fk
	int receiverID;
	string description;
	string payTime;
	double payAmount;
};*/

/* //For Later
struct Received {
	int receiveReceipt;
	int receiverID;
	int payerID;
	string description;
	string receiveTime;
	double receiveAmount;
};*/

int menu(void);
int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp);
void displayEmployee(Connection* conn, struct Employee emp);
void displayAllEmployees(Connection* conn);
//int findCustomer(Connection* conn, int cust_id, Customer* cust);
//void displayCustomer(Connection* conn, struct Customer cust);
//void displayAllCustomers(Connection* conn);
int findCard(Connection* conn, int card_num, Card* crd);
void displayCard(Connection* conn, struct Card crd);
void displayAllCards(Connection* conn);
//int findPayment(Connection* conn, int payment_receipt, Payment* pay);
//void displayPayment(Connection* conn, struct Payment pay);
//void displayAllPayments(Connection* conn);

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

	try
	{
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);
		cout << "Database Connection is successful!" << endl;
		cout << "Project Milestone 1 and 2" << endl;

		struct Employee employee;
		struct Customer customer;
		struct Card crd;
		struct Payment pay;
		bool keepgoing = false;

		int input, num = 0;
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
				/*Ryan Locke 034748129
			case 4:
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
			case 5:
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
			case 6:
				keepgoing = true;
				displayAllCustomers(conn);
				break;
				*/
				//Chungon Tse 154928188
			case 7:
				keepgoing = true;
				cout << "Enter Card Number: ";
				cin >> num;
				if (findCard(conn, num, &crd) == 1)
				{
					cout << endl << "Valid Card" << endl << endl;
				}
				else
				{
					cout << "Card numbered " << num << " does not exist." << endl << endl;
				}
				break;
			case 8:
				keepgoing = true;
				cout << "Enter Card Number to display a card: ";
				cin >> num;
				if (findCard(conn, num, &crd) == 1)
				{
					cout << endl << "Valid Card" << endl << endl;
				}
				else
				{
					cout << "Card numbered " << num << " does not exist." << endl << endl;
				}
				if (findCard(conn, num, &crd) == 1) displayCard(conn, crd);
				break;
			case 9:
				keepgoing = true;
				displayAllCards(conn);
				break;
				/*Stephen Suresh 117916213
			case 10:
				keepgoing = true;
				cout << "Enter a Payment Number: ";
				cin >> num;
				if (findPayment(conn, num, &pay) == 1) {
					cout << endl << "Valid Payment Number" << endl << endl;
				}
				else {
					cout << "Payment numbered " << num << " does not exist." << endl << endl;
				}
				break;
				//Stephen Suresh 117916213
			case 11: //displayPayment(conn, pay);
				keepgoing = true;
				cout << "Enter a Payment Number to Display a Payment: ";
				cin >> num;
				if (findPayment(conn, num, &pay) == 1) {
					cout << endl << "Valid Payment Number" << endl << endl;
				}
				else {
					cout << "Payment numbered " << num << " does not exist." << endl << endl;
				}
				if (findPayment(conn, num, &pay) == 1) displayPayment(conn, pay);
				break;
				//Stephen Suresh 117916213
			case 12:
				keepgoing = true;
				displayAllPayments(conn);
				break;*/
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
	cout << "------------- HR Menu -------------" << endl;
	cout << "1. Find Employee" << endl;
	cout << "2. Employees Report" << endl;
	cout << "3. Display All Employees" << endl;
	//cout << "4. Find Customer" << endl;
	//cout << "5. Customer Report" << endl;
	//cout << "6. Display All Customers" << endl;
	cout << "7. Find Card" << endl;
	cout << "8. Card Report" << endl;
	cout << "9. Display All Cards" << endl;
	//cout << "10. Find a Payment Transaction" << endl;
	//cout << "11. Payment Transaction Report" << endl;
	//cout << "12. Display All Payment Transactions" << endl;
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
			cout << "Invalid. Enter an option of 1, 2, 3, 7, 8, 9,or 0: ";
		}
		else
		{
			done = choice = 0 or 1 or 2 or 3 or 7 or 8 or 9;//individualized
			if (!done)
			{
				cout << "Invalid. Enter an option of 1, 2, 3, 7, 8, 9,or 0: ";
			}
		}
	} while (!done);
	return choice;
}

int findEmployee(Connection* conn, int employeeNumber, struct Employee* emp)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT employeenumber, lastname, firstname, email, phone, extension, reportsto, jobtitle, city FROM employees JOIN offices ON employees.officecode = offices.officecode WHERE employeenumber =" + to_string(employeeNumber));

	if (!rs->next())
	{
		return 0;
	}
	else
	{
		emp->employeeNumber = rs->getInt(1);
		emp->firstName = rs->getString(2);
		emp->lastName = rs->getString(3);
		emp->extension = rs->getString(4);
		emp->email = rs->getString(5);
		emp->city = rs->getString(6);
		emp->reportsTo = rs->getInt(7);
		emp->jobTitle = rs->getString(8);
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

//Chungon Tse 154928188
int findCard(Connection* conn, int card_num, Card* crd)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT card_num, upper(card_type), TO_CHAR(card_exp, 'FMMonth DD, YYYY'), cust_id, interest_rate FROM card WHERE card_num =" + to_string(card_num));

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