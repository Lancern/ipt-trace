#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include "ipt-device.h"
#include "ipt-info.h"

MODULE_LICENSE(IPT_LICENSE);
MODULE_AUTHOR(IPT_AUTHOR);
MODULE_DESCRIPTION(IPT_DESCRIPTION);
MODULE_VERSION(IPT_VERSION);

static int __init ipt_init(void) {
  int ret = ipt_device_init();
  if (ret < 0) {
    pr_alert("Failed to init IPT device file: error code is %d\n", ret);
    return ret;
  }

  pr_info("ipt module loaded\n");
  return 0;
}

static void __exit ipt_exit(void) {
  ipt_device_uninit();

  pr_info("ipt module unloaded\n");
}

module_init(ipt_init);
module_exit(ipt_exit);
