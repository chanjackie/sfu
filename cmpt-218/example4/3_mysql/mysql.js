var mysql = require('mysql');

var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password:"",
  database: "users"
});

con.connect(function(err){
  if (err) console.log(err);
  else console.log('connection: '+con.threadId);
});
