kernel:
	cd kernel
	$(make) all

user:
	cd ipt-trace
	cargo build
