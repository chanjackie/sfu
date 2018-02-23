var http = require('http');

var options = {
  hostname: "www.sfu.ca",
  path: "/computing/acm/",
  port:80,
  method:'GET'
}
var req = http.request(options, function(res){
  var body = '';
  res.on('data', function(packet){
    console.log("-packet-length: ", packet.length);
  });
});

console.log('request ended');
req.end();
