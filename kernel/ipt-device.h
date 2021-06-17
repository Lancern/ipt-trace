#ifndef IPT_DEVICE_H
#define IPT_DEVICE_H

/// Initialize the virtual device at /dev/ipt.
int ipt_device_init(void);

/// Uninitialize the virtual device at /dev/ipt.
void ipt_device_uninit(void);

#endif // IPT_DEVICE_H
