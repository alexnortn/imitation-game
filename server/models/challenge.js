
let db = require('../db.js');

module.exports.create = function (spec) {
	args = args || {};

	let dml = norm()
		.insert("challenges")
		.values(args.spec);

	return db.query(dml.sql(), dml.binds());
};

module.exports.applyScore = function (spec) {
	let dml = norm()
		.insert("scores")
		.values(spec);

	return db.query(dml.sql(), dml.binds());
};

module.exports.fetchScores = function (challenge_id) {
	let dml = norm()
		.select("*")
		.from("scores")
		.where("challenge_id = ?", challenge_id);

	return db.query(dml.sql(), dml.binds());
};



