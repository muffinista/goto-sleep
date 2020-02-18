if ( process.platform !== 'darwin' && process.platform !== 'win32' ) {
  var exec = require('child_process').exec;
  child = exec('npm install which').stderr.pipe(process.stderr);
}