var http = require('http');
var fs = require('fs');
var url = require('url');


http.createServer(function(req,res){
	fs.readFile('./index.html', function(err,data){
		if(err) {
			res.write("404 Not Found");
		}
		var request = url.parse(req.url, true);
		var action = request.pathname;
		if (action == '/image.jpg') {
			var img = fs.readFileSync('./image.jpg');
			res.writeHead(200, {'Content-type': 'image/jpg' });
			res.end(img, 'binary');
		} else {
			res.writeHead(200, {'Content-Type': 'text/html'});
			res.write(data);
			res.end();
		}
	});
}).listen(12834);