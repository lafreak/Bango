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
	job TINYINT NOT NULL DEFAULT 1,
	class TINYINT NOT NULL,
	level TINYINT NOT NULL DEFAULT 1,
	strength SMALLINT NOT NULL,
	health SMALLINT NOT NULL,
	inteligence SMALLINT NOT NULL,
	wisdom SMALLINT NOT NULL,
	dexterity SMALLINT NOT NULL,
	face TINYINT NOT NULL,
	hair TINYINT NOT NULL,
	deleted TINYINT NOT NULL DEFAULT 0,

	PRIMARY KEY (idplayer),
	FOREIGN KEY (idaccount) 
		REFERENCES account (idaccount),
	UNIQUE(name)
);

INSERT INTO account (login, password, secondary)
	VALUES
	('qwe', 'asd', '00000000')
;

INSERT INTO player (idaccount, name, job, class, level, strength,
				health, inteligence, wisdom, dexterity, face, hair)
	VALUES
	(1, 'lafreak1', 23, 3, 100, 50, 60, 70, 80, 90, 1, 1),
	(1, 'lafreak2', 11, 0, 60, 50, 60, 70, 80, 90, 1, 1),
	(1, 'lafreak3', 11, 1, 60, 50, 60, 70, 80, 90, 1, 1),
	(1, 'lafreak4', 11, 2, 60, 50, 60, 70, 80, 90, 1, 1),
	(1, 'lafreak5', 11, 0, 60, 50, 60, 70, 80, 90, 1, 1)
;

	