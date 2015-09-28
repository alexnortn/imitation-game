
let db = require('../db.js'),
	users = require('../models/users.js');

module.exports.list = function (req, res) {
	users.all()
		.then(function (rows) {

			let output = rows.map(function (row) {
				return {
					username: row.username,
					first_name: row.first_name,
					last_name: row.last_name,
				};
			});

			res.writeHead(200, { 'Content-Type': 'application/json' });
			res.end(JSON.stringify(output));
		})
		.catch(function (error) {
			res.end("An error occured.");
		});
};