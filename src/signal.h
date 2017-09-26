#ifndef _SIGNAL_H_
#define _SIGNAL_H_
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

void segfault_sigaction(int signal, siginfo_t *si, void *arg);

void set_sigaction(struct sigaction &sa);

#else
#endif
