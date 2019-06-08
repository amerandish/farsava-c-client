/*
 * tts_voice_gender.h
 *
 * The gender of the requested voice to synthesize.
 */

#ifndef _tts_voice_gender_H_
#define _tts_voice_gender_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct tts_voice_gender_t {

} tts_voice_gender_t;

tts_voice_gender_t *tts_voice_gender_create(
);

void tts_voice_gender_free(tts_voice_gender_t *tts_voice_gender);

tts_voice_gender_t *tts_voice_gender_parseFromJSON(char *jsonString);

cJSON *tts_voice_gender_convertToJSON(tts_voice_gender_t *tts_voice_gender);

#endif /* _tts_voice_gender_H_ */

