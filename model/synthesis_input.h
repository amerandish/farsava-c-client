/*
 * synthesis_input.h
 *
 * The Synthesizer requires either plain text or SSML as input. Only provide text OR ssml. Providing both will result in a bad request response.
 */

#ifndef _synthesis_input_H_
#define _synthesis_input_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct synthesis_input_t {
        char *text; //no enum string
        char *ssml; //no enum string

} synthesis_input_t;

synthesis_input_t *synthesis_input_create(
        char *text,
        char *ssml
);

void synthesis_input_free(synthesis_input_t *synthesis_input);

synthesis_input_t *synthesis_input_parseFromJSON(char *jsonString);

cJSON *synthesis_input_convertToJSON(synthesis_input_t *synthesis_input);

#endif /* _synthesis_input_H_ */

