#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "recognition_audio_data.h"



recognition_audio_data_t *recognition_audio_data_create(
    ) {
	recognition_audio_data_t *recognition_audio_data = malloc(sizeof(recognition_audio_data_t));
	recognition_audio_data->data = data;

	return recognition_audio_data;
}


void recognition_audio_data_free(recognition_audio_data_t *recognition_audio_data) {
    listEntry_t *listEntry;

	free(recognition_audio_data);
}

cJSON *recognition_audio_data_convertToJSON(recognition_audio_data_t *recognition_audio_data) {
	cJSON *item = cJSON_CreateObject();
	// recognition_audio_data->data

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

recognition_audio_data_t *recognition_audio_data_parseFromJSON(char *jsonString){

    recognition_audio_data_t *recognition_audio_data = NULL;
    cJSON *recognition_audio_dataJSON = cJSON_Parse(jsonString);
    if(recognition_audio_dataJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // recognition_audio_data->data


    recognition_audio_data = recognition_audio_data_create (
        );
 cJSON_Delete(recognition_audio_dataJSON);
    return recognition_audio_data;
end:
    cJSON_Delete(recognition_audio_dataJSON);
    return NULL;

}

