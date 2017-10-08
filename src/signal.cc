#include "signal.h"
void sigaction(int signal, siginfo_t *si, void *arg)
{
	if(signal == SIGSEGV)
	{
		cerr<<"segmentation fault";
		exit(-1);
	}
	else if(signal == SIGALRM)
	{
		cerr<<"infinite loop";
		exit(-1);
	}
	else if(signal == SIGABRT) {
		cerr<<"core dumped"
	}
	else if(signal == SIGBUS) {
		cerr<<"core dumped"
	}
	else if(signal == SIGFPE) {
		cerr<<"arithmetic error"
	}
	else if(signal == SIGHUP) {
		cerr<<"hang up"
	}
	else if(signal == SIGILL) {
		cerr<<"invalid command"
	}
	else if(signal == SIGINT) {
		cerr<<"terminal interrupt"
	}
	else if(signal == SIGKILL) {
		cerr<<"signal kill"
	}
	else if(signal == SIGQUIT) {
		cerr<<"terminal exited"
	}
	else if(signal == SIGSTOP) {
		cerr<<"signal stopped"
	}
	else if(signal == SIGSYS) {
		cerr<<"invalid system call"
	}
	else if(signal == SIGTERM) {
		cerr<<"signal termination"
	}
	else if(signal == SIGTRAP) {
		cerr<<"trace/break point trap called"
	}
	else if(signal == SIGTTIN) {
		cerr<<"background process on"
	}
	else if(signal == SIGTTOU) {
		cerr<<"background process on"
	}
	else if(signal == SIGXCPU) {
		cerr<<"cpu time over"
	}
	else if(signal == SIGXFSZ) {
		cerr<<"file size over"
	}
}

void set_sigaction(struct sigaction &sa)
{
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sigaction;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGALRM, &sa, NULL);
	sigaction(SIGABRT, &sa, NULL);
	sigaction(SIGBUS, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);
	sigaction(SIGHUP, &sa, NULL);
	sigaction(SIGILL, &sa, NULL);
	sigaction(SIGKILL, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGSTOP, &sa, NULL);
	sigaction(SIGSYS, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGTRAP, &sa, NULL);
	sigaction(SIGTTIN, &sa, NULL);
	sigaction(SIGTTOU, &sa, NULL);
	sigaction(SIGXCPU, &sa, NULL);
	sigaction(SIGXFSZ, &sa, NULL);
}
