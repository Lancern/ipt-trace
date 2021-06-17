use crate::device_file::IptDeviceFile;

#[derive(Clone, Debug)]
#[repr(C)]
pub struct IptCpuCap {
    flags: u16,
    num_address_ranges: u16,
    supported_mtc_period: u16,
    supported_cycle_threshold: u16,
    supported_psb_freq: u16,
}

impl IptCpuCap {
    const FLAG_OFFSET_PT_SUPPORT: usize = 0;
    const FLAG_OFFSET_CR3_FILTER_SUPPORT: usize = 1;
    const FLAG_OFFSET_PSB_FREQ_SUPPORT: usize = 2;
    const FLAG_OFFSET_IP_FILTER_SUPPORT: usize = 3;
    const FLAG_OFFSET_MTC_SUPPORT: usize = 4;
    const FLAG_OFFSET_PTWRITE_SUPPORT: usize = 5;
    const FLAG_OFFSET_POWER_EVENT_TRACE_SUPPORT: usize = 6;
    const FLAG_OFFSET_TOPA_OUTPUT_SUPPORT: usize = 7;
    const FLAG_OFFSET_TOPA_TABLES_ALLOW_MULTIPLE_OUTPUT_ENTRIES: usize = 8;
    const FLAG_OFFSET_SINGLE_RANGE_OUTPUT_SUPPORT: usize = 9;
    const FLAG_OFFSET_TRACE_TRANSPORT_SYSTEM_SUPPORT: usize = 10;
    const FLAG_OFFSET_IP_PAYLOADS_ARE_LIP: usize = 11;
    const FLAG_OFFSET_HAS_EXTRA_PARAM: usize = 12;

    pub fn query() -> std::io::Result<Self> {
        IptDeviceFile::open()?.query_cpu_cap()
    }

    fn get_flag(&self, offset: usize) -> bool {
        (self.flags >> offset) & 1 == 1
    }

    pub fn is_pt_supported(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_PT_SUPPORT)
    }

    pub fn is_cr3_filter_supported(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_CR3_FILTER_SUPPORT)
    }

    pub fn is_psb_freq_supported(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_PSB_FREQ_SUPPORT)
    }

    pub fn is_ip_filter_supported(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_IP_FILTER_SUPPORT)
    }

    pub fn is_mtc_supported(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_MTC_SUPPORT)
    }

    pub fn is_ptwrite_supported(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_PTWRITE_SUPPORT)
    }

    pub fn is_power_event_trace_supported(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_POWER_EVENT_TRACE_SUPPORT)
    }

    pub fn is_topa_output_supported(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_TOPA_OUTPUT_SUPPORT)
    }

    pub fn topa_tables_allow_multiple_output_entries(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_TOPA_TABLES_ALLOW_MULTIPLE_OUTPUT_ENTRIES)
    }

    pub fn is_single_range_output_supported(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_SINGLE_RANGE_OUTPUT_SUPPORT)
    }

    pub fn is_trace_transport_system_supported(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_TRACE_TRANSPORT_SYSTEM_SUPPORT)
    }

    pub fn is_ip_payloads_lip(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_IP_PAYLOADS_ARE_LIP)
    }

    pub fn has_extra_params(&self) -> bool {
        self.get_flag(Self::FLAG_OFFSET_HAS_EXTRA_PARAM)
    }

    pub fn num_address_ranges(&self) -> u32 {
        self.num_address_ranges as u32
    }

    pub fn supported_mtc_periods(&self) -> Vec<u32> {
        (0..16u32).filter(|x| self.is_supported_mtc_period(*x)).collect()
    }

    pub fn is_supported_mtc_period(&self, mtc_period: u32) -> bool {
        if mtc_period >= 16 {
            false
        } else {
            (self.supported_mtc_period >> mtc_period) & 1 == 1
        }
    }

    pub fn supported_cycle_thresholds(&self) -> Vec<u32> {
        (0..16u32).filter(|x| self.is_supported_cycle_threshold(*x)).collect()
    }

    pub fn is_supported_cycle_threshold(&self, cycle_threshold: u32) -> bool {
        if cycle_threshold >= 16 {
            false
        } else {
            (self.supported_cycle_threshold >> cycle_threshold) & 1 == 1
        }
    }

    pub fn supported_psb_freq(&self) -> Vec<u32> {
        (0..16u32).filter(|x| self.is_supported_psb_freq(*x)).collect()
    }

    pub fn is_supported_psb_freq(&self, psb_freq: u32) -> bool {
        if psb_freq >= 16 {
            false
        } else {
            (self.supported_psb_freq >> psb_freq) & 1 == 1
        }
    }
}
