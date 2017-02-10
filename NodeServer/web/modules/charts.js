(function () {
    "use strict"

    var chartsCtrl = function ($scope, $state, roomsApi) {
        $scope.roomName = $state.params.room;
        var maxOccupancy = $state.params.maxOccupancy;
        console.log(maxOccupancy);
        if ($scope.roomName == null || $scope.roomName == 'default') {
            $scope.roomName = localStorage.getItem("roomName");
        }

        localStorage.setItem("roomName", $scope.roomName);

        $scope.startDateOpened = false;
        $scope.openStartDate = function () {
            $scope.startDateOpened = true;
        }

        roomsApi.getRoom($scope.roomName).then(function (data) {
            $scope.data = data;
            convertTimeStampsToDate();
        });

        //http://www.chartjs.org/docs/#time-scale

        $scope.now = $scope.startDate = new Date();
        $scope.startDate.setHours(0, 0, 0, 0);

        var dateThreshold;
        var numberOfDataPoints = 50;

        var isDateToBeDispalyed = function (dateDiff) {
            return dateDiff > 0 && dateThreshold - $scope.startDate >= dateDiff;
        }

        var smoothData = function (rawDisplayedData) {
            var step = rawDisplayedData.length / numberOfDataPoints;
            var smoothedData = [];
            for (var i = 0, length = rawDisplayedData.length; i < length; i += step) {
                var index = Math.round(i);

                if (index >= rawDisplayedData.length) {
                    break;
                }

                smoothedData.push(rawDisplayedData[index]);
            }

            return smoothedData;
        }

        var averageDisplayedData = function (rawDisplayedData) {
            $scope.labels = [];
            $scope.displayedData = [[]];

            rawDisplayedData = _.sortBy(rawDisplayedData, 'date');
            if (rawDisplayedData.length > numberOfDataPoints) {
                rawDisplayedData = smoothData(rawDisplayedData);
            }

            for (var i = 0; i < rawDisplayedData.length; i++) {
                $scope.labels.push(moment(rawDisplayedData[i].date));
                $scope.displayedData[0].push(rawDisplayedData[i].occupancy);
            }
        }

        $scope.updateData = function () {
            var rawDisplayedData = _.filter($scope.data, function (entry) {
                var dateDiff = entry.date - $scope.startDate;
                return isDateToBeDispalyed(dateDiff);
            });

            console.log(rawDisplayedData.length);
            averageDisplayedData(rawDisplayedData);
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
                    $scope.options.scales.xAxes[0].time.unit = "week";
                    dateThreshold = addMonths($scope.startDate, 1);
                    break;
                case "Year":
                    $scope.options.scales.xAxes[0].time.unit = "month";
                    dateThreshold = addYears($scope.startDate, 1);
                    break;
            }

            $scope.updateData();
        }

        var convertTimeStampsToDate = function () {
            _.each($scope.data, function (entry) {
                if (entry.timestamp == null) {
                    return;
                }

                entry.date = new Date(entry.timestamp);
            })
        }

        $scope.back = function () {
            $state.go("rooms");
        }

        $scope.graphXAxisOptions = ["Day", "Week", "Month", "Year"];
        $scope.graphXAxisConfig = $scope.graphXAxisOptions[0];

        dateThreshold = addDays($scope.startDate, 1);
        $scope.options = {
            scales: {
                yAxes: [
                    {
                        id: 'y-axis-1',
                        type: 'linear',
                        display: true,
                        position: 'left'
                    }
                ],
                xAxes: [{
                    type: 'time',
                    time: {
                        unit: 'month',
                        displayFormats: {
                            hour: 'H:mm',
                            day: 'ddd Do MMM',
                            week: 'ddd Do MMM'
                        }
                    }
                }]
            }
        };
    };

    angular
        .module("fyp")
        .controller("chartsCtrl", chartsCtrl)
        ;
})();