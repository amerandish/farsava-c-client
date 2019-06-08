#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "asr_response_body.h"


char* statusasr_response_body_ToString(status_e status){
    char *statusArray[] =  { "queued","processing","done","partial" };
    return statusArray[status];

}

status_e statusasr_response_body_FromString(char* status){
    int stringToReturn = 0;
    char *statusArray[] =  { "queued","processing","done","partial" };
    size_t sizeofArray = sizeof(statusArray) / sizeof(statusArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(status, statusArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
}

asr_response_body_t *asr_response_body_create(
    char *transcriptionId,
    double duration,
    double inferenceTime,
    asr_status_t *status,
    list_t *results
    ) {
	asr_response_body_t *asr_response_body = malloc(sizeof(asr_response_body_t));
	asr_response_body->transcriptionId = transcriptionId;
	asr_response_body->duration = duration;
	asr_response_body->inferenceTime = inferenceTime;
	asr_response_body->status = status;
	asr_response_body->results = results;

	return asr_response_body;
}


void asr_response_body_free(asr_response_body_t *asr_response_body) {
    listEntry_t *listEntry;
    free(asr_response_body->transcriptionId);
	asr_status_free(asr_response_body->status);
		list_ForEach(listEntry, asr_response_body->results) {
		speech_recognition_result_free(listEntry->data);
	}
	list_free(asr_response_body->results);

	free(asr_response_body);
}

cJSON *asr_response_body_convertToJSON(asr_response_body_t *asr_response_body) {
	cJSON *item = cJSON_CreateObject();
	// asr_response_body->transcriptionId
    if(cJSON_AddStringToObject(item, "transcriptionId", asr_response_body->transcriptionId) == NULL) {
    goto fail; //String
    }

	// asr_response_body->duration
    if(cJSON_AddNumberToObject(item, "duration", asr_response_body->duration) == NULL) {
    goto fail; //Numeric
    }

	// asr_response_body->inferenceTime
    if(cJSON_AddNumberToObject(item, "inferenceTime", asr_response_body->inferenceTime) == NULL) {
    goto fail; //Numeric
    }

	// asr_response_body->status
	cJSON *status = asr_status_convertToJSON(asr_response_body->status);
	if(status == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "status", status);
	if(item->child == NULL) {
		goto fail;
	}

	// asr_response_body->results
    cJSON *results = cJSON_AddArrayToObject(item, "results");
	if(results == NULL) {
		goto fail; //nonprimitive container
	}

	listEntry_t *resultsListEntry;
	list_ForEach(resultsListEntry, asr_response_body->results) {
		cJSON *item = speech_recognition_result_convertToJSON(resultsListEntry->data);
		if(item == NULL) {
			goto fail;
		}
		cJSON_AddItemToArray(results, item);
	}

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

asr_response_body_t *asr_response_body_parseFromJSON(char *jsonString){

    asr_response_body_t *asr_response_body = NULL;
    cJSON *asr_response_bodyJSON = cJSON_Parse(jsonString);
    if(asr_response_bodyJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // asr_response_body->transcriptionId
    cJSON *transcriptionId = cJSON_GetObjectItemCaseSensitive(asr_response_bodyJSON, "transcriptionId");
    if(!cJSON_IsString(transcriptionId) || (transcriptionId->valuestring == NULL)){
    goto end; //String
    }

    // asr_response_body->duration
    cJSON *duration = cJSON_GetObjectItemCaseSensitive(asr_response_bodyJSON, "duration");
    if(!cJSON_IsNumber(duration))
    {
    goto end; //Numeric
    }

    // asr_response_body->inferenceTime
    cJSON *inferenceTime = cJSON_GetObjectItemCaseSensitive(asr_response_bodyJSON, "inferenceTime");
    if(!cJSON_IsNumber(inferenceTime))
    {
    goto end; //Numeric
    }

    // asr_response_body->status
    asr_status_t *status;
    cJSON *statusJSON = cJSON_GetObjectItemCaseSensitive(asr_response_bodyJSON, "status");
    if(asr_response_bodyJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *statusJSONData = cJSON_Print(statusJSON);
    status = asr_status_parseFromJSON(statusJSONData);

    // asr_response_body->results
    cJSON *results;
    cJSON *resultsJSON = cJSON_GetObjectItemCaseSensitive(asr_response_bodyJSON,"results");
    if(!cJSON_IsArray(resultsJSON)){
        goto end; //nonprimitive container
    }

    list_t *resultsList = list_create();

    cJSON_ArrayForEach(results,resultsJSON )
    {
        if(!cJSON_IsObject(results)){
            goto end;
        }
		char *JSONData = cJSON_Print(results);
        speech_recognition_result_t *resultsItem = speech_recognition_result_parseFromJSON(JSONData);

        list_addElement(resultsList, resultsItem);
        free(JSONData);
    }


    asr_response_body = asr_response_body_create (
        strdup(transcriptionId->valuestring),
        duration->valuedouble,
        inferenceTime->valuedouble,
        status,
        resultsList
        );
        free(statusJSONData);
 cJSON_Delete(asr_response_bodyJSON);
    return asr_response_body;
end:
    cJSON_Delete(asr_response_bodyJSON);
    return NULL;

}

