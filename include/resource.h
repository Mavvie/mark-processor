#pragma once

extern int opterr, optind, optopt, optreset;
extern char *optarg;
int getopt(int nargc, char * const nargv[], const char *ostr);