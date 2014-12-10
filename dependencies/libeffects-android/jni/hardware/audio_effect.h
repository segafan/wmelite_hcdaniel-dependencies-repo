/*
 * Copyright (C) 2011 The Android Open Source Project
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


#ifndef ANDROID_AUDIO_EFFECT_H
#define ANDROID_AUDIO_EFFECT_H

#include <errno.h>
#ifndef _WIN32
#include <strings.h>
#include <sys/cdefs.h>
#else
#ifdef __cplusplus
#define __BEGIN_DECLS extern"C"{
#define __END_DECLS   }
#else
#define __BEGIN_DECLS
#define __END_DECLS  
#endif
#endif
#include <sys/types.h>

// #include <system/audio.h>


enum {
    /* output channels */
    AUDIO_CHANNEL_OUT_FRONT_LEFT            = 0x1,
    AUDIO_CHANNEL_OUT_FRONT_RIGHT           = 0x2,

    AUDIO_CHANNEL_OUT_MONO     = AUDIO_CHANNEL_OUT_FRONT_LEFT,
    AUDIO_CHANNEL_OUT_STEREO   = (AUDIO_CHANNEL_OUT_FRONT_LEFT |
                                  AUDIO_CHANNEL_OUT_FRONT_RIGHT)
};

typedef enum {
    AUDIO_FORMAT_PCM_SUB_16_BIT          = 0x1, /* DO NOT CHANGE - PCM signed 16 bits */
    AUDIO_FORMAT_PCM_SUB_8_BIT           = 0x2, /* DO NOT CHANGE - PCM unsigned 8 bits */
    AUDIO_FORMAT_PCM_SUB_32_BIT          = 0x3, /* PCM signed .31 fixed point */
    AUDIO_FORMAT_PCM_SUB_8_24_BIT        = 0x4, /* PCM signed 7.24 fixed point */
} audio_format_pcm_sub_fmt_t;

typedef enum {
    AUDIO_FORMAT_INVALID             = 0xFFFFFFFFUL,
    AUDIO_FORMAT_DEFAULT             = 0,
    AUDIO_FORMAT_PCM                 = 0x00000000UL, /* DO NOT CHANGE */
    AUDIO_FORMAT_MP3                 = 0x01000000UL,
    AUDIO_FORMAT_AMR_NB              = 0x02000000UL,
    AUDIO_FORMAT_AMR_WB              = 0x03000000UL,
    AUDIO_FORMAT_AAC                 = 0x04000000UL,
    AUDIO_FORMAT_HE_AAC_V1           = 0x05000000UL,
    AUDIO_FORMAT_HE_AAC_V2           = 0x06000000UL,
    AUDIO_FORMAT_VORBIS              = 0x07000000UL,
    AUDIO_FORMAT_MAIN_MASK           = 0xFF000000UL,
    AUDIO_FORMAT_SUB_MASK            = 0x00FFFFFFUL,

    /* Aliases */
    AUDIO_FORMAT_PCM_16_BIT          = (AUDIO_FORMAT_PCM |
                                        AUDIO_FORMAT_PCM_SUB_16_BIT),
    AUDIO_FORMAT_PCM_8_BIT           = (AUDIO_FORMAT_PCM |
                                        AUDIO_FORMAT_PCM_SUB_8_BIT),
    AUDIO_FORMAT_PCM_32_BIT          = (AUDIO_FORMAT_PCM |
                                        AUDIO_FORMAT_PCM_SUB_32_BIT),
    AUDIO_FORMAT_PCM_8_24_BIT        = (AUDIO_FORMAT_PCM |
                                        AUDIO_FORMAT_PCM_SUB_8_24_BIT),
} audio_format_t;

__BEGIN_DECLS

/////////////////////////////////////////////////
//      Common Definitions
/////////////////////////////////////////////////

//
//--- Effect descriptor structure effect_descriptor_t
//

// Unique effect ID (can be generated from the following site:
//  http://www.itu.int/ITU-T/asn1/uuid.html)
// This format is used for both "type" and "uuid" fields of the effect descriptor structure.
// - When used for effect type and the engine is implementing and effect corresponding to a standard
// OpenSL ES interface, this ID must be the one defined in OpenSLES_IID.h for that interface.
// - When used as uuid, it should be a unique UUID for this particular implementation.
typedef struct effect_uuid_s {
    uint32_t timeLow;
    uint16_t timeMid;
    uint16_t timeHiAndVersion;
    uint16_t clockSeq;
    uint8_t node[6];
} effect_uuid_t;

