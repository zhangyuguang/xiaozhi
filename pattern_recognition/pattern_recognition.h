#ifndef _PATTERN_RECOGNITION_
#define _PATTERN_RECOGNITION_

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#define INPUT_LEN               256

#define NUM_USER                1000

#define USER_ID_RANGE_NEW       1000
#define USER_ID_RANGE_HIGH      700
#define USER_ID_RANGE_MEDIUM    300
#define USER_ID_RANGE_LOW       0

#define LOC_LEN                 32

    typedef enum user_type {
        HIGH,
        MEDIUM,
        LOW,
        INVALID_USER
    } USER_TYPE;

    typedef struct user_data {
        int user_id;
        USER_TYPE user_t;
        char home_loc[LOC_LEN];
        char work_loc[LOC_LEN];
        char school_loc[LOC_LEN];
        char curr_loc[LOC_LEN];
        char target_loc[LOC_LEN];
    } USER_DATA;

/*--- INTERFACES ---------------------------------------------------------------*/
#ifdef PT_REC_C
#	define private_pt_rec(x) x
#	define public_pt_rec(x) x
#else
#	define private_pt_rec(x)
#	define public_pt_rec(x) extern x
#endif

/** @defgroup pattern_recognition interfaces
 * @{*/
public_pt_rec(void init_users(void););
public_pt_rec(int pattern_recognition(lamp_data_t *input, pr_result_t *output);)
/* @}*/
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

#endif
