var path = require('path');

var pathObj = path.parse(__filename);
console.log(path.join(pathObj.dir,'foo','bar'));
