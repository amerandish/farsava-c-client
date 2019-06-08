#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "recognition_config.h"


char* audioEncodingrecognition_config_ToString(audioEncoding_e audioEncoding){
    char *audioEncodingArray[] =  { "LINEAR16","FLAC","MP3" };
    return audioEncodingArray[audioEncoding];

}

audioEncoding_e audioEncodingrecognition_config_FromString(char* audioEncoding){
    int stringToReturn = 0;
    char *audioEncodingArray[] =  { "LINEAR16","FLAC","MP3" };
    size_t sizeofArray = sizeof(audioEncodingArray) / sizeof(audioEncodingArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(audioEncoding, audioEncodingArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
}
char* languageCoderecognition_config_ToString(languageCode_e languageCode){
    char *languageCodeArray[] =  { "fa","en" };
    return languageCodeArray[languageCode];

}

languageCode_e languageCoderecognition_config_FromString(char* languageCode){
    int stringToReturn = 0;
    char *languageCodeArray[] =  { "fa","en" };
    size_t sizeofArray = sizeof(languageCodeArray) / sizeof(languageCodeArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(languageCode, languageCodeArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
}
char* asrModelrecognition_config_ToString(asrModel_e asrModel){
    char *asrModelArray[] =  { "_default","video","command_and_search","phone_call" };
    return asrModelArray[asrModel];

}

asrModel_e asrModelrecognition_config_FromString(char* asrModel){
    int stringToReturn = 0;
    char *asrModelArray[] =  { "_default","video","command_and_search","phone_call" };
    size_t sizeofArray = sizeof(asrModelArray) / sizeof(asrModelArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(asrModel, asrModelArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
}

recognition_config_t *recognition_config_create(
    audio_encoding_t *audioEncoding,
    int sampleRateHertz,
    language_code_t *languageCode,
    int maxAlternatives,
    bool profanityFilter,
    speech_recognition_model_t *asrModel,
    char *languageModel
    ) {
	recognition_config_t *recognition_config = malloc(sizeof(recognition_config_t));
	recognition_config->audioEncoding = audioEncoding;
	recognition_config->sampleRateHertz = sampleRateHertz;
	recognition_config->languageCode = languageCode;
	recognition_config->maxAlternatives = maxAlternatives;
	recognition_config->profanityFilter = profanityFilter;
	recognition_config->asrModel = asrModel;
	recognition_config->languageModel = languageModel;

	return recognition_config;
}


void recognition_config_free(recognition_config_t *recognition_config) {
    listEntry_t *listEntry;
	audio_encoding_free(recognition_config->audioEncoding);
	language_code_free(recognition_config->languageCode);
	speech_recognition_model_free(recognition_config->asrModel);
    free(recognition_config->languageModel);

	free(recognition_config);
}

cJSON *recognition_config_convertToJSON(recognition_config_t *recognition_config) {
	cJSON *item = cJSON_CreateObject();
	// recognition_config->audioEncoding
	cJSON *audioEncoding = audio_encoding_convertToJSON(recognition_config->audioEncoding);
	if(audioEncoding == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "audioEncoding", audioEncoding);
	if(item->child == NULL) {
		goto fail;
	}

	// recognition_config->sampleRateHertz
    if(cJSON_AddNumberToObject(item, "sampleRateHertz", recognition_config->sampleRateHertz) == NULL) {
    goto fail; //Numeric
    }

	// recognition_config->languageCode
	cJSON *languageCode = language_code_convertToJSON(recognition_config->languageCode);
	if(languageCode == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "languageCode", languageCode);
	if(item->child == NULL) {
		goto fail;
	}

	// recognition_config->maxAlternatives
    if(cJSON_AddNumberToObject(item, "maxAlternatives", recognition_config->maxAlternatives) == NULL) {
    goto fail; //Numeric
    }

	// recognition_config->profanityFilter
    if(cJSON_AddBoolToObject(item, "profanityFilter", recognition_config->profanityFilter) == NULL) {
    goto fail; //Numeric
    }

	// recognition_config->asrModel
	cJSON *asrModel = speech_recognition_model_convertToJSON(recognition_config->asrModel);
	if(asrModel == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "asrModel", asrModel);
	if(item->child == NULL) {
		goto fail;
	}

	// recognition_config->languageModel
    if(cJSON_AddStringToObject(item, "languageModel", recognition_config->languageModel) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

recognition_config_t *recognition_config_parseFromJSON(char *jsonString){

    recognition_config_t *recognition_config = NULL;
    cJSON *recognition_configJSON = cJSON_Parse(jsonString);
    if(recognition_configJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // recognition_config->audioEncoding
    audio_encoding_t *audioEncoding;
    cJSON *audioEncodingJSON = cJSON_GetObjectItemCaseSensitive(recognition_configJSON, "audioEncoding");
    if(recognition_configJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *audioEncodingJSONData = cJSON_Print(audioEncodingJSON);
    audioEncoding = audio_encoding_parseFromJSON(audioEncodingJSONData);

    // recognition_config->sampleRateHertz
    cJSON *sampleRateHertz = cJSON_GetObjectItemCaseSensitive(recognition_configJSON, "sampleRateHertz");
    if(!cJSON_IsNumber(sampleRateHertz))
    {
    goto end; //Numeric
    }

    // recognition_config->languageCode
    language_code_t *languageCode;
    cJSON *languageCodeJSON = cJSON_GetObjectItemCaseSensitive(recognition_configJSON, "languageCode");
    if(recognition_configJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *languageCodeJSONData = cJSON_Print(languageCodeJSON);
    languageCode = language_code_parseFromJSON(languageCodeJSONData);

    // recognition_config->maxAlternatives
    cJSON *maxAlternatives = cJSON_GetObjectItemCaseSensitive(recognition_configJSON, "maxAlternatives");
    if(!cJSON_IsNumber(maxAlternatives))
    {
    goto end; //Numeric
    }

    // recognition_config->profanityFilter
    cJSON *profanityFilter = cJSON_GetObjectItemCaseSensitive(recognition_configJSON, "profanityFilter");
    if(!cJSON_IsBool(profanityFilter))
    {
    goto end; //Numeric
    }

    // recognition_config->asrModel
    speech_recognition_model_t *asrModel;
    cJSON *asrModelJSON = cJSON_GetObjectItemCaseSensitive(recognition_configJSON, "asrModel");
    if(recognition_configJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *asrModelJSONData = cJSON_Print(asrModelJSON);
    asrModel = speech_recognition_model_parseFromJSON(asrModelJSONData);

    // recognition_config->languageModel
    cJSON *languageModel = cJSON_GetObjectItemCaseSensitive(recognition_configJSON, "languageModel");
    if(!cJSON_IsString(languageModel) || (languageModel->valuestring == NULL)){
    goto end; //String
    }


    recognition_config = recognition_config_create (
        audioEncoding,
        sampleRateHertz->valuedouble,
        languageCode,
        maxAlternatives->valuedouble,
        profanityFilter->valueint,
        asrModel,
        strdup(languageModel->valuestring)
        );
        free(audioEncodingJSONData);
        free(languageCodeJSONData);
        free(asrModelJSONData);
 cJSON_Delete(recognition_configJSON);
    return recognition_config;
end:
    cJSON_Delete(recognition_configJSON);
    return NULL;

}

