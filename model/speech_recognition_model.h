/*
 * speech_recognition_model.h
 *
 * Optional Which model to select for the given request. Select the model best suited to your domain to get best results. If a model is not explicitly specified, then we auto-select a model based on the parameters in the RecognitionConfig.      Model | Description   ------------ | -------------   default | Best for audio that is not one of the specific audio models. For example, long-form audio. Ideally the audio is high-fidelity, recorded at a 16khz or greater sampling rate.   video | Best for audio that originated from from video or includes multiple speakers. Ideally the audio is recorded at a 16khz or greater sampling rate.   command_and_search | Best for short queries such as voice commands or voice search. To be released.   phone_call | Best for audio that originated from a phone call (typically recorded at an 8khz sampling rate). To be released. 
 */

#ifndef _speech_recognition_model_H_
#define _speech_recognition_model_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct speech_recognition_model_t {

} speech_recognition_model_t;

speech_recognition_model_t *speech_recognition_model_create(
);

void speech_recognition_model_free(speech_recognition_model_t *speech_recognition_model);

speech_recognition_model_t *speech_recognition_model_parseFromJSON(char *jsonString);

cJSON *speech_recognition_model_convertToJSON(speech_recognition_model_t *speech_recognition_model);

#endif /* _speech_recognition_model_H_ */

