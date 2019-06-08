#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "asr_status.h"



asr_status_t *asr_status_create(
    ) {
	asr_status_t *asr_status = malloc(sizeof(asr_status_t));

	return asr_status;
}


void asr_status_free(asr_status_t *asr_status) {
    listEntry_t *listEntry;

	free(asr_status);
}

cJSON *asr_status_convertToJSON(asr_status_t *asr_status) {
	cJSON *item = cJSON_CreateObject();
	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

asr_status_t *asr_status_parseFromJSON(char *jsonString){

    asr_status_t *asr_status = NULL;
    cJSON *asr_statusJSON = cJSON_Parse(jsonString);
    if(asr_statusJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }


    asr_status = asr_status_create (
        );
 cJSON_Delete(asr_statusJSON);
    return asr_status;
end:
    cJSON_Delete(asr_statusJSON);
    return NULL;

}

