#include <string.h>
#include <stdio.h>
//#include <time.h>

#include "../utils/log/log.h"
//#include "../utils/db/db_mysql.h"
#include "../collab_filter/collab_filter.h"
#include "../common.h"

#include "pattern_recognition.h"

#define PT_RET_C

static char *result[MAX_LEN] = {0};

static USER_DATA users[NUM_USER];

void init_users(void)
{
    users[500].user_id = 500;
    users[500].user_t = MEDIUM;
    strncpy(users[500].home_loc, "山河城", MAX_LEN);
    strncpy(users[500].work_loc, "株洲路159号", MAX_LEN);
    
    users[200].user_id = 200;
    users[200].user_t = LOW;
    strncpy(users[200].school_loc, "海大崂山校区", MAX_LEN);
}

USER_TYPE get_user_type(int user_id)
{
    USER_TYPE user_t;

    return user_t;
}

int is_new_user(int user_id)
{
    return false;
}

USER_TYPE classify_user(int user_id, lamp_data_t *input)
{
    USER_TYPE user_t = INVALID_USER;

    if (user_id > USER_ID_RANGE_HIGH)
        user_t = HIGH;
    else if (user_id > USER_ID_RANGE_MEDIUM)
        user_t = MEDIUM;
    else if (user_id > USER_ID_RANGE_LOW)
        user_t = LOW;
    else
        user_t = INVALID_USER;

    return user_t;
}

int update_location(int user_id, char *loc)
{
    strncpy(users[user_id].curr_loc, loc, MAX_LEN);

    return 0; 
}

int is_road_blocking(char *src, char *dst, char *blocking)
{
    src = src;
    dst = dst;

    strncpy(blocking, "枣山东路", MAX_LEN);

    return true;
}

int scenario_on_working_way(int user_id, pr_result_t *output)
{
    char blocking[MAX_LEN];

    if (!strcmp(users[user_id].curr_loc, users[user_id].home_loc))
        output->pr_type = EMPTY;
    else if (!strcmp(users[user_id].curr_loc, users[user_id].work_loc))
        output->pr_type = EMPTY;
    else if (is_road_blocking(users[user_id].curr_loc, users[user_id].work_loc, blocking))
    {
        output->pr_type = LU_KUANG;
        snprintf(output->pr_prompt, MAX_LEN, "%s 路段发生交通事故，从此至 %s 道路拥堵，请提前规划路线", blocking, users[user_id].work_loc);
        strncpy(output->pr_special, blocking, MAX_LEN);

        return true;
    }
	printf("dddddddddddddddd\n");
    return false;
}

int scenario_in_film_window(int user_id, lamp_data_t *input, pr_result_t *output)
{
   if (!strcmp(users[user_id].curr_loc, "李沧万达"))
   {
        output->pr_type = RECOMMEND;
        strncpy(output->pr_prompt, "距离电影入场还有30分钟，现向您推荐以下快餐", MAX_LEN);
        strncpy(output->pr_special, collab_filter(input->add_info), MAX_LEN);

        return true;
   }
   else
   {
       output->pr_type = EMPTY;
       return false;
   }
}

int pattern_recognition(lamp_data_t *input, pr_result_t *output)
{
    char *result = 0;

    EVENT_TYPE_T event = input->lamp_type;
    struct tm *lamp_date_time = gmtime(&input->lamp_date_time);
    char *add_info = input->add_info;
    USER_TYPE user_t;
/*
    if (is_new_user(input->lamp_uid))
        user_t = classify_user(input->lamp_uid, input);
    else
        user_t = get_user_type(input->lamp_uid);
*/
    switch (event)
    {
        case LOCATION:
            update_location(input->lamp_uid, input->lamp_info);
            printf("XXXXXXXXXXXXxx%d\n",lamp_date_time->tm_hour);
            if ((lamp_date_time->tm_hour < 9) && (lamp_date_time->tm_hour > 6))
            {
               if (scenario_on_working_way(input->lamp_uid, output))
               {
					//PRT_LOG_T(LOG_INFO, PATTERN_RECOGNITION,"The pattern recognition prompt info is %s\n", output->pr_prompt);
					//PRT_LOG_T(LOG_INFO, PATTERN_RECOGNITION,"The pattern recognition special info is %s\n", output->pr_special);
					printf("The pattern recognition prompt info is %s\n", output->pr_prompt);
					printf("The pattern recognition special info is %s\n", output->pr_special);
					return true;
               }
               else
                   return false;
            }
            
            if ((lamp_date_time->tm_hour > 17) && (lamp_date_time->tm_hour < 19))
            {
                if (scenario_in_film_window(input->lamp_uid, input, output))
                {
					//PRT_LOG_T(LOG_INFO, PATTERN_RECOGNITION,"The pattern recognition prompt info is %s\n", output->pr_prompt);
					//PRT_LOG_T(LOG_INFO, PATTERN_RECOGNITION,"The pattern recognition special info is %s\n", output->pr_special);
					printf("The pattern recognition prompt info is %s\n", output->pr_prompt);
					printf("The pattern recognition special info is %s\n", output->pr_special);
					return true;
                }
            }
            break;

        case SMS:

            break;
        case CALL:
            break;
        case SEARCH:
            break;
        default:
            break;
    }
}

/*
void main(void)
{
	//lamp_data_t input = {LOCATION, 500, 123406389, "劲松路", ""};
	lamp_data_t input = {LOCATION, 123445989, "李沧万达", "20590 3.0 98925 5.0 8587 2.0"};
	pr_result_t output;
	
	init_users();
	pattern_recognition(&input, &output);
}
*/

