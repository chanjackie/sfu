// users-api

var express = require('express');
var app = express();
var serverIndex = require('serve-index');
var http = require('http');
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

var port = process.env.PORT || 3000;
var users = [];

// parsing body
app.use(express.json());
app.use(express.urlencoded( { extended:false} ));

var options = {
  dotfiles: 'ignore',
  etag: false,
  extensions: ['htm','html'],
  index: "start.html"
}

app.use('/', function(req,res,next){
  console.log(req.method, 'request:', req.url, JSON.stringify(req.body));
  next();
});

// app.all('/', function(req,res,next){
//   console.log('Accessing root folder');
//   next();
// });

app.use('/', express.static('./pub_html', options));
app.use('/files', serverIndex('pub_html/files', {'icons': true}));

app.get('/users-api', function(req,res,next){
  // serve users as json
  // res.json(users);
  con.query("select * from users", function(err,result){
    if (err) throw err;
    res.json(result);
  });
});

app.post('/users-api', function(req,res,next){
  //console.log(req.body);
  //users.push(req.body);
  con.query(`insert into users (fname,lname) values ('${req.body.fname}','${req.body.lname}')`, function(err,result){
    if (err) console.log(err.sqlMessage);
  });
  //res.json(users);
  con.query("select * from users", function(err,result){
    if (err) console.log(err.sqlMessage);
    res.json(result);
  });
});

app.delete('/users-api/:user', function(req,res,next){
  // search database for 'user'
  var user = req.params.user;
  console.log(user);

  // users = users.filter(function(people){
  //   return ((people.fname !== req.body.fname) || (people.lname !== req.body.lname));
  // });
  con.query(`delete from users where fname='${req.body.fname}' and lname='${req.body.lname}'`, function(err,result){
    if (err) console.log(err.sqlMessage);
  });
  //res.json(users);
  con.query("select * from users", function(err,result){
    if (err) console.log(err.sqlMessage);
    res.json(result);
  });
});

http.createServer(app).listen(port);
console.log('running on port',port);

process.on('uncaughtException', function(err) {
	console.log(err);
});