#ifndef IPT_DEVICE_H
#define IPT_DEVICE_H

#define IPT_DEVICE_NAME "ipt"
#define IPT_DEVICE_PATH "/dev/ipt"

int ipt_device_init(void);
void ipt_device_uninit(void);

#endif // IPT_DEVICE_H
