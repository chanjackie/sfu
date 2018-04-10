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
  con.query("create database if not exists "+db, function (err, result) {
   if (err) console.log(err);
   console.log(JSON.stringify(result));
  });
  con.query("use "+db, function (err, result, fields) {
   if (err) throw err;
   console.log(JSON.stringify(result));
  });
  con.query("create table if not exists users(id int auto_increment, fname varchar(10),lname varchar(10), age int, primary key(id))", function (err, result, fields) {
   if (err) throw err;
   console.log(JSON.stringify(result));
  });
  con.end();
});
