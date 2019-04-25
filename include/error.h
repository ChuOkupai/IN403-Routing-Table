#ifndef _ERROR_H
#define _ERROR_H

#include <errno.h>
#include <stdio.h>

// Vérifie la valeur de errno, si elle est différente de 0 affiche l'erreur et quitte le programme
#define CHECK(FUNCTION) ({FUNCTION; if (errno) { perror("error"); exit(EXIT_FAILURE);} })

// Affiche un avertissement uniquement
#define WARNING(ERRNUM) ({errno = ERRNUM; perror("warning");})

#endif