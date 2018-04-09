var cp = require('child_process');
var os = require('os');

if (os.platform() === 'win32'){
  cp.execFile('hello.bat',['Bobby'], function(err,stdout,stderr){
    console.log(stdout);
  });
} else if (os.platform() === 'linux' || os.platform() === 'darwin'){
  // linux commands
}
