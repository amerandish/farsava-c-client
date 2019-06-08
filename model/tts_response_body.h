/*
 * tts_response_body.h
 *
 * 
 */

#ifndef _tts_response_body_H_
#define _tts_response_body_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct tts_response_body_t {

} tts_response_body_t;

tts_response_body_t *tts_response_body_create(
);

void tts_response_body_free(tts_response_body_t *tts_response_body);

tts_response_body_t *tts_response_body_parseFromJSON(char *jsonString);

cJSON *tts_response_body_convertToJSON(tts_response_body_t *tts_response_body);

#endif /* _tts_response_body_H_ */

