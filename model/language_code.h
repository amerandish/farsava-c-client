/*
 * language_code.h
 *
 * The language of the supplied audio as a language tag. Example **en** for english language. See Language Support for a list of the currently supported language codes. 
 */

#ifndef _language_code_H_
#define _language_code_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct language_code_t {

} language_code_t;

language_code_t *language_code_create(
);

void language_code_free(language_code_t *language_code);

language_code_t *language_code_parseFromJSON(char *jsonString);

cJSON *language_code_convertToJSON(language_code_t *language_code);

#endif /* _language_code_H_ */

