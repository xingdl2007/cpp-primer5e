//
// Created by xing on 4/7/18.
//

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// switch from root to non-root user
static bool switch_to_user(uid_t user_id, gid_t gp_id) {
  if (user_id == 0 && gp_id == 0) {
    return false;
  }
  gid_t gid = getgid();
  uid_t uid = getuid();
  // must be root or target user
  if ((gid == 0 && uid == 0) || (gid == gp_id && uid == user_id)) {
    if (uid != 0) {
      return true; // we are already target user
    }
    if (setgid(gp_id) < 0 || setuid(user_id) < 0) {
      return false;
    } else {
      return true;
    }
  }
  return false;
}

// demo: how to switch from root to normal user after start
// 1. sudo chown root:root uid
// 2. sudo uid
int main() {
  uid_t uid = getuid();
  uid_t e_uid = geteuid();
  printf("user id is %d, effective user id is: %d\n", uid, e_uid);

  // switch to normal user
  bool ret = switch_to_user(1000, 1000);
  assert(ret);

  printf("user id is %d, group id is: %d\n", getuid(), getgid());
  return 0;
}
