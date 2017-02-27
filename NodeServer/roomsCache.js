var RoomsCache = function() {
    var rooms = [];

    this.addRoom = function(name) {
        rooms.push(name);
    }

    this.doesRoomExist = function(name) {
        return rooms.indexOf(name) > -1;
    }

    this.getRooms = function() {
        return rooms;
    }
}

module.exports = new RoomsCache();