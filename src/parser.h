#ifndef _parser_
#define _parser_

#include "donjon.h"

/* separe une string par:
 * * ses fins de ligne
 * * oublie les ligne vide
 * * oublie les commentaires
 */
char** preprocess(const char * input);

/* separe une string par ses espaces */
char** divide_str(const char * input);


/* appelle preprocess, puis divide_str,
 * puis construit une struct donjon* a partir des tokens
 */
struct donjon * process(const char * input);

/* lit un fichier et le place dans une chaine de char */
char * str_of_file(const char * filename);

/* appelle str_of_file, puis process */
struct donjon * parse(const char * filename);

#endif
