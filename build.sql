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
	x INT NOT NULL DEFAULT 360931,
	y INT NOT NULL DEFAULT 187024,
	z INT NOT NULL DEFAULT 42140,
	strength SMALLINT NOT NULL,
	health SMALLINT NOT NULL,
	inteligence SMALLINT NOT NULL,
	wisdom SMALLINT NOT NULL,
	dexterity SMALLINT NOT NULL,
	contribute SMALLINT NOT NULL DEFAULT 0,
	curhp SMALLINT NOT NULL,
	curmp SMALLINT NOT NULL,
	exp BIGINT NOT NULL DEFAULT 0,
	pupoint SMALLINT NOT NULL DEFAULT 0,
	supoint SMALLINT NOT NULL DEFAULT 0,
	anger INT NOT NULL DEFAULT 0,
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
	('qwe', 'asd', '00000000'),
	('qwe1', 'asd', '00000000')
;

INSERT INTO player (idaccount, name, job, class, level, strength,
				health, inteligence, wisdom, dexterity, curhp, curmp, face, hair)
	VALUES
	(1, 'lafreak1', 23, 3, 100, 50, 60, 70, 80, 90, 100, 80, 1, 1),
	(1, 'lafreak2', 11, 0, 60, 50, 60, 70, 80, 90, 100, 80, 1, 1),
	(1, 'lafreak3', 11, 1, 60, 50, 60, 70, 80, 90, 100, 80, 1, 1),
	(1, 'lafreak4', 11, 2, 60, 50, 60, 70, 80, 90, 100, 80, 1, 1),
	(1, 'lafreak5', 11, 0, 60, 50, 60, 70, 80, 90, 100, 80, 1, 1)
;

	