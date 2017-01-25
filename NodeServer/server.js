var express = require("express");
var connect = require('connect');
var serveStatic = require('serve-static');
var bodyParser = require('body-parser');
var connection = require('./sqlPoolConnection');
var routes = require('./routes');

app = express();

//https://scotch.io/tutorials/build-a-restful-api-using-node-and-express-4
var bodyParser = require('body-parser');

// configure app to use bodyParser()
// this will let us get the data from a POST
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

connection.init();
routes.configure(app, express);

app.use(serveStatic("web")).listen(8080, function () {
    console.log('Server running on 8080...');
});