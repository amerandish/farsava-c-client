/*
 * audio_encoding.h
 *
 * Encoding of audio data sent in all RecognitionAudio messages. In case of voice synthesize, this is the format of the requested audio byte stream. This field is required for all audio formats. 
 */

#ifndef _audio_encoding_H_
#define _audio_encoding_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct audio_encoding_t {

} audio_encoding_t;

audio_encoding_t *audio_encoding_create(
);

void audio_encoding_free(audio_encoding_t *audio_encoding);

audio_encoding_t *audio_encoding_parseFromJSON(char *jsonString);

cJSON *audio_encoding_convertToJSON(audio_encoding_t *audio_encoding);

#endif /* _audio_encoding_H_ */

