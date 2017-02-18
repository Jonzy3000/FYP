(function () {
    "use strict"

    var chartDataService = function () {
        var data = [];
        var labels = [];
        var numberOfDataPoints = 75;
        var maxOccupancy = 10;

        var getPercentage = function (val) {
            return Math.round(val / maxOccupancy * 100 * 10) / 10;
        }

        var smoothData = function (rawDisplayedData) {
            var step = Math.round(rawDisplayedData.length / numberOfDataPoints);
            var smoothedData = [];
            for (var i = 0, length = rawDisplayedData.length; i < length; i++) {
                if (i % step == 0) {
                    smoothedData.push(rawDisplayedData[i]);
                }
            }

            return smoothedData;
        }

        var averageDisplayedData = function (rawDisplayedData) {
            labels = [];
            data = [];

            rawDisplayedData = _.sortBy(rawDisplayedData, 'date');
            if (rawDisplayedData.length > numberOfDataPoints) {
                rawDisplayedData = smoothData(rawDisplayedData);
            }

            for (var i = 0; i < rawDisplayedData.length; i++) {
                labels.push(moment(rawDisplayedData[i].date));
                data.push(getPercentage(rawDisplayedData[i].occupancy));
            }

            return { data: data, labels: labels };
        }

        var isDateToBeDispalyed = function (dateDiff, startDate, dateThreshold) {
            return dateDiff > 0 && dateThreshold - startDate >= dateDiff;
        }

        this.updateData = function (data, startDate, dateThreshold, maxOccupancy_) {
            maxOccupancy = maxOccupancy_;
            var rawDisplayedData = _.filter(data, function (entry) {
                var dateDiff = entry.date - startDate;
                return isDateToBeDispalyed(dateDiff, startDate, dateThreshold);
            });

            console.log(rawDisplayedData.length);
            return averageDisplayedData(rawDisplayedData);
        }


    }

    angular.module("fyp")
        .service("chartDataService", chartDataService)
})();