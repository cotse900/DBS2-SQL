-- Sample Tables for LAB4 DBS211.ca website samples
-- --------------------------------------------------

CREATE TABLE Gameteams (
    teamID INT PRIMARY KEY,
    teamName varchar(15),
    shirtColor varchar(10),
    homeField varchar(15)
);

INSERT ALL
    INTO Gameteams VALUES (10, 'Hornets', 'Yellow', 'Toronto')
    INTO Gameteams VALUES (11, 'Falcons', 'Brown', 'Barrie')
    INTO Gameteams VALUES (12, 'Bloopers', 'Red', 'Kitchener')
	  INTO Gameteams VALUES (14, 'BlueJays', 'Blue', 'Markham')
	    INTO Gameteams VALUES (15, 'Michigans', 'White', 'RichmondHill')
SELECT * FROM dual;
COMMIT;

CREATE TABLE Teamplayers (
    playerID INT PRIMARY KEY,
    firstName varchar(20),
    lastName varchar(20),
    teamID INT );
    
INSERT ALL
    INTO Teamplayers VALUES (1, 'John', 'Smith', 10)
    INTO Teamplayers VALUES (2, 'Bob', 'Marley', 10)
    INTO Teamplayers VALUES (3, 'Steven', 'King', 11)
    INTO Teamplayers VALUES (4, 'Jim', 'Parsons', NULL)
	 INTO Teamplayers VALUES (5, 'Ronald', 'Ritchie', NULL)
SELECT * FROM dual;
COMMIT;

CREATE TABLE Teamfields (
    fieldname varchar(15) PRIMARY KEY,
    Address varchar(50),
    Manager varchar(25));

INSERT ALL
    INTO Teamfields VALUES ('Toronto', '22 Queen St. E.', 'Doug Ford')
    INTO Teamfields VALUES ('Barrie', '380 Bayview Ave', 'Richard Alexander')
    INTO Teamfields VALUES ('Kitchener', '220 Weber St. S', 'Marco Albano')
    INTO Teamfields VALUES ('Waterloo', '576 King St. N', 'Pauyl Caruso')
	INTO Teamfields VALUES ('Markham', '455 Highway 7 N', 'DeSouza')
	INTO Teamfields VALUES ('RichmondHill', '33 Rose St', 'Robbie')
SELECT * FROM dual;

COMMIT;