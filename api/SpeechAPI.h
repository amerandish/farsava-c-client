#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../model/asr_request_body_data.h"
#include "../model/asr_request_body_uri.h"
#include "../model/asr_response_body.h"
#include "../model/error.h"
#include "../model/health_check_response_body.h"


// DELETE /speech/transcriptions/{transcriptionId}
//
// Deletes a transcription for a previous file using transcriptionId. *** 
//
void
SpeechAPI_deleteTranscription(apiClient_t *apiClient,char_t* transcriptionId );



// GET /speech/transcriptions/{transcriptionId}
//
// Transcription endpoint enable us to retrieve a previous speech recognition result or inform us on a long running speech recognition status. To access a speech recognition result transcriptionId should be provided.    ***    
//
asr_response_body_t*
SpeechAPI_getTranscription(apiClient_t *apiClient,char_t* transcriptionId );



// POST /speech/asr
//
// ## Performs synchronous speech recognition  *** This resource receives audio data in different formats and transcribes the audio using state-of-the-art deep neural networks. It performs synchronous speech recognition and the result will be availble after all audio has been sent and processed. This endpoint is designed for transcription of short audio files upto 1 minute. *** Using *config* object you can can specify audio configs such as *audioEncoding* and *sampleRateHertz*. We will support different languages so you can choose the *languageCode*. Using *asrModel* and *languageModel* in config you can use customized models. Refer to *asrLongRunning* and *WebSocket API* for longer audio transcriptions. 
//
asr_response_body_t*
SpeechAPI_recognize(apiClient_t *apiClient,asr_request_body_data_t* asr_request_body_data );



// GET /speech/asrlive
//
// ## Performs asynchronous live speech recognition using websocket *** This resource establish a websocket with client and receives audio data using websocket. It will start transcribing the audio using state-of-the-art deep neural networks and returns the partial results on the websocket. This endpoint is designed for transcription of stream audio data upto 15 minute. It will send back partial (status=partial) result everytime it transcribes an endpoint. After client sends the close signal, it will receive a ASRResponseBody with status=done. *** Using *config* object you can can specify audio configs such as *audioEncoding* and *sampleRateHertz*. We will support different languages so you can choose the *languageCode*. Using *asrModel* and *languageModel* in config you can use customized models. Refer to *ASRLongRuning API* for long audio speech recognition. Refer to *ASR API* for fast recognition for short audio files. 
//
asr_response_body_t*
SpeechAPI_recognizeLive(apiClient_t *apiClient);



// POST /speech/asrlongrunning
//
// ## Performs asynchronous speech recognition  *** This resource receives a uri containing the audio resource, download it and transcribes the audio using state-of-the-art deep neural networks. It performs asynchronous speech recognition and the result will be availble using transcription endpoint. This endpoint is designed for transcription of long audio files upto 240 minute. *** Using *config* object you can can specify audio configs such as *audioEncoding* and *sampleRateHertz*. We will support different languages so you can choose the *languageCode*. Using *asrModel* and *languageModel* in config you can use customized models. Refer to *WebSocket API* for speech recognition with streams. Refer to *ASR API* for fast recognition for short audio files. 
//
asr_response_body_t*
SpeechAPI_recognizeLongRunning(apiClient_t *apiClient,asr_request_body_uri_t* asr_request_body_uri );



// GET /speech/healthcheck
//
// ## speech health check endpoint. *** This endpoint will return a simple json including **service status** and **API version**. 
//
health_check_response_body_t*
SpeechAPI_speechHealthCheck(apiClient_t *apiClient);



