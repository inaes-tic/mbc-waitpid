var assert = require("assert");

describe('require-waitpid', function() {
	var waitpid = require('../lib/mbc_waitpid');
});

describe('waitpid-exit', function() {
	var exec = require('child_process').exec;
	var waitpid = require('../lib/mbc_waitpid');

	var ps = exec('sleep 2');
	var r = waitpid(ps.pid);

        it('--should return 0', function(){
            assert.equal(r, 0);
        });
});

describe('waitpid-kill', function() {
	var exec = require('child_process').exec;
	var waitpid = require('../lib/mbc_waitpid');

	var ps = exec('sleep 2');
	ps.kill('SIGTERM');
	var r = waitpid(ps.pid);

        it('--should return killed', function(){
            assert.equal(r, "killed");
        });
});

