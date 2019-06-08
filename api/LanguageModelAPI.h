#include <stdlib.h>
#include <stdio.h>
#include "../include/apiClient.h"
#include "../include/list.h"
#include "../external/cJSON.h"
#include "../include/keyValuePair.h"
#include "../model/error.h"
#include "../model/language_model_result.h"
#include "../model/language_model_train_request_body.h"


// GET /speech/languagemodels/{languageModelId}
//
// Retrieving the status of a language model with specified languageModelId. A language model is ready to use when its status is *trained*. *** 
//
language_model_result_t*
LanguageModelAPI_getLanguageModelById(apiClient_t *apiClient,char* languageModelId );



// GET /speech/languagemodels
//
// Returns list of user available language models. Each user can access *general* language models plus their own *custom* trained language models. *** 
//
list_t*
LanguageModelAPI_getLanguageModelList(apiClient_t *apiClient);



// POST /speech/languagemodels
//
// Train a custom language model using pharases provided by user. Returning a languageModelId for accessing the language model later and using this custom language model to transcribe audios. Using custom language models will boost accuracy for specific keywords/phrases and can be used for a domain-specific speech recognition. *** 
//
language_model_result_t*
LanguageModelAPI_trainLanguageModel(apiClient_t *apiClient,language_model_train_request_body_t* language_model_train_request_body );



