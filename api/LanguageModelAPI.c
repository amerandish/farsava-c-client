#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "LanguageModelAPI.h"


#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)

// GET /speech/languagemodels/{languageModelId}
//
// Retrieving the status of a language model with specified languageModelId. A language model is ready to use when its status is *trained*. *** 
//
language_model_result_t*
LanguageModelAPI_getLanguageModelById(apiClient_t *apiClient, char* languageModelId) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/speech/languagemodels/{languageModelId}")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/speech/languagemodels/{languageModelId}");


    // Path Params
    long sizeOfPathParams_languageModelId = strlen(languageModelId)+3 + strlen("{ languageModelId }");

    if(languageModelId == NULL) {
        goto end;
    }
    char* localVarToReplace_languageModelId = malloc(sizeOfPathParams_languageModelId);
    sprintf(localVarToReplace_languageModelId, "%s%s%s", "{", "languageModelId", "}");

    localVarPath = strReplace(localVarPath, localVarToReplace_languageModelId, languageModelId);
    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "GET");

    if (apiClient->response_code == 200) {
        printf("%s\n","OK. Language Model Retrieved.");
    }
    if (apiClient->response_code == 400) {
        printf("%s\n","This response means that server could not understand the request due to invalid syntax. ");
    }
    if (apiClient->response_code == 401) {
        printf("%s\n","Authentication is needed to get requested response. This is similar to 403, but in this case, authentication is possible. ");
    }
    if (apiClient->response_code == 403) {
        printf("%s\n","Client does not have access rights to the content so server is rejecting to give proper response. ");
    }
    if (apiClient->response_code == 404) {
        printf("%s\n","Server can not find requested resource. ");
    }
    if (apiClient->response_code == 405) {
        printf("%s\n","The request method is known by the server but has been disabled and cannot be used. ");
    }
    if (apiClient->response_code == 429) {
        printf("%s\n","The user has sent too many requests in a given amount of time (\&quot;rate limiting\&quot;). ");
    }
    if (apiClient->response_code == 500) {
        printf("%s\n","The server has encountered a situation it doesn&#39;t know how to handle. ");
    }
    if (apiClient->response_code == 501) {
        printf("%s\n","The request method is not supported by the server and cannot be handled. ");
    }
    //nonprimitive not container
    language_model_result_t *elementToReturn = language_model_result_parseFromJSON(apiClient->dataReceived);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    
    
    
    list_free(localVarHeaderType);
    
    free(localVarPath);
    free(localVarToReplace_languageModelId);
    return elementToReturn;
end:
    return NULL;

}

// GET /speech/languagemodels
//
// Returns list of user available language models. Each user can access *general* language models plus their own *custom* trained language models. *** 
//
list_t*
LanguageModelAPI_getLanguageModelList(apiClient_t *apiClient) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/speech/languagemodels")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/speech/languagemodels");

    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "GET");

    if (apiClient->response_code == 200) {
        printf("%s\n","OK. List of Language Models Retrieved.");
    }
    if (apiClient->response_code == 400) {
        printf("%s\n","This response means that server could not understand the request due to invalid syntax. ");
    }
    if (apiClient->response_code == 401) {
        printf("%s\n","Authentication is needed to get requested response. This is similar to 403, but in this case, authentication is possible. ");
    }
    if (apiClient->response_code == 403) {
        printf("%s\n","Client does not have access rights to the content so server is rejecting to give proper response. ");
    }
    if (apiClient->response_code == 404) {
        printf("%s\n","Server can not find requested resource. ");
    }
    if (apiClient->response_code == 429) {
        printf("%s\n","The user has sent too many requests in a given amount of time (\&quot;rate limiting\&quot;). ");
    }
    if (apiClient->response_code == 500) {
        printf("%s\n","The server has encountered a situation it doesn&#39;t know how to handle. ");
    }
    if (apiClient->response_code == 501) {
        printf("%s\n","The request method is not supported by the server and cannot be handled. ");
    }
    cJSON *LanguageModelAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    if(!cJSON_IsArray(LanguageModelAPIlocalVarJSON)) {
        return 0;//nonprimitive container
    }
    list_t *elementToReturn = list_create();
    cJSON *VarJSON;
    cJSON_ArrayForEach(VarJSON, LanguageModelAPIlocalVarJSON)
    {
        if(!cJSON_IsObject(VarJSON))
        {
           // return 0;
        }
        char *localVarJSONToChar = cJSON_Print(VarJSON);
        list_addElement(elementToReturn , localVarJSONToChar);
    }

    cJSON_Delete( LanguageModelAPIlocalVarJSON);
    cJSON_Delete( VarJSON);
    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    
    
    
    list_free(localVarHeaderType);
    
    free(localVarPath);
    return elementToReturn;
end:
    return NULL;

}

// POST /speech/languagemodels
//
// Train a custom language model using pharases provided by user. Returning a languageModelId for accessing the language model later and using this custom language model to transcribe audios. Using custom language models will boost accuracy for specific keywords/phrases and can be used for a domain-specific speech recognition. *** 
//
language_model_result_t*
LanguageModelAPI_trainLanguageModel(apiClient_t *apiClient, language_model_train_request_body_t* language_model_train_request_body) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = list_create();
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/speech/languagemodels")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/speech/languagemodels");


    // Body Param
    cJSON *localVarSingleItemJSON_language_model_train_request_body;
    if (language_model_train_request_body != NULL) {
        //string
        localVarSingleItemJSON_language_model_train_request_body = language_model_train_request_body_convertToJSON(language_model_train_request_body);
        localVarBodyParameters = cJSON_Print(localVarSingleItemJSON_language_model_train_request_body);
    }
    list_addElement(localVarHeaderType,"application/json"); //produces
    list_addElement(localVarContentType,"application/json"); //consumes
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "POST");

    if (apiClient->response_code == 201) {
        printf("%s\n","OK. Processing and Training Language Model.");
    }
    if (apiClient->response_code == 400) {
        printf("%s\n","This response means that server could not understand the request due to invalid syntax. ");
    }
    if (apiClient->response_code == 401) {
        printf("%s\n","Authentication is needed to get requested response. This is similar to 403, but in this case, authentication is possible. ");
    }
    if (apiClient->response_code == 403) {
        printf("%s\n","Client does not have access rights to the content so server is rejecting to give proper response. ");
    }
    if (apiClient->response_code == 405) {
        printf("%s\n","The request method is known by the server but has been disabled and cannot be used. ");
    }
    if (apiClient->response_code == 429) {
        printf("%s\n","The user has sent too many requests in a given amount of time (\&quot;rate limiting\&quot;). ");
    }
    if (apiClient->response_code == 500) {
        printf("%s\n","The server has encountered a situation it doesn&#39;t know how to handle. ");
    }
    if (apiClient->response_code == 501) {
        printf("%s\n","The request method is not supported by the server and cannot be handled. ");
    }
    //nonprimitive not container
    language_model_result_t *elementToReturn = language_model_result_parseFromJSON(apiClient->dataReceived);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    
    
    
    list_free(localVarHeaderType);
    list_free(localVarContentType);
    free(localVarPath);
    cJSON_Delete(localVarSingleItemJSON_language_model_train_request_body);
    free(localVarBodyParameters);
    return elementToReturn;
end:
    return NULL;

}

