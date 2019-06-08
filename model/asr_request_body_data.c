#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "asr_request_body_data.h"



asr_request_body_data_t *asr_request_body_data_create(
    recognition_config_t *config,
    recognition_audio_data_t *audio
    ) {
	asr_request_body_data_t *asr_request_body_data = malloc(sizeof(asr_request_body_data_t));
	asr_request_body_data->config = config;
	asr_request_body_data->audio = audio;

	return asr_request_body_data;
}


void asr_request_body_data_free(asr_request_body_data_t *asr_request_body_data) {
    listEntry_t *listEntry;
	recognition_config_free(asr_request_body_data->config);
	recognition_audio_data_free(asr_request_body_data->audio);

	free(asr_request_body_data);
}

cJSON *asr_request_body_data_convertToJSON(asr_request_body_data_t *asr_request_body_data) {
	cJSON *item = cJSON_CreateObject();
	// asr_request_body_data->config
	cJSON *config = recognition_config_convertToJSON(asr_request_body_data->config);
	if(config == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "config", config);
	if(item->child == NULL) {
		goto fail;
	}

	// asr_request_body_data->audio
	cJSON *audio = recognition_audio_data_convertToJSON(asr_request_body_data->audio);
	if(audio == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "audio", audio);
	if(item->child == NULL) {
		goto fail;
	}

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

asr_request_body_data_t *asr_request_body_data_parseFromJSON(char *jsonString){

    asr_request_body_data_t *asr_request_body_data = NULL;
    cJSON *asr_request_body_dataJSON = cJSON_Parse(jsonString);
    if(asr_request_body_dataJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // asr_request_body_data->config
    recognition_config_t *config;
    cJSON *configJSON = cJSON_GetObjectItemCaseSensitive(asr_request_body_dataJSON, "config");
    if(asr_request_body_dataJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *configJSONData = cJSON_Print(configJSON);
    config = recognition_config_parseFromJSON(configJSONData);

    // asr_request_body_data->audio
    recognition_audio_data_t *audio;
    cJSON *audioJSON = cJSON_GetObjectItemCaseSensitive(asr_request_body_dataJSON, "audio");
    if(asr_request_body_dataJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *audioJSONData = cJSON_Print(audioJSON);
    audio = recognition_audio_data_parseFromJSON(audioJSONData);


    asr_request_body_data = asr_request_body_data_create (
        config,
        audio
        );
        free(configJSONData);
        free(audioJSONData);
 cJSON_Delete(asr_request_body_dataJSON);
    return asr_request_body_data;
end:
    cJSON_Delete(asr_request_body_dataJSON);
    return NULL;

}