// Maximum length of character strings in structures defines by this API.
#define EFFECT_STRING_LEN_MAX 64

// NULL UUID definition (matches SL_IID_NULL_)
#define EFFECT_UUID_INITIALIZER { 0xec7178ec, 0xe5e1, 0x4432, 0xa3f4, \
                                  { 0x46, 0x57, 0xe6, 0x79, 0x52, 0x10 } }
static const effect_uuid_t EFFECT_UUID_NULL_ = EFFECT_UUID_INITIALIZER;
static const effect_uuid_t * const EFFECT_UUID_NULL = &EFFECT_UUID_NULL_;
static const char * const EFFECT_UUID_NULL_STR = "ec7178ec-e5e1-4432-a3f4-4657e6795210";


// The effect descriptor contains necessary information to facilitate the enumeration of the effect
// engines present in a library.
typedef struct effect_descriptor_s {
    effect_uuid_t type;     // UUID of to the OpenSL ES interface implemented by this effect
    effect_uuid_t uuid;     // UUID for this particular implementation
    uint32_t apiVersion;    // Version of the effect control API implemented
    uint32_t flags;         // effect engine capabilities/requirements flags (see below)
    uint16_t cpuLoad;       // CPU load indication (see below)
    uint16_t memoryUsage;   // Data Memory usage (see below)
    char    name[EFFECT_STRING_LEN_MAX];   // human readable effect name
    char    implementor[EFFECT_STRING_LEN_MAX];    // human readable effect implementor name
} effect_descriptor_t;

// CPU load and memory usage indication: each effect implementation must provide an indication of
// its CPU and memory usage for the audio effect framework to limit the number of effects
// instantiated at a given time on a given platform.
// The CPU load is expressed in 0.1 MIPS units as estimated on an ARM9E core (ARMv5TE) with 0 WS.
// The memory usage is expressed in KB and includes only dynamically allocated memory

// Definitions for flags field of effect descriptor.
//  +---------------------------+-----------+-----------------------------------
//  | description               | bits      | values
//  +---------------------------+-----------+-----------------------------------
//  | connection mode           | 0..2      | 0 insert: after track process
//  |                           |           | 1 auxiliary: connect to track auxiliary
//  |                           |           |  output and use send level
//  |                           |           | 2 replace: replaces track process function;
//  |                           |           |   must implement SRC, volume and mono to stereo.
//  |                           |           | 3 pre processing: applied below audio HAL on input
//  |                           |           | 4 post processing: applied below audio HAL on output
//  |                           |           | 5 - 7 reserved
//  +---------------------------+-----------+-----------------------------------
//  | insertion preference      | 3..5      | 0 none
//  |                           |           | 1 first of the chain
//  |                           |           | 2 last of the chain
//  |                           |           | 3 exclusive (only effect in the insert chain)
//  |                           |           | 4..7 reserved
//  +---------------------------+-----------+-----------------------------------
//  | Volume management         | 6..8      | 0 none
//  |                           |           | 1 implements volume control
//  |                           |           | 2 requires volume indication
//  |                           |           | 4 reserved
//  +---------------------------+-----------+-----------------------------------
//  | Device indication         | 9..11     | 0 none
//  |                           |           | 1 requires device updates
//  |                           |           | 2, 4 reserved
//  +---------------------------+-----------+-----------------------------------
//  | Sample input mode         | 12..13    | 1 direct: process() function or EFFECT_CMD_SET_CONFIG
//  |                           |           |   command must specify a buffer descriptor
//  |                           |           | 2 provider: process() function uses the
//  |                           |           |   bufferProvider indicated by the
//  |                           |           |   EFFECT_CMD_SET_CONFIG command to request input.
//  |                           |           |   buffers.
//  |                           |           | 3 both: both input modes are supported
//  +---------------------------+-----------+-----------------------------------
//  | Sample output mode        | 14..15    | 1 direct: process() function or EFFECT_CMD_SET_CONFIG
//  |                           |           |   command must specify a buffer descriptor
//  |                           |           | 2 provider: process() function uses the
//  |                           |           |   bufferProvider indicated by the
//  |                           |           |   EFFECT_CMD_SET_CONFIG command to request output
//  |                           |           |   buffers.
//  |                           |           | 3 both: both output modes are supported
//  +---------------------------+-----------+-----------------------------------
//  | Hardware acceleration     | 16..17    | 0 No hardware acceleration
//  |                           |           | 1 non tunneled hw acceleration: the process() function
//  |                           |           |   reads the samples, send them to HW accelerated
//  |                           |           |   effect processor, reads back the processed samples
//  |                           |           |   and returns them to the output buffer.
//  |                           |           | 2 tunneled hw acceleration: the process() function is
//  |                           |           |   transparent. The effect interface is only used to
//  |                           |           |   control the effect engine. This mode is relevant for
//  |                           |           |   global effects actually applied by the audio
//  |                           |           |   hardware on the output stream.
//  +---------------------------+-----------+-----------------------------------
//  | Audio Mode indication     | 18..19    | 0 none
//  |                           |           | 1 requires audio mode updates
//  |                           |           | 2..3 reserved
//  +---------------------------+-----------+-----------------------------------
//  | Audio source indication   | 20..21    | 0 none
//  |                           |           | 1 requires audio source updates
//  |                           |           | 2..3 reserved
//  +---------------------------+-----------+-----------------------------------
//  | Effect offload supported  | 22        | 0 The effect cannot be offloaded to an audio DSP
//  |                           |           | 1 The effect can be offloaded to an audio DSP
//  +---------------------------+-----------+-----------------------------------

