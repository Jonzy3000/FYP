var mysql = require('mysql');
var Connection = function () {
    this.pool = null;

    this.acquire = function (callback) {
        this.pool.getConnection(function (err, connection) {
            callback(err, connection);
        });
    };

    //SQL INJECTION
    this.init = function () {
        this.pool = mysql.createPool({
            multipleStatements: true,
            connectionLimit: 20,
            host: 'localhost',
            user: 'root',
            password: 'fyp123',
            database: 'fyp_db'
        });

        this.createTableIfDoesNotExist();
    }

    this.roomsTableName = 'rooms';

    this.createTableIfDoesNotExist = function () {
        var _this = this;
        this.acquire(function (error, connection) {
            var query = "SELECT 1 FROM " + _this.roomsTableName + " LIMIT 1";
            connection.query(query, function (err) {
                connection.release();
                if (err) {
                    _this.createTable();
                }
            });
        })
    }

    this.createTable = function () {
        console.log("creating table");
        var _this = this;
        this.acquire(function (error, connection) {
            var query = 'CREATE TABLE ' + _this.roomsTableName + ' (id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255) UNIQUE, occupancy INT, maxOccupancy INT)';
            connection.query(query, function (err) {
                connection.release();
                if (err) {
                    console.error('error connecting: ' + err.stack);
                    return;
                }

                console.log("table created");
            })
        });
    }
}

module.exports = new Connection();