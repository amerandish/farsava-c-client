#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "voice_selection_params.h"


char* languageCodevoice_selection_params_ToString(languageCode_e languageCode){
    char *languageCodeArray[] =  { "fa","en" };
    return languageCodeArray[languageCode];

}

languageCode_e languageCodevoice_selection_params_FromString(char* languageCode){
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
char* gendervoice_selection_params_ToString(gender_e gender){
    char *genderArray[] =  { "male","female" };
    return genderArray[gender];

}

gender_e gendervoice_selection_params_FromString(char* gender){
    int stringToReturn = 0;
    char *genderArray[] =  { "male","female" };
    size_t sizeofArray = sizeof(genderArray) / sizeof(genderArray[0]);
    while(stringToReturn < sizeofArray) {
        if(strcmp(gender, genderArray[stringToReturn]) == 0) {
            return stringToReturn;
        }
        stringToReturn++;
    }
}

voice_selection_params_t *voice_selection_params_create(
    char *voiceId,
    language_code_t *languageCode,
    char *name,
    tts_voice_gender_t *gender
    ) {
	voice_selection_params_t *voice_selection_params = malloc(sizeof(voice_selection_params_t));
	voice_selection_params->voiceId = voiceId;
	voice_selection_params->languageCode = languageCode;
	voice_selection_params->name = name;
	voice_selection_params->gender = gender;

	return voice_selection_params;
}


void voice_selection_params_free(voice_selection_params_t *voice_selection_params) {
    listEntry_t *listEntry;
    free(voice_selection_params->voiceId);
	language_code_free(voice_selection_params->languageCode);
    free(voice_selection_params->name);
	tts_voice_gender_free(voice_selection_params->gender);

	free(voice_selection_params);
}

cJSON *voice_selection_params_convertToJSON(voice_selection_params_t *voice_selection_params) {
	cJSON *item = cJSON_CreateObject();
	// voice_selection_params->voiceId
    if(cJSON_AddStringToObject(item, "voiceId", voice_selection_params->voiceId) == NULL) {
    goto fail; //String
    }

	// voice_selection_params->languageCode
	cJSON *languageCode = language_code_convertToJSON(voice_selection_params->languageCode);
	if(languageCode == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "languageCode", languageCode);
	if(item->child == NULL) {
		goto fail;
	}

	// voice_selection_params->name
    if(cJSON_AddStringToObject(item, "name", voice_selection_params->name) == NULL) {
    goto fail; //String
    }

	// voice_selection_params->gender
	cJSON *gender = tts_voice_gender_convertToJSON(voice_selection_params->gender);
	if(gender == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "gender", gender);
	if(item->child == NULL) {
		goto fail;
	}

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

voice_selection_params_t *voice_selection_params_parseFromJSON(char *jsonString){

    voice_selection_params_t *voice_selection_params = NULL;
    cJSON *voice_selection_paramsJSON = cJSON_Parse(jsonString);
    if(voice_selection_paramsJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // voice_selection_params->voiceId
    cJSON *voiceId = cJSON_GetObjectItemCaseSensitive(voice_selection_paramsJSON, "voiceId");
    if(!cJSON_IsString(voiceId) || (voiceId->valuestring == NULL)){
    goto end; //String
    }

    // voice_selection_params->languageCode
    language_code_t *languageCode;
    cJSON *languageCodeJSON = cJSON_GetObjectItemCaseSensitive(voice_selection_paramsJSON, "languageCode");
    if(voice_selection_paramsJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *languageCodeJSONData = cJSON_Print(languageCodeJSON);
    languageCode = language_code_parseFromJSON(languageCodeJSONData);

    // voice_selection_params->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(voice_selection_paramsJSON, "name");
    if(!cJSON_IsString(name) || (name->valuestring == NULL)){
    goto end; //String
    }

    // voice_selection_params->gender
    tts_voice_gender_t *gender;
    cJSON *genderJSON = cJSON_GetObjectItemCaseSensitive(voice_selection_paramsJSON, "gender");
    if(voice_selection_paramsJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *genderJSONData = cJSON_Print(genderJSON);
    gender = tts_voice_gender_parseFromJSON(genderJSONData);


    voice_selection_params = voice_selection_params_create (
        strdup(voiceId->valuestring),
        languageCode,
        strdup(name->valuestring),
        gender
        );
        free(languageCodeJSONData);
        free(genderJSONData);
 cJSON_Delete(voice_selection_paramsJSON);
    return voice_selection_params;
end:
    cJSON_Delete(voice_selection_paramsJSON);
    return NULL;

}