// Insert mode
#define EFFECT_FLAG_TYPE_SHIFT          0
#define EFFECT_FLAG_TYPE_SIZE           3
#define EFFECT_FLAG_TYPE_MASK           (((1 << EFFECT_FLAG_TYPE_SIZE) -1) \
                                            << EFFECT_FLAG_TYPE_SHIFT)
#define EFFECT_FLAG_TYPE_INSERT         (0 << EFFECT_FLAG_TYPE_SHIFT)
#define EFFECT_FLAG_TYPE_AUXILIARY      (1 << EFFECT_FLAG_TYPE_SHIFT)
#define EFFECT_FLAG_TYPE_REPLACE        (2 << EFFECT_FLAG_TYPE_SHIFT)
#define EFFECT_FLAG_TYPE_PRE_PROC       (3 << EFFECT_FLAG_TYPE_SHIFT)
#define EFFECT_FLAG_TYPE_POST_PROC      (4 << EFFECT_FLAG_TYPE_SHIFT)

// Insert preference
#define EFFECT_FLAG_INSERT_SHIFT        (EFFECT_FLAG_TYPE_SHIFT + EFFECT_FLAG_TYPE_SIZE)
#define EFFECT_FLAG_INSERT_SIZE         3
#define EFFECT_FLAG_INSERT_MASK         (((1 << EFFECT_FLAG_INSERT_SIZE) -1) \
                                            << EFFECT_FLAG_INSERT_SHIFT)
#define EFFECT_FLAG_INSERT_ANY          (0 << EFFECT_FLAG_INSERT_SHIFT)
#define EFFECT_FLAG_INSERT_FIRST        (1 << EFFECT_FLAG_INSERT_SHIFT)
#define EFFECT_FLAG_INSERT_LAST         (2 << EFFECT_FLAG_INSERT_SHIFT)
#define EFFECT_FLAG_INSERT_EXCLUSIVE    (3 << EFFECT_FLAG_INSERT_SHIFT)


// Volume control
#define EFFECT_FLAG_VOLUME_SHIFT        (EFFECT_FLAG_INSERT_SHIFT + EFFECT_FLAG_INSERT_SIZE)
#define EFFECT_FLAG_VOLUME_SIZE         3
#define EFFECT_FLAG_VOLUME_MASK         (((1 << EFFECT_FLAG_VOLUME_SIZE) -1) \
                                            << EFFECT_FLAG_VOLUME_SHIFT)
#define EFFECT_FLAG_VOLUME_CTRL         (1 << EFFECT_FLAG_VOLUME_SHIFT)
#define EFFECT_FLAG_VOLUME_IND          (2 << EFFECT_FLAG_VOLUME_SHIFT)
#define EFFECT_FLAG_VOLUME_NONE         (0 << EFFECT_FLAG_VOLUME_SHIFT)

