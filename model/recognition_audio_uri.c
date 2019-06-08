#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "recognition_audio_uri.h"



recognition_audio_uri_t *recognition_audio_uri_create(
    char *uri
    ) {
	recognition_audio_uri_t *recognition_audio_uri = malloc(sizeof(recognition_audio_uri_t));
	recognition_audio_uri->uri = uri;

	return recognition_audio_uri;
}


void recognition_audio_uri_free(recognition_audio_uri_t *recognition_audio_uri) {
    listEntry_t *listEntry;
    free(recognition_audio_uri->uri);

	free(recognition_audio_uri);
}

cJSON *recognition_audio_uri_convertToJSON(recognition_audio_uri_t *recognition_audio_uri) {
	cJSON *item = cJSON_CreateObject();
	// recognition_audio_uri->uri
    if(cJSON_AddStringToObject(item, "uri", recognition_audio_uri->uri) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

recognition_audio_uri_t *recognition_audio_uri_parseFromJSON(char *jsonString){

    recognition_audio_uri_t *recognition_audio_uri = NULL;
    cJSON *recognition_audio_uriJSON = cJSON_Parse(jsonString);
    if(recognition_audio_uriJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // recognition_audio_uri->uri
    cJSON *uri = cJSON_GetObjectItemCaseSensitive(recognition_audio_uriJSON, "uri");
    if(!cJSON_IsString(uri) || (uri->valuestring == NULL)){
    goto end; //String
    }


    recognition_audio_uri = recognition_audio_uri_create (
        strdup(uri->valuestring)
        );
 cJSON_Delete(recognition_audio_uriJSON);
    return recognition_audio_uri;
end:
    cJSON_Delete(recognition_audio_uriJSON);
    return NULL;

}

