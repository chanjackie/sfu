// users-api

var express = require('express');
var app = express();
var serverIndex = require('serve-index');
var http = require('http');
var ajax = require('ajax');

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
  console.log(req.method, 'request:', req.url);
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
  res.json(users);
});

app.post('/users-api', function(req,res,next){
  console.log(req.body);
  users.push(req.body);
  var x = json(users);
  res = $.parseJSON(x);
  $(function() {
    $.each(res, function(i, item) {
      var $tr = $('<tr>').append(
        $('<td>').text(item.fname),
        $('<td>').text(item.lname),
        $('<td>').text(item.age)
      );
    });
  });
});

http.createServer(app).listen(port);
console.log('running on port',port);
