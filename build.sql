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

CREATE TABLE player (
	idplayer int AUTO_INCREMENT,
	idaccount int NOT NULL,
	name VARCHAR(30) NOT NULL,
	job TINYINT NOT NULL,
	class TINYINT NOT NULL,
	level TINYINT NOT NULL,
	strength SMALLINT NOT NULL,
	health SMALLINT NOT NULL,
	inteligence SMALLINT NOT NULL,
	wisdom SMALLINT NOT NULL,
	dexterity SMALLINT NOT NULL,
	face TINYINT NOT NULL,
	hair TINYINT NOT NULL,

	PRIMARY KEY (idplayer),
	FOREIGN KEY (idaccount) 
		REFERENCES account (idaccount)
);

INSERT INTO account (login, password)
	VALUES
	('qwe', 'asd');

INSERT INTO player (idaccount, name, job, class, level, strength,
				health, inteligence, wisdom, dexterity, face, hair)
	VALUES
	(1, 'lafreak', 3, 3, 100, 50, 60, 70, 80, 90, 1, 1);

	