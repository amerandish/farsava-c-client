/*
 * asr_request_body_data.h
 *
 * 
 */

#ifndef _asr_request_body_data_H_
#define _asr_request_body_data_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "recognition_audio_data.h"
#include "recognition_config.h"




typedef struct asr_request_body_data_t {
        recognition_config_t *config; //nonprimitive
        recognition_audio_data_t *audio; //nonprimitive

} asr_request_body_data_t;

asr_request_body_data_t *asr_request_body_data_create(
        recognition_config_t *config,
        recognition_audio_data_t *audio
);

void asr_request_body_data_free(asr_request_body_data_t *asr_request_body_data);

asr_request_body_data_t *asr_request_body_data_parseFromJSON(char *jsonString);

cJSON *asr_request_body_data_convertToJSON(asr_request_body_data_t *asr_request_body_data);

#endif /* _asr_request_body_data_H_ */

