var http = require('http');
var fs = require('fs');
var path = require('path');
var url = require('url');
var qs = require('querystring');
var script = require('./script.js');

var json = {};
fs.writeFile('./data/users.json', json, 'utf8');

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
			var ppl = {"users":[]};
			var len = 0;
			try {
				postObj.fname.forEach(function() {
					len++;
				})
			}
			catch(err) {
				len = 1;
			}
			if (len>1) {
				for (var i=0;i<len;i++) {
					var person = {"fname": postObj.fname[i], "lname": postObj.lname[i], "bday": postObj.bday[i], "email": postObj.email[i]};
					ppl.users.push(person);
				}
			} else {
				var person = {"fname": postObj.fname, "lname": postObj.lname, "bday": postObj.bday, "email": postObj.email};
				ppl.users.push(person);
			}			
			json = JSON.stringify(ppl);
			console.log(json);
			fs.writeFile('./data/users.json', json, 'utf8');
			res.end();
		});
	} else if (req.method === 'GET' && req.url === '/users.html'){
		fs.readFile("./users.html", function (err, contents) {
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
	} else if (req.method === 'GET' && req.url.match(/^\/.+\.json$/)){
		var jsonpath = path.join(__dirname,req.url);
		fs.readFile(jsonpath, function(err, contents){
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