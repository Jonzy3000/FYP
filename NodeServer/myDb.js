(function () {
    var myDb = function () {
        var fs = require("fs");
        var file = "test.db";
        var sqlite3 = require("sqlite3").verbose();
        var db = new sqlite3.Database(file);
    }

    module.exports.getDbConnection = function () {
        console.log("HELLO");
        return myDb();
    }
} ());