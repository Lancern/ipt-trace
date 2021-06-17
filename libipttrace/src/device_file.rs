use std::fs::{File, OpenOptions};
use std::mem::MaybeUninit;
use std::os::raw::c_ulong;
use std::os::unix::io::AsRawFd;

use crate::cap::IptCpuCap;

#[repr(i32)]
#[allow(non_camel_case_types)]
pub enum IptDeviceFileIoctlCmd {
    IPT_IOCTL_CMD_CPU_CAP = 1,
}

pub struct IptDeviceFile {
    f: File,
}

impl IptDeviceFile {
    pub fn open() -> std::io::Result<Self> {
        let f = OpenOptions::new()
            .read(true)
            .write(true)
            .create(false)
            .create_new(false)
            .open("/dev/ipt")?;
        Ok(Self { f })
    }

    pub fn query_cpu_cap(&mut self) -> std::io::Result<IptCpuCap> {
        let fd = self.f.as_raw_fd();
        let mut cap = MaybeUninit::<IptCpuCap>::uninit();

        let ret = unsafe {
            libc::ioctl(
                fd,
                IptDeviceFileIoctlCmd::IPT_IOCTL_CMD_CPU_CAP as c_ulong,
                cap.as_mut_ptr())
        };
        if ret != 0 {
            return Err(std::io::Error::last_os_error());
        }

        let cap = unsafe { cap.assume_init() };
        Ok(cap)
    }
}
