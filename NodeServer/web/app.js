(function () {
    'use strict';

    angular.module('fyp', ['chart.js', 'ui.router', 'ui.bootstrap', 'smart-table'])
        .config([
            '$urlRouterProvider', '$stateProvider',
            function ($urlRouterProvider, $stateProvider) {
                // Set Default view
                $urlRouterProvider.otherwise('/rooms');

                $stateProvider
                    .state("rooms", {
                        url: "/rooms",
                        views: {
                            "main": {
                                templateUrl: "modules/roomController.html",
                                controller: "roomCtrl"
                            }
                        }
                    })

                    .state("charts", {
                        url: "/charts",
                        views: {
                            "main": {
                                templateUrl: 'modules/charts.html',
                                controller: 'chartsCtrl'
                            }
                        },
                        params: {
                            maxOccupancy: 15,
                            room: null
                        }
                    })
            }])
})();