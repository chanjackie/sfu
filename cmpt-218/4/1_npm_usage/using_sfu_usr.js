var User = require('sfu_user');

var instr = new User("bobby", "chan", 24, 20000000);

instr.on('speak', function(words){
  this.say(words);
});

instr.emit('speak','HAHAHAHAHA');
