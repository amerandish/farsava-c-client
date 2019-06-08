#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "speech_recognition_result.h"



speech_recognition_result_t *speech_recognition_result_create(
    char *transcript,
    double confidence,
    list_t *words
    ) {
	speech_recognition_result_t *speech_recognition_result = malloc(sizeof(speech_recognition_result_t));
	speech_recognition_result->transcript = transcript;
	speech_recognition_result->confidence = confidence;
	speech_recognition_result->words = words;

	return speech_recognition_result;
}


void speech_recognition_result_free(speech_recognition_result_t *speech_recognition_result) {
    listEntry_t *listEntry;
    free(speech_recognition_result->transcript);
		list_ForEach(listEntry, speech_recognition_result->words) {
		word_info_free(listEntry->data);
	}
	list_free(speech_recognition_result->words);

	free(speech_recognition_result);
}

cJSON *speech_recognition_result_convertToJSON(speech_recognition_result_t *speech_recognition_result) {
	cJSON *item = cJSON_CreateObject();
	// speech_recognition_result->transcript
    if(cJSON_AddStringToObject(item, "transcript", speech_recognition_result->transcript) == NULL) {
    goto fail; //String
    }

	// speech_recognition_result->confidence
    if(cJSON_AddNumberToObject(item, "confidence", speech_recognition_result->confidence) == NULL) {
    goto fail; //Numeric
    }

	// speech_recognition_result->words
    cJSON *words = cJSON_AddArrayToObject(item, "words");
	if(words == NULL) {
		goto fail; //nonprimitive container
	}

	listEntry_t *wordsListEntry;
	list_ForEach(wordsListEntry, speech_recognition_result->words) {
		cJSON *item = word_info_convertToJSON(wordsListEntry->data);
		if(item == NULL) {
			goto fail;
		}
		cJSON_AddItemToArray(words, item);
	}

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

speech_recognition_result_t *speech_recognition_result_parseFromJSON(char *jsonString){

    speech_recognition_result_t *speech_recognition_result = NULL;
    cJSON *speech_recognition_resultJSON = cJSON_Parse(jsonString);
    if(speech_recognition_resultJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // speech_recognition_result->transcript
    cJSON *transcript = cJSON_GetObjectItemCaseSensitive(speech_recognition_resultJSON, "transcript");
    if(!cJSON_IsString(transcript) || (transcript->valuestring == NULL)){
    goto end; //String
    }

    // speech_recognition_result->confidence
    cJSON *confidence = cJSON_GetObjectItemCaseSensitive(speech_recognition_resultJSON, "confidence");
    if(!cJSON_IsNumber(confidence))
    {
    goto end; //Numeric
    }

    // speech_recognition_result->words
    cJSON *words;
    cJSON *wordsJSON = cJSON_GetObjectItemCaseSensitive(speech_recognition_resultJSON,"words");
    if(!cJSON_IsArray(wordsJSON)){
        goto end; //nonprimitive container
    }

    list_t *wordsList = list_create();

    cJSON_ArrayForEach(words,wordsJSON )
    {
        if(!cJSON_IsObject(words)){
            goto end;
        }
		char *JSONData = cJSON_Print(words);
        word_info_t *wordsItem = word_info_parseFromJSON(JSONData);

        list_addElement(wordsList, wordsItem);
        free(JSONData);
    }


    speech_recognition_result = speech_recognition_result_create (
        strdup(transcript->valuestring),
        confidence->valuedouble,
        wordsList
        );
 cJSON_Delete(speech_recognition_resultJSON);
    return speech_recognition_result;
end:
    cJSON_Delete(speech_recognition_resultJSON);
    return NULL;

}

