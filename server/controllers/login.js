
let Facebook = require('facebook-node-sdk'),
	fs = require('fs'),
	db = require('../db.js'),
	users = require('../models/users.js');

let credentials = JSON.parse(fs.readFileSync('credentials/facebook-api.json'));

let facebook = new Facebook({ appID: credentials.app_id, secret: credentials.secret });

module.exports.facebookLogin = function (req, res) {
	facebook.api('/me', {}, function (err, fb_user) {
		if (err) {
			res.writeHead(403, { 'Content-Type': 'application/json' });
			res.end(JSON.stringify({
				error: true,
			}));
			return;
		}

		let user = users.fromFbid(fb_user.id);

		if (!user) {
			users.create({
				fbid: fb_user.id,
				first_name: fb_user.name,
			})
			.then(function () {
				users.fromUsername()
					.then(function (user) {
						res.writeHead(200, { 'Content-Type': 'application/json' });			
						res.end(JSON.stringify({
							id: user.id,
							username: user.username,
						}));
					});
			})
		}
		else {
			res.writeHead(200, { 'Content-Type': 'application/json' });
			res.end(JSON.stringify({
				id: user.id,
				username: user.username,
			}));
		}
	});
};




