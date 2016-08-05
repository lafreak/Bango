DROP DATABASE IF EXISTS kalonline;

CREATE DATABASE kalonline;
USE kalonline;

CREATE TABLE account (
	idaccount int AUTO_INCREMENT,
	login varchar(30) NOT NULL,
	password varchar(30) NOT NULL,
	secondary varchar(8),
	PRIMARY KEY (idaccount),
	UNIQUE (login)
);

INSERT INTO account (login, password)
VALUES
	('qwe', 'asd');

	SELECT 
				EXISTS(SELECT 1 FROM account WHERE login='qwe') as bIsLogin, 
				EXISTS(SELECT 1 FROM account WHERE login='qwe' AND password='asd') as bIsPW,
				EXISTS(SELECT 1 FROM account WHERE login='qwe' AND password='asd' AND secondary IS NULL) as bIsCreate2ND;