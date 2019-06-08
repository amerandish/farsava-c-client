#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "SpeechAPI.h"


#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)

// DELETE /speech/transcriptions/{transcriptionId}
//
// Deletes a transcription for a previous file using transcriptionId. *** 
//
void
SpeechAPI_deleteTranscription(apiClient_t *apiClient, char_t* transcriptionId) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/speech/transcriptions/{transcriptionId}")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/speech/transcriptions/{transcriptionId}");


    // Path Params
    long sizeOfPathParams_transcriptionId =  + strlen("{ transcriptionId }");

    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "DELETE");

    if (apiClient->response_code == 204) {
        printf("%s\n","The resource was deleted successfully.");
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
    //No return type
end:
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    
    
    
    list_free(localVarHeaderType);
    
    free(localVarPath);
    free(localVarToReplace_transcriptionId);

}

// GET /speech/transcriptions/{transcriptionId}
//
// Transcription endpoint enable us to retrieve a previous speech recognition result or inform us on a long running speech recognition status. To access a speech recognition result transcriptionId should be provided.    ***    
//
asr_response_body_t*
SpeechAPI_getTranscription(apiClient_t *apiClient, char_t* transcriptionId) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/speech/transcriptions/{transcriptionId}")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/speech/transcriptions/{transcriptionId}");


    // Path Params
    long sizeOfPathParams_transcriptionId =  + strlen("{ transcriptionId }");

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
        printf("%s\n","OK. Transcription Retrieved.");
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
    asr_response_body_t *elementToReturn = asr_response_body_parseFromJSON(apiClient->dataReceived);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    
    
    
    list_free(localVarHeaderType);
    
    free(localVarPath);
    free(localVarToReplace_transcriptionId);
    return elementToReturn;
end:
    return NULL;

}

// POST /speech/asr
//
// ## Performs synchronous speech recognition  *** This resource receives audio data in different formats and transcribes the audio using state-of-the-art deep neural networks. It performs synchronous speech recognition and the result will be availble after all audio has been sent and processed. This endpoint is designed for transcription of short audio files upto 1 minute. *** Using *config* object you can can specify audio configs such as *audioEncoding* and *sampleRateHertz*. We will support different languages so you can choose the *languageCode*. Using *asrModel* and *languageModel* in config you can use customized models. Refer to *asrLongRunning* and *WebSocket API* for longer audio transcriptions. 
//
asr_response_body_t*
SpeechAPI_recognize(apiClient_t *apiClient, asr_request_body_data_t* asr_request_body_data) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = list_create();
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/speech/asr")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/speech/asr");


    // Body Param
    cJSON *localVarSingleItemJSON_asr_request_body_data;
    if (asr_request_body_data != NULL) {
        //string
        localVarSingleItemJSON_asr_request_body_data = asr_request_body_data_convertToJSON(asr_request_body_data);
        localVarBodyParameters = cJSON_Print(localVarSingleItemJSON_asr_request_body_data);
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
        printf("%s\n","OK. Transcription Generated.");
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
    //nonprimitive not container
    asr_response_body_t *elementToReturn = asr_response_body_parseFromJSON(apiClient->dataReceived);
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
    cJSON_Delete(localVarSingleItemJSON_asr_request_body_data);
    free(localVarBodyParameters);
    return elementToReturn;
end:
    return NULL;

}

// GET /speech/asrlive
//
// ## Performs asynchronous live speech recognition using websocket *** This resource establish a websocket with client and receives audio data using websocket. It will start transcribing the audio using state-of-the-art deep neural networks and returns the partial results on the websocket. This endpoint is designed for transcription of stream audio data upto 15 minute. It will send back partial (status=partial) result everytime it transcribes an endpoint. After client sends the close signal, it will receive a ASRResponseBody with status=done. *** Using *config* object you can can specify audio configs such as *audioEncoding* and *sampleRateHertz*. We will support different languages so you can choose the *languageCode*. Using *asrModel* and *languageModel* in config you can use customized models. Refer to *ASRLongRuning API* for long audio speech recognition. Refer to *ASR API* for fast recognition for short audio files. 
//
asr_response_body_t*
SpeechAPI_recognizeLive(apiClient_t *apiClient) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/speech/asrlive")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/speech/asrlive");

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
    if (apiClient->response_code == 415) {
        printf("%s\n","The media format of the requested data is not supported by the server, so the server is rejecting the request. ");
    }
    if (apiClient->response_code == 429) {
        printf("%s\n","The user has sent too many requests in a given amount of time (\&quot;rate limiting\&quot;). ");
    }
    if (apiClient->response_code == 500) {
        printf("%s\n","The server has encountered a situation it doesn&#39;t know how to handle. ");
    }
    //nonprimitive not container
    asr_response_body_t *elementToReturn = asr_response_body_parseFromJSON(apiClient->dataReceived);
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

// POST /speech/asrlongrunning
//
// ## Performs asynchronous speech recognition  *** This resource receives a uri containing the audio resource, download it and transcribes the audio using state-of-the-art deep neural networks. It performs asynchronous speech recognition and the result will be availble using transcription endpoint. This endpoint is designed for transcription of long audio files upto 240 minute. *** Using *config* object you can can specify audio configs such as *audioEncoding* and *sampleRateHertz*. We will support different languages so you can choose the *languageCode*. Using *asrModel* and *languageModel* in config you can use customized models. Refer to *WebSocket API* for speech recognition with streams. Refer to *ASR API* for fast recognition for short audio files. 
//
asr_response_body_t*
SpeechAPI_recognizeLongRunning(apiClient_t *apiClient, asr_request_body_uri_t* asr_request_body_uri) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = list_create();
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/speech/asrlongrunning")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/speech/asrlongrunning");


    // Body Param
    cJSON *localVarSingleItemJSON_asr_request_body_uri;
    if (asr_request_body_uri != NULL) {
        //string
        localVarSingleItemJSON_asr_request_body_uri = asr_request_body_uri_convertToJSON(asr_request_body_uri);
        localVarBodyParameters = cJSON_Print(localVarSingleItemJSON_asr_request_body_uri);
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
        printf("%s\n","OK. Transcription Generated.");
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
    //nonprimitive not container
    asr_response_body_t *elementToReturn = asr_response_body_parseFromJSON(apiClient->dataReceived);
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
    cJSON_Delete(localVarSingleItemJSON_asr_request_body_uri);
    free(localVarBodyParameters);
    return elementToReturn;
end:
    return NULL;

}

// GET /speech/healthcheck
//
// ## speech health check endpoint. *** This endpoint will return a simple json including **service status** and **API version**. 
//
health_check_response_body_t*
SpeechAPI_speechHealthCheck(apiClient_t *apiClient) {
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/speech/healthcheck")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/speech/healthcheck");

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

