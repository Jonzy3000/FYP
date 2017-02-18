(function () {
    "use strict"

    var chartOptionsFactory = function () {
        return {
            options: {
                legend: {
                    display: true,
                },
                tooltips: {
                    callbacks: {
                        label: function (tooltipItem) {
                            return tooltipItem.yLabel + "%";
                        }
                    }
                },
                scales: {
                    yAxes: [
                        {
                            id: 'y-axis-1',
                            type: 'linear',
                            display: true,
                            position: 'left',
                            scaleLabel: {
                                display: true,
                                labelString: 'Occupancy (%)'
                            }
                        }
                    ],
                    xAxes: [{
                        type: 'time',
                        ticks: {
                            autoSkip: true,
                            maxTicksLimit: 15
                        },
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
            },
            colours: ["rgba(151,187,205,1)", "rgba(247,70,74,1)"]
        };
    }

    angular.module("fyp")
        .factory("chartOptionsFactory", chartOptionsFactory);
})();
