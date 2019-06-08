/*
 * word_info.h
 *
 * 
 */

#ifndef _word_info_H_
#define _word_info_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"




typedef struct word_info_t {
        double startTime; //numeric
        double endTime; //numeric
        char *word; //no enum string
        double confidence; //numeric

} word_info_t;

word_info_t *word_info_create(
        double startTime,
        double endTime,
        char *word,
        double confidence
);

void word_info_free(word_info_t *word_info);

word_info_t *word_info_parseFromJSON(char *jsonString);

cJSON *word_info_convertToJSON(word_info_t *word_info);

#endif /* _word_info_H_ */

