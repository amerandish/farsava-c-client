cmake_minimum_required (VERSION 2.6)
project (CGenerator)

cmake_policy(SET CMP0063 NEW)

set(CMAKE_C_VISIBILITY_PRESET default)
set(CMAKE_CXX_VISIBILITY_PRESET default)
set(CMAKE_VISIBILITY_INLINES_HIDDEN OFF)
set(CMAKE_BUILD_TYPE Debug)

set(pkgName "farsava_api")

find_program(VALGRIND valgrind)
if(VALGRIND)
	set(CMAKE_MEMORYCHECK_COMMAND valgrind)
	set(CMAKE_MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --track-origins=yes --read-var-info=yes --show-leak-kinds=all --error-exitcode=1")
	set(VALGRIND_LIST "")
endif()

find_package(CURL 7.58.0 REQUIRED)
if(CURL_FOUND)
	include_directories(${CURL_INCLUDE_DIR})
	set(PLATFORM_LIBRARIES ${PLATFORM_LIBRARIES} ${CURL_LIBRARIES} )
else(CURL_FOUND)
	message(FATAL_ERROR "Could not find the CURL library and development files.")
endif()

set(SRCS
    src/list.c
    src/apiKey.c
    src/apiClient.c
    external/cJSON.c
    model/asr_request_body_data.c
    model/asr_request_body_uri.c
    model/asr_response_body.c
    model/asr_status.c
    model/audio_encoding.c
    model/error.c
    model/health_check_response_body.c
    model/language_code.c
    model/language_model_result.c
    model/language_model_train_request_body.c
    model/lm_status.c
    model/recognition_audio_data.c
    model/recognition_audio_uri.c
    model/recognition_config.c
    model/speech_recognition_model.c
    model/speech_recognition_result.c
    model/synthesis_input.c
    model/tts_audio_config.c
    model/tts_request_body.c
    model/tts_response_body.c
    model/tts_voice_gender.c
    model/voice_selection_params.c
    model/word_info.c
    api/LanguageModelAPI.c
    api/SpeechAPI.c
    api/VoiceAPI.c

)

set(HDRS
    include/apiClient.h
    include/list.h
    include/keyValuePair.h
    external/cJSON.h
    model/asr_request_body_data.h
    model/asr_request_body_uri.h
    model/asr_response_body.h
    model/asr_status.h
    model/audio_encoding.h
    model/error.h
    model/health_check_response_body.h
    model/language_code.h
    model/language_model_result.h
    model/language_model_train_request_body.h
    model/lm_status.h
    model/recognition_audio_data.h
    model/recognition_audio_uri.h
    model/recognition_config.h
    model/speech_recognition_model.h
    model/speech_recognition_result.h
    model/synthesis_input.h
    model/tts_audio_config.h
    model/tts_request_body.h
    model/tts_response_body.h
    model/tts_voice_gender.h
    model/voice_selection_params.h
    model/word_info.h
    api/LanguageModelAPI.h
    api/SpeechAPI.h
    api/VoiceAPI.h

)

add_library(${pkgName} SHARED ${SRCS} ${HDRS})
target_link_libraries(${pkgName} ${CURL_LIBRARIES} )
install(TARGETS ${pkgName} DESTINATION ${CMAKE_INSTALL_PREFIX})

#For common coding standard (code beautifier/pretty printing)
find_program(UNCRUSTIFY uncrustify)
if(UNCRUSTIFY)
	add_custom_target(
		uncrustify
	)

	foreach(ELEMENT ${ALL_SRC_LIST})
		string(REGEX REPLACE "/" "_" ELEMENT_NAME ${ELEMENT})
		set(DEP_NAME "uncrustify-${ELEMENT_NAME}")
		add_custom_target(
			${DEP_NAME}
			uncrustify -c uncrustify-rules.cfg --no-backup ${ELEMENT}
			DEPENDS ${ELEMENT}
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
			VERBATIM
		)
		add_dependencies(uncrustify ${DEP_NAME})
	endforeach()
endif()
