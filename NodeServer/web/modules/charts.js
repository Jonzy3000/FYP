(function () {
    "use strict"

    var chartsCtrl = function ($scope, $state, roomsApi, $interval, chartDataService, chartOptionsFactory) {
        $scope.roomName = $state.params.room;
        var maxOccupancy = $state.params.maxOccupancy;
        if ($scope.roomName == null || $scope.roomName == 'default') {
            $scope.roomName = localStorage.getItem("roomName");
            maxOccupancy = localStorage.getItem("maxOccupancy");
        }

        $scope.onUpdateOfRoomsToCompare = function (roomsToCompare) {
            console.log(roomsToCompare);
            if (roomsToCompare.length > 0) {
                roomsApi.getRoom(roomsToCompare[0].name).then(function (data) {
                    if (data.result) {
                        $scope.compareData = _.sortBy(data.result, 'date');
                        $scope.compareData = convertTimeStampsToDate($scope.compareData);

                        if ($scope.series.length > 1) {
                            $scope.series.pop();
                        }

                        $scope.series.push(roomsToCompare[0].name);
                        $scope.updateData();
                    }
                });
            }
        }

        localStorage.setItem("roomName", $scope.roomName);
        localStorage.setItem("maxOccupancy", maxOccupancy);

        $scope.startDateOpened = false;
        $scope.openStartDate = function () {
            $scope.startDateOpened = true;
        }

        var onNewData = function (data) {
            transID = data.id;
            if (data.result && data.result.length > 0) {
                var newData = convertTimeStampsToDate(data.result);
                $scope.data = $scope.data.concat(data.result);
                _.sortBy($scope.data, 'date');
                $scope.updateData();
            }
        }

        var transID = 0;
        roomsApi.getRoom($scope.roomName, transID).then(function (data) {
            transID = data.id;
            if (data.result) {
                $scope.data = data.result;
                $scope.data = convertTimeStampsToDate($scope.data);
                _.sortBy($scope.data, 'date');
                $scope.updateData();
            }
        });

        var interval = $interval(function () {
            if ($scope.data.length > 0) {
                roomsApi.getRoomWithDateRange($scope.roomName, $scope.data[$scope.data.length - 1].date, new Date(), transID)
                    .then(onNewData);
            }
        }, 5000);

        //http://www.chartjs.org/docs/#time-scale

        $scope.startDate = new Date();
        $scope.startDate.setHours(0, 0, 0, 0);

        var dateThreshold;

        $scope.updateData = function () {
            var data = chartDataService.updateData($scope.data, $scope.startDate, dateThreshold, maxOccupancy);
            $scope.labels = data.labels;
            $scope.displayedData = [data.data];
            if ($scope.compareData) {
                data = chartDataService.updateData($scope.compareData, $scope.startDate, dateThreshold, maxOccupancy);
                $scope.displayedData.push(data.data);
            }
        }

        function addDays(date, days) {
            var result = new Date(date);
            result.setDate(result.getDate() + days);
            return result;
        }

        function addWeeks(date, weeks) {
            var result = new Date(date);
            return addDays(result, weeks * 7);
        }

        function addMonths(date, months) {
            var result = new Date(date);
            return result.setMonth(date.getMonth() + months);
        }

        function addYears(date, years) {
            var result = new Date(date);
            return result.setFullYear(date.getFullYear() + years);
        }

        $scope.updateGraphAxis = function (option) {
            $scope.graphXAxisConfig = option;
            console.log($scope.graphXAxisConfig);
            switch (option) {
                case "Day":
                    $scope.options.scales.xAxes[0].time.unit = "hour";
                    dateThreshold = addDays($scope.startDate, 1);
                    break;
                case "Week":
                    $scope.options.scales.xAxes[0].time.unit = "day";
                    dateThreshold = addWeeks($scope.startDate, 1);
                    break;
                case "Month":
                    $scope.options.scales.xAxes[0].time.unit = "day";
                    dateThreshold = addMonths($scope.startDate, 1);
                    break;
                case "Year":
                    $scope.options.scales.xAxes[0].time.unit = "month";
                    dateThreshold = addYears($scope.startDate, 1);
                    break;
            }

            $scope.updateData();
        }

        var convertTimeStampsToDate = function (data) {
            _.each(data, function (entry) {
                if (entry.timestamp == null) {
                    return;
                }

                entry.date = new Date(entry.timestamp);
            });

            return data;
        }

        $scope.back = function () {
            $interval.cancel(interval);
            interval = undefined;
            $state.go("rooms");
        }

        $scope.graphXAxisOptions = ["Day", "Week", "Month", "Year"];
        $scope.graphXAxisConfig = $scope.graphXAxisOptions[0];

        dateThreshold = addDays($scope.startDate, 1);

        $scope.series = [
            $scope.roomName
        ];

        $scope.options = chartOptionsFactory.options;
        $scope.colours = chartOptionsFactory.colours;

        $scope.updateGraphAxis($scope.graphXAxisConfig);
    };

    angular
        .module("fyp")
        .controller("chartsCtrl", chartsCtrl)
        ;
})();