/**
 * Module dependencies.
 */

require('node-jsx').install();

var express = require('express'),
	exphbs  = require('express-handlebars'),
	session = require('express-session'),
	React = require('react'),
	compression = require('compression'),
	favicon = require('serve-favicon'),
	morgan = require('morgan'),
	methodOverride = require('method-override'),
	serveStatic = require('serve-static'),
	bodyParser = require('body-parser'),
	routes = require('./routes'),
	http = require('http'),
	path = require('path'),
	fs = require('fs');

let app = express();

let app_secret = fs.readFileSync('./credentials/app-secret.key'); 

// all environments

let PORT = process.env.PORT || 3000;

app.set('port', PORT);
app.set('views', path.join(__dirname, 'build/views/'));

app.engine('handlebars', exphbs({ }));
app.set('view engine', 'handlebars');

app.use(compression({ threshold: 512 }));
//app.use(favicon(__dirname + "/public/images/favicon.ico"));
app.use(morgan('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: true}));
app.use(methodOverride());
// app.use(session({ 
// 	secret: app_secret,
// 	resave: false,
// 	saveUninitialized: true,
// }));
//app.use(require('stylus').middleware(path.join(__dirname, 'public')));
//app.use(serveStatic('build/public'));
//app.use(favicon('build/public/favicon.ico'));

routes.bind(app);

http.createServer(app).listen(app.get('port'), function(){
  console.log('Express server listening on port ' + app.get('port'));
});
