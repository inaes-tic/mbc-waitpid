try {
	var binding = require('../build/Release/mbc_waitpid');
}
catch(err) {
	var binding = require('../build/Debug/mbc_waitpid');
}

module.exports = function waitpid(pid) {
	//returns the exit code/signal
	return binding.waitpid(pid);
};

