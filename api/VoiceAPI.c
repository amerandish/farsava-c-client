#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "VoiceAPI.h"


#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)

// GET /voice/speakers
//
// This endpoint retrieves the list of available speakers for speech synthesization. Each speaker has a unique *voiceId* which can be used to synthesize speech. The result aslo includes each speaker langauge, gender and name. *** 
//
list_t*
VoiceAPI_getVoicesList(apiClient_t *apiClient) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/voice/speakers")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/voice/speakers");

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
        printf("%s\n","OK. TTS Voices List Retrieved.");
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
    cJSON *VoiceAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    if(!cJSON_IsArray(VoiceAPIlocalVarJSON)) {
        return 0;//nonprimitive container
    }
    list_t *elementToReturn = list_create();
    cJSON *VarJSON;
    cJSON_ArrayForEach(VarJSON, VoiceAPIlocalVarJSON)
    {
        if(!cJSON_IsObject(VarJSON))
        {
           // return 0;
        }
        char *localVarJSONToChar = cJSON_Print(VarJSON);
        list_addElement(elementToReturn , localVarJSONToChar);
    }

    cJSON_Delete( VoiceAPIlocalVarJSON);
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

// POST /voice/tts
//
// ## Synthesizes speech synchronously  *** Receives text and data configs and synthesize speech in different voices and format using state-of-the-art deep neural networks. This service synthesizes speech synchronously and the results will be available after all text input has been processed.  *** Using *config* object you can can specify audio configs such as *audioEncoding* and *sampleRateHertz*. We will support different languages so you can choose the *languageCode*. using *voiceSelectionParams* you can choose between the supported voices with specifying voiceId. Voices differ in gender, tone and style.  
//
tts_response_body_t*
VoiceAPI_synthesize(apiClient_t *apiClient, tts_request_body_t* tts_request_body) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = list_create();
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/voice/tts")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/voice/tts");


    // Body Param
    cJSON *localVarSingleItemJSON_tts_request_body;
    if (tts_request_body != NULL) {
        //string
        localVarSingleItemJSON_tts_request_body = tts_request_body_convertToJSON(tts_request_body);
        localVarBodyParameters = cJSON_Print(localVarSingleItemJSON_tts_request_body);
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
        printf("%s\n","OK. Speech Synthesized.");
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
    if (apiClient->response_code == 415) {
        printf("%s\n","The media format of the requested data is not supported by the server, so the server is rejecting the request. ");
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
    tts_response_body_t *elementToReturn = tts_response_body_parseFromJSON(apiClient->dataReceived);
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
    cJSON_Delete(localVarSingleItemJSON_tts_request_body);
    free(localVarBodyParameters);
    return elementToReturn;
end:
    return NULL;

}

// GET /voice/healthcheck
//
// ## voice health check endpoint. *** This endpoint will return a simple json including **service status** and **API version**. 
//
health_check_response_body_t*
VoiceAPI_voiceHealthCheck(apiClient_t *apiClient) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/voice/healthcheck")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/voice/healthcheck");

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
        printf("%s\n","OK.");
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
    //nonprimitive not container
    health_check_response_body_t *elementToReturn = health_check_response_body_parseFromJSON(apiClient->dataReceived);
    if(elementToReturn == NULL) {
        // return 0;
    }

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

