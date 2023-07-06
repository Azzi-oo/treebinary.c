#ifndef SRC_PRINT_MODULE_H
#define SRC_PRINT_MODULE_H
 
#define Module_load_success_message "Output stream module load: success\n"
#define Log_prefix "[LOG]"
 
/*
input: printchar-callback, log message
output: void
result: "Log_prefix HH:MM:SS message"
*/
void print_log(char (*print)(char)(int), char* message);
 
int print_char(char ch);
 
void print_docs(short mask, int documents_count, ...);
 
#endif // PRINT_MODULE_H
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
 
#include "print_module.h"
 
#define LOG_PREFIX "LOG"
 
int print_char(int ch) {
return putchar(ch);
}
 
void print_log(int (*print)(int), char* message) {
time_t raw;
struct tm* timeinfo = (struct tm*)malloc(sizeof(struct tm));
time(&raw);
timeinfo = localtime_r(&raw, timeinfo);
int hour = timeinfo->tm_hour;
int min = timeinfo->tm_min;
int sec = timeinfo->tm_sec;
printf("%s %d:%d:%d ", LOG_PREFIX, hour, min, sec);
while (*message != '\0') {
print(*message);
message++;
}
}
 
void print_docs(short mask, int documents_count, ...) {
va_list ptr;
va_start(ptr, documents_count);
int ct = 0;
while (mask > 0) {
if (ct == documents_count)
break;
ct++;
char* str = va_arg(ptr, char*);
if ((mask % 2) == 1) {
printf("%d.%-15s:", ct, str);
printf("available\n");
} else {
printf("%d.%-15s:", ct, str);
printf("unavailable\n");
}
mask /= 2;
}
va_end(ptr);
}
