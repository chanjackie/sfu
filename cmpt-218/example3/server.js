var http = require('http');
var fs = require('fs');
var server = http.createServer();

server.on('request', function(req,res){
  // req.url === '/image.jpg'
  res.writeHead(200, {"Content-Type": "text/html"});
  res.write(`
    <!DOCTYPE html>
    <html>
    	<head>
    		<title>BASIC HTML Response</title>
    	</head>
    	<body>
    	 <h1>Serving Webpage</h1>
       <p>${req.url}</p>
       <p>${req.method}</p>
       <p>${req.httpVersion}</p>
    	</body>
    </html>
  `);

  res.end()

});

server.listen(8080);

console.log('Magic is happening on port 8080');
