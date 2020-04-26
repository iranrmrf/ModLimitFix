#include "GameAPI.h"
#include "GameRTTI.h"

#if FALLOUT_VERSION == FALLOUT_VERSION_1_0

#include "GameRTTI_1_0.inl"

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_0_15

#include "GameRTTI_1_0_15.inl"

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_1_35

#include "GameRTTI_1_1_35.inl"

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6

#include "GameRTTI_1_4_6.inl"

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_4_6b

#include "GameRTTI_1_4_6b.inl"

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_5_22

#include "GameRTTI_1_5_22.inl"

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_6

#include "GameRTTI_1_6_3.inl"

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7

#include "GameRTTI_1_7_3.inl"

#elif FALLOUT_VERSION == FALLOUT_VERSION_1_7ng

#include "GameRTTI_1_7_3ng.inl"

#else

#error unsupported version of runtime

#endif
