// users
// mongo -u jgc11 -p jp8j/Fdl --authenticationDatabase admin

var express = require('express');
var app = express();
var http = require('http');
var MongoClient = require('mongodb').MongoClient

var url = 'mongodb://jgc11:jp8j/Fdl@127.0.0.1:27017/cmpt218_jgc11?authSource=admin';
//var url = 'mongodb://root:root@ds123259.mlab.com:23259/cmpt218_jgc11';
MongoClient.connect(url, function(err, client) {
	if (err) {throw err;}
	else {console.log("Successfully connected to server!");}
	db = client.db('cmpt218_jgc11');
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
	"active":false
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
	if(req.url === '/admin.html' || req.url === '/admincheckin.html' || req.url === '/hist.html') {
		if (!loggedin) {
			console.log("Nice try kid");
			res.redirect('/');
			return false;
		}
	}
	loggedin=false;
	next();
});

app.use('/', express.static('./', options));

app.post('/adminlanding', function(req, res, next) {
	console.log("req body: ", req.body);
	if (JSON.stringify(credentials) === JSON.stringify(req.body)) {
		loggedin=true;
		res.redirect('/admin.html');
	} else if (req.body.uname) {
		loggedin=false;
		res.redirect('/');
	} else if (cids.active === true) {
		console.log("End checkin for", cids._id);
		cids.active = false;
		db.collection('checkin').update({_id:cids._id}, {$set: {active:false}});
		loggedin=true;
		res.redirect('/admin.html');
	} else {
		loggedin=false;
		res.redirect('/');
	}
});

app.post('/exitHist', function(req,res) {
	loggedin=true;
	res.redirect('/admin.html');
});

app.post('/admincheckin', function(req, res, next) {
	console.log("id body: ", req.body);
	cids._id = req.body._id;
	cids.active = true;
	console.log("current _id: ", cids._id);
	db.collection('checkin').update({_id:cids._id}, {$set: {_id:cids._id, active:true}}, {upsert:true});
		/*if (err) {
			return console.log(err);
		} 
		console.log("Saved ", cids);*/
	loggedin=true;
	res.redirect('/admincheckin.html');
});

app.get('/cids', function(req, res, next) {
	res.json(cids);
});

app.post('/checkinhist', function(req, res) {
	loggedin=true;
	res.redirect('/hist.html');
});

app.post('/checkin', function(req, res) {
	console.log("req body: ", req.body);
	if (!req.body.userid) {
		res.redirect('/checkin.html');
	} else {
		if (req.body._id === cids._id && cids.active) {
			console.log("userid:", req.body.userid, "name:", req.body.name);
			db.collection('checkin').update({_id:req.body._id}, {$push: { users: {userid:req.body.userid, name:req.body.name, date:req.body.date}}});
			res.redirect('/thankyou.html');
		} else {
			console.log("checkin id", JSON.stringify(req.body._id), "is not currently active.");
			res.redirect('/checkin.html');
		}
	}
});

app.get('/showhist', function(req, res) {
	db.collection('checkin').find().toArray(function(err, result) {
		console.log("Result:", result);
		res.json(result);
	});
});

app.delete('/deleteCheck', function(req, res) {
	console.log('Delete request for', req.body);
	db.collection('checkin').remove({_id:req.body._id});
	function waitForUpdate() {
		db.collection('checkin').find().toArray(function(err, result) {
			console.log("Result:", result);
			res.json(result);
		});
	}
	setTimeout(waitForUpdate, 100);
});

app.post('/return', function(req, res) {
	res.redirect('/');
});

http.createServer(app).listen(port);
console.log('Port', port);