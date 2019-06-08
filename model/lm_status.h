/*
 * lm_status.h
 *
 * Status of the language model training process. After a language model training finishes it can be used for speech recognition using its languageModelId. 
 */

#ifndef _lm_status_H_
#define _lm_status_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct lm_status_t {

} lm_status_t;

lm_status_t *lm_status_create(
);

void lm_status_free(lm_status_t *lm_status);

lm_status_t *lm_status_parseFromJSON(char *jsonString);

cJSON *lm_status_convertToJSON(lm_status_t *lm_status);

#endif /* _lm_status_H_ */

