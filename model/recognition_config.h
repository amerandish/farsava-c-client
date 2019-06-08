/*
 * recognition_config.h
 *
 * Provides information to the recognizer that specifies how to process the request. 
 */

#ifndef _recognition_config_H_
#define _recognition_config_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "audio_encoding.h"
#include "language_code.h"
#include "speech_recognition_model.h"

typedef int bool;
#define true 1
#define false 0

typedef enum  {  LINEAR16, FLAC, MP3 } audioEncoding_e;
typedef enum  {  fa, en } languageCode_e;
typedef enum  {  _default, video, command_and_search, phone_call } asrModel_e;

char* audioEncodingrecognition_config_ToString(audioEncoding_e audioEncoding);

audioEncoding_e audioEncodingrecognition_config_FromString(char* audioEncoding);
char* languageCoderecognition_config_ToString(languageCode_e languageCode);

languageCode_e languageCoderecognition_config_FromString(char* languageCode);
char* asrModelrecognition_config_ToString(asrModel_e asrModel);

asrModel_e asrModelrecognition_config_FromString(char* asrModel);

typedef struct recognition_config_t {
        audio_encoding_t *audioEncoding; //nonprimitive
        int sampleRateHertz; //numeric
        language_code_t *languageCode; //nonprimitive
        int maxAlternatives; //numeric
        bool profanityFilter; //boolean
        speech_recognition_model_t *asrModel; //nonprimitive
        char *languageModel; //no enum string

} recognition_config_t;

recognition_config_t *recognition_config_create(
        audio_encoding_t *audioEncoding,
        int sampleRateHertz,
        language_code_t *languageCode,
        int maxAlternatives,
        bool profanityFilter,
        speech_recognition_model_t *asrModel,
        char *languageModel
);

void recognition_config_free(recognition_config_t *recognition_config);

recognition_config_t *recognition_config_parseFromJSON(char *jsonString);

cJSON *recognition_config_convertToJSON(recognition_config_t *recognition_config);

#endif /* _recognition_config_H_ */

