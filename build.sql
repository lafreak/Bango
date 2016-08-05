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

