objcopy -I binary -O elf64-x86-64 kernel/Omega/zap-light16.psf kernel/font.o
nm kernel/font.o
rm $(find ./ -type f -name "*.o")
