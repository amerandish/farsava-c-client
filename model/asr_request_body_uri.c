#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "asr_request_body_uri.h"



asr_request_body_uri_t *asr_request_body_uri_create(
    recognition_config_t *config,
    recognition_audio_uri_t *audio
    ) {
	asr_request_body_uri_t *asr_request_body_uri = malloc(sizeof(asr_request_body_uri_t));
	asr_request_body_uri->config = config;
	asr_request_body_uri->audio = audio;

	return asr_request_body_uri;
}


void asr_request_body_uri_free(asr_request_body_uri_t *asr_request_body_uri) {
    listEntry_t *listEntry;
	recognition_config_free(asr_request_body_uri->config);
	recognition_audio_uri_free(asr_request_body_uri->audio);

	free(asr_request_body_uri);
}

cJSON *asr_request_body_uri_convertToJSON(asr_request_body_uri_t *asr_request_body_uri) {
	cJSON *item = cJSON_CreateObject();
	// asr_request_body_uri->config
	cJSON *config = recognition_config_convertToJSON(asr_request_body_uri->config);
	if(config == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "config", config);
	if(item->child == NULL) {
		goto fail;
	}

	// asr_request_body_uri->audio
	cJSON *audio = recognition_audio_uri_convertToJSON(asr_request_body_uri->audio);
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

asr_request_body_uri_t *asr_request_body_uri_parseFromJSON(char *jsonString){

    asr_request_body_uri_t *asr_request_body_uri = NULL;
    cJSON *asr_request_body_uriJSON = cJSON_Parse(jsonString);
    if(asr_request_body_uriJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // asr_request_body_uri->config
    recognition_config_t *config;
    cJSON *configJSON = cJSON_GetObjectItemCaseSensitive(asr_request_body_uriJSON, "config");
    if(asr_request_body_uriJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *configJSONData = cJSON_Print(configJSON);
    config = recognition_config_parseFromJSON(configJSONData);

    // asr_request_body_uri->audio
    recognition_audio_uri_t *audio;
    cJSON *audioJSON = cJSON_GetObjectItemCaseSensitive(asr_request_body_uriJSON, "audio");
    if(asr_request_body_uriJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *audioJSONData = cJSON_Print(audioJSON);
    audio = recognition_audio_uri_parseFromJSON(audioJSONData);


    asr_request_body_uri = asr_request_body_uri_create (
        config,
        audio
        );
        free(configJSONData);
        free(audioJSONData);
 cJSON_Delete(asr_request_body_uriJSON);
    return asr_request_body_uri;
end:
    cJSON_Delete(asr_request_body_uriJSON);
    return NULL;

}

