(function () {
    var myDb = function () {
        var mysql = require('mysql');
        var connection = mysql.createConnection({
            host: 'localhost',
            user: 'root',
            password: 'fyp123',
            database: 'fyp_db'
        });

        var createConnection = function () {
            connection.connect(function (err) {
                if (err) {
                    console.error('error connecting: ' + err.stack);
                    return;
                }

                console.log('connected as id ' + connection.threadId);
            });
        }

        var createTableIfDoesNotExist = function () {
            var query = "SELECT 1 FROM testtable LIMIT 1";
            connection.query(query, function (err) {
                if (err) {
                    createTable();
                }
            })
        }

        var createTable = function () {
            console.log("creating table");
            var query = 'CREATE TABLE rooms (id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, name TEXT, max_occupancy INT)';
            connection.query(query, function (err) {
                if (err) {
                    console.error('error connecting: ' + err.stack);
                    return;
                }

                console.log("table created");
            })
        }

        createConnection();
        createTableIfDoesNotExist();
    }

    module.exports.getDbConnection = function () {
        console.log("HELLO");
        return myDb();
    }
} ());