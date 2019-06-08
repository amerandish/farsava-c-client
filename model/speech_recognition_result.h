/*
 * speech_recognition_result.h
 *
 * 
 */

#ifndef _speech_recognition_result_H_
#define _speech_recognition_result_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "word_info.h"




typedef struct speech_recognition_result_t {
        char *transcript; //no enum string
        double confidence; //numeric
        list_t *words; //nonprimitive container

} speech_recognition_result_t;

speech_recognition_result_t *speech_recognition_result_create(
        char *transcript,
        double confidence,
        list_t *words
);

void speech_recognition_result_free(speech_recognition_result_t *speech_recognition_result);

speech_recognition_result_t *speech_recognition_result_parseFromJSON(char *jsonString);

cJSON *speech_recognition_result_convertToJSON(speech_recognition_result_t *speech_recognition_result);

#endif /* _speech_recognition_result_H_ */

