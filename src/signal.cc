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
		cerr<<"core dumped";
		exit(-1);
	}
	else if(signal == SIGBUS) {
		cerr<<"core dumped";
		exit(-1);
	}
	else if(signal == SIGFPE) {
		cerr<<"arithmetic error";
		exit(-1);
	}
	else if(signal == SIGHUP) {
		cerr<<"hang up";
		exit(-1);
	}
	else if(signal == SIGILL) {
		cerr<<"invalid command";
		exit(-1);
	}
	else if(signal == SIGINT) {
		cerr<<"terminal interrupt";
		exit(-1);
	}
	else if(signal == SIGKILL) {
		cerr<<"signal kill";
		exit(-1);
	}
	else if(signal == SIGQUIT) {
		cerr<<"terminal exited";
		exit(-1);
	}
	else if(signal == SIGSTOP) {
		cerr<<"signal stopped";
		exit(-1);
	}
	else if(signal == SIGSYS) {
		cerr<<"invalid system call";
		exit(-1);
	}
	else if(signal == SIGTERM) {
		cerr<<"signal termination";
		exit(-1);
	}
	else if(signal == SIGTRAP) {
		cerr<<"trace/break point trap called";
		exit(-1);
	}
	else if(signal == SIGTTIN) {
		cerr<<"background process on";
		exit(-1);
	}
	else if(signal == SIGTTOU) {
		cerr<<"background process on";
		exit(-1);
	}
	else if(signal == SIGXCPU) {
		cerr<<"cpu time over";
		exit(-1);
	}
	else if(signal == SIGXFSZ) {
		cerr<<"file size over";
		exit(-1);
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
