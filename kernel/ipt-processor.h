#ifndef IPT_PROCESSOR_H
#define IPT_PROCESSOR_H

struct ipt_cpu_cap {
  unsigned int cr3_filter_support: 1;
  unsigned int psb_freq_support: 1;
  unsigned int ip_filter_support: 1;
  unsigned int mtc_support: 1;
  unsigned int ptwrite_support: 1;
  unsigned int power_event_trace_support: 1;
  unsigned int topa_output_support: 1;
  unsigned int topa_tables_allow_multiple_output_entries: 1;
  unsigned int single_range_output_support: 1;
  unsigned int trace_transport_system_support: 1;
  unsigned int ip_payloads_are_lip: 1;

  unsigned int extra_param_valid: 1;
  unsigned short num_address_ranges;
  unsigned short supported_mtc_period;
  unsigned short supported_cycle_threshold;
  unsigned short supported_psb_freq;
};

/// Test whether the CPU supports Intel PT
int ipt_is_cpu_supported(void);

/// Query the supported Intel PT functionality supported by the CPU
void ipt_query_cpu_cap(struct ipt_cpu_cap *cap);

#endif // IPT_PROCESSOR_H
