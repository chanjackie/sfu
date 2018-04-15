// users
// mongo -u jgc11 -p jp8j3Fdl --authenticationDatabase admin

var express = require('express');
var app = express();
var http = require('http');
var MongoClient = require('mongodb').MongoClient

var collection = null;

var url = 'mongodb://jgc11:jp8j3Fdl@127.0.0.1:27017/cmpt218_jgc11?authSource=admin';
//var url = 'mongodb://root:root@ds125479.mlab.com:25479/as4-218';
MongoClient.connect(url, function(err, client) {
	if (err) {throw err;}
	else {console.log("Successfully connected to server!");}
	db = client.db('cmpt218_jgc11');
	collection = db.collection('users');
});

//Global variables
var loggedin = false;
var port = process.env.PORT || 12834;
var options = {
	dotfiles: 'ignore',
	etag: false,
	extensions: ['htm','html'],
	index: "login.html"
}
var user = {
	"_id": "",
	"pword": "",
	"win": 0,
	"loss": 0,
	"player1": false
}
var userArray = [];
var inRoom = 0;
var server = http.createServer(app).listen(port);
console.log('Port', port);

var io = require('socket.io')(server);

app.use(express.json());
app.use(express.urlencoded({extended:false}));

app.use('/', function(req,res,next) {
	console.log(req.method, 'request: ', req.url, JSON.stringify(req.body));
	if (req.url === "/userlanding.html" || req.url === "/thankyou.html" || req.url === "/board.html") {
		if (!loggedin) {
			console.log("Nice try kid");
			res.redirect('/login.html');
		}
	}
	loggedin=false;
	next();
});

app.use('/', express.static('./pub_html', options));

io.on('connection', function(socket) {
	console.log("Socket connection");
	socket.on('broadcast', function(msg) {
		socket.broadcast.emit('userCon', msg);
		socket.emit('userCon', msg);
	});
	socket.on('updateTurn', function(data) {
		socket.broadcast.emit('changeTurn', data);
		socket.emit('changeTurn', data);
	});
	socket.on('oneQuit', function() {
		socket.broadcast.emit('quitOther');
	});
	socket.on('updateWin', function(msg) {
		socket.broadcast.emit('clientWin', userArray, msg);
		socket.emit('clientWin', userArray, msg);
	});
	socket.on('updateData', function(player1) {
		console.log("User array:", userArray);
		socket.broadcast.emit('changeData', userArray, player1);
		socket.emit('changeData', userArray, player1);
	});
	socket.on('returnOther', function() {
		socket.broadcast.emit('returnThis');
	});
});

app.post('/userlanding', function(req,res,next) {
	collection.find({_id:req.body._id}).toArray(function(err, result) {
		if (result.length == 0) {
			console.log("User not found on database");
			res.redirect('/login.html');
		} else if (req.body.pword != result[0].pword) {
			console.log("Incorrect password");
			res.redirect('/login.html');
		} else {
			user._id = result[0]._id;
			user.pword = result[0].pword;
			user.win = result[0].win;
			user.loss = result[0].loss;
			user.player1 = result[0].player1;
			console.log("User info:", user);
			loggedin = true;
			res.redirect('/userlanding.html');
		}
	});
});

app.post('/disconnect', function(req,res,next) {
	console.log(req.body._id, "has disconnected");
	user._id = req.body._id;
	if (userArray.length == 2) {
		collection.update({_id:user._id}, {$inc:{loss:1}});
	} else {
		collection.update({_id:user._id}, {$inc:{win:1}});
	}
	var index = userArray.indexOf(user._id);
	userArray.splice(index, 1);
	loggedin=true;
	res.redirect('/userlanding.html');
});

app.post('/playerWin', function(req,res,next) {
	console.log(req.body._id, "won");
	user._id = req.body._id;
	collection.update({_id:user._id}, {$inc:{win:1}});
	var index = userArray.indexOf(user._id);
	userArray.splice(index, 1);
	loggedin=true;
	res.redirect('/userlanding.html');
});

app.post('/playerLoss', function(req,res,next) {
	console.log(req.body._id, "lost");
	user._id = req.body._id;
	collection.update({_id:user._id}, {$inc:{loss:1}});
	var index = userArray.indexOf(user._id);
	userArray.splice(index, 1);
	loggedin=true;
	res.redirect('/userlanding.html');
});

app.post('/play', function(req,res,next) {
	loggedin=true;
	user._id = req.body._id;
	if (userArray.length < 2) {
		userArray.push(user._id);
		console.log("Current users:", userArray);
		res.redirect("/waiting.html");
	} else {
		res.redirect("/userlanding.html");
	}
});

app.post('/returnLanding', function(req,res,next) {
	loggedin=true;
	user._id = req.body._id;
	var index = userArray.indexOf(user._id);
	userArray.splice(index, 1);
	console.log("Current users:", userArray);
	res.redirect("/userlanding.html");
});

app.post('/join1', function(req,res,next) {
	loggedin=true;
	user._id = req.body._id;
	user.player1 = true;
	collection.update({_id:user._id}, {$set:{player1:true}});
	res.redirect("/board.html");
});

app.post('/join2', function(req,res,next) {
	loggedin=true;
	user._id = req.body._id;
	user.player1 = false;
	collection.update({_id:user._id}, {$set:{player1:false}});
	res.redirect("/board.html");
});

app.get('/stats', function(req,res,next) {
	console.log("Finding user", user._id);
	collection.find({_id:user._id}).toArray(function(err, result) {
		console.log("Feeding ", result);
		res.json(result);
	});
});

app.post('/register', function(req,res,next) {
	console.log("Register info: ", req.body);
	if (req.body.confirmpword !== req.body.pword) {
		res.redirect('/register.html');
	} else {
		collection.find({_id:req.body._id}).toArray(function(err, result) {
			if (result.length == 1) {
				console.log("User already exists in database");
				res.redirect('/register.html');
			} else {
				collection.save({_id:req.body._id, pword:req.body.pword, win:0, loss:0, player1:false});
				loggedin = true;
				res.redirect('/thankyou.html');
			}
		});
	}
});

app.post('/recordStats', function(req,res,next) {
	console.log("Game stats: ", req.body);
	db.collection('games').find({_id:req.body._id}).toArray(function(err, result) {
		if (result.length == 1) {
			console.log("Game already exists");
		} else {
			db.collection('games').save({_id:req.body._id, moves:req.body.moves, winner:req.body.winner, loser:req.body.loser});
		}
	});
});