#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tts_response_body.h"



tts_response_body_t *tts_response_body_create(
    ) {
	tts_response_body_t *tts_response_body = malloc(sizeof(tts_response_body_t));
	tts_response_body->audioContent = audioContent;

	return tts_response_body;
}


void tts_response_body_free(tts_response_body_t *tts_response_body) {
    listEntry_t *listEntry;

	free(tts_response_body);
}

cJSON *tts_response_body_convertToJSON(tts_response_body_t *tts_response_body) {
	cJSON *item = cJSON_CreateObject();
	// tts_response_body->audioContent

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

tts_response_body_t *tts_response_body_parseFromJSON(char *jsonString){

    tts_response_body_t *tts_response_body = NULL;
    cJSON *tts_response_bodyJSON = cJSON_Parse(jsonString);
    if(tts_response_bodyJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // tts_response_body->audioContent


    tts_response_body = tts_response_body_create (
        );
 cJSON_Delete(tts_response_bodyJSON);
    return tts_response_body;
end:
    cJSON_Delete(tts_response_bodyJSON);
    return NULL;

}

