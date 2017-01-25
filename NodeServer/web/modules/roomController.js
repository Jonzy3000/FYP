(function () {
    "use strict"

    var roomCtrl = function ($scope, $state, roomsApi) {
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

        $scope.goToRoom = function (roomName) {
            roomsApi.getRoom(roomName).then(function (data) {
                console.log(data);
                $state.go("charts", { room: roomName, data: data });
            })

        }

        $scope.getPercentage = function (n1, n2) {
            return Math.round((n1 / n2) * 100);
        }

        $scope.getters = {
            sortByPercentage: function (room) {
                return $scope.getPercentage(room.occupancy, room.maxOccupancy);
            }
        }
    }

    angular
        .module("fyp")

        .controller("roomCtrl", roomCtrl)
        ;
})();
