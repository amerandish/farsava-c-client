#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lm_status.h"



lm_status_t *lm_status_create(
    ) {
	lm_status_t *lm_status = malloc(sizeof(lm_status_t));

	return lm_status;
}


void lm_status_free(lm_status_t *lm_status) {
    listEntry_t *listEntry;

	free(lm_status);
}

cJSON *lm_status_convertToJSON(lm_status_t *lm_status) {
	cJSON *item = cJSON_CreateObject();
	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

lm_status_t *lm_status_parseFromJSON(char *jsonString){

    lm_status_t *lm_status = NULL;
    cJSON *lm_statusJSON = cJSON_Parse(jsonString);
    if(lm_statusJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }


    lm_status = lm_status_create (
        );
 cJSON_Delete(lm_statusJSON);
    return lm_status;
end:
    cJSON_Delete(lm_statusJSON);
    return NULL;

}

