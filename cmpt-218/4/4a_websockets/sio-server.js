var express = require('express');
var http = require('http');
var app = express();
var server = http.createServer(app).listen(8080);

var io = require('socket.io')(server);

var clients = 0;

app.use(express.static("./public"));

io.on('connection', function(socket){
  console.log('new connection');
  clients++;
  socket.emit('clientChange',clients);
  socket.broadcast.emit('clientChange',clients);

  socket.on('chat', function(message){
    socket.broadcast.emit('message',message);
  });

  socket.on('disconnect', function(){
    console.log('Disconnect event');
    clients--;
    //socket.emit('clientChange',clients);
    socket.broadcast.emit('clientChange',clients);
  });

  socket.emit("message", "You're connected!!!");
});

console.log("app running on 8080");
