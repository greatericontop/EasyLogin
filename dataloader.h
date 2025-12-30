#pragma once


#include <stdbool.h>


#define PW_ARRAY_LEN 32
#define PW_SCANF "%31s"
#define DATAFILE_SCANF "%lld %31s"


struct UserData {
  long long timestamp;
  char password[PW_ARRAY_LEN];
};


/* Verify that the user data file exists and is valid */
bool verify_file();


/* Load the user data and return whether it was successful */
bool load(struct UserData *output);


/* Save the user data, returns whether it was successful */
bool save(const struct UserData data);