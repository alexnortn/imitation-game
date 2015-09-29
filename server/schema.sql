CREATE TABLE IF NOT EXISTS users (
	id serial PRIMARY KEY,
	username varchar UNIQUE NOT NULL,
	first_name varchar,
	last_name varchar,
	fbid integer NOT NULL,
	created TIMESTAMP NOT NULL DEFAULT NOW(),
	deleted TIMESTAMP DEFAULT NULL
);

CREATE TABLE IF NOT EXISTS challenges (
	id serial PRIMARY KEY,
	user_one_id integer NOT NULL REFERENCES users(id),
	user_two_id integer REFERENCES users(id),
	step integer NOT NULL DEFAULT 1,
	score_one_id integer,
	score_two_id integer,
	created TIMESTAMP NOT NULL DEFAULT NOW()
);

CREATE TABLE IF NOT EXISTS scores (
	id serial PRIMARY KEY,
	user_id integer NOT NULL REFERENCES users(id),
	challenge_id integer NOT NULL REFERENCES challenges(id),
	joy integer NOT NULL,
	anger integer NOT NULL,
	fear integer NOT NULL,
	disgust integer NOT NULL,
	contempt integer NOT NULL,
	sadness integer NOT NULL,
	surprise integer NOT NULL,
	overall integer NOT NULL,
	created TIMESTAMP NOT NULL DEFAULT NOW()
);

CREATE TABLE IF NOT EXISTS challenge_pics (
	id serial PRIMARY KEY,
	file varchar NOT NULL, 
	created TIMESTAMP NOT NULL DEFAULT NOW()
);



