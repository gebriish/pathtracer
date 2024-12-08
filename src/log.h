#pragma once
#include <iostream>

#define LOG_INFO(...) printf("[INFO] >  " __VA_ARGS__)
#define LOG_WARN(...) printf("[WARN] >  " __VA_ARGS__)
#define LOG_SVER(...) printf("[SVER] >  " __VA_ARGS__)

#define ERROR_EXIT(...) printf(__VA_ARGS__); exit(1)
