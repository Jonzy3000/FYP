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
            .post(apiQueries.newRoom);

        router.route(counterURL + "updateCounter")
            .post(apiQueries.updateCounter);

        var roomsURL = "/rooms/"
        router.route(roomsURL + "allRooms")
            .get(apiQueries.apiGetAllRooms);

        router.route(roomsURL + "room")
            .get(apiQueries.apiGetRoom)

        router.route(roomsURL + "roomWithinDateRange")
            .get(apiQueries.apiGetRoomWithinDateRange);

        // router.route(roomsURL + "roomWithDateRangeAndTimeRange")
        //     .get(apiQueries.apiGetRoomWithDateRangeAndTimeRange);

        // router.route(roomsURL + "roomId")
        //     .get(apiQueries.apiGetRoomID);

        router.route(roomsURL + "generateRandomData")
            .get(function (req, res) {
                apiQueries.generateRandomData();
                res.send();
            });
    }
}