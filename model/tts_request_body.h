/*
 * tts_request_body.h
 *
 * 
 */

#ifndef _tts_request_body_H_
#define _tts_request_body_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "synthesis_input.h"
#include "tts_audio_config.h"
#include "voice_selection_params.h"




typedef struct tts_request_body_t {
        synthesis_input_t *synthesisInput; //nonprimitive
        voice_selection_params_t *voiceConfig; //nonprimitive
        tts_audio_config_t *audioConfig; //nonprimitive

} tts_request_body_t;

tts_request_body_t *tts_request_body_create(
        synthesis_input_t *synthesisInput,
        voice_selection_params_t *voiceConfig,
        tts_audio_config_t *audioConfig
);

void tts_request_body_free(tts_request_body_t *tts_request_body);

tts_request_body_t *tts_request_body_parseFromJSON(char *jsonString);

cJSON *tts_request_body_convertToJSON(tts_request_body_t *tts_request_body);

#endif /* _tts_request_body_H_ */

