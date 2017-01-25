var connection = require('./sqlPoolConnection');

function SqlApiQueries() {
    var roomsTableName = connection.roomsTableName;
    this.newRoom = function (req, res) {
        console.log(req.body);
        var roomName = sanitizeRoomName(req.body.name);
        var maxOccupancy = req.body.maxOccupancy;
        var occupancy = 0;
        getRowOfRoom(roomName, function (result) {
            connection.acquire(function (err, con) {
                if (!result.length) {
                    var query = "INSERT INTO " + roomsTableName + " VALUES(NULL,?,?,?)";
                    con.query(query, [roomName, occupancy, maxOccupancy], createRoomCounterTable.bind(null, con, roomName));
                } else {
                    var id = result[0].id;
                    var query = "UPDATE " + roomsTableName + " SET maxOccupancy = ? WHERE ID = ?";
                    con.query(query, [maxOccupancy, id], handleQueryResult.bind(null, con));
                }
            });
        });

        res.send();
    }

    var jsStringDateToMySQLDate = function (date) {
        return new Date(date).toISOString().slice(0, 19).replace('T', ' ');
    }

    this.updateCounter = function (req, res) {
        var roomName = sanitizeRoomName(req.body.name);
        var incrementBy = req.body.incrementBy;
        var timestamp = jsStringDateToMySQLDate(new Date());

        //TODO PARSE TIMESTAMP TO VALID;

        getRowOfRoom(roomName, function (result) {
            connection.acquire(function (err, con) {
                if (!result) {
                    console.log("CANNOT FIND ROOM " + roomName);
                    return
                }

                var occupancy = Number(result[0].occupancy) + Number(incrementBy);
                var id = result[0].id;
                var query = "UPDATE " + roomsTableName + " SET occupancy = ? WHERE ID = ? ;"
                query += " INSERT INTO `" + roomName + "` VALUES(NULL,?,?) "
                con.query(query, [occupancy, id, timestamp, occupancy], handleQueryResult.bind(null, con));

            });
        });

        res.send();
    }

    //TODO tidy thesse as only query is different
    this.apiGetAllRooms = function (res) {
        connection.acquire(function (err, con) {
            var query = "SELECT * FROM " + roomsTableName;
            con.query(query, function (err, result) {
                con.release();
                res.send(result);
            })
        })
    }

    this.apiGetRoom = function (req, res) {
        connection.acquire(function (err, con) {
            if (req.query.name == null) {
                con.release();
                res.send();
                return;
            }

            var roomName = sanitizeRoomName(req.query.name);
            var query = "SELECT * FROM `" + roomName + "`";
            con.query(query, function (err, result) {
                con.release();
                res.send(result);
            })

        });
    }

    this.apiGetRoomWithinDateRange = function (req, res) {
        connection.acquire(function (err, con) {
            var startDate = jsStringDateToMySQLDate(req.query.startDate);
            var endDate = jsStringDateToMySQLDate(req.query.endDate);
            var query = "SELECT * FROM `" + roomName + "`  WHERE timestamp > ? AND timestamp < ?";
            con.query(query, [startDate, endDate], function (err, result) {
                con.release();
                res.send(result);
            })
        })
    }

    var sanitizeRoomName = function (room) {
        return room.toLowerCase().trim();
    }

    var createRoomCounterTable = function (con, roomName, err) {
        if (err) {
            console.error(err.stack);
            con.release();
            return;
        }

        var query = "CREATE TABLE `" + roomName + "` (id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, timestamp DATETIME, occupancy INT)";

        con.query(query, handleQueryResult.bind(null, con));
    }

    //HELPERS
    var getIdOfRoom = function (room, callback) {
        room = room.toLowerCase().trim();
        var query = "SELECT ID FROM " + roomsTableName + "WHERE name = " + room;
        connection.acquire(function (err, con) {
            con.query(query, function (err, result) {
                con.release();
                callback(result);
            })
        })
    }

    var getRowOfRoom = function (room, callback) {
        room = room.toLowerCase().trim();
        var query = "SELECT * FROM " + roomsTableName + " WHERE name = ?";
        connection.acquire(function (err, con) {
            con.query(query, [room], function (err, result) {
                con.release();
                callback(result);
            })
        })
    }

    var handleQueryResult = function (con, err, result) {
        con.release();
        if (err) {
            console.error('error' + err.stack)
        }
    }
}

module.exports = new SqlApiQueries();