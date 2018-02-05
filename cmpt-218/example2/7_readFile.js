var path = require('path');
var fs = require('fs');

var fileName = process.argv[2];

var filePath = path.join(__dirname,fileName);
console.log(filePath);
var contents = fs.readFileSync(filePath);
console.log(contents.toString());
