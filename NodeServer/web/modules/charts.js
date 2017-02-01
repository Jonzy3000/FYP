(function () {
    "use strict"

    var chartsCtrl = function ($scope, $state) {
        $scope.room = $state.params.room;
        $scope.data = $state.params.data;
        $scope.startDateOpened = false;
        $scope.openStartDate = function () {
            updateData();
            $scope.startDateOpened = true;
        }
        $scope.now = $scope.startDate = new Date();

        $scope.updateGraphAxis = function (option) {
            $scope.graphXAxisConfig = option;
            console.log($scope.graphXAxisConfig);
            switch (option) {
                case "Day":
                    $scope.labels = $scope.dayView;
                    break;
                case "Week":
                    $scope.labels = $scope.weekView;
                    break;
                case "Month":
                    $scope.labels = $scope.weekView.concat($scope.weekView.concat($scope.weekView.concat($scope.weekView)));
                    break;
                case "Year":
                    $scope.labels = $scope.yearView;
                    break;
            }
            //add some clever logic;
            // var diffOfDates = new Date($scope.endDate - $scop.startDate);
        }

        var convertTimeStampsToDate = function () {
            _.each($scope.data, function (entry) {
                if (entry.timestamp == null) {
                    return;
                }

                entry.date = new Date(entry.timestamp);
            })
        }

        convertTimeStampsToDate();
        console.log($scope.data);

        $scope.back = function () {
            $state.go("rooms");
        }

        $scope.yearView = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
        $scope.weekView = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"];
        $scope.dayView = ["7:00", "8:00", "9:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00", "18:00", "19:00", "20:00"];

        $scope.graphXAxisOptions = ["Day", "Week", "Month", "Year"];
        $scope.graphXAxisConfig = $scope.graphXAxisOptions[0];


        $scope.labels = ["January", "February", "March", "April", "May", "June", "July"];
        $scope.data = [
            [28, 100, 40, 19, 86, 27, 90]
        ];
        $scope.onClick = function (points, evt) {
            console.log(points, evt);
        };
        $scope.options = {
            scales: {
                yAxes: [
                    {
                        id: 'y-axis-1',
                        type: 'linear',
                        display: true,
                        position: 'left'
                    }
                ]
            }
        };
    };

    angular
        .module("fyp")
        .controller("chartsCtrl", chartsCtrl)
        ;
})();