(function () {
    "use strict"

    var roomsApiService = function ($http) {
        var path = "fypApi/rooms/";

        var getData = function (r) {
            return r.data;
        }

        this.getAllRooms = function (id) {
            return $http.get(path + "allRooms", { params: { id: id } }).then(getData);
        }

        this.getRoom = function (name, id) {
            console.log(name);
            return $http.get(path + "room", { params: { name: name, id: id } }).then(getData);
        }

        this.getRoomWithDateRange = function (name, startDate, endDate, id) {
            return $http.get(path + "roomWithinDateRange", { params: { name: name, startDate: startDate, endDate: endDate, id: id } }).then(getData);
        }

        this.generateRandomData = function () {
            return $http.get(path + "generateRandomData");
        }
    }

    angular.module("fyp")
        .service("roomsApi", roomsApiService)
        ;
})();