// Device indication
#define EFFECT_FLAG_DEVICE_SHIFT        (EFFECT_FLAG_VOLUME_SHIFT + EFFECT_FLAG_VOLUME_SIZE)
#define EFFECT_FLAG_DEVICE_SIZE         3
#define EFFECT_FLAG_DEVICE_MASK         (((1 << EFFECT_FLAG_DEVICE_SIZE) -1) \
                                            << EFFECT_FLAG_DEVICE_SHIFT)
#define EFFECT_FLAG_DEVICE_IND          (1 << EFFECT_FLAG_DEVICE_SHIFT)
#define EFFECT_FLAG_DEVICE_NONE         (0 << EFFECT_FLAG_DEVICE_SHIFT)

// Sample input modes
#define EFFECT_FLAG_INPUT_SHIFT         (EFFECT_FLAG_DEVICE_SHIFT + EFFECT_FLAG_DEVICE_SIZE)
#define EFFECT_FLAG_INPUT_SIZE          2
#define EFFECT_FLAG_INPUT_MASK          (((1 << EFFECT_FLAG_INPUT_SIZE) -1) \
                                            << EFFECT_FLAG_INPUT_SHIFT)
#define EFFECT_FLAG_INPUT_DIRECT        (1 << EFFECT_FLAG_INPUT_SHIFT)
#define EFFECT_FLAG_INPUT_PROVIDER      (2 << EFFECT_FLAG_INPUT_SHIFT)
#define EFFECT_FLAG_INPUT_BOTH          (3 << EFFECT_FLAG_INPUT_SHIFT)

// Sample output modes
#define EFFECT_FLAG_OUTPUT_SHIFT        (EFFECT_FLAG_INPUT_SHIFT + EFFECT_FLAG_INPUT_SIZE)
#define EFFECT_FLAG_OUTPUT_SIZE         2
#define EFFECT_FLAG_OUTPUT_MASK         (((1 << EFFECT_FLAG_OUTPUT_SIZE) -1) \
                                            << EFFECT_FLAG_OUTPUT_SHIFT)
#define EFFECT_FLAG_OUTPUT_DIRECT       (1 << EFFECT_FLAG_OUTPUT_SHIFT)
#define EFFECT_FLAG_OUTPUT_PROVIDER     (2 << EFFECT_FLAG_OUTPUT_SHIFT)
#define EFFECT_FLAG_OUTPUT_BOTH         (3 << EFFECT_FLAG_OUTPUT_SHIFT)

// Hardware acceleration mode
#define EFFECT_FLAG_HW_ACC_SHIFT        (EFFECT_FLAG_OUTPUT_SHIFT + EFFECT_FLAG_OUTPUT_SIZE)
#define EFFECT_FLAG_HW_ACC_SIZE         2
#define EFFECT_FLAG_HW_ACC_MASK         (((1 << EFFECT_FLAG_HW_ACC_SIZE) -1) \
                                            << EFFECT_FLAG_HW_ACC_SHIFT)
#define EFFECT_FLAG_HW_ACC_SIMPLE       (1 << EFFECT_FLAG_HW_ACC_SHIFT)
#define EFFECT_FLAG_HW_ACC_TUNNEL       (2 << EFFECT_FLAG_HW_ACC_SHIFT)

// Audio mode indication
#define EFFECT_FLAG_AUDIO_MODE_SHIFT    (EFFECT_FLAG_HW_ACC_SHIFT + EFFECT_FLAG_HW_ACC_SIZE)
#define EFFECT_FLAG_AUDIO_MODE_SIZE     2
#define EFFECT_FLAG_AUDIO_MODE_MASK     (((1 << EFFECT_FLAG_AUDIO_MODE_SIZE) -1) \
                                            << EFFECT_FLAG_AUDIO_MODE_SHIFT)
#define EFFECT_FLAG_AUDIO_MODE_IND      (1 << EFFECT_FLAG_AUDIO_MODE_SHIFT)
#define EFFECT_FLAG_AUDIO_MODE_NONE     (0 << EFFECT_FLAG_AUDIO_MODE_SHIFT)

