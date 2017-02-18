(function () {
    "use strict"

    var comapreDirective = function (roomsApi) {
        return {
            scope: {
                callback: '&'
            },
            templateUrl: 'modules/directives/compareDirective.html',
            link: function (scope, element, attrs) {
                console.log("hello");
                scope.rooms = [];
                roomsApi.getAllRooms().then(function (data) {
                    console.log(data);
                    scope.rooms = data.result;
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