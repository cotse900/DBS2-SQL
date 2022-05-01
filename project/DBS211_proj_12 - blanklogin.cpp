// DBS211 Project – Milestone 1
// Group 12
// Members: Ryan Locke (ID: 034748129), Chung On Tse (ID: 154928188), Stephen Suresh (ID: 117916213)
// Class: DBS211 NII

#include <iostream>
#include <iomanip>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;


int findEmployee(Connection* conn, int employeeNumber);

int main(void) {
	Environment* env = nullptr;
	Connection* conn = nullptr;
	string str;
	string usr = "usr";
	string pass = "pass";
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);
		cout << "Connect is successful!" << endl;
		cout << "Group 12" << endl;
		cout << "Ryan Locke" << endl;
		cout << "Stephen Suresh" << endl;
		cout << "Chungon Tse" << endl;

		Statement* stmt = conn->createStatement();

		ResultSet* rs = stmt->executeQuery("SELECT officecode, city, state, country, postalcode FROM offices ORDER BY officecode");

		cout << "The company offices are:" << endl;
		cout << "# City" << setw(17) << "State" << setw(14) << "Country" << setw(20) << "Postal Code" << endl;

		while (rs->next()) {
			int count = rs->getInt(1);
			string city = rs->getString(2);
			string state = rs->getString(3);
			string country = rs->getString(4);
			string pc = rs->getString(5);
			cout << count << " ";
			cout.width(15);
			cout.setf(ios::left);
			cout << city << " ";
			cout.width(11);
			cout << state << " ";
			cout.width(15);
			cout << country << " " << pc << endl;
		}

		conn->terminateStatement(stmt);

		int ecode;
		bool correctCode = false;
		do {
			cout << "Enter employee number: ";
			cin >> ecode;
			if (!cin || findEmployee(conn, ecode) != 1)
			{
				correctCode = false;
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Employee Number\n";
			}

			else {
				correctCode = true;
				cout << "Valid input" << endl;
				cout << "Search in table..." << endl;
			}
		} while (correctCode == false);
		Statement* stmt2 = conn->createStatement();

		ResultSet* rs2 = stmt2->executeQuery("SELECT employeenumber, lastname, firstname, extension, email, officecode, reportsto, jobtitle FROM employees WHERE employeenumber =" + to_string(ecode));

		cout << setw(19) << "Employeenumber" << setw(14) << "Last Name" << setw(14) << "First Name" << setw(13) << "Extension" << setw(34) << "Email" << setw(13) << "Officecode" << setw(11) << "Reportsto" << "Jobtitle" << endl;

		while (rs2->next()) {
			int employeenumber = rs2->getInt(1);
			string lastname = rs2->getString(2);
			string firstname = rs2->getString(3);
			string extension = rs2->getString(4);
			string email = rs2->getString(5);
			int officecode = rs2->getInt(6);
			int reportsto = rs2->getInt(7);
			string jobtitle = rs2->getString(8);

			cout.width(18);
			cout << employeenumber << " ";
			cout.width(13);
			cout << lastname << " ";
			cout.width(13);
			cout << firstname << " ";
			cout.width(12);
			cout << extension << " ";
			cout.width(33);
			cout << email << " ";
			cout.width(12);
			cout << officecode << " ";
			cout.width(10);
			cout << reportsto << " ";
			cout << jobtitle << endl;
		}

		conn->terminateStatement(stmt2);
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}


	return 0;
}

int findEmployee(Connection* conn, int employeeNumber)
{
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT employeenumber, lastname, firstname, extension, email, officecode, reportsto, jobtitle FROM employees WHERE employeenumber=" + to_string(employeeNumber));

	if (!rs->next())
	{
		return 0;
	}
	else
	{
		return 1;
	}
}