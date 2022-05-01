--1a
SET AUTOCOMMIT ON;
CREATE TABLE L5_MOVIES (mid int primary key, title varchar(35) not null, releaseYear int not null,
director int not null, score decimal(3,2), constraint scorechk check (score > 0 and score <= 5));
--1b
CREATE TABLE L5_ACTORS (aid int primary key, firstName varchar(20) not null, lastName varchar(30) not null);
CREATE TABLE L5_CASTINGS (moveid int, actorid int, 
constraint mfk FOREIGN KEY (moveid) REFERENCES L5_MOVIES(mid), 
constraint afk FOREIGN KEY (actorid) REFERENCES L5_ACTORS(aid),
primary key (moveid, actorid));
CREATE TABLE L5_DIRECTORS (directorid int primary key, firstname varchar(20) not null, 
lastname varchar(30) not null);
--2
ALTER TABLE L5_MOVIES add constraint dfk FOREIGN KEY (director) REFERENCES L5_DIRECTORS(directorid);
--3
ALTER TABLE L5_MOVIES add constraint titleuni UNIQUE(title);
--4
INSERT ALL
    INTO L5_DIRECTORS VALUES (1010, 'Rob', 'Minkoff')
    INTO L5_DIRECTORS VALUES (1020, 'Bill', 'Condon')
    INTO L5_DIRECTORS VALUES (1050, 'Josh', 'Cooley')
    INTO L5_DIRECTORS VALUES (2010, 'Brad', 'Bird')
    INTO L5_DIRECTORS VALUES (3020, 'Lake', 'Bell')
SELECT * FROM dual;
INSERT ALL
    INTO L5_MOVIES VALUES (100, 'The Lion King', 2019, 3020, 3.50)
    INTO L5_MOVIES VALUES (200, 'Beauty and the Beast', 2017, 1050, 4.20)
    INTO L5_MOVIES VALUES (300, 'Toy Story 4', 2019, 1020, 4.50)
    INTO L5_MOVIES VALUES (400, 'Mission Impossible', 2018, 2010, 5.00)
    INTO L5_MOVIES VALUES (500, 'The Secret Life of Pets', 2016, 1010, 3.90)
SELECT * FROM dual;
--5
drop table L5_MOVIES cascade constraints;
drop table L5_CASTINGS cascade constraints;
drop table L5_ACTORS;
drop table L5_DIRECTORS;
--6
create table employee2 as (select * from employees);
--7
alter table employee2 add username varchar(100);
--8
delete from employee2;
--9
insert into employee2 (employeenumber, lastname, firstname, extension,
email, officecode, reportsto, jobtitle)
select employeenumber, lastname, firstname, extension,
email, officecode, reportsto, jobtitle from employees;
--10
update employee2 set lastname = 'Tse', firstname = 'Chungon'
where employeenumber = 1002;
--11
update employee2
set username=lower(concat(substr(firstname,1,1),lastname));
--12
delete from employee2
where officecode = 4;
--13
drop table employee2;