#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "health_check_response_body.h"


char* statushealth_check_response_body_ToString(status_e status){
    char *statusArray[] =  { "Running","Warnings","Critical" };
    return statusArray[status];

}

status_e statushealth_check_response_body_FromString(char* status){
    int stringToReturn = 0;
    char *statusArray[] =  { "Running","Warnings","Critical" };
    size_t sizeofArray = sizeof(statusArray) / sizeof(statusArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(status, statusArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
}

health_check_response_body_t *health_check_response_body_create(
    status_e status,
    char *message,
    char *version
    ) {
	health_check_response_body_t *health_check_response_body = malloc(sizeof(health_check_response_body_t));
	health_check_response_body->status = status;
	health_check_response_body->message = message;
	health_check_response_body->version = version;

	return health_check_response_body;
}


void health_check_response_body_free(health_check_response_body_t *health_check_response_body) {
    listEntry_t *listEntry;
    free(health_check_response_body->message);
    free(health_check_response_body->version);

	free(health_check_response_body);
}

cJSON *health_check_response_body_convertToJSON(health_check_response_body_t *health_check_response_body) {
	cJSON *item = cJSON_CreateObject();
	// health_check_response_body->status
    if(cJSON_AddStringToObject(item, "status", statushealth_check_response_body_ToString(health_check_response_body->status)) == NULL) {
    goto fail; //String
    }

	// health_check_response_body->message
    if(cJSON_AddStringToObject(item, "message", health_check_response_body->message) == NULL) {
    goto fail; //String
    }

	// health_check_response_body->version
    if(cJSON_AddStringToObject(item, "version", health_check_response_body->version) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

health_check_response_body_t *health_check_response_body_parseFromJSON(char *jsonString){

    health_check_response_body_t *health_check_response_body = NULL;
    cJSON *health_check_response_bodyJSON = cJSON_Parse(jsonString);
    if(health_check_response_bodyJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // health_check_response_body->status
    status_e statusVariable;
    cJSON *status = cJSON_GetObjectItemCaseSensitive(health_check_response_bodyJSON, "status");
    if(!cJSON_IsString(status) || (status->valuestring == NULL)){
    goto end; //String
    }

    statusVariable = statushealth_check_response_body_FromString(status->valuestring);

    // health_check_response_body->message
    cJSON *message = cJSON_GetObjectItemCaseSensitive(health_check_response_bodyJSON, "message");
    if(!cJSON_IsString(message) || (message->valuestring == NULL)){
    goto end; //String
    }

    // health_check_response_body->version
    cJSON *version = cJSON_GetObjectItemCaseSensitive(health_check_response_bodyJSON, "version");
    if(!cJSON_IsString(version) || (version->valuestring == NULL)){
    goto end; //String
    }


    health_check_response_body = health_check_response_body_create (
        statusVariable,
        strdup(message->valuestring),
        strdup(version->valuestring)
        );
 cJSON_Delete(health_check_response_bodyJSON);
    return health_check_response_body;
end:
    cJSON_Delete(health_check_response_bodyJSON);
    return NULL;

}

