#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "error.h"



error_t *error_create(
    char *status,
    char *detail,
    char *title,
    char *type
    ) {
	error_t *error = malloc(sizeof(error_t));
	error->status = status;
	error->detail = detail;
	error->title = title;
	error->type = type;

	return error;
}


void error_free(error_t *error) {
    listEntry_t *listEntry;
    free(error->status);
    free(error->detail);
    free(error->title);
    free(error->type);

	free(error);
}

cJSON *error_convertToJSON(error_t *error) {
	cJSON *item = cJSON_CreateObject();
	// error->status
    if(cJSON_AddStringToObject(item, "status", error->status) == NULL) {
    goto fail; //String
    }

	// error->detail
    if(cJSON_AddStringToObject(item, "detail", error->detail) == NULL) {
    goto fail; //String
    }

	// error->title
    if(cJSON_AddStringToObject(item, "title", error->title) == NULL) {
    goto fail; //String
    }

	// error->type
    if(cJSON_AddStringToObject(item, "type", error->type) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

error_t *error_parseFromJSON(char *jsonString){

    error_t *error = NULL;
    cJSON *errorJSON = cJSON_Parse(jsonString);
    if(errorJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // error->status
    cJSON *status = cJSON_GetObjectItemCaseSensitive(errorJSON, "status");
    if(!cJSON_IsString(status) || (status->valuestring == NULL)){
    goto end; //String
    }

    // error->detail
    cJSON *detail = cJSON_GetObjectItemCaseSensitive(errorJSON, "detail");
    if(!cJSON_IsString(detail) || (detail->valuestring == NULL)){
    goto end; //String
    }

    // error->title
    cJSON *title = cJSON_GetObjectItemCaseSensitive(errorJSON, "title");
    if(!cJSON_IsString(title) || (title->valuestring == NULL)){
    goto end; //String
    }

    // error->type
    cJSON *type = cJSON_GetObjectItemCaseSensitive(errorJSON, "type");
    if(!cJSON_IsString(type) || (type->valuestring == NULL)){
    goto end; //String
    }


    error = error_create (
        strdup(status->valuestring),
        strdup(detail->valuestring),
        strdup(title->valuestring),
        strdup(type->valuestring)
        );
 cJSON_Delete(errorJSON);
    return error;
end:
    cJSON_Delete(errorJSON);
    return NULL;

}

