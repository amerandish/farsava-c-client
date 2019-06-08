#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "synthesis_input.h"



synthesis_input_t *synthesis_input_create(
    char *text,
    char *ssml
    ) {
	synthesis_input_t *synthesis_input = malloc(sizeof(synthesis_input_t));
	synthesis_input->text = text;
	synthesis_input->ssml = ssml;

	return synthesis_input;
}


void synthesis_input_free(synthesis_input_t *synthesis_input) {
    listEntry_t *listEntry;
    free(synthesis_input->text);
    free(synthesis_input->ssml);

	free(synthesis_input);
}

cJSON *synthesis_input_convertToJSON(synthesis_input_t *synthesis_input) {
	cJSON *item = cJSON_CreateObject();
	// synthesis_input->text
    if(cJSON_AddStringToObject(item, "text", synthesis_input->text) == NULL) {
    goto fail; //String
    }

	// synthesis_input->ssml
    if(cJSON_AddStringToObject(item, "ssml", synthesis_input->ssml) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

synthesis_input_t *synthesis_input_parseFromJSON(char *jsonString){

    synthesis_input_t *synthesis_input = NULL;
    cJSON *synthesis_inputJSON = cJSON_Parse(jsonString);
    if(synthesis_inputJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // synthesis_input->text
    cJSON *text = cJSON_GetObjectItemCaseSensitive(synthesis_inputJSON, "text");
    if(!cJSON_IsString(text) || (text->valuestring == NULL)){
    goto end; //String
    }

    // synthesis_input->ssml
    cJSON *ssml = cJSON_GetObjectItemCaseSensitive(synthesis_inputJSON, "ssml");
    if(!cJSON_IsString(ssml) || (ssml->valuestring == NULL)){
    goto end; //String
    }


    synthesis_input = synthesis_input_create (
        strdup(text->valuestring),
        strdup(ssml->valuestring)
        );
 cJSON_Delete(synthesis_inputJSON);
    return synthesis_input;
end:
    cJSON_Delete(synthesis_inputJSON);
    return NULL;

}

