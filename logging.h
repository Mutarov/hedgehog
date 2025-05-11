#ifndef LIVCSLL
#define LIVCSLL
// From github.com/Mutarov/livcsll

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#ifdef _WIN32
#include <stdlib.h>
#include <sys/timeb.h>
#include <windows.h>
#endif

#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_WHITE "\033[37m"
#define COLOR_GRAY "\033[90m"

static int has_color_support() {
  static int checked = -1;
  if (checked == -1) {
    checked = isatty(fileno(stdout));
  }
  return checked;
}

static const char *get_current_time() {
  static char buffer[64]; // Увеличиваем размер буфера для безопасности
  time_t t = time(NULL);
  struct tm lt = *localtime(&t);

  int offset;
#ifdef _WIN32
  TIME_ZONE_INFORMATION tz;
  GetTimeZoneInformation(&tz);
  offset =
      -tz.Bias / 60; // Bias is in minutes, so divide by 60 for hours offset
#else
  offset = lt.tm_gmtoff / 3600;
#endif

  snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d%+03d",
           lt.tm_year + 1900, lt.tm_mon + 1, lt.tm_mday, lt.tm_hour, lt.tm_min,
           lt.tm_sec, offset);
  return buffer;
}

#define LOG(level_color, level, fmt, ...)                                      \
  do {                                                                         \
    const char *time_str = get_current_time();                                 \
    if (has_color_support()) {                                                 \
      printf(COLOR_GRAY "[%s] " level_color "(%s) " fmt COLOR_RESET "\n",      \
             time_str, level, ##__VA_ARGS__);                                  \
    } else {                                                                   \
      printf("[%s] (%s) " fmt "\n", time_str, level, ##__VA_ARGS__);           \
    }                                                                          \
  } while (0)

#define L_INFO(fmt, ...) LOG(COLOR_WHITE, "INFO", fmt, ##__VA_ARGS__)
#define L_SUCCESS(fmt, ...) LOG(COLOR_GREEN, "SUCCESS", fmt, ##__VA_ARGS__)
#define L_WARN(fmt, ...) LOG(COLOR_YELLOW, "WARN", fmt, ##__VA_ARGS__)
#define L_ERROR(fmt, ...) LOG(COLOR_RED, "ERROR", fmt, ##__VA_ARGS__)

#endif // LIVCSLL
