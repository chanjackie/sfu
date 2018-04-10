const https = require('https');
const fs = require('fs');

const options = {
  key: fs.readFileSync('./encrypt/key.pem'),
  cert: fs.readFileSync('./encrypt/cert.pem'),

};

https.createServer(options, function(req, res){
  res.writeHead(200);
  res.end('hello world\n');
}).listen(443);
