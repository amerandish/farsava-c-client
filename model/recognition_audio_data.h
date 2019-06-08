/*
 * recognition_audio_data.h
 *
 * Contains audio data in the encoding specified in the RecognitionConfig.    A base64-encoded string.   *For asr endpoint only binary data is accepted.*      Property | Description   ------------ | -------------   data | The audio data bytes encoded as specified in RecognitionConfig. A base64-encoded string. 
 */

#ifndef _recognition_audio_data_H_
#define _recognition_audio_data_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct recognition_audio_data_t {

} recognition_audio_data_t;

recognition_audio_data_t *recognition_audio_data_create(
);

void recognition_audio_data_free(recognition_audio_data_t *recognition_audio_data);

recognition_audio_data_t *recognition_audio_data_parseFromJSON(char *jsonString);

cJSON *recognition_audio_data_convertToJSON(recognition_audio_data_t *recognition_audio_data);

#endif /* _recognition_audio_data_H_ */

