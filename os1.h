#include <stdio.h>
#include <time.h>
#include <string.h>
time_t datetime_to_epoch(const char* datetime_str){
    int res;
    struct tm timeinfo = {0};
// Parse the datetime string (yyyy-MM-ddThh:mm:ss f>
    res = sscanf(datetime_str, "%4d-%2d-%2dT%2d:%2d:%2d",
               &timeinfo.tm_year, &timeinfo.tm_mon, &timeinfo.tm_mday,
               &timeinfo.tm_hour, &timeinfo.tm_min, &timeinfo.tm_sec);
    printf("res: %d\n",res);

    // Adjust struct tm values (tm_year is years since >
    timeinfo.tm_year -= 1900;
    timeinfo.tm_mon -= 1;

    // Convert to time_t (seconds since epoch)
    return mktime(&timeinfo);
}
void epoch_to_datetime(time_t epoch_seconds, char* buffer, size_t buffer_size){
    struct tm* timeinfo;
    // Convert epoch seconds to struct t
   timeinfo = localtime(&epoch_seconds);

    // Format as yyyy-MM-ddThh:mm:ss
    strftime(buffer, buffer_size, "%Y-%m-%dT%H:%M:%S", timeinfo);
}
