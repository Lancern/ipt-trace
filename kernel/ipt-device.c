#include "ipt-device.h"

#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>

#include "ipt-processor.h"

#define IPT_CHRDEV_NAME       "ipt"
#define IPT_DEVICE_NAME       "ipt"
#define IPT_DEVICE_CLASS_NAME "ipt"

#define IPT_FIRST_MINOR 0
#define IPT_NUM_MINORS  1

#define IPT_IOCTL_CMD_CPU_CAP 1

static int ipt_major = -1;
static int ipt_device_created;
static struct cdev ipt_cdev;
static struct class *ipt_class;

static int ipt_device_open(struct inode *inode, struct file *filp);
static int ipt_device_release(struct inode *inode, struct file *filp);
static ssize_t ipt_device_read(struct file *filp, char *buf, size_t len, loff_t *off);
static ssize_t ipt_device_write(struct file *filp, const char *buf, size_t len, loff_t *off);
static long ipt_device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);

static struct file_operations ipt_fileops = {
  .open = ipt_device_open,
  .release = ipt_device_release,
  .read = ipt_device_read,
  .write = ipt_device_write,
  .unlocked_ioctl = ipt_device_ioctl,
};

static int ipt_device_open(struct inode *inode, struct file *filp) {
  // TODO: finish ipt_device_open
  return -ENOSYS;
}

static int ipt_device_release(struct inode *inode, struct file *filp) {
  // TODO: finish ipt_device_release
  return -ENOSYS;
}

static ssize_t ipt_device_read(struct file *filp, char *buf, size_t len, loff_t *off) {
  // TODO: finish ipt_device_read
  return -ENOSYS;
}

static ssize_t ipt_device_write(struct file *filp, const char *buf, size_t len, loff_t *off) {
  // TODO: finish ipt_device_write
  return -ENOSYS;
}

static long ipt_device_ioctl_cpu_cap(unsigned long arg) {
  struct ipt_cpu_cap cap;

  ipt_query_cpu_cap(&cap);
  copy_to_user((struct ipt_cpu_cap *)arg, &cap, sizeof(cap));

  return 0;
}

static long ipt_device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
  // TODO: finish ipt_device_ioctl

  switch (cmd) {
  case IPT_IOCTL_CMD_CPU_CAP:
    return ipt_device_ioctl_cpu_cap(arg);

  default:
    return -ENOTTY;
  }

  return 0;
}

int ipt_device_init(void) {
  int ret = 0;

  do {
    ret = alloc_chrdev_region(&ipt_major, IPT_FIRST_MINOR, IPT_NUM_MINORS, IPT_CHRDEV_NAME);
    if (ret < 0) {
      pr_alert("cannot allocate ipt character device region \"%s\": %d\n", IPT_CHRDEV_NAME, ret);
      break;
    }

    ipt_class = class_create(THIS_MODULE, IPT_DEVICE_CLASS_NAME);
    if (!ipt_class) {
      pr_alert("cannot create ipt device class \"%s\"\n", IPT_DEVICE_CLASS_NAME);
      ret = -1;
      break;
    }

    // device_create will create a device file under /dev
    if (!device_create(ipt_class, NULL, ipt_major, NULL, IPT_DEVICE_NAME)) {
      pr_alert("cannot create ipt device \"%s\"\n", IPT_DEVICE_NAME);
      ret = -1;
      break;
    }

    ipt_device_created = 1;

    cdev_init(&ipt_cdev, &ipt_fileops);
    ret = cdev_add(&ipt_cdev, ipt_major, 1);
    if (ret < 0) {
      pr_alert("cannot add ipt character device: %d\n", ret);
    }
  } while (0);

  if (ret != 0) {
    ipt_device_uninit();
  }

  return ret;
}

void ipt_device_uninit(void) {
  if (ipt_device_created) {
    device_destroy(ipt_class, ipt_major);
    cdev_del(&ipt_cdev);
    ipt_device_created = 0;
  }
  if (ipt_class) {
    class_destroy(ipt_class);
    ipt_class = 0;
  }
  if (ipt_major != -1) {
    unregister_chrdev_region(ipt_major, 1);
    ipt_major = -1;
  }
}
