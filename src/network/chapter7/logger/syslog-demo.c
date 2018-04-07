//
// Created by xing on 4/7/18.
//

#include <syslog.h>
#include <unistd.h>

// will output /var/log/syslog
// or logger "something" in terminal
// see:
// https://stackoverflow.com/questions/10952515/c-c-syslog-to-custom-file-not-var-log-syslog-but-var-log-mylog-ubuntu-12
// or https://askubuntu.com/questions/186592/how-do-i-configure-rsyslog-to-send-logs-from-a-specific-program-to-a-remote-sysl
// for custom log file name

int main() {
  setlogmask(LOG_UPTO(LOG_NOTICE));
  openlog("demo", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL0);
  syslog(LOG_NOTICE, "Program started by User %d", getuid());
  syslog(LOG_WARNING, "Warning: A tree falls in a forest");
  syslog(LOG_INFO, "INFO: A tree falls in a forest");
  closelog();

  return 0;
}