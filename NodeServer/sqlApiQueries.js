var connection = require('./sqlPoolConnection');
var roomsCache = require('./roomsCache');

function SqlApiQueries() {
    var uuid = function () {
        return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
            var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
            return v.toString(16);
        });
    }

    var updateTransID = function () {
        transID = uuid;
    }

    var transID = uuid();

    var roomsTableName = connection.roomsTableName;

    function onStartup() {
        /*
            TODO - create local map that we call on start up and keep rooms there so we know if a room is in a db or not
        */
        var updateRoomsCache = function () {
            getAllCurrentTables(function (err, result) {
                if (err) {
                    return;
                }

                for (var i = 0; i < result.length; i++) {
                    var room = result[i];
                    roomsCache.addRoom(room.TABLE_NAME);
                }
            });
        }

        var getAllCurrentTables = function (callback) {
            connection.acquire(function (err, con) {
                var query = "SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE = 'BASE TABLE' AND TABLE_SCHEMA= 'fyp_db'";
                con.query(query, function (err, result) {
                    con.release();
                    callback(err, result);
                })
            })
        }

        return {
            "updateRoomsCache" : updateRoomsCache,
        }
    }

    onStartup().updateRoomsCache();

    this.newRoom = function (req, res) {
        console.log(req.body);
        var roomName = sanitizeRoomName(req.body.name);
        var maxOccupancy = req.body.maxOccupancy;
        var occupancy = 0;

        connection.acquire(function (err, con) {
            if (roomsCache.doesRoomExist(roomName)) {
                createRoomCounterTable(con, roomName, err);
                var query = "INSERT INTO " + roomsTableName + " VALUES(NULL,?,?,?) ";
                query += "CREATE TABLE `" + roomName + "` (id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY, timestamp DATETIME, occupancy INT)";
                con.query(query, [roomName, occupancy, maxOccupancy], function (err, result) {
                    con.release();
                    if (err) {
                        console.log(err);
                    }

                    roomsCache.addRoom(roomName);
                });
            } else {
                var id = result[0].id;
                var query = "UPDATE " + roomsTableName + " SET maxOccupancy = ? WHERE ID = ?";
                con.query(query, [maxOccupancy, id], handleQueryResult.bind(null, con));
            }
        });

        if (res) {
            res.send();
        }
    }

    var jsStringDateToMySQLDate = function (date) {
        return new Date(date).toISOString().slice(0, 19).replace('T', ' ');
    }

    this.updateCounter = function (req, res) {
        var roomName = sanitizeRoomName(req.body.name);
        var incrementBy = req.body.incrementBy;
        var date = req.body.date ? req.body.date : new Date();
        var timestamp = jsStringDateToMySQLDate(date);

        //TODO PARSE TIMESTAMP TO VALID;
        if (roomsCache.doesRoomExist(roomName)) {
            getRowOfRoom(roomName, function (result) {
                connection.acquire(function (err, con) {
                    if (err) {
                        console.log(err);
                        return;
                    }

                    if (!result) {
                        console.log("CANNOT FIND ROOM " + roomName);
                        con.release();
                        return;
                    }

                    updateTransID();
                    if (result.length > 0) {
                        var occupancy = Number(result[0].occupancy) + Number(incrementBy);
                        var id = result[0].id;
                        var query = "UPDATE " + roomsTableName + " SET occupancy = ? WHERE ID = ? ;"
                        query += " INSERT INTO `" + roomName + "` VALUES(NULL,?,?) "
                        con.query(query, [occupancy, id, timestamp, occupancy], handleQueryResult.bind(null, con));
                    }

                });
            });
        }

        if (res) {
            res.send();
        }
    }

    //TODO tidy thesse as only query is different
    this.apiGetAllRooms = function (req, res) {
        connection.acquire(function (err, con) {
            if (err) {
                console.log(err);
                res.send();
                return;
            }

            if (req.query.id == transID) {
                res.send({ id: transID });
                con.release();
                return;
            }

            var query = "SELECT * FROM " + roomsTableName;
            con.query(query, function (err, result) {
                con.release();
                res.send({ id: transID, result: result });
            })
        })
    }

    this.apiGetRoom = function (req, res) {
        connection.acquire(function (err, con) {
            if (err) {
                console.log(err);
                res.send();
                return;
            }
            if (req.query.name == null) {
                con.release();
                res.send();
                return;
            }

            if (req.query.id == transID) {
                res.send({ id: transID });
                return
            }

            var roomName = sanitizeRoomName(req.query.name);
            var query = "SELECT * FROM `" + roomName + "`";
            console.time("test");
            con.query(query, function (err, result) {
                console.timeEnd("test");
                con.release();
                res.send({ id: transID, result: result });
                
            })

        });
    }

    this.apiGetRoomWithinDateRange = function (req, res) {
        connection.acquire(function (err, con) {
            if (err) {
                console.log(err);
                res.send();
                return;
            }

            if (req.query.id == transID) {
                res.send({ id: transID });
                con.release();
                return;
            }

            var startDate = jsStringDateToMySQLDate(req.query.startDate);
            var endDate = jsStringDateToMySQLDate(req.query.endDate);
            var roomName = sanitizeRoomName(req.query.name);

            var query = "SELECT * FROM `" + roomName + "`  WHERE timestamp > ? AND timestamp < ?";
            con.query(query, [startDate, endDate], function (err, result) {
                con.release();
                res.send({ id: transID, result: result });
            })
        })
    }

    var sanitizeRoomName = function (room) {
        return room.toLowerCase().trim();
    }

    //HELPERS
    var getIdOfRoom = function (room, callback) {
        room = room.toLowerCase().trim();
        var query = "SELECT ID FROM " + roomsTableName + "WHERE name = " + room;
        connection.acquire(function (err, con) {
            if (err) {
                con.release();
                console.log(err);
                callback();

            }
            con.query(query, function (err, result) {
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

    var randomDate = function (start, end) {
        return new Date(start.getTime() + Math.random() * (end.getTime() - start.getTime()));
    }

    var randomSingedNumber = function (between) {
        return (Math.random() < 0.5 ? -1 : 1) * Math.round(Math.random() * between);
    }

    this.generateRandomData = function (test, res) {
        var roomName = "4E 1.2";
        var _this = this;
        var req = {
            "body": {
                "maxOccupancy": 160,
                "name": roomName
            }
        }

        _this.newRoom(req);
        for (var i = 0; i < 10000; i++) {
            var date = randomDate(new Date("2016"), new Date());
            var req = {
                "body": {
                    "name": roomName,
                    "date": date,
                    "incrementBy": randomSingedNumber(5)
                }
            }

            try {
                _this.updateCounter(req, res);
            } catch (err) {
                console.log(err);
            }
        }
    }
}

module.exports = new SqlApiQueries();