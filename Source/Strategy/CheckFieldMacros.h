#pragma once

#include "CoreMinimal.h"

#define CHECK_FIELD(Category, Ptr)                                                                                     \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(Ptr))                                                                                                    \
        {                                                                                                              \
            UE_LOG(Category, Error, TEXT("[%s:%d] %s - Field '%s' is null or invalid"), TEXT(__FILE__), __LINE__,      \
                TEXT(__FUNCTION__), TEXT(#Ptr));                                                                       \
        }                                                                                                              \
    } while (false)

#define CHECK_FIELD_RETURN(Category, Ptr)                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(Ptr))                                                                                                    \
        {                                                                                                              \
            UE_LOG(Category, Error, TEXT("[%s:%d] %s - Field '%s' is null or invalid, returning"), TEXT(__FILE__),     \
                __LINE__, TEXT(__FUNCTION__), TEXT(#Ptr));                                                             \
            return;                                                                                                    \
        }                                                                                                              \
    } while (false)

#define CHECK_FIELD_RETURN_VAL(Category, Ptr, Val)                                                                     \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(Ptr))                                                                                                    \
        {                                                                                                              \
            UE_LOG(Category, Error, TEXT("[%s:%d] %s - Field '%s' is null or invalid, returning '%s'"),                \
                TEXT(__FILE__), __LINE__, TEXT(__FUNCTION__), TEXT(#Ptr), TEXT(#Val));                                 \
            return Val;                                                                                                \
        }                                                                                                              \
    } while (false)
