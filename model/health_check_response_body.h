/*
 * health_check_response_body.h
 *
 * 
 */

#ifndef _health_check_response_body_H_
#define _health_check_response_body_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"


typedef enum  {  Running, Warnings, Critical } status_e;

char* statushealth_check_response_body_ToString(status_e status);

status_e statushealth_check_response_body_FromString(char* status);

typedef struct health_check_response_body_t {
        status_e status; //enum string
        char *message; //no enum string
        char *version; //no enum string

} health_check_response_body_t;

health_check_response_body_t *health_check_response_body_create(
        status_e status,
        char *message,
        char *version
);

void health_check_response_body_free(health_check_response_body_t *health_check_response_body);

health_check_response_body_t *health_check_response_body_parseFromJSON(char *jsonString);

cJSON *health_check_response_body_convertToJSON(health_check_response_body_t *health_check_response_body);

#endif /* _health_check_response_body_H_ */

