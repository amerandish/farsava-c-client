#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "language_model_result.h"


char* statuslanguage_model_result_ToString(status_e status){
    char *statusArray[] =  { "queued","training","trained" };
    return statusArray[status];

}

status_e statuslanguage_model_result_FromString(char* status){
    int stringToReturn = 0;
    char *statusArray[] =  { "queued","training","trained" };
    size_t sizeofArray = sizeof(statusArray) / sizeof(statusArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(status, statusArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
}

language_model_result_t *language_model_result_create(
    char *languageModelId,
    char *name,
    lm_status_t *status
    ) {
	language_model_result_t *language_model_result = malloc(sizeof(language_model_result_t));
	language_model_result->languageModelId = languageModelId;
	language_model_result->name = name;
	language_model_result->status = status;

	return language_model_result;
}


void language_model_result_free(language_model_result_t *language_model_result) {
    listEntry_t *listEntry;
    free(language_model_result->languageModelId);
    free(language_model_result->name);
	lm_status_free(language_model_result->status);

	free(language_model_result);
}

cJSON *language_model_result_convertToJSON(language_model_result_t *language_model_result) {
	cJSON *item = cJSON_CreateObject();
	// language_model_result->languageModelId
    if(cJSON_AddStringToObject(item, "languageModelId", language_model_result->languageModelId) == NULL) {
    goto fail; //String
    }

	// language_model_result->name
    if(cJSON_AddStringToObject(item, "name", language_model_result->name) == NULL) {
    goto fail; //String
    }

	// language_model_result->status
	cJSON *status = lm_status_convertToJSON(language_model_result->status);
	if(status == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "status", status);
	if(item->child == NULL) {
		goto fail;
	}

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

language_model_result_t *language_model_result_parseFromJSON(char *jsonString){

    language_model_result_t *language_model_result = NULL;
    cJSON *language_model_resultJSON = cJSON_Parse(jsonString);
    if(language_model_resultJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // language_model_result->languageModelId
    cJSON *languageModelId = cJSON_GetObjectItemCaseSensitive(language_model_resultJSON, "languageModelId");
    if(!cJSON_IsString(languageModelId) || (languageModelId->valuestring == NULL)){
    goto end; //String
    }

    // language_model_result->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(language_model_resultJSON, "name");
    if(!cJSON_IsString(name) || (name->valuestring == NULL)){
    goto end; //String
    }

    // language_model_result->status
    lm_status_t *status;
    cJSON *statusJSON = cJSON_GetObjectItemCaseSensitive(language_model_resultJSON, "status");
    if(language_model_resultJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *statusJSONData = cJSON_Print(statusJSON);
    status = lm_status_parseFromJSON(statusJSONData);


    language_model_result = language_model_result_create (
        strdup(languageModelId->valuestring),
        strdup(name->valuestring),
        status
        );
        free(statusJSONData);
 cJSON_Delete(language_model_resultJSON);
    return language_model_result;
end:
    cJSON_Delete(language_model_resultJSON);
    return NULL;

}

