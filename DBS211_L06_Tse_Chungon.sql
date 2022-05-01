--2
CREATE TABLE newCustomers AS (SELECT * FROM Customers WHERE 1=2);
--3
SET AUTOCOMMIT OFF;
SET TRANSACTION READ WRITE;
--4
INSERT ALL
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (100,'Ralph Patel','Patel','Ralph',2233355555,'10 SenecaWay','Paris','France')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (101,'Betty Denis','Denis','Betty',3344455555,'110 SenecaWay','Chicago','USA')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (102,'Ben Biri','Biri','Ben',44555445544,'13000 SenecaWay','Toronto','Canada')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (103,'Chad Newman','Newman','Chad',66777332233,'12 SenecaWay','Mexico City','Mexico')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (104,'Audrey Ropeburn','Ropeburn','Audrey',7788811212,'15000 SenecaWay','Havana','Cuba')
SELECT * FROM DUAL;
--5
SELECT * from newCustomers;
--6
ROLLBACK;
SELECT * from newCustomers;
--7
INSERT ALL
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (100,'Ralph Patel','Patel','Ralph',2233355555,'10 SenecaWay','Paris','France')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (101,'Betty Denis','Denis','Betty',3344455555,'110 SenecaWay','Chicago','USA')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (102,'Ben Biri','Biri','Ben',44555445544,'13000 SenecaWay','Toronto','Canada')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (103,'Chad Newman','Newman','Chad',66777332233,'12 SenecaWay','Mexico City','Mexico')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (104,'Audrey Ropeburn','Ropeburn','Audrey',7788811212,'15000 SenecaWay','Havana','Cuba')
SELECT * FROM DUAL;
COMMIT;
SELECT * FROM newCustomers;
--8
UPDATE newCustomers
SET addressLine1 = 'unknown';
--9
COMMIT;
--10
ROLLBACK;
--10a
SELECT * FROM newCustomers
WHERE addressLine1 = 'unknown';
--11
BEGIN
DELETE FROM newCustomers WHERE
customerNumber=100 or customerNumber=101 or customerNumber=102 or customerNumber=103 or customerNumber=104;
END;
--12
CREATE VIEW vwNewCusts AS
SELECT * FROM newCustomers
ORDER BY contactLastName, contactFirstName;
--13
ROLLBACK;
SELECT * FROM newCustomers;
--14
INSERT ALL
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (100,'Ralph Patel','Patel','Ralph',2233355555,'10 SenecaWay','Paris','France')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (101,'Betty Denis','Denis','Betty',3344455555,'110 SenecaWay','Chicago','USA')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (102,'Ben Biri','Biri','Ben',44555445544,'13000 SenecaWay','Toronto','Canada')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (103,'Chad Newman','Newman','Chad',66777332233,'12 SenecaWay','Mexico City','Mexico')
INTO newCustomers (customerNumber, customerName, contactLastName, contactFirstName, phone, addressLine1, city, country)
VALUES (104,'Audrey Ropeburn','Ropeburn','Audrey',7788811212,'15000 SenecaWay','Havana','Cuba')
SELECT * FROM DUAL;
--15
SAVEPOINT insertion;
--16
UPDATE newCustomers
SET addressLine1 = 'unknown';
SELECT * FROM newCustomers;
--17
ROLLBACK to insertion;
SELECT * FROM newCustomers;
--18
ROLLBACK;
SELECT * FROM newCustomers;
--19
REVOKE all ON newCustomers from public;
--20
GRANT select on newCustomers to dbs211_213i27;
--21
GRANT insert, update, delete on newCustomers to dbs211_213i27;
--22
REVOKE all on newCustomers from dbs211_213i27;
--23
DROP VIEW vwNewCusts;
DROP TABLE newCustomers;
COMMIT;