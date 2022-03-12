all:
	cd kernel/; rm -rf limine 2> /dev/null; make clean; bash buildall.sh
	cd kernel/; bash build.sh; mv Omega.iso ../
	git clone https://github.com/limine-bootloader/limine.git --branch=v2.0-branch-binary --depth=1 kernel/limine
	@ rm $$(find ./ -type f -name "*.d")
	@ rm $$(find ./ -type f -name "*.o")

reset:
	cd kernel/; make clean; rm -rf limine
	@ rm $$(find ./ -type f -name "*.d")
	@ rm $$(find ./ -type f -name "*.o")



run:
	qemu-system-x86_64 -cdrom Omega.iso -monitor stdio -d int -no-reboot -D logfile.txt -M smm=off

# DO NOT USE THIS WITHOUT KNOWING WHAT YOU ARE DOING!
burn_danger:
	dd if=Omega.iso of=/dev/sdb status=progress
