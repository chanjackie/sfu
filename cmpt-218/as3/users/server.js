// users

var express = require('express');
var app = express();
var http = require('http');

var port = process.env.PORT || 12834;
var users = [];

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
	next();
});

app.use('/', express.static('./pub_html', options));


http.createServer(app).listen(port);
console.log('Port', port);