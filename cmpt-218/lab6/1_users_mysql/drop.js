var mysql = require('mysql');

var con = mysql.createConnection({
  host: "35.224.238.241",
  user: "root",
  password: "root",
});
var db = "c301310345"; // replace the string with "c<YOURSTUDENTID>"
con.connect(function(err) {
  if (err) throw err;
  console.log('connected as id ' + con.threadId);
  con.query("drop database "+db, function (err, result) {
   if (err) console.log(err);
   console.log(JSON.stringify(result));
  });
  con.end();
});
