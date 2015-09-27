

let pg = require('pg'),
	fs = require('fs');


let credentials = JSON.parse(fs.readFileSync('credentials/database.json'));

let conString = `postgres://${credentials.username}:${credentials.password}@localhost/imitation`;


//this initializes a connection pool
//it will keep idle connections open for a (configurable) 30 seconds
//and set a limit of 20 (also configurable)

module.exports.query = function (sql, binds) {
	binds = binds || [];

	let promise = new Promise(function (fufill, reject) {
		pg.connect(conString, function(err, client, done) {
			if (err) {
				reject(err);
				return console.error('error fetching client from pool', err);
			}

			setTimeout(function () {
				reject("timeout");
				done();
			}, 10000);

			client.query(sql, binds, function (err, result) {
				//call `done()` to release the client back to the pool
				done();

				if (err) {
					console.error(err);
					reject(err);
				}
				else{
					fufill(result.rows);
				}
			});
		});
	});

	return promise.catch(function (err) {
		console.error(err);
	});
};

module.exports.first = function (sql, binds) {
	return module.exports.query.apply(this, arguments)
		.then(function (rows) {
			return rows[0];
		});
};
