console.log(process.argv);

var port = process.argv[2];
if (typeof(port) !== 'undefined'){
  console.log(`app is running on port: ${port}`);
} 
