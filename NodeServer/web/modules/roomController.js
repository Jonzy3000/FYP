(function () {
    "use strict"

    var roomCtrl = function ($scope, $state, roomsApi) {
        var uuid = function () {
            return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
                var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
                return v.toString(16);
            });
        }

        /*
        TODO - auto refresh from server, uuid to check for new updates?
        */
        console.log("hello");
        $scope.data = [
            { "name": "1W 1.1", "occupancy": 10, "maxOccupancy": 15 },
            { "name": "2E 1.1", "occupancy": 22, "maxOccupancy": 30 },
            { "name": "3W 4.1", "occupancy": 13, "maxOccupancy": 14 },
            { "name": "5 S1.1", "occupancy": 67, "maxOccupancy": 100 },
            { "name": "6N 2.1", "occupancy": 98, "maxOccupancy": 360 },
        ];

        roomsApi.getAllRooms().then(function (data) {
            console.log(data);
            $scope.data = $scope.data.concat(data);
        })

        $scope.goToRoom = function (roomName, maxOccupancy) {
            $state.go("charts", { room: roomName, maxOccupancy: maxOccupancy });
        }

        $scope.getPercentage = function (n1, n2) {
            return Math.round((n1 / n2) * 100);
        }

        $scope.getters = {
            sortByPercentage: function (room) {
                return $scope.getPercentage(room.occupancy, room.maxOccupancy);
            }
        }

        $scope.generateRandomData = function () {
            roomsApi.generateRandomData();
        }
    }

    angular
        .module("fyp")

        .controller("roomCtrl", roomCtrl)
        ;
})();
