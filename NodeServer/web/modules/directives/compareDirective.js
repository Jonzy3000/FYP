(function () {
    "use strict"

    var comapreDirective = function (roomsApi) {
        return {
            scope: {
                callback: '&',
                ignore: '='
            },
            templateUrl: 'modules/directives/compareDirective.html',
            link: function (scope, element, attrs) {
                console.log("hello");
                scope.rooms = [];
                roomsApi.getAllRooms().then(function (data) {
                    console.log(data);
                    scope.rooms = _.filter(data.result, function (room) {
                        return room.name != scope.ignore;
                    });

                });

                scope.compareRoom = function (room) {
                    scope.callback({ rooms: [room] });
                }
            }
        }
    }

    angular.module("fyp")
        .directive("compareDirective", comapreDirective);
})();