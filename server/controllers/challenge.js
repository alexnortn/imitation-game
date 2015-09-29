
let db = require('../db.js'),
	challengeModel = require('../models/challenge.js');


module.exports.issue = function (req, res) {
	challengeModel.create({
		user_one_id: req.body.from,
		user_two_id: req.body.to,
		step: 1,
	});

	// notify the other player
};

module.exports.score = function (req, res) {
	challengeModel.applyScore({
		challenge_id: req.query.challenge_id,
		user_id: req.query.user_id,
		joy: req.query.joy,
		anger: req.query.anger,
		fear: req.query.fear,
		disgust: req.query.disgust,
		contempt: req.query.contempt,
		sadness: req.query.sadness,
		surprise: req.query.surprise,
		overall: req.query.overall,
	})
	.then(function (rows) {
		res.writeHead(200);
		res.end(JSON.stringify({ ok: true }));
	})
	.catch(function (err) {
		res.writeHead(500);
	});
};

module.exports.result = function (req, res) {
	challengeModel.fetchScore()
		.then(function (results) {
			res.writeHead(200);
			res.end(JSON.stringify(results));
		});
};






