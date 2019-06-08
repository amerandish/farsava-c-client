/*
 * asr_request_body_uri.h
 *
 * 
 */

#ifndef _asr_request_body_uri_H_
#define _asr_request_body_uri_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "recognition_audio_uri.h"
#include "recognition_config.h"




typedef struct asr_request_body_uri_t {
        recognition_config_t *config; //nonprimitive
        recognition_audio_uri_t *audio; //nonprimitive

} asr_request_body_uri_t;

asr_request_body_uri_t *asr_request_body_uri_create(
        recognition_config_t *config,
        recognition_audio_uri_t *audio
);

void asr_request_body_uri_free(asr_request_body_uri_t *asr_request_body_uri);

asr_request_body_uri_t *asr_request_body_uri_parseFromJSON(char *jsonString);

cJSON *asr_request_body_uri_convertToJSON(asr_request_body_uri_t *asr_request_body_uri);

#endif /* _asr_request_body_uri_H_ */

