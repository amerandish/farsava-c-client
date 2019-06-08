/*
 * asr_response_body.h
 *
 * 
 */

#ifndef _asr_response_body_H_
#define _asr_response_body_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "asr_status.h"
#include "speech_recognition_result.h"


typedef enum  {  queued, processing, done, partial } status_e;

char* statusasr_response_body_ToString(status_e status);

status_e statusasr_response_body_FromString(char* status);

typedef struct asr_response_body_t {
        char *transcriptionId; //no enum string
        double duration; //numeric
        double inferenceTime; //numeric
        asr_status_t *status; //nonprimitive
        list_t *results; //nonprimitive container

} asr_response_body_t;

asr_response_body_t *asr_response_body_create(
        char *transcriptionId,
        double duration,
        double inferenceTime,
        asr_status_t *status,
        list_t *results
);

void asr_response_body_free(asr_response_body_t *asr_response_body);

asr_response_body_t *asr_response_body_parseFromJSON(char *jsonString);

cJSON *asr_response_body_convertToJSON(asr_response_body_t *asr_response_body);

#endif /* _asr_response_body_H_ */

