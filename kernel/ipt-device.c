#include "ipt-device.h"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

#define IPT_DEVICE_MAJOR 42

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

static long ipt_device_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
  // TODO: finish ipt_device_ioctl
  return -ENOSYS;
}

int ipt_device_init(void) {
  int ret = register_chrdev(IPT_DEVICE_MAJOR, IPT_DEVICE_NAME, &ipt_fileops);
  if (ret < 0) {
    return ret;
  }

  return 0;
}

void ipt_device_uninit(void) {
  unregister_chrdev(IPT_DEVICE_MAJOR, IPT_DEVICE_NAME);
}
