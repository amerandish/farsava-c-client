#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tts_audio_config.h"


char* audioEncodingtts_audio_config_ToString(audioEncoding_e audioEncoding){
    char *audioEncodingArray[] =  { "LINEAR16","FLAC","MP3" };
    return audioEncodingArray[audioEncoding];

}

audioEncoding_e audioEncodingtts_audio_config_FromString(char* audioEncoding){
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

tts_audio_config_t *tts_audio_config_create(
    audio_encoding_t *audioEncoding,
    int sampleRateHertz,
    double speakingRate,
    double pitch,
    double volumeGainDb
    ) {
	tts_audio_config_t *tts_audio_config = malloc(sizeof(tts_audio_config_t));
	tts_audio_config->audioEncoding = audioEncoding;
	tts_audio_config->sampleRateHertz = sampleRateHertz;
	tts_audio_config->speakingRate = speakingRate;
	tts_audio_config->pitch = pitch;
	tts_audio_config->volumeGainDb = volumeGainDb;

	return tts_audio_config;
}


void tts_audio_config_free(tts_audio_config_t *tts_audio_config) {
    listEntry_t *listEntry;
	audio_encoding_free(tts_audio_config->audioEncoding);

	free(tts_audio_config);
}

cJSON *tts_audio_config_convertToJSON(tts_audio_config_t *tts_audio_config) {
	cJSON *item = cJSON_CreateObject();
	// tts_audio_config->audioEncoding
	cJSON *audioEncoding = audio_encoding_convertToJSON(tts_audio_config->audioEncoding);
	if(audioEncoding == NULL) {
		goto fail; //nonprimitive
	}
	cJSON_AddItemToObject(item, "audioEncoding", audioEncoding);
	if(item->child == NULL) {
		goto fail;
	}

	// tts_audio_config->sampleRateHertz
    if(cJSON_AddNumberToObject(item, "sampleRateHertz", tts_audio_config->sampleRateHertz) == NULL) {
    goto fail; //Numeric
    }

	// tts_audio_config->speakingRate
    if(cJSON_AddNumberToObject(item, "speakingRate", tts_audio_config->speakingRate) == NULL) {
    goto fail; //Numeric
    }

	// tts_audio_config->pitch
    if(cJSON_AddNumberToObject(item, "pitch", tts_audio_config->pitch) == NULL) {
    goto fail; //Numeric
    }

	// tts_audio_config->volumeGainDb
    if(cJSON_AddNumberToObject(item, "volumeGainDb", tts_audio_config->volumeGainDb) == NULL) {
    goto fail; //Numeric
    }

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

tts_audio_config_t *tts_audio_config_parseFromJSON(char *jsonString){

    tts_audio_config_t *tts_audio_config = NULL;
    cJSON *tts_audio_configJSON = cJSON_Parse(jsonString);
    if(tts_audio_configJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // tts_audio_config->audioEncoding
    audio_encoding_t *audioEncoding;
    cJSON *audioEncodingJSON = cJSON_GetObjectItemCaseSensitive(tts_audio_configJSON, "audioEncoding");
    if(tts_audio_configJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
            fprintf(stderr, "Error Before: %s\n", error_ptr);
        goto end; //nonprimitive
    }
    char *audioEncodingJSONData = cJSON_Print(audioEncodingJSON);
    audioEncoding = audio_encoding_parseFromJSON(audioEncodingJSONData);

    // tts_audio_config->sampleRateHertz
    cJSON *sampleRateHertz = cJSON_GetObjectItemCaseSensitive(tts_audio_configJSON, "sampleRateHertz");
    if(!cJSON_IsNumber(sampleRateHertz))
    {
    goto end; //Numeric
    }

    // tts_audio_config->speakingRate
    cJSON *speakingRate = cJSON_GetObjectItemCaseSensitive(tts_audio_configJSON, "speakingRate");
    if(!cJSON_IsNumber(speakingRate))
    {
    goto end; //Numeric
    }

    // tts_audio_config->pitch
    cJSON *pitch = cJSON_GetObjectItemCaseSensitive(tts_audio_configJSON, "pitch");
    if(!cJSON_IsNumber(pitch))
    {
    goto end; //Numeric
    }

    // tts_audio_config->volumeGainDb
    cJSON *volumeGainDb = cJSON_GetObjectItemCaseSensitive(tts_audio_configJSON, "volumeGainDb");
    if(!cJSON_IsNumber(volumeGainDb))
    {
    goto end; //Numeric
    }


    tts_audio_config = tts_audio_config_create (
        audioEncoding,
        sampleRateHertz->valuedouble,
        speakingRate->valuedouble,
        pitch->valuedouble,
        volumeGainDb->valuedouble
        );
        free(audioEncodingJSONData);
 cJSON_Delete(tts_audio_configJSON);
    return tts_audio_config;
end:
    cJSON_Delete(tts_audio_configJSON);
    return NULL;

}

