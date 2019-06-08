/*
 * tts_audio_config.h
 *
 * The configuration of the synthesized audio.
 */

#ifndef _tts_audio_config_H_
#define _tts_audio_config_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "audio_encoding.h"


typedef enum  {  LINEAR16, FLAC, MP3 } audioEncoding_e;

char* audioEncodingtts_audio_config_ToString(audioEncoding_e audioEncoding);

audioEncoding_e audioEncodingtts_audio_config_FromString(char* audioEncoding);

typedef struct tts_audio_config_t {
        audio_encoding_t *audioEncoding; //nonprimitive
        int sampleRateHertz; //numeric
        double speakingRate; //numeric
        double pitch; //numeric
        double volumeGainDb; //numeric

} tts_audio_config_t;

tts_audio_config_t *tts_audio_config_create(
        audio_encoding_t *audioEncoding,
        int sampleRateHertz,
        double speakingRate,
        double pitch,
        double volumeGainDb
);

void tts_audio_config_free(tts_audio_config_t *tts_audio_config);

tts_audio_config_t *tts_audio_config_parseFromJSON(char *jsonString);

cJSON *tts_audio_config_convertToJSON(tts_audio_config_t *tts_audio_config);

#endif /* _tts_audio_config_H_ */

