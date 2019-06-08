/*
 * language_model_result.h
 *
 * 
 */

#ifndef _language_model_result_H_
#define _language_model_result_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "lm_status.h"


typedef enum  {  queued, training, trained } status_e;

char* statuslanguage_model_result_ToString(status_e status);

status_e statuslanguage_model_result_FromString(char* status);

typedef struct language_model_result_t {
        char *languageModelId; //no enum string
        char *name; //no enum string
        lm_status_t *status; //nonprimitive

} language_model_result_t;

language_model_result_t *language_model_result_create(
        char *languageModelId,
        char *name,
        lm_status_t *status
);

void language_model_result_free(language_model_result_t *language_model_result);

language_model_result_t *language_model_result_parseFromJSON(char *jsonString);

cJSON *language_model_result_convertToJSON(language_model_result_t *language_model_result);

#endif /* _language_model_result_H_ */

