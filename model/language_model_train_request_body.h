/*
 * language_model_train_request_body.h
 *
 * 
 */

#ifndef _language_model_train_request_body_H_
#define _language_model_train_request_body_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct language_model_train_request_body_t {
        list_t *corpora; //primitive container
        char *name; //no enum string

} language_model_train_request_body_t;

language_model_train_request_body_t *language_model_train_request_body_create(
        list_t *corpora,
        char *name
);

void language_model_train_request_body_free(language_model_train_request_body_t *language_model_train_request_body);

language_model_train_request_body_t *language_model_train_request_body_parseFromJSON(char *jsonString);

cJSON *language_model_train_request_body_convertToJSON(language_model_train_request_body_t *language_model_train_request_body);

#endif /* _language_model_train_request_body_H_ */

