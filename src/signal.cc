#include "signal.h"
void segfault_sigaction(int signal, siginfo_t *si, void *arg)
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
}

void set_sigaction(struct sigaction &sa)
{
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_sigaction;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGALRM, &sa, NULL);
}
