var events = require('events');
var EventEmitter = events.EventEmitter; // constructor

var util = require('util');

var User = function(fname,lname,age){ // constructor
  this.fname = fname;
  this.lname = lname;
  this.age = age;
}

util.inherits(User,EventEmitter);
// User inherits from EventEmitter

var u1 = new User('Bobby','Chan',24);
u1.on('poke', function(says){
  console.log(`${this.fname}: says ${says}`);
});

u1.emit('poke', 'HEY! What the @#$%');

// u1.removeListener('poke', callback);