// Audio source indication
#define EFFECT_FLAG_AUDIO_SOURCE_SHIFT  (EFFECT_FLAG_AUDIO_MODE_SHIFT + EFFECT_FLAG_AUDIO_MODE_SIZE)
#define EFFECT_FLAG_AUDIO_SOURCE_SIZE   2
#define EFFECT_FLAG_AUDIO_SOURCE_MASK   (((1 << EFFECT_FLAG_AUDIO_SOURCE_SIZE) -1) \
                                          << EFFECT_FLAG_AUDIO_SOURCE_SHIFT)
#define EFFECT_FLAG_AUDIO_SOURCE_IND    (1 << EFFECT_FLAG_AUDIO_SOURCE_SHIFT)
#define EFFECT_FLAG_AUDIO_SOURCE_NONE   (0 << EFFECT_FLAG_AUDIO_SOURCE_SHIFT)

// Effect offload indication
#define EFFECT_FLAG_OFFLOAD_SHIFT       (EFFECT_FLAG_AUDIO_SOURCE_SHIFT + \
                                                    EFFECT_FLAG_AUDIO_SOURCE_SIZE)
#define EFFECT_FLAG_OFFLOAD_SIZE        1
#define EFFECT_FLAG_OFFLOAD_MASK        (((1 << EFFECT_FLAG_OFFLOAD_SIZE) -1) \
                                          << EFFECT_FLAG_OFFLOAD_SHIFT)
#define EFFECT_FLAG_OFFLOAD_SUPPORTED   (1 << EFFECT_FLAG_OFFLOAD_SHIFT)

#define EFFECT_MAKE_API_VERSION(M, m)  (((M)<<16) | ((m) & 0xFFFF))
#define EFFECT_API_VERSION_MAJOR(v)    ((v)>>16)
#define EFFECT_API_VERSION_MINOR(v)    ((m) & 0xFFFF)



/////////////////////////////////////////////////
//      Effect control interface
/////////////////////////////////////////////////

// Effect control interface version 2.0
#define EFFECT_CONTROL_API_VERSION EFFECT_MAKE_API_VERSION(2,0)

// Effect control interface structure: effect_interface_s
// The effect control interface is exposed by each effect engine implementation. It consists of
// a set of functions controlling the configuration, activation and process of the engine.
// The functions are grouped in a structure of type effect_interface_s.
//
// Effect control interface handle: effect_handle_t
// The effect_handle_t serves two purposes regarding the implementation of the effect engine:
// - 1 it is the address of a pointer to an effect_interface_s structure where the functions
// of the effect control API for a particular effect are located.
// - 2 it is the address of the context of a particular effect instance.
// A typical implementation in the effect library would define a structure as follows:
// struct effect_module_s {
//        const struct effect_interface_s *itfe;
//        effect_config_t config;
//        effect_context_t context;
// }
// The implementation of EffectCreate() function would then allocate a structure of this
// type and return its address as effect_handle_t
typedef struct effect_interface_s **effect_handle_t;


// Forward definition of type audio_buffer_t
typedef struct audio_buffer_s audio_buffer_t;

//
//--- Standardized command codes for command() function
//
enum effect_command_e {
   EFFECT_CMD_INIT,                 // initialize effect engine
   EFFECT_CMD_SET_CONFIG,           // configure effect engine (see effect_config_t)
   EFFECT_CMD_RESET,                // reset effect engine
   EFFECT_CMD_ENABLE,               // enable effect process
   EFFECT_CMD_DISABLE,              // disable effect process
   EFFECT_CMD_SET_PARAM,            // set parameter immediately (see effect_param_t)
   EFFECT_CMD_SET_PARAM_DEFERRED,   // set parameter deferred
   EFFECT_CMD_SET_PARAM_COMMIT,     // commit previous set parameter deferred
   EFFECT_CMD_GET_PARAM,            // get parameter
   EFFECT_CMD_SET_DEVICE,           // set audio device (see audio.h, audio_devices_t)
   EFFECT_CMD_SET_VOLUME,           // set volume
   EFFECT_CMD_SET_AUDIO_MODE,       // set the audio mode (normal, ring, ...)
   EFFECT_CMD_SET_CONFIG_REVERSE,   // configure effect engine reverse stream(see effect_config_t)
   EFFECT_CMD_SET_INPUT_DEVICE,     // set capture device (see audio.h, audio_devices_t)
   EFFECT_CMD_GET_CONFIG,           // read effect engine configuration
   EFFECT_CMD_GET_CONFIG_REVERSE,   // read configure effect engine reverse stream configuration
   EFFECT_CMD_GET_FEATURE_SUPPORTED_CONFIGS,// get all supported configurations for a feature.
   EFFECT_CMD_GET_FEATURE_CONFIG,   // get current feature configuration
   EFFECT_CMD_SET_FEATURE_CONFIG,   // set current feature configuration
   EFFECT_CMD_SET_AUDIO_SOURCE,     // set the audio source (see audio.h, audio_source_t)
   EFFECT_CMD_OFFLOAD,              // set if effect thread is an offload one,
                                    // send the ioHandle of the effect thread
   EFFECT_CMD_FIRST_PROPRIETARY = 0x10000 // first proprietary command code
};

