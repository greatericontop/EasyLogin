#include "dataloader.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


bool verify_file() {
  char path[2000];
  snprintf(path, sizeof(path), "%s/.easylogin_config", getenv("HOME"));
  FILE *fp = fopen(path, "r");
  if (!fp) {
    return false;
  }
  // Check permissions equal to 600
  struct stat st;
  if (fstat(fileno(fp), &st) != 0) {
    fclose(fp);
    return false;
  }
  if ((st.st_mode & 0777) != 0600) {
    fclose(fp);
    return false;
  }
  fclose(fp);
  return true;
}


bool load(struct UserData *output) {
  if (!verify_file()) {
    return false;
  }
  char path[2000];
  snprintf(path, sizeof(path), "%s/.easylogin_config", getenv("HOME"));
  FILE *fp = fopen(path, "r");
  if (!fp) {
    return false;
  }
  int count = fscanf(fp, "%lld %31s", &output->timestamp, output->password);
  if (count != 2) {
    fclose(fp);
    return false;
  }
  fclose(fp);
  return true;
}


bool save(const struct UserData data) {
  char path[2000];
  snprintf(path, sizeof(path), "%s/.easylogin_config", getenv("HOME"));
  FILE *fp = fopen(path, "w");
  if (!fp) {
    return false;
  }
  if (fchmod(fileno(fp), S_IRUSR | S_IWUSR) != 0) {
    fclose(fp);
    return false;
  }
  int count = fprintf(fp, "%lld %s\n", data.timestamp, data.password);
  if (count < 0) {
    fclose(fp);
    return false;
  }
  fclose(fp);
  return true;
}
