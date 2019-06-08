/*
 * asr_status.h
 *
 * Status of the recognition process. *USE THE RECOGNITION RESULT ONLY WHEN STATUS IS DONE*. 
 */

#ifndef _asr_status_H_
#define _asr_status_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct asr_status_t {

} asr_status_t;

asr_status_t *asr_status_create(
);

void asr_status_free(asr_status_t *asr_status);

asr_status_t *asr_status_parseFromJSON(char *jsonString);

cJSON *asr_status_convertToJSON(asr_status_t *asr_status);

#endif /* _asr_status_H_ */

