#include "os1.h"
// Usage example
int main() {
    const char* datetime = "2024-01-15T14:30:00";
    char buf[24] = "";
    time_t epoch_seconds = datetime_to_epoch(datetime);

    if (epoch_seconds != -1) {
	printf("Datetime: %s\n", datetime);
        printf("Epoch seconds: %ld\n", epoch_seconds);
    } else {
	printf("Failed to parse datetime string\n");
    }
    epoch_to_datetime(epoch_seconds,buf,23);
    printf("Original datetime: %s\n",buf);
    return 0;
}
