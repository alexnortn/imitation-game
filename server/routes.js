
let controllers = require('./controllers');

module.exports.bind = function (app) {
	app.post('/login', controllers.login.facebookLogin);

	app.get('/players/', controllers.players.list);

	app.get('/challenge/issue', controllers.challenge.issue);
	
	app.get('/challenge/result', controllers.challenge.issue);
	app.post('/challenge/result', controllers.challenge.issue);
};