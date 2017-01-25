var express = require("express");
var connect = require('connect');
var serveStatic = require('serve-static');
var bodyParser = require('body-parser');
var myDb = require('./myDb');

app = express();

var bodyParser = require('body-parser');

// configure app to use bodyParser()
// this will let us get the data from a POST
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
var router = express.Router();

router.get('/', function(req, res) {
    res.json({ message: 'hooray! welcome to our api!' });   
});

app.use('/fypApi', router);

app.use(serveStatic("web")).listen(8080, function () {
    console.log('Server running on 8080...');
});