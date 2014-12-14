/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_EFFECTREVERB_H_
#define ANDROID_EFFECTREVERB_H_

// from Reverb/lib
#include "LVREV.h"

// #include <stdint.h>

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#include <audio_effects/effect_environmentalreverb.h>
#include <audio_effects/effect_presetreverb.h>

#ifdef _WIN32
#ifndef LIBEFFECTS_NO_EXPORT_DLL_SYMBOLS
#ifdef LIBEFFECTS_EXPORTS
#define EXPORT_FUNCTION __declspec(dllexport)
#else
#define EXPORT_FUNCTION __declspec(dllimport)
#endif
#else
#define EXPORT_FUNCTION
#endif
// not available in VS2008
#ifndef ENODATA
#define ENODATA 61
#endif
#define inline __inline
#else 
#define EXPORT_FUNCTION
#endif

#if __cplusplus
extern "C" {
#endif

#define MAX_NUM_BANDS           5
#define MAX_CALL_SIZE           256
#define LVREV_MAX_T60           7000
#define LVREV_MAX_REVERB_LEVEL  2000
#define LVREV_MAX_FRAME_SIZE    2560
#define LVREV_CUP_LOAD_ARM9E    470    // Expressed in 0.1 MIPS
#define LVREV_MEM_USAGE         71+(LVREV_MAX_FRAME_SIZE>>7)     // Expressed in kB
//#define LVM_PCM

typedef struct _LPFPair_t
{
    int16_t Room_HF;
    int16_t LPF;
} LPFPair_t;

typedef struct ReverbContext_t {
    const struct effect_interface_s *itfe;
    effect_config_t                 config;
    LVREV_Handle_t                  hInstance;
    int16_t                         SavedRoomLevel;
    int16_t                         SavedHfLevel;
    int16_t                         SavedDecayTime;
    int16_t                         SavedDecayHfRatio;
    int16_t                         SavedReverbLevel;
    int16_t                         SavedDiffusion;
    int16_t                         SavedDensity;
    uint32_t                        boolEnabled;
    #ifdef LVM_PCM
    FILE                            *PcmInPtr;
    FILE                            *PcmOutPtr;
    #endif
    LVM_Fs_en                       SampleRate;
    LVM_INT32                       *InFrames32;
    LVM_INT32                       *OutFrames32;
    uint32_t                        boolAuxiliary;
    uint32_t                        boolPreset;
    uint16_t                        curPreset;
    uint16_t                        nextPreset;
    int                             SamplesToExitCount;
    LVM_INT16                       leftVolume;
    LVM_INT16                       rightVolume;
    LVM_INT16                       prevLeftVolume;
    LVM_INT16                       prevRightVolume;
    int                             volumeMode;
} ReverbContext;

enum {
    REVERB_VOLUME_OFF,
    REVERB_VOLUME_FLAT,
    REVERB_VOLUME_RAMP,
};

//--- local function prototypes
EXPORT_FUNCTION int  Reverb_init            (ReverbContext *pContext);
EXPORT_FUNCTION void Reverb_free            (ReverbContext *pContext);
EXPORT_FUNCTION int  Reverb_setConfig       (ReverbContext *pContext, effect_config_t *pConfig);
EXPORT_FUNCTION void Reverb_getConfig       (ReverbContext *pContext, effect_config_t *pConfig);
EXPORT_FUNCTION int  Reverb_setParameter    (ReverbContext *pContext, void *pParam, void *pValue);
EXPORT_FUNCTION int  Reverb_getParameter    (ReverbContext *pContext,
								             void          *pParam,
											 size_t        *pValueSize,
											 void          *pValue);
EXPORT_FUNCTION int Reverb_LoadPreset       (ReverbContext   *pContext);
EXPORT_FUNCTION int Reverb_process(ReverbContext *pContext,
				                   audio_buffer_t         *inBuffer,
				                   audio_buffer_t         *outBuffer);
EXPORT_FUNCTION int Reverb_command(ReverbContext *pContext,
                                   uint32_t            cmdCode,
                                   uint32_t            cmdSize,
                                   void                *pCmdData,
                                   uint32_t            *replySize,
                                   void                *pReplyData);

#if __cplusplus
}  // extern "C"
#endif


#endif /*ANDROID_EFFECTREVERB_H_*/
