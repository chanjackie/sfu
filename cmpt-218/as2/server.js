var http = require('http');
var fs = require('fs');
var path = require('path');
var url = require('url');
var qs = require('querystring');
var script = require('./script.js');


var server = http.createServer();
server.on('request', function(req,res){
	console.log('request: ', req.url);
	if (req.method === 'GET' && req.url === '/'){
		fs.readFile("./form.html", function (err, contents) {
			if (err) {
				res.writeHead(404);
				res.write('404 Error');
				res.end();
			} else {
				res.writeHead(200, {"Content-Type": "text/html"});
				res.write(contents);
				res.end();
			}
		});
	} else if (req.method === 'POST' && req.url === '/') {
		var body = '';
		req.on('data', function(data){
			body += data.toString();
		});
		req.on('end', function(){
			var postObj = qs.parse(body);
			console.log(postObj);
			var json = JSON.stringify(postObj);
			console.log(json);
			fs.writeFile('./data/users.json', json, 'utf8');
			res.end();
		});
	} else if (req.method === 'GET' && req.url === '/users.html'){
		fs.readFile("./form.html", function (err, contents) {
			if (err) {
				res.writeHead(404);
				res.write('404 Error');
				res.end();
			} else {
				res.writeHead(200, {"Content-Type": "text/html"});
				res.write(contents);
				res.end();
			}
		});
	} else if (req.method === 'GET' && req.url.match(/^\/.+\.js$/)){
		var jspath = path.join(__dirname,req.url);
		fs.readFile(jspath, function(err, contents){
			if (err) {
				res.writeHead(404);
				res.write('404 Error');
				res.end();
			} else {
				res.writeHead(200, {"Content-Type": "text/javascript"});
				res.write(contents);
				res.end();
			}
		})
	} else {
		res.writeHead(404);
		res.write('404 Error');
		res.end();
	}
});
server.listen(12834);

console.log("Running on port 12834!");