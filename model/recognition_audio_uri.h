/*
 * recognition_audio_uri.h
 *
 * Contains audio source URI with the encoding specified in the RecognitionConfig.    *For asrlongrunning endpoint only uri is accepted.*      Property | Description   ------------ | -------------   uri | URI that points to a file that contains audio data bytes as specified in RecognitionConfig. The file must not be compressed (for example, gzip). 
 */

#ifndef _recognition_audio_uri_H_
#define _recognition_audio_uri_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct recognition_audio_uri_t {
        char *uri; //no enum string

} recognition_audio_uri_t;

recognition_audio_uri_t *recognition_audio_uri_create(
        char *uri
);

void recognition_audio_uri_free(recognition_audio_uri_t *recognition_audio_uri);

recognition_audio_uri_t *recognition_audio_uri_parseFromJSON(char *jsonString);

cJSON *recognition_audio_uri_convertToJSON(recognition_audio_uri_t *recognition_audio_uri);

#endif /* _recognition_audio_uri_H_ */

