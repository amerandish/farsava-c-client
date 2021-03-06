#ifndef INCLUDE_API_CLIENT_H
#define INCLUDE_API_CLIENT_H

#include "../include/list.h"
#include "../include/keyValuePair.h"

typedef int bool;
#define true 1
#define false 0

typedef struct apiClient_t {
    char *basePath;
    void *dataReceived;
    long response_code;
    char *username;
    char *password;
} apiClient_t;

typedef struct FileStruct
{
    char* fileData;
    long fileSize;
}FileStruct;

apiClient_t* apiClient_create();

void apiClient_free(apiClient_t *apiClient);

void apiClient_invoke(apiClient_t *apiClient,char* operationParameter, list_t *queryParameters, list_t *headerParameters, list_t *formParameters,list_t *headerType,list_t *contentType, char *bodyParameters, char *requestType);

char *strReplace(char *orig, char *rep, char *with);

#endif // INCLUDE_API_CLIENT_H
