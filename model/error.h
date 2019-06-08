/*
 * error.h
 *
 * 
 */

#ifndef _error_H_
#define _error_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct error_t {
        char *status; //no enum string
        char *detail; //no enum string
        char *title; //no enum string
        char *type; //no enum string

} error_t;

error_t *error_create(
        char *status,
        char *detail,
        char *title,
        char *type
);

void error_free(error_t *error);

error_t *error_parseFromJSON(char *jsonString);

cJSON *error_convertToJSON(error_t *error);

#endif /* _error_H_ */

