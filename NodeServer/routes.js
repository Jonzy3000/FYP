apiQueries = require('./sqlApiQueries');

module.exports = {
    configure: function (app, express) {
        var router = express.Router();

        app.use('/fypApi', router);
        router.get('/', function (req, res) {
            res.json({ message: 'hooray! welcome to our api!' });
        });

        var counterURL = "/counter/"
        router.route(counterURL + "newRoom")
            .post(function (req, res) {
                apiQueries.newRoom(req, res);
            });

        router.route(counterURL + "updateCounter")
            .post(function (req, res) {
                apiQueries.updateCounter(req, res);
            });

        var roomsURL = "/rooms/"
        router.route(roomsURL + "allRooms")
            .get(function (req, res) {
                apiQueries.apiGetAllRooms(res);
            });

        router.route(roomsURL + "room")
            .get(function (req, res) {
                apiQueries.apiGetRoom(req, res);
            })

        router.route(roomsURL + "roomWithinDateRange")
            .get(function (req, res) {
                apiQueries.apiGetRoomWithinDateRange(req, res);
            });

        router.route(roomsURL + "roomWithDateRangeAndTimeRange")
            .get(function (req, res) {
                apiQueries.apiGetRoomWithDateRangeAndTimeRange(req, res);
            });

        router.route(roomsURL + "roomId")
            .get(function (req, res) {
                apiQueries.apiGetRoomID(req, res);
            });

        router.route(roomsURL + "generateRandomData")
            .get(function (req, res) {
                apiQueries.generateRandomData();
                res.send();
            });
    }
}