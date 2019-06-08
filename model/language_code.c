#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "language_code.h"



language_code_t *language_code_create(
    ) {
	language_code_t *language_code = malloc(sizeof(language_code_t));

	return language_code;
}


void language_code_free(language_code_t *language_code) {
    listEntry_t *listEntry;

	free(language_code);
}

cJSON *language_code_convertToJSON(language_code_t *language_code) {
	cJSON *item = cJSON_CreateObject();
	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

language_code_t *language_code_parseFromJSON(char *jsonString){

    language_code_t *language_code = NULL;
    cJSON *language_codeJSON = cJSON_Parse(jsonString);
    if(language_codeJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }


    language_code = language_code_create (
        );
 cJSON_Delete(language_codeJSON);
    return language_code;
end:
    cJSON_Delete(language_codeJSON);
    return NULL;

}

