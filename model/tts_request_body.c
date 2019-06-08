#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tts_request_body.h"



tts_request_body_t *tts_request_body_create(
    synthesis_input_t *synthesisInput,
    voice_selection_params_t *voiceConfig,
    tts_audio_config_t *audioConfig
    ) {
	tts_request_body_t *tts_request_body = malloc(sizeof(tts_request_body_t));
	tts_request_body->synthesisInput = synthesisInput;
	tts_request_body->voiceConfig = voiceConfig;
	tts_request_body->audioConfig = audioConfig;

	return tts_request_body;
}


void tts_request_body_free(tts_request_body_t *tts_request_body) {
    listEntry_t *listEntry;
	synthesis_input_free(tts_request_body->synthesisInput);
	voice_selection_params_free(tts_request_body->voiceConfig);
	tts_audio_config_free(tts_request_body->audioConfig);

	free(tts_request_body);
}

cJSON *tts_request_body_convertToJSON(tts_request_body_t *tts_request_body) {
	cJSON *item = cJSON_CreateObject();
	// tts_request_body->synthesisInput
	cJSON *synthesisInput = synthesis_input_convertToJSON(tts_request_body->synthesisInput);
	if(synthesisInput == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "synthesisInput", synthesisInput);
	if(item->child == NULL) {
		goto fail;
	}

	// tts_request_body->voiceConfig
	cJSON *voiceConfig = voice_selection_params_convertToJSON(tts_request_body->voiceConfig);
	if(voiceConfig == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "voiceConfig", voiceConfig);
	if(item->child == NULL) {
		goto fail;
	}

	// tts_request_body->audioConfig
	cJSON *audioConfig = tts_audio_config_convertToJSON(tts_request_body->audioConfig);
	if(audioConfig == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "audioConfig", audioConfig);
	if(item->child == NULL) {
		goto fail;
	}

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

tts_request_body_t *tts_request_body_parseFromJSON(char *jsonString){

    tts_request_body_t *tts_request_body = NULL;
    cJSON *tts_request_bodyJSON = cJSON_Parse(jsonString);
    if(tts_request_bodyJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // tts_request_body->synthesisInput
    synthesis_input_t *synthesisInput;
    cJSON *synthesisInputJSON = cJSON_GetObjectItemCaseSensitive(tts_request_bodyJSON, "synthesisInput");
    if(tts_request_bodyJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *synthesisInputJSONData = cJSON_Print(synthesisInputJSON);
    synthesisInput = synthesis_input_parseFromJSON(synthesisInputJSONData);

    // tts_request_body->voiceConfig
    voice_selection_params_t *voiceConfig;
    cJSON *voiceConfigJSON = cJSON_GetObjectItemCaseSensitive(tts_request_bodyJSON, "voiceConfig");
    if(tts_request_bodyJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *voiceConfigJSONData = cJSON_Print(voiceConfigJSON);
    voiceConfig = voice_selection_params_parseFromJSON(voiceConfigJSONData);

    // tts_request_body->audioConfig
    tts_audio_config_t *audioConfig;
    cJSON *audioConfigJSON = cJSON_GetObjectItemCaseSensitive(tts_request_bodyJSON, "audioConfig");
    if(tts_request_bodyJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *audioConfigJSONData = cJSON_Print(audioConfigJSON);
    audioConfig = tts_audio_config_parseFromJSON(audioConfigJSONData);


    tts_request_body = tts_request_body_create (
        synthesisInput,
        voiceConfig,
        audioConfig
        );
        free(synthesisInputJSONData);
        free(voiceConfigJSONData);
        free(audioConfigJSONData);
 cJSON_Delete(tts_request_bodyJSON);
    return tts_request_body;
end:
    cJSON_Delete(tts_request_bodyJSON);
    return NULL;

}

