#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "language_model_train_request_body.h"



language_model_train_request_body_t *language_model_train_request_body_create(
    list_t *corpora,
    char *name
    ) {
	language_model_train_request_body_t *language_model_train_request_body = malloc(sizeof(language_model_train_request_body_t));
	language_model_train_request_body->corpora = corpora;
	language_model_train_request_body->name = name;

	return language_model_train_request_body;
}


void language_model_train_request_body_free(language_model_train_request_body_t *language_model_train_request_body) {
    listEntry_t *listEntry;
	list_ForEach(listEntry, language_model_train_request_body->corpora) {
		free(listEntry->data);
	}
	list_free(language_model_train_request_body->corpora);
    free(language_model_train_request_body->name);

	free(language_model_train_request_body);
}

cJSON *language_model_train_request_body_convertToJSON(language_model_train_request_body_t *language_model_train_request_body) {
	cJSON *item = cJSON_CreateObject();
	// language_model_train_request_body->corpora
	cJSON *corpora = cJSON_AddArrayToObject(item, "corpora");
	if(corpora == NULL) {
		goto fail; //primitive container
	}

	listEntry_t *corporaListEntry;
    list_ForEach(corporaListEntry, language_model_train_request_body->corpora) {
        if(cJSON_AddStringToObject(corpora, "", (char*)corporaListEntry->data) == NULL)
        {
            goto fail;
        }
    }

	// language_model_train_request_body->name
    if(cJSON_AddStringToObject(item, "name", language_model_train_request_body->name) == NULL) {
    goto fail; //String
    }

	return item;
fail:
	cJSON_Delete(item);
	return NULL;
}

language_model_train_request_body_t *language_model_train_request_body_parseFromJSON(char *jsonString){

    language_model_train_request_body_t *language_model_train_request_body = NULL;
    cJSON *language_model_train_request_bodyJSON = cJSON_Parse(jsonString);
    if(language_model_train_request_bodyJSON == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error Before: %s\n", error_ptr);
            goto end;
        }
    }

    // language_model_train_request_body->corpora
    cJSON *corpora;
    cJSON *corporaJSON = cJSON_GetObjectItemCaseSensitive(language_model_train_request_bodyJSON, "corpora");
    if(!cJSON_IsArray(corporaJSON)) {
        goto end;//primitive container
    }
    list_t *corporaList = list_create();

    cJSON_ArrayForEach(corpora, corporaJSON)
    {
        if(!cJSON_IsString(corpora))
        {
            goto end;
        }
        list_addElement(corporaList , strdup(corpora->valuestring));

    }

    // language_model_train_request_body->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(language_model_train_request_bodyJSON, "name");
    if(!cJSON_IsString(name) || (name->valuestring == NULL)){
    goto end; //String
    }


    language_model_train_request_body = language_model_train_request_body_create (
        corporaList,
        strdup(name->valuestring)
        );
 cJSON_Delete(language_model_train_request_bodyJSON);
    return language_model_train_request_body;
end:
    cJSON_Delete(language_model_train_request_bodyJSON);
    return NULL;

}

