#include "ipt-processor.h"

#include <asm/processor.h>

int ipt_is_cpu_supported(void) {
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

  cpuid(0x14, &eax, &ebx, &ecx, &edx);
  cap->cr3_filter_support = ebx & 1;
  cap->psb_freq_support = (ebx >> 1) & 1;
  cap->ip_filter_support = (ebx >> 2) & 1;
  cap->mtc_support = (ebx >> 3) & 1;
  cap->ptwrite_support = (ebx >> 4) & 1;
  cap->power_event_trace_support = (ebx >> 5) & 1;
  cap->topa_output_support = ecx & 1;
  cap->topa_tables_allow_multiple_output_entries = (ecx >> 1) & 1;
  cap->single_range_output_support = (ecx >> 2) & 1;
  cap->trace_transport_system_support = (ecx >> 3) & 1;
  cap->ip_payloads_are_lip = (ecx >> 31) & 1;

  if (eax) {
    cpuid_count(0x14, 0x1, &eax, &ebx, &ecx, &edx);
    cap->extra_param_valid = 1;
    cap->num_address_ranges = eax & 0x3;
    cap->supported_mtc_period = eax >> 16;
    cap->supported_cycle_threshold = ebx & 0xffff;
    cap->supported_psb_freq = ebx >> 16;
  }
}
