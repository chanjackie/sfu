// users
// mongo -u jgc11 -p jp8j/Fdl --authenticationDatabase admin

var express = require('express');
var app = express();
var http = require('http');
var MongoClient = require('mongodb').MongoClient
var collection = null;

//var url = 'mongodb://jgc11:jp8j/Fdl@127.0.0.1:27017/as3-218?authSource=admin';
var url = 'mongodb://root:root@ds125479.mlab.com:25479/as4-218';
MongoClient.connect(url, function(err, client) {
	if (err) {throw err;}
	else {console.log("Successfully connected to server!");}
	db = client.db('as4-218');
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
	"loss": 0
}

app.use(express.json());
app.use(express.urlencoded({extended:false}));

app.use('/', function(req,res,next) {
	console.log(req.method, 'request: ', req.url, JSON.stringify(req.body));
	if (req.url === "/userlanding.html" || req.url === "thankyou.html") {
		if (!loggedin) {
			console.log("Nice try kid");
			res.redirect('/login.html');
		}
	}
	loggedin=false;
	next();
});

app.use('/', express.static('./pub_html', options));
	
app.post('/userlanding', function(req,res,next) {
	collection.find({_id:req.body._id}).toArray(function(err, result) {
		if (result.length == 0) {
			console.log("User not found on database");
			res.redirect('/login.html');
		} else if (req.body.pword != result[0].pword) {
			console.log("Incorrect password");
			res.redirect('/login.html');
		} else {
			user._id = req.body._id;
			user.pword = req.body.pword;
			user.win = req.body.win;
			user.loss = req.body.loss;
			loggedin = true;
			res.redirect('/userlanding.html');
		}
	});
});

app.get('/stats', function(req,res,next) {
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
				collection.save({_id:req.body._id, pword:req.body.pword, win:0, loss:0});
				loggedin = true;
				res.redirect('/thankyou.html');
			}
		});
	}
});

http.createServer(app).listen(port);
console.log('Port', port);