show databases;
use 20BCS009;
show tables;
create table EMPLOYEE
(Fname varchar(15) not null,
Minit char,
Lname varchar(15) not null,
Ssn char(9) not null,
Bdate date,
Address varchar(30),
Sex char,
Salary decimal(10,2),
Super_ssn char(9),
Dno int not null,
primary key(Ssn)
);

desc EMPLOYEE;


create table DEPARTMENT
(Dname varchar(15) not null,
Dnumber int not null,
Mgr_ssn char(9) not null,
Mgr_start_date date,
primary key(Dnumber),
unique(Dname)
);

desc DEPARTMENT; 

create table DEPT_LOCATION
(Dnumber int not null,
Dlocation varchar(15) not null,
primary key(Dnumber,Dlocation),
foreign key(Dnumber) references DEPARTMENT(Dnumber) 
);

DESC DEPT_LOCATION;


create table PROJECT
( Pname varchar(15) not null,
  Pnumber int not null,
  Plocation varchar(15),
  Dnum int not null,
  primary key(Pnumber),
  unique(Pname),
  foreign key(Dnum) references DEPARTMENT(Dnumber)
  );


desc PROJECT;

 CREATE TABLE WORKS_ON
 ( Essn char(9) not null,
 Pno int not null,
 Hours decimal(3,1) not null,
 primary key(Essn,Pno),
 foreign key(Essn) references EMPLOYEE(Ssn),
 foreign key(Pno) references PROJECT(Pnumber)
 );
 
 desc WORKS_ON;


CREATE TABLE DEPENDENT 
( Essn char(9) not null,
Dependent_name varchar(15) not null,
Sex char,
Bdate date,
Relationship varchar(9),
primary key(Essn,Dependent_name),
foreign key(Essn) references EMPLOYEE(Ssn)
);

desc DEPENDENT;

show tables;







;
