#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <node.h>
#include <v8.h>

using namespace v8;

Handle<Value> WaitPID(const Arguments& args) {
	pid_t pid, w;
	int status;
	HandleScope scope;

	if (args.Length() < 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}

	if (!args[0]->IsNumber()) {
	    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
	    return scope.Close(Undefined());
	}

	pid = args[0]->NumberValue();

	Local<String> msg;

	do {
		w = waitpid(pid, &status, WUNTRACED | WCONTINUED);

		if (w == -1) {
			ThrowException(Exception::Error(String::New(strerror(errno))));
			return scope.Close(Undefined());
		};

		if (WIFEXITED(status)) {
			return scope.Close(Integer::New(WEXITSTATUS(status)));
		} else if (WIFSIGNALED(status)) {
			msg = String::NewSymbol("killed");
			printf("killed by signal %d\n", WTERMSIG(status));
		} else if (WIFSTOPPED(status)) {
			msg = String::NewSymbol("stopped");
		} else if (WIFCONTINUED(status)) {
			msg = String::NewSymbol("continued");
		}
	} while(!WIFEXITED(status) && !WIFSIGNALED(status));

	return scope.Close(msg);
}

void init(Handle<Object> exports) {
	  exports->Set(String::NewSymbol("waitpid"),
			        FunctionTemplate::New(WaitPID)->GetFunction());
}

NODE_MODULE(mbc_waitpid, init)

