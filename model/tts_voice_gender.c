#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tts_voice_gender.h"



tts_voice_gender_t *tts_voice_gender_create(
    ) {
	tts_voice_gender_t *tts_voice_gender = malloc(sizeof(tts_voice_gender_t));

	return tts_voice_gender;
}


void tts_voice_gender_free(tts_voice_gender_t *tts_voice_gender) {
    listEntry_t *listEntry;

	free(tts_voice_gender);
}

cJSON *tts_voice_gender_convertToJSON(tts_voice_gender_t *tts_voice_gender) {
	cJSON *item = cJSON_CreateObject();
	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

tts_voice_gender_t *tts_voice_gender_parseFromJSON(char *jsonString){

    tts_voice_gender_t *tts_voice_gender = NULL;
    cJSON *tts_voice_genderJSON = cJSON_Parse(jsonString);
    if(tts_voice_genderJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }


    tts_voice_gender = tts_voice_gender_create (
        );
 cJSON_Delete(tts_voice_genderJSON);
    return tts_voice_gender;
end:
    cJSON_Delete(tts_voice_genderJSON);
    return NULL;

}

