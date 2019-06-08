#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../model/error.h"
#include "../model/health_check_response_body.h"
#include "../model/tts_request_body.h"
#include "../model/tts_response_body.h"
#include "../model/voice_selection_params.h"


// GET /voice/speakers
//
// This endpoint retrieves the list of available speakers for speech synthesization. Each speaker has a unique *voiceId* which can be used to synthesize speech. The result aslo includes each speaker langauge, gender and name. *** 
//
list_t*
VoiceAPI_getVoicesList(apiClient_t *apiClient);



// POST /voice/tts
//
// ## Synthesizes speech synchronously  *** Receives text and data configs and synthesize speech in different voices and format using state-of-the-art deep neural networks. This service synthesizes speech synchronously and the results will be available after all text input has been processed.  *** Using *config* object you can can specify audio configs such as *audioEncoding* and *sampleRateHertz*. We will support different languages so you can choose the *languageCode*. using *voiceSelectionParams* you can choose between the supported voices with specifying voiceId. Voices differ in gender, tone and style.  
//
tts_response_body_t*
VoiceAPI_synthesize(apiClient_t *apiClient,tts_request_body_t* tts_request_body );



// GET /voice/healthcheck
//
// ## voice health check endpoint. *** This endpoint will return a simple json including **service status** and **API version**. 
//
health_check_response_body_t*
VoiceAPI_voiceHealthCheck(apiClient_t *apiClient);



