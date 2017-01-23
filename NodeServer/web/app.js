(function () {
    'use strict';

    angular.module('fyp', ['chart.js', 'ui.router', 'ui.bootstrap'])
        .config([
            '$urlRouterProvider',
            function ($urlRouterProvider) {
                // Set Default view
                $urlRouterProvider.otherwise('/charts');
            }])
})();