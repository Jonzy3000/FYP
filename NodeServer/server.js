var express = require("express");
var connect = require('connect');
var serveStatic = require('serve-static');
var bodyParser = require('body-parser');
var connection = require('./sqlPoolConnection');

app = express();

//https://scotch.io/tutorials/build-a-restful-api-using-node-and-express-4
// https://scotch.io/tutorials/use-expressjs-to-get-url-and-post-parameters
// http://www.yogasaikrishna.com/simple-restful-api-using-nodejs-express-and-mysql/
var bodyParser = require('body-parser');

// configure app to use bodyParser()
// this will let us get the data from a POST
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

connection.init();

var routes = require('./routes');
routes.configure(app, express);

app.use(serveStatic("web")).listen(8080, function () {
    console.log('Server running on 8080...');
});