#ifndef IPT_PROCESSOR_H
#define IPT_PROCESSOR_H

struct ipt_cpu_cap {
  unsigned short flags;

  unsigned short num_address_ranges;
  unsigned short supported_mtc_period;
  unsigned short supported_cycle_threshold;
  unsigned short supported_psb_freq;
};

#define IPT_CPU_CAP_FLAG_OFFSET_PT_SUPPORT                                0
#define IPT_CPU_CAP_FLAG_OFFSET_CR3_FILTER_SUPPORT                        1
#define IPT_CPU_CAP_FLAG_OFFSET_PSB_FREQ_SUPPORT                          2
#define IPT_CPU_CAP_FLAG_OFFSET_IP_FILTER_SUPPORT                         3
#define IPT_CPU_CAP_FLAG_OFFSET_MTC_SUPPORT                               4
#define IPT_CPU_CAP_FLAG_OFFSET_PTWRITE_SUPPORT                           5
#define IPT_CPU_CAP_FLAG_OFFSET_POWER_EVENT_TRACE_SUPPORT                 6
#define IPT_CPU_CAP_FLAG_OFFSET_TOPA_OUTPUT_SUPPORT                       7
#define IPT_CPU_CAP_FLAG_OFFSET_TOPA_TABLES_ALLOW_MULTIPLE_OUTPUT_ENTRIES 8
#define IPT_CPU_CAP_FLAG_OFFSET_SINGLE_RANGE_OUTPUT_SUPPORT               9
#define IPT_CPU_CAP_FLAG_OFFSET_TRACE_TRANSPORT_SYSTEM_SUPPORT            10
#define IPT_CPU_CAP_FLAG_OFFSET_IP_PAYLOADS_ARE_LIP                       11
#define IPT_CPU_CAP_FLAG_OFFSET_HAS_EXTRA_PARAM                           12

#define IPT_CPU_CAP_FLAG_SET(cap, offset, value) \
  (cap)->flags |= (((value) & 1) << (offset))

/// Query the supported Intel PT functionality supported by the CPU
void ipt_query_cpu_cap(struct ipt_cpu_cap *cap);

#endif // IPT_PROCESSOR_H
