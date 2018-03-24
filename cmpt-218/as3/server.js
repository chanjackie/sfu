// users
// mongo -u jgc11 -p jp8j/Fdl --authenticationDatabase admin

var express = require('express');
var app = express();
var http = require('http');
var MongoClient = require('mongodb').MongoClient

//var url = 'mongodb://jgc11:jp8j/Fdl@127.0.0.1:27017/cmpt218_jgc11?authSource=admin';
var url = 'mongodb://root:root@ds123259.mlab.com:23259/as3-218';
MongoClient.connect(url, function(err, client) {
	if (err) {throw err;}
	else {console.log("Successfully connected to server!");}
	db = client.db('as3-218');
	// var collection = db.collection('checkin');
});

//Global variables
var loggedin = false;
var credentials = {
	uname:"admin",
	pword:"1234"
}
var port = process.env.PORT || 12834;
var cids = {
	"_id":"",
	"active":false,
	"users":[{
		"userid":"",
		"name":""
	}]
};
var options = {
	dotfiles: 'ignore',
	etag: false,
	extensions: ['htm','html'],
	index: "login.html"
}

app.use(express.json());
app.use(express.urlencoded({extended:false}));


app.use('/', function(req,res,next) {
	console.log(req.method, 'request: ', req.url, JSON.stringify(req.body));
	if(req.url === '/admin.html' || req.url === '/admincheckin.html') {
		if (!loggedin) {
			console.log("Nice try kid");
			res.redirect('/');
			return false;
		}
	}
	next();
});

app.use('/', express.static('./', options));

app.post('/adminlanding', function(req, res, next) {
	console.log("req body: ", req.body);
	if (JSON.stringify(credentials) === JSON.stringify(req.body)) {
		loggedin=true;
		res.redirect('/admin.html');
	} else if (loggedin === true) {
		console.log("End checkin for ", cids._id);
		cids.active = false;
		db.collection('checkin').save(cids);
		res.redirect('/admin.html');
	} else {
		loggedin=false;
		res.redirect('/');
	}
});

app.post('/admincheckin', function(req, res, next) {
	console.log("id body: ", req.body);
	cids._id = req.body._id;
	cids.active = true;
	console.log("current _id: ", cids);
	db.collection('checkin').save(cids, function(err, result) {
		if (err) {
			return console.log(err);
		} 
		console.log("Saved ", cids);
	});
	res.redirect('admincheckin.html');
});

app.get('/cids', function(req, res, next) {
	res.json(cids);
})

app.post('/checkinhist', function(req, res) {
	//db.collection('checkin').
})

//var url = 'mongodb://jgc11:jp8j/Fdl@127.0.0.1:27017/cmpt218_jgc11?authSource=admin';

http.createServer(app).listen(port);
console.log('Port', port);