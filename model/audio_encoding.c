#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "audio_encoding.h"



audio_encoding_t *audio_encoding_create(
    ) {
	audio_encoding_t *audio_encoding = malloc(sizeof(audio_encoding_t));

	return audio_encoding;
}


void audio_encoding_free(audio_encoding_t *audio_encoding) {
    listEntry_t *listEntry;

	free(audio_encoding);
}

cJSON *audio_encoding_convertToJSON(audio_encoding_t *audio_encoding) {
	cJSON *item = cJSON_CreateObject();
	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

audio_encoding_t *audio_encoding_parseFromJSON(char *jsonString){

    audio_encoding_t *audio_encoding = NULL;
    cJSON *audio_encodingJSON = cJSON_Parse(jsonString);
    if(audio_encodingJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }


    audio_encoding = audio_encoding_create (
        );
 cJSON_Delete(audio_encodingJSON);
    return audio_encoding;
end:
    cJSON_Delete(audio_encodingJSON);
    return NULL;

}

