/*
 * voice_selection_params.h
 *
 * The desired voice of the synthesized audio.
 */

#ifndef _voice_selection_params_H_
#define _voice_selection_params_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "language_code.h"
#include "tts_voice_gender.h"


typedef enum  {  fa, en } languageCode_e;
typedef enum  {  male, female } gender_e;

char* languageCodevoice_selection_params_ToString(languageCode_e languageCode);

languageCode_e languageCodevoice_selection_params_FromString(char* languageCode);
char* gendervoice_selection_params_ToString(gender_e gender);

gender_e gendervoice_selection_params_FromString(char* gender);

typedef struct voice_selection_params_t {
        char *voiceId; //no enum string
        language_code_t *languageCode; //nonprimitive
        char *name; //no enum string
        tts_voice_gender_t *gender; //nonprimitive

} voice_selection_params_t;

voice_selection_params_t *voice_selection_params_create(
        char *voiceId,
        language_code_t *languageCode,
        char *name,
        tts_voice_gender_t *gender
);

void voice_selection_params_free(voice_selection_params_t *voice_selection_params);

voice_selection_params_t *voice_selection_params_parseFromJSON(char *jsonString);

cJSON *voice_selection_params_convertToJSON(voice_selection_params_t *voice_selection_params);

#endif /* _voice_selection_params_H_ */

