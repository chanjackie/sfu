var mongoose = require('mongoose');

mongoose.connect("mongodb://root:root@ds213229.mlab.com:13229/cmpt218");
var db = mongoose.connection;

//db.on('error', function(){});
db.once('open', function(){
  console.log('connection success');
});

// Schema is a constructor
var Schema = mongoose.Schema;
// instantiate the constructor
var userSchema = new Schema({
  uname: { type:String },
  age: { type:Number, min:[0,'not born yet'], max:120 },
  password: { type:String, minlength:4 }
});
// create a new model
var User = mongoose.model('user', userSchema);

var Bobby = new User({
   uname: "bobbyc",
   age: -2,
   password: "password"
});

Bobby.save(function(error) {
  if (error) {
    console.error(error);
  } else {
    console.log("Your user has been saved!");
  }
});
