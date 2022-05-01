--1
SELECT t.teamID, teamname, fieldname, address
FROM gameteams t left outer JOIN teamplayers p ON p.teamID = t.teamID right outer join teamfields f ON t.homeFIELD=f.fieldname
WHERE shirtcolor = 'White';
--2
SELECT t.teamid, teamname, firstname, lastname
FROM gameteams t right outer JOIN teamplayers p ON p.teamID = t.teamID
--3a
SELECT employeenumber, firstname, lastname, city, phone, postalcode
FROM employees, offices
WHERE employees.officecode = offices.officecode AND employees.officecode = 4
--3b
SELECT employeenumber, firstname, lastname, city, phone, postalcode
FROM employees JOIN offices ON employees.officecode = offices.officecode
WHERE employees.officecode = 4
--4a
SELECT customers.customernumber
FROM customers JOIN payments ON customers.customernumber = payments.customernumber
WHERE customers.country = 'Canada'
--4b
SELECT customers.customernumber, customername, to_char(paymentdate, 'Mon DD, yyyy') as paymentdate, amount
FROM customers JOIN payments ON customers.customernumber = payments.customernumber
WHERE customers.country = 'Canada';
--5
SELECT customers.customernumber, customername
FROM customers full outer JOIN payments ON customers.customernumber = payments.customernumber
WHERE customers.country = 'USA' AND amount is null
ORDER BY customernumber
--6a
CREATE VIEW vwCustomerOrder AS SELECT customers.customernumber, orders.ordernumber, 
orders.orderdate, products.productname, orderdetails.quantityordered, orderdetails.priceeach
FROM customers JOIN orders ON customers.customernumber = orders.customernumber 
JOIN orderdetails ON orders.ordernumber = orderdetails.ordernumber 
JOIN products ON orderdetails.productcode = products.productcode
--6b
SELECT * FROM vwCustomerOrder
--7
SELECT * FROM vwCustomerOrder
JOIN orderdetails ON vwCustomerOrder.ordernumber = orderdetails.ordernumber
WHERE customernumber = 124
ORDER BY vwCustomerOrder.ordernumber, orderdetails.orderlinenumber
--8
SELECT customers.customernumber, contactfirstname as firstname, contactlastname as lastname, phone, creditlimit
FROM customers LEFT OUTER JOIN orders ON customers.customernumber = orders.customernumber
WHERE orders.ordernumber is null
--9
CREATE VIEW vwEmployeeManager AS SELECT original.*, compare.firstname||' '||compare.lastname as managerlastname
FROM employees original LEFT OUTER JOIN employees compare ON original.reportsto = compare.employeenumber
order by original.employeenumber
--10
CREATE OR REPLACE VIEW vwEmployeeManager
AS SELECT original.*, compare.firstname||' '||compare.lastname as managerlastname
FROM employees original JOIN employees compare ON original.reportsto = compare.employeenumber
order by original.employeenumber
--11
DROP VIEW vwCustomerOrder;
DROP VIEW vwEmployeeManager;