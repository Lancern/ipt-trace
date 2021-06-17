#include "ipt-processor.h"

#include <asm/processor.h>

static int ipt_is_cpu_supported(void) {
  unsigned int eax;
  unsigned int ebx;
  unsigned int ecx;
  unsigned int edx;

  cpuid(0x07, &eax, &ebx, &ecx, &edx);
  return (ebx >> 25) & 1;
}

void ipt_query_cpu_cap(struct ipt_cpu_cap *cap) {
  unsigned int eax;
  unsigned int ebx;
  unsigned int ecx;
  unsigned int edx;

  if (!cap) {
    return;
  }

  memset(cap, 0, sizeof(struct ipt_cpu_cap));

  if (!ipt_is_cpu_supported()) {
    return;
  }

  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_PT_SUPPORT, 1);

  cpuid(0x14, &eax, &ebx, &ecx, &edx);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_CR3_FILTER_SUPPORT, ebx & 1);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_PSB_FREQ_SUPPORT, (ebx >> 1) & 1);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_IP_FILTER_SUPPORT, (ebx >> 2) & 1);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_MTC_SUPPORT, (ebx >> 3) & 1);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_PTWRITE_SUPPORT, (ebx >> 4) & 1);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_POWER_EVENT_TRACE_SUPPORT, (ebx >> 5) & 1);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_TOPA_OUTPUT_SUPPORT, ecx & 1);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_TOPA_TABLES_ALLOW_MULTIPLE_OUTPUT_ENTRIES, (ecx >> 1) & 1);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_SINGLE_RANGE_OUTPUT_SUPPORT, (ecx >> 2) & 1);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_TRACE_TRANSPORT_SYSTEM_SUPPORT, (ecx >> 3) & 1);
  IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_IP_PAYLOADS_ARE_LIP, (ecx >> 31) & 1);

  if (eax) {
    cpuid_count(0x14, 0x1, &eax, &ebx, &ecx, &edx);
    IPT_CPU_CAP_FLAG_SET(cap, IPT_CPU_CAP_FLAG_OFFSET_HAS_EXTRA_PARAM, 1);
    cap->num_address_ranges = eax & 0x3;
    cap->supported_mtc_period = eax >> 16;
    cap->supported_cycle_threshold = ebx & 0xffff;
    cap->supported_psb_freq = ebx >> 16;
  }
}
