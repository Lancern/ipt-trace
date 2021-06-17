extern crate clap;
extern crate colored;
extern crate libipttrace;

use std::error::Error;

use clap::{App, ArgMatches, SubCommand};
use colored::*;

use libipttrace::IptCpuCap;

fn main() {
    let matches = App::new("ipttrace")
        .version("0.1.0")
        .author("Sirui Mu <msrlancern@126.com>")
        .about("Program tracing with Intel Processor Trace")
        .subcommand(SubCommand::with_name("cap")
            .about("Query Intel PT capabilities supported by the CPU")
            .version("0.1.0")
            .author("Sirui Mu <msrlancern@126.com>"))
        .get_matches();

    let command_result = if let Some(matches) = matches.subcommand_matches("cap") {
        cap(matches)
    } else {
        eprintln!("No valid subcommands specified.");
        eprintln!("Please specify -h or --help for help.");
        std::process::exit(1);
    };

    if let Err(e) = command_result {
        eprintln!("{}", e);
        std::process::exit(1);
    }
}

fn cap(_matches: &ArgMatches) -> Result<(), Box<dyn Error>> {
    let cap = IptCpuCap::query()?;
    dump_cpu_cap(&cap);

    Ok(())
}

fn dump_cpu_cap(cap: &IptCpuCap) {
    println!("Intel PT Support Measurements");
    println!("=============================");

    let support_msg = |supported: bool| {
        if supported {
            "Supported".green()
        } else {
            "Not Supported".red()
        }
    };

    println!("Intel PT: {}", support_msg(cap.is_pt_supported()));
    if !cap.is_pt_supported() {
        return;
    }

    println!("CR3 Filtering: {}", support_msg(cap.is_cr3_filter_supported()));
    println!("Configurable PSB and Cycle-Accurate Mode: {}", support_msg(cap.is_psb_freq_supported()));
    println!("IP Filtering and TraceStop: {}", support_msg(cap.is_ip_filter_supported()));
    println!("MTC: {}", support_msg(cap.is_mtc_supported()));
    println!("PTWRITE: {}", support_msg(cap.is_ptwrite_supported()));
    println!("Power Event Trace: {}", support_msg(cap.is_power_event_trace_supported()));
    println!("ToPA Output: {}", support_msg(cap.is_topa_output_supported()));
    println!("ToPA Tables Allow Multiple Output Entries: {}",
        support_msg(cap.topa_tables_allow_multiple_output_entries()));
    println!("Single-Range Output: {}", support_msg(cap.is_single_range_output_supported()));
    println!("Output to Trace Transport Subsystem: {}",
        support_msg(cap.is_trace_transport_system_supported()));
    println!("IP Payloads are LIP: {}", support_msg(cap.is_ip_payloads_lip()));

    println!("Number of Address Ranges: {}", cap.num_address_ranges());
    println!("Supported MTC Period Encodings: {:?}", cap.supported_mtc_periods());
    println!("Supported Cycle Threshold Values: {:?}", cap.supported_cycle_thresholds());
    println!("Supported Configurable PSB Frequencies: {:?}", cap.supported_psb_freq());
}
