
let db = require('../db.js'),
	norm = require('norm-sql'),
	co = require('co');

module.exports.create = function (spec) {
	args = args || {};

	var dml = norm()
		.insert("users")
		.values(args.spec);

	return db.query(dml.sql(), dml.binds());
};

module.exports.fromId = function (id) {
	let sql = norm()
		.select("*")
		.from("users")
		.where(
			[ "id = ?", id ]
		)

	return db.first(sql.sql(), sql.binds());
};

module.exports.fromUsername = function (username) {
	let sql = norm()
		.select("*")
		.from("users")
		.where(
			["username = ?", username]
		)

	return db.first(sql.sql(), sql.binds());
};

module.exports.all = function () {
	return db.query(`select * from users`);
};

