#pragma once


struct UserData {
  long long timestamp;
  char password[32];
};


/* Verify that the user data file exists and is valid */
bool verify_file();


/* Load the user data and return whether it was successful */
bool load(struct UserData *output);


/* Save the user data, returns whether it was successful */
bool save(const struct UserData data);