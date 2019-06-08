#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "speech_recognition_model.h"



speech_recognition_model_t *speech_recognition_model_create(
    ) {
	speech_recognition_model_t *speech_recognition_model = malloc(sizeof(speech_recognition_model_t));

	return speech_recognition_model;
}


void speech_recognition_model_free(speech_recognition_model_t *speech_recognition_model) {
    listEntry_t *listEntry;

	free(speech_recognition_model);
}

cJSON *speech_recognition_model_convertToJSON(speech_recognition_model_t *speech_recognition_model) {
	cJSON *item = cJSON_CreateObject();
	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

speech_recognition_model_t *speech_recognition_model_parseFromJSON(char *jsonString){

    speech_recognition_model_t *speech_recognition_model = NULL;
    cJSON *speech_recognition_modelJSON = cJSON_Parse(jsonString);
    if(speech_recognition_modelJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }


    speech_recognition_model = speech_recognition_model_create (
        );
 cJSON_Delete(speech_recognition_modelJSON);
    return speech_recognition_model;
end:
    cJSON_Delete(speech_recognition_modelJSON);
    return NULL;

}

