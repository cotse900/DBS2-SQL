--Ryan Locke (ID: 034748129)
--Chung On Tse (ID: 154928188)
--Stephen Suresh (ID: 117916213)
--Note: The SQL tables have been changed from our Lab07 submission after reviewing the submission and normalizing the database.
--The SQL code below represents our changed tables.
--Ryan
CREATE TABLE CUSTOMER(
cust_id INT PRIMARY KEY,
cust_name VARCHAR(35) NOT NULL,
cust_email VARCHAR(35) NOT NULL,
phone_num INT NOT NULL,
address VARCHAR(100) NOT NULL
);

INSERT ALL
INTO customer VALUES ( 100, 'Lara Cherish', 'lcherish@myseneca.ca', 2223335555, '2583 Parkdale Avenue, Hamilton, ON L8K 1A4')
INTO customer VALUES (101,'Sommer Jackson', 'lcherish@myseneca.ca' ,3334445555, '3558 Central Street, Brooklyn, NS B5A 4A8')
INTO customer VALUES (102, 'Cherise Chastity', 'cchastity@myseneca.ca', 4445556666, '2058 50th Street, Edmonton, AB T6B 2W9')
INTO customer VALUES (103, 'Nikolas Isaac', 'nisaac@myseneca.ca', 5556667777, '2758 Water Street, Kitchener, ON N2H 5A5')
INTO customer VALUES (104, 'Parris Bailey','pbailey@myseneca.ca', 6667778888,  '4421 Lynden Road, Kleinburg, ON L0J 1C0')
INTO customer VALUES (105, 'Robert Newton', 'rnewton@myseneca.ca', 1112224444, '4489 Keith Road, North Vancouver, BC V5T 2C1')
INTO customer VALUES (106, 'Brian Smith',  'bsmith@myseneca.ca', 9998887777, '4236 5th Avenue, Woking, AB T0H 3V0')
INTO customer VALUES (107, 'Kayden Kolton', 'kkolton@myseneca.ca', 8887776666 ,'1829 Danforth Avenue, Toronto, ON M4K 1A6')
INTO customer VALUES (108, 'Mikey Lylah', 'mlylah@myseneca.ca', 7776665555, '2671 Hammarskjold Dr, Burnaby, BC V5B 3C9')
INTO customer VALUES (109, 'Graham Ellery', 'gellery@myseneca.ca', 4443332222,'4345 Barton Street, Waterdown, ON L8G 3R4')
SELECT * FROM dual;

--Stephen
CREATE TABLE ACCOUNT(
account_id INT PRIMARY KEY,
cust_id INT NOT NULL,
account_type VARCHAR(35) NOT NULL,
balance DEC(15,2) NOT NULL,
interest_rate DEC(4,2) NOT NULL,
CONSTRAINT customer_fk FOREIGN KEY (cust_id) REFERENCES CUSTOMER (cust_id)
);

INSERT ALL
INTO account VALUES (1001, 100, 'Chequing', 10956.45, 0)
INTO account VALUES (1002, 101, 'Savings', 10345.34, 1.2)
INTO account VALUES (1003, 102, 'Chequing', 3045.33, 0)
INTO account VALUES (1004, 103, 'TFSA', 85786.35, 0)
INTO account VALUES (1005, 104, 'Savings', 67834.32, 1.3)
INTO account VALUES (1006, 105, 'Chequing', 4743.66, 0)
INTO account VALUES (1007, 106, 'Chequing', 2962.45, 0)
INTO account VALUES (1008, 107, 'Savings',9542.82, 1.2)
INTO account VALUES (1009, 108, 'Chequing', 1232.76, 0)
INTO account VALUES (1010, 109, 'Savings', 58494.66, 1.3)
SELECT * FROM dual;

--Chungon
CREATE TABLE CARD(
card_num INT PRIMARY KEY,
card_type VARCHAR(35) NOT NULL,
card_exp DATE NOT NULL,
cust_id INT NOT NULL,
interest_rate DEC(4,2) NOT NULL,
CONSTRAINT customerfk FOREIGN KEY (cust_id) REFERENCES CUSTOMER (cust_id)
);

INSERT ALL
INTO card VALUES (1234567890, 'credit', DATE '2022-11-20', 100, 20.00)
INTO card VALUES (1234567889, 'debit', DATE '2023-03-16', 100, 0.0)
INTO card VALUES (1234567888, 'debit', DATE '2022-04-11', 101, 0.0)
INTO card VALUES (1234567887, 'credit', DATE '2024-09-22', 104, 19.85)
INTO card VALUES (1234567886, 'credit', DATE '2024-05-30', 105, 21.20)
INTO card VALUES (1234567885, 'debit', DATE '2023-01-11', 106, 0)
INTO card VALUES (1234567884, 'credit', DATE '2024-06-22',106,20.00)
INTO card VALUES (1234567883, 'credit', DATE '2022-03-11', 107, 21.20)
INTO card VALUES (1234567882, 'debit', DATE '2023-02-10', 107, 0)
INTO card VALUES (1234567881, 'credit', DATE '2024-11-22', 108, 20.00)
SELECT * FROM dual;

