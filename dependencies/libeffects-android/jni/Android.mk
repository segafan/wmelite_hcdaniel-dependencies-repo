LOCAL_PATH:= $(call my-dir)

# Reverb library
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES:= \
    Reverb/src/LVREV_ApplyNewSettings.c \
    Reverb/src/LVREV_ClearAudioBuffers.c \
    Reverb/src/LVREV_GetControlParameters.c \
    Reverb/src/LVREV_GetInstanceHandle.c \
    Reverb/src/LVREV_GetMemoryTable.c \
    Reverb/src/LVREV_Process.c \
    Reverb/src/LVREV_SetControlParameters.c \
    Reverb/src/LVREV_Tables.c \
    Common/src/Abs_32.c \
    Common/src/InstAlloc.c \
    Common/src/LoadConst_16.c \
    Common/src/LoadConst_32.c \
    Common/src/From2iToMono_32.c \
    Common/src/Mult3s_32x16.c \
    Common/src/FO_1I_D32F32C31_TRC_WRA_01.c \
    Common/src/FO_1I_D32F32Cll_TRC_WRA_01_Init.c \
    Common/src/DelayAllPass_Sat_32x16To32.c \
    Common/src/Copy_16.c \
    Common/src/Mac3s_Sat_32x16.c \
    Common/src/DelayWrite_32.c \
    Common/src/Shift_Sat_v32xv32.c \
    Common/src/Add2_Sat_32x32.c \
    Common/src/JoinTo2i_32x32.c \
    Common/src/MonoTo2I_32.c \
    Common/src/LVM_FO_HPF.c \
    Common/src/LVM_FO_LPF.c \
    Common/src/LVM_Polynomial.c \
    Common/src/LVM_Power10.c \
    Common/src/LVM_GetOmega.c \
    Common/src/MixSoft_2St_D32C31_SAT.c \
    Common/src/MixSoft_1St_D32C31_WRA.c \
    Common/src/MixInSoft_D32C31_SAT.c \
    Common/src/LVM_Mixer_TimeConstant.c \
    Common/src/Core_MixHard_2St_D32C31_SAT.c \
    Common/src/Core_MixSoft_1St_D32C31_WRA.c \
    Common/src/Core_MixInSoft_D32C31_SAT.c

LOCAL_MODULE:= libeffectscore

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/Reverb/lib \
    $(LOCAL_PATH)/Reverb/src \
    $(LOCAL_PATH)/Common/lib \
    $(LOCAL_PATH)/Common/src

LOCAL_CFLAGS += -fvisibility=hidden -std=c99
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES:= \
    Wrapper/ReverbLibrary.c

LOCAL_MODULE:= libeffects

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/Wrapper    \
    $(LOCAL_PATH)/Reverb/lib \
    $(LOCAL_PATH)/Reverb/src \
    $(LOCAL_PATH)/Common/lib \
    $(LOCAL_PATH)/Common/src \
    $(LOCAL_PATH)/

LOCAL_STATIC_LIBRARIES += libeffectscore

LOCAL_CFLAGS += -fvisibility=hidden  -std=c99

include $(BUILD_SHARED_LIBRARY)

