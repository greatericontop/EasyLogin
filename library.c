
#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dataloader.h"


PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  struct pam_conv *conv;
  if (pam_get_item(pamh, PAM_CONV, (const void **)&conv) != PAM_SUCCESS) {
    return PAM_AUTH_ERR;
  }

  struct UserData data;
  if (!load(&data)) {
    return PAM_AUTH_ERR;
  }
  if (time(NULL) > data.timestamp) {
    memset(data.password, 0, strlen(data.password));
    return PAM_AUTH_ERR;
  }

  struct pam_message msg = { .msg_style = PAM_PROMPT_ECHO_OFF, .msg = "EasyLogin Code: " };
  struct pam_message *msg_ptr = &msg;
  struct pam_response *resp_ptr;
  int ret1 = conv->conv(1, (const struct pam_message **)&msg_ptr, &resp_ptr, conv->appdata_ptr);
  if (ret1 != PAM_SUCCESS) {
    memset(data.password, 0, strlen(data.password));
    return PAM_AUTH_ERR;
  }

  // Immediately lock timestamp once a non-empty attempt is entered
  if (strlen(resp_ptr->resp) != 0) {
    data.timestamp = 0LL;
    if (!save(data)) {
      memset(data.password, 0, strlen(data.password));
      memset(resp_ptr->resp, 0, strlen(resp_ptr->resp));
      free(resp_ptr->resp);
      free(resp_ptr);
      return PAM_AUTH_ERR;
    }
  }
  // Don't really care about hashing or comparison timing
  int ret2;
  if (strcmp(resp_ptr->resp, data.password) == 0) {
    ret2 = PAM_SUCCESS;
  } else {
    ret2 = PAM_AUTH_ERR;
  }
  memset(data.password, 0, strlen(data.password));
  memset(resp_ptr->resp, 0, strlen(resp_ptr->resp));
  free(resp_ptr->resp);
  free(resp_ptr);
  return ret2;
}


PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  return PAM_SUCCESS;
}
