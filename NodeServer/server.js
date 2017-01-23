var connect = require('connect');
var serveStatic = require('serve-static');
var myDb = require('./myDb');
var app = connect().use(serveStatic("web")).listen(8080, function () {
    console.log('Server running on 8080...');
    console.log(myDb);
    console.log(myDb.getDbConnection());
});