// Audio buffer descriptor used by process(), bufferProvider() functions and buffer_config_t
// structure. Multi-channel audio is always interleaved. The channel order is from LSB to MSB with
// regard to the channel mask definition in audio.h, audio_channel_mask_t e.g :
// Stereo: left, right
// 5 point 1: front left, front right, front center, low frequency, back left, back right
// The buffer size is expressed in frame count, a frame being composed of samples for all
// channels at a given time. Frame size for unspecified format (AUDIO_FORMAT_OTHER) is 8 bit by
// definition
struct audio_buffer_s {
    size_t   frameCount;        // number of frames in buffer
    union {
        void*       raw;        // raw pointer to start of buffer
        int32_t*    s32;        // pointer to signed 32 bit data at start of buffer
        int16_t*    s16;        // pointer to signed 16 bit data at start of buffer
        uint8_t*    u8;         // pointer to unsigned 8 bit data at start of buffer
    };
};

// The buffer_provider_s structure contains functions that can be used
// by the effect engine process() function to query and release input
// or output audio buffer.
// The getBuffer() function is called to retrieve a buffer where data
// should read from or written to by process() function.
// The releaseBuffer() function MUST be called when the buffer retrieved
// with getBuffer() is not needed anymore.
// The process function should use the buffer provider mechanism to retrieve
// input or output buffer if the inBuffer or outBuffer passed as argument is NULL
// and the buffer configuration (buffer_config_t) given by the EFFECT_CMD_SET_CONFIG
// command did not specify an audio buffer.

typedef int32_t (* buffer_function_t)(void *cookie, audio_buffer_t *buffer);

typedef struct buffer_provider_s {
    buffer_function_t getBuffer;       // retrieve next buffer
    buffer_function_t releaseBuffer;   // release used buffer
    void       *cookie;                // for use by client of buffer provider functions
} buffer_provider_t;


// The buffer_config_s structure specifies the input or output audio format
// to be used by the effect engine. It is part of the effect_config_t
// structure that defines both input and output buffer configurations and is
// passed by the EFFECT_CMD_SET_CONFIG or EFFECT_CMD_SET_CONFIG_REVERSE command.
typedef struct buffer_config_s {
    audio_buffer_t  buffer;     // buffer for use by process() function if not passed explicitly
    uint32_t   samplingRate;    // sampling rate
    uint32_t   channels;        // channel mask (see audio_channel_mask_t in audio.h)
    buffer_provider_t bufferProvider;   // buffer provider
    uint8_t    format;          // Audio format  (see see audio_format_t in audio.h)
    uint8_t    accessMode;      // read/write or accumulate in buffer (effect_buffer_access_e)
    uint16_t   mask;            // indicates which of the above fields is valid
} buffer_config_t;

// Values for "accessMode" field of buffer_config_t:
//   overwrite, read only, accumulate (read/modify/write)
enum effect_buffer_access_e {
    EFFECT_BUFFER_ACCESS_WRITE,
    EFFECT_BUFFER_ACCESS_READ,
    EFFECT_BUFFER_ACCESS_ACCUMULATE

};

// feature identifiers for EFFECT_CMD_GET_FEATURE_SUPPORTED_CONFIGS command
enum effect_feature_e {
    EFFECT_FEATURE_AUX_CHANNELS, // supports auxiliary channels (e.g. dual mic noise suppressor)
    EFFECT_FEATURE_CNT
};

