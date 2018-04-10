var bcrypt = require('bcrypt');

var h;
var passw = 'P@ssw0rd';

bcrypt.hash(passw, 10, function(err,hash){
  // Store paswd into db
  h = hash;
  console.log(hash);
});

process.stdin.on('data', function(data){
  // collect from db
  var entered_pw = data.toString().trim();
  bcrypt.compare(entered_pw, h, function(err,res){
    if(res){
      console.log("MATCH");
    } else {
      console.log("NOT MATCH");
    }
  });
});
