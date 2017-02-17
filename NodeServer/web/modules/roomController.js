(function () {
    "use strict"

    var roomCtrl = function ($scope, $state, roomsApi, $interval) {
        /*
        TODO - auto refresh from server, uuid to check for new updates?
        */
        $scope.data = [
            { "name": "1W 1.1", "occupancy": 10, "maxOccupancy": 15 },
            { "name": "2E 1.1", "occupancy": 22, "maxOccupancy": 30 },
            { "name": "3W 4.1", "occupancy": 13, "maxOccupancy": 14 },
            { "name": "5 S1.1", "occupancy": 67, "maxOccupancy": 100 },
            { "name": "6N 2.1", "occupancy": 98, "maxOccupancy": 360 },
        ];

        roomsApi.getAllRooms().then(function (data) {
            console.log(data);
            $scope.data = $scope.data.concat(data.result);
        })

        $scope.goToRoom = function (roomName, maxOccupancy) {
            $interval.cancel(interval);
            interval = undefined;
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

        var transID = 0;
        var interval = $interval(function () {
            roomsApi.getAllRooms(transID).then(function (data) {
                transID = data.id
                if (data.result) {
                    $scope.data = $scope.data.concat(data.result);
                }
            })
        }, 1000)
    }

    angular
        .module("fyp")

        .controller("roomCtrl", roomCtrl)
        ;
})();
