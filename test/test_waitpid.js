var exec = require('child_process').exec;
var waitpid = require('mbc_waitpid').waitpid;

var ps = exec('sleep 5');

console.log("Waiting...");

var r = waitpid(ps.pid);

console.log("Exit..." + r);
