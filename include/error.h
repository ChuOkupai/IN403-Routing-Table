#ifndef _ERROR_H
#define _ERROR_H

#include <errno.h>
#include <stdio.h>

// Affiche l'erreur et quitte le programme
#define ERROR_EXIT() { perror("error"); exit(EXIT_FAILURE);}
// Affiche un avertissement uniquement
#define WARNING(ERRNUM) { errno = ERRNUM;perror("warning");}

#endif