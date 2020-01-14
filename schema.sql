DROP DATABASE IF EXISTS `Hospital`;
CREATE DATABASE `Hospital`; 
USE `Hospital`;


CREATE TABLE doctors (
	d_id SERIAL PRIMARY KEY,
	first_name VARCHAR(64) NOT NULL,
	last_name VARCHAR(64) NOT NULL,
	birth_date DATE NOT NULL CHECK (birth_date > '1900-01-01'),
   	joined_date DATE NOT NULL,
   	salary INTEGER NOT NULL CHECK(salary >= 0),
   	CHECK (joined_date > birth_date),
	email VARCHAR(128) NOT NULL UNIQUE
);

CREATE TABLE medical_cards (
	card_id SERIAL PRIMARY KEY,
	blood_type SMALLINT NOT NULL CHECK (blood_type>=1 AND blood_type<=4),
	rh_factor SMALLINT NOT NULL CHECK (rh_factor =-1 OR rh_factor=1),
	chronic_disiases TEXT,
	vaccinations TEXT
);

CREATE TABLE nurses (
	n_id SERIAL PRIMARY KEY,
	first_name VARCHAR(64) NOT NULL,
	last_name VARCHAR(64) NOT NULL,
	birth_date DATE CHECK (birth_date > '1900-01-01'),
   	joined_date DATE NOT NULL,
   	salary INTEGER NOT NULL CHECK(salary >= 0),
	d_id  INTEGER REFERENCES doctors(d_id),
   	CHECK (joined_date > birth_date),
	email VARCHAR(128) NOT NULL UNIQUE
);

CREATE TABLE patients (
	p_id SERIAL PRIMARY KEY,
	first_name VARCHAR(64) NOT NULL,
	last_name VARCHAR(64) NOT NULL,
	date_of_birth DATE NOT NULL CHECK (date_of_birth > '1900-01-01'),
	gender SMALLINT NOT NULL CHECK (gender=0 OR gender=1),
	medical_history INTEGER REFERENCES medical_cards (card_id),
email VARCHAR(128) NOT NULL UNIQUE
);

CREATE TABLE staff (
	s_id SERIAL PRIMARY KEY,
	first_name VARCHAR(64) NOT NULL,
	last_name VARCHAR(64) NOT NULL,
	birth_date DATE NOT NULL CHECK (birth_date > '1900-01-01'),
   	joined_date DATE NOT NULL,
   	salary INTEGER NOT NULL CHECK(salary >= 0),
 	position VARCHAR(64) NOT NULL,
	email VARCHAR(128) NOT NULL UNIQUE
);



CREATE TABLE wards (
	w_id SERIAL PRIMARY KEY,
number_of_beds INTEGER NOT NULL
);


	

CREATE TABLE appointments(
	d_id INTEGER REFERENCES doctors(d_id),
	time_slot TIMESTAMP NOT NULL,
n_id INTEGER REFERENCES nurses (n_id),
	p_id INTEGER REFERENCES patients(p_id),
	PRIMARY KEY (d_id, time_slot)
);

CREATE TABLE wards_nurses (
	w_id INTEGER REFERENCES wards(w_id),
	n_id INTEGER REFERENCES nurses (n_id),
	date DATE NOT NULL,
	PRIMARY KEY (w_id, date)
);

CREATE TABLE drugs (
	drug_id SERIAL PRIMARY KEY,
	price INTEGER NOT NULL CHECK (price>0),
	commercial_name VARCHAR(32) NOT NULL UNIQUE,
	international_nonproprietary_name VARCHAR(64) NOT NULL,
	amount INTEGER NOT NULL CHECK(amount>=0)
);

CREATE TABLE wards_assigned (
	p_id INTEGER REFERENCES patients(p_id),
	w_id INTEGER REFERENCES wards(w_id),
	start_date DATE NOT NULL,
	end_date DATE NOT NULL,
	PRIMARY KEY (p_id, start_date, end_date)
);

CREATE TABLE prescriptions (
	d_id INTEGER REFERENCES doctors(d_id),
	p_id INTEGER REFERENCES patients(p_id),
	drug_id INTEGER REFERENCES drugs(drug_id),
	date DATE NOT NULL,
	pr_id SERIAL PRIMARY KEY
);


CREATE TABLE janitor_wards (
	j_id INTEGER REFERENCES staff(s_id),
	w_id INTEGER REFERENCES wards(w_id),
	date DATE NOT NULL,
	PRIMARY KEY (j_id, date)
);

CREATE TABLE attend_patients (
	d_id INTEGER REFERENCES doctors(d_id),
	w_id INTEGER REFERENCES wards(w_id),
	date DATE NOT NULL,
	PRIMARY KEY(d_id, date)
);

CREATE TABLE buy (
	pr_id INTEGER REFERENCES prescriptions (pr_id),
	date DATE NOT NULL,
	PRIMARY KEY(pr_id, date)
);