// EFFECT_FEATURE_AUX_CHANNELS feature configuration descriptor. Describe a combination
// of main and auxiliary channels supported
//typedef struct channel_config_s {
//    audio_channel_mask_t main_channels; // channel mask for main channels
//    audio_channel_mask_t aux_channels;  // channel mask for auxiliary channels
//} channel_config_t;


// Values for bit field "mask" in buffer_config_t. If a bit is set, the corresponding field
// in buffer_config_t must be taken into account when executing the EFFECT_CMD_SET_CONFIG command
#define EFFECT_CONFIG_BUFFER    0x0001  // buffer field must be taken into account
#define EFFECT_CONFIG_SMP_RATE  0x0002  // samplingRate field must be taken into account
#define EFFECT_CONFIG_CHANNELS  0x0004  // channels field must be taken into account
#define EFFECT_CONFIG_FORMAT    0x0008  // format field must be taken into account
#define EFFECT_CONFIG_ACC_MODE  0x0010  // accessMode field must be taken into account
#define EFFECT_CONFIG_PROVIDER  0x0020  // bufferProvider field must be taken into account
#define EFFECT_CONFIG_ALL (EFFECT_CONFIG_BUFFER | EFFECT_CONFIG_SMP_RATE | \
                           EFFECT_CONFIG_CHANNELS | EFFECT_CONFIG_FORMAT | \
                           EFFECT_CONFIG_ACC_MODE | EFFECT_CONFIG_PROVIDER)


// effect_config_s structure describes the format of the pCmdData argument of EFFECT_CMD_SET_CONFIG
// command to configure audio parameters and buffers for effect engine input and output.
typedef struct effect_config_s {
    buffer_config_t   inputCfg;
    buffer_config_t   outputCfg;
} effect_config_t;


// effect_param_s structure describes the format of the pCmdData argument of EFFECT_CMD_SET_PARAM
// command and pCmdData and pReplyData of EFFECT_CMD_GET_PARAM command.
// psize and vsize represent the actual size of parameter and value.
//
// NOTE: the start of value field inside the data field is always on a 32 bit boundary:
//
//  +-----------+
//  | status    | sizeof(int)
//  +-----------+
//  | psize     | sizeof(int)
//  +-----------+
//  | vsize     | sizeof(int)
//  +-----------+
//  |           |   |           |
//  ~ parameter ~   > psize     |
//  |           |   |           >  ((psize - 1)/sizeof(int) + 1) * sizeof(int)
//  +-----------+               |
//  | padding   |               |
//  +-----------+
//  |           |   |
//  ~ value     ~   > vsize
//  |           |   |
//  +-----------+

typedef struct effect_param_s {
    int32_t     status;     // Transaction status (unused for command, used for reply)
    uint32_t    psize;      // Parameter size
    uint32_t    vsize;      // Value size
    char        data[];     // Start of Parameter + Value data
} effect_param_t;

// structure used by EFFECT_CMD_OFFLOAD command

//typedef struct effect_offload_param_s {
//    bool isOffload;         // true if the playback thread the effect is attached to is offloaded
//    int ioHandle;           // io handle of the playback thread the effect is attached to
//} effect_offload_param_t;


/////////////////////////////////////////////////
//      Effect library interface
/////////////////////////////////////////////////

// Effect library interface version 3.0
// Note that EffectsFactory.c only checks the major version component, so changes to the minor
// number can only be used for fully backwards compatible changes
#define EFFECT_LIBRARY_API_VERSION EFFECT_MAKE_API_VERSION(3,0)

#define AUDIO_EFFECT_LIBRARY_TAG ((('A') << 24) | (('E') << 16) | (('L') << 8) | ('T'))

// Every effect library must have a data structure named AUDIO_EFFECT_LIBRARY_INFO_SYM
// and the fields of this data structure must begin with audio_effect_library_t

// Name of the hal_module_info
#define AUDIO_EFFECT_LIBRARY_INFO_SYM         AELI

// Name of the hal_module_info as a string
#define AUDIO_EFFECT_LIBRARY_INFO_SYM_AS_STR  "AELI"

__END_DECLS

#endif  // ANDROID_AUDIO_EFFECT_H
