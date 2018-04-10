
var users = [];

function nextUser(){
  process.stdout.write('\n next user fname,lname,age: (exit to quit): ');
}

process.stdin.on('data', function(data){
  if (data.toString().trim() !== 'exit'){
    users.push(data.toString().trim());
    nextUser();
  } else {
    process.exit();
  }
});

process.on('exit', function(){
  users.forEach(function(user){
    process.stdout.write(user);
  })
});

nextUser();
