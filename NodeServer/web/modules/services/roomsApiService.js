(function () {
    "use strict"

    var roomsApiService = function ($http) {
        var path = "fypApi/rooms/";

        var getData = function (r) {
            return r.data;
        }

        this.getAllRooms = function () {
            return $http.get(path + "allRooms").then(getData);
        }

        this.getRoom = function (name) {
            console.log(name);
            return $http.get(path + "room", { params: { name: name } }).then(getData);
        }

        this.getRoomWithDateRange = function (name, startDate, endDate) {
            return $http.get(path + "roomWithinDateRange", { params: { name: name, startDate: startDate, endDate: endDate } }).then(getData);
        }

        this.generateRandomData = function () {
            return $http.get(path + "generateRandomData");
        }
    }

    angular.module("fyp")
        .service("roomsApi", roomsApiService)
        ;
})();