(function () {
    "use strict"

    var roomCtrl = function ($scope, $state) {
        console.log("hello");
        $scope.data = [
            { "room": "1W 1.1", "occupancy": 10, "max_occupancy": 15 },
            { "room": "2E 1.1", "occupancy": 22, "max_occupancy": 30 },
            { "room": "3W 4.1", "occupancy": 13, "max_occupancy": 14 },
            { "room": "5 S1.1", "occupancy": 67, "max_occupancy": 100 },
            { "room": "6N 2.1", "occupancy": 98, "max_occupancy": 360 },
        ];

        $scope.goToRoom = function () {
            $state.go("charts");
        }

        $scope.getPercentage = function (n1, n2) {
            return Math.round((n1 / n2) * 100);
        }

        $scope.getters = {
            sortByPercentage: function (room) {
                return $scope.getPercentage(room.occupancy, room.max_occupancy);
            }
        }
    }

    angular
        .module("fyp")

        .controller("roomCtrl", roomCtrl)
        ;
})();
