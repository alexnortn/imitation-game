CREATE TABLE IF NOT EXISTS users (
	id serial PRIMARY KEY,
	username char(20) UNIQUE,
	first_name char(20),
	last_name char(20),
	created TIMESTAMP NOT NULL,
	deleted TIMESTAMP DEFAULT NULL
);

CREATE TABLE IF NOT EXISTS challenges (
	id serial PRIMARY KEY,
	user_one_id integer NOT NULL REFERENCES users(id),
	user_two_id integer NOT NULL REFERENCES users(id),
	step integer NOT NULL DEFAULT 1,
	score_one_id integer,
	score_two_id integer,
	created TIMESTAMP NOT NULL
);

CREATE TABLE IF NOT EXISTS scores (
	id serial PRIMARY KEY,
	user_id integer NOT NULL REFERENCES users(id),
	overall integer,
	created TIMESTAMP NOT NULL
);

CREATE TABLE IF NOT EXISTS challenge_pics (
	id serial PRIMARY KEY,
	file varchar NOT NULL, 
	created TIMESTAMP NOT NULL
);



