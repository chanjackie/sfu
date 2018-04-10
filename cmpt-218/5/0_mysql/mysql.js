var mysql = require('mysql');

var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password:"",
  database: "c218"
});

con.connect(function(err){
  if (err) throw err;
  console.log('connection: '+con.threadId);
});

con.query("select * from users", function(err,result,fields){
  if (err) console.log(err.sqlMessage);
  console.log(JSON.stringify(result));
  console.log(JSON.stringify(fields));
});