--Ryan
CREATE TABLE RECEIVEAMOUNT(
receive_receipt INT PRIMARY KEY,
receiver_id INT NOT NULL,
payer_id INT NOT NULL,
receive_desc VARCHAR(35),
receive_time DATE NOT NULL,
receive_amount DEC(7,2) NOT NULL,
CONSTRAINT receiver_id_fk FOREIGN KEY (receiver_id) REFERENCES ACCOUNT (account_id)
);

INSERT ALL
INTO receiveamount VALUES (12345, 1001, 9699, 'rent', DATE '2021-11-20', 1400.00)
INTO receiveamount VALUES (23456, 1003, 8927, 'payroll', DATE '2021-05-21', 5555.00)
INTO receiveamount VALUES (34567, 1003, 5842, 'etransfer',  DATE '2021-02-10',120.00)
INTO receiveamount VALUES (45678, 1006, 6893, 'payroll', DATE '2021-01-09',12000.00)
INTO receiveamount VALUES (56789, 1006, 4872, 'etransfer', DATE '2021-10-22', 40.00)
INTO receiveamount VALUES (67890, 1007, 6583, 'payroll', DATE '2021-02-11', 3503.14)
INTO receiveamount VALUES (78901, 1007, 1220, 'etransfer', DATE '2021-03-21', 355.12)
INTO receiveamount VALUES (89012, 1007, 7894, 'etransfer', DATE '2021-09-10', 26.22)
INTO receiveamount VALUES (90123, 1009, 9847, 'payroll', DATE '2021-10-20', 7233.44)
INTO receiveamount VALUES (11234, 1009, 7127, 'rent', DATE '2021-03-24', 2350.00)
SELECT * FROM dual;

--Stephen
CREATE TABLE PAYAMOUNT(
payment_receipt INT PRIMARY KEY,
payer_id INT NOT NULL,
receiver_id INT NOT NULL,
pay_desc VARCHAR(35),
pay_time DATE NOT NULL,
pay_amount DEC(7,2) NOT NULL,
CONSTRAINT payer_id_fk FOREIGN KEY (payer_id) REFERENCES ACCOUNT (account_id)
);

INSERT ALL
INTO payamount VALUES (12345, 1003, 4587, 'phone bill', DATE '2021-11-27', 70.00)
INTO payamount VALUES (23456, 1003, 3456, 'pizza pizza', DATE '2020-06-22', 35.43)
INTO payamount VALUES (34567, 1006, 2132, 'internet bill', DATE '2021-05-30', 60.00)
INTO payamount VALUES (45678, 1006, 5234, 'burger king', DATE '2021-03-09', 12.34)
INTO payamount VALUES (56789, 1007, 3124, 'etransfer', DATE '2021-06-01', 22.33)
INTO payamount VALUES (67890, 1007, 1231, 'hair salon', DATE '2021-10-30', 34.55)
INTO payamount VALUES (78901, 1007, 9678, 'phone bill', DATE '2021-09-11', 55.43)
INTO payamount VALUES (89012, 1009, 5683, 'kfc', DATE '2021-08-22', 80.33)
INTO payamount VALUES (90123, 1009, 0268, 'etransfer', DATE '2021-01-12', 23.44)
INTO payamount VALUES (11234, 1009, 8972, 'phone bill', DATE '2021-09-11', 35.33)
SELECT * FROM dual;

--Chungon
CREATE TABLE STATEMENT(
statement_id INT PRIMARY KEY,
account_id INT NOT NULL,
stmt_type INT NOT NULL,
start_date DATE NOT NULL,
end_date DATE NOT NULL,
CONSTRAINT account_id_fk FOREIGN KEY (account_id) REFERENCES ACCOUNT(account_id),
CONSTRAINT stmt_type_chk CHECK (stmt_type BETWEEN 0 AND 3)
--CONSTRAINT end_date_chk CHECK (end_date <= GETDATE();)
);

INSERT ALL
INTO statement VALUES (123456789, 1001, 1, DATE '2021-11-01', DATE '2021-11-30')
INTO statement VALUES (123456790, 1002, 2, DATE '2021-10-01', DATE '2021-10-31')
INTO statement VALUES (123456791, 1003, 1, DATE '2021-11-01', DATE '2021-11-30')
INTO statement VALUES (123456792, 1004, 3, DATE '2021-10-01', DATE '2021-10-31')
INTO statement VALUES (123456793, 1005, 1, DATE '2021-11-01', DATE '2021-11-30')
INTO statement VALUES (123456794, 1006, 2, DATE '2021-11-01', DATE '2021-11-30')
INTO statement VALUES (123456795, 1007, 3, DATE '2021-11-01', DATE '2021-11-30')
INTO statement VALUES (123456796, 1008, 2, DATE '2021-11-01', DATE '2021-11-30')
INTO statement VALUES (123456797, 1009, 1, DATE '2021-10-01', DATE '2021-10-31')
INTO statement VALUES (123456798, 1010, 2, DATE '2021-11-01', DATE '2021-11-30')
SELECT * FROM dual;

COMMIT;
