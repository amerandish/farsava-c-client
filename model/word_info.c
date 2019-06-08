#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "word_info.h"



word_info_t *word_info_create(
    double startTime,
    double endTime,
    char *word,
    double confidence
    ) {
	word_info_t *word_info = malloc(sizeof(word_info_t));
	word_info->startTime = startTime;
	word_info->endTime = endTime;
	word_info->word = word;
	word_info->confidence = confidence;

	return word_info;
}


void word_info_free(word_info_t *word_info) {
    listEntry_t *listEntry;
    free(word_info->word);

	free(word_info);
}

cJSON *word_info_convertToJSON(word_info_t *word_info) {
	cJSON *item = cJSON_CreateObject();
	// word_info->startTime
    if(cJSON_AddNumberToObject(item, "startTime", word_info->startTime) == NULL) {
    goto fail; //Numeric
    }

	// word_info->endTime
    if(cJSON_AddNumberToObject(item, "endTime", word_info->endTime) == NULL) {
    goto fail; //Numeric
    }

	// word_info->word
    if(cJSON_AddStringToObject(item, "word", word_info->word) == NULL) {
    goto fail; //String
    }

	// word_info->confidence
    if(cJSON_AddNumberToObject(item, "confidence", word_info->confidence) == NULL) {
    goto fail; //Numeric
    }

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

word_info_t *word_info_parseFromJSON(char *jsonString){

    word_info_t *word_info = NULL;
    cJSON *word_infoJSON = cJSON_Parse(jsonString);
    if(word_infoJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // word_info->startTime
    cJSON *startTime = cJSON_GetObjectItemCaseSensitive(word_infoJSON, "startTime");
    if(!cJSON_IsNumber(startTime))
    {
    goto end; //Numeric
    }

    // word_info->endTime
    cJSON *endTime = cJSON_GetObjectItemCaseSensitive(word_infoJSON, "endTime");
    if(!cJSON_IsNumber(endTime))
    {
    goto end; //Numeric
    }

    // word_info->word
    cJSON *word = cJSON_GetObjectItemCaseSensitive(word_infoJSON, "word");
    if(!cJSON_IsString(word) || (word->valuestring == NULL)){
    goto end; //String
    }

    // word_info->confidence
    cJSON *confidence = cJSON_GetObjectItemCaseSensitive(word_infoJSON, "confidence");
    if(!cJSON_IsNumber(confidence))
    {
    goto end; //Numeric
    }


    word_info = word_info_create (
        startTime->valuedouble,
        endTime->valuedouble,
        strdup(word->valuestring),
        confidence->valuedouble
        );
 cJSON_Delete(word_infoJSON);
    return word_info;
end:
    cJSON_Delete(word_infoJSON);
    return NULL;

}

