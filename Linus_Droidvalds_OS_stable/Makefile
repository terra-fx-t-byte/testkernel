x86_kernel_source := $(shell find src/implementation/kernel -name *.c)
x86_kernel_obj := $(patsubst src/implementation/kernel/%.c, build/kernel/%.o, $(x86_kernel_source))

x86_C_source := $(shell find src/implementation/x86_64 -name *.c)
x86_C_obj := $(patsubst src/implementation/x86_64/%.c, build/x86_64/%.o, $(x86_C_source))

x86_asm_source := $(shell find src/implementation/x86_64 -name *.asm)
x86_asm_obj := $(patsubst src/implementation/x86_64/%.asm, build/x86_64/%.o, $(x86_asm_source))

x86_ALL_obj := $(x86_C_obj) $(x86_asm_obj) 

$(x86_C_obj): build/x86_64/%.o : src/implementation/x86_64/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/intf -ffreestanding $(patsubst build/x86_64/%.o, src/implementation/x86_64/%.c, $@) -o $@ 

$(x86_kernel_obj): build/kernel/%.o : src/implementation/kernel/%.c
	mkdir -p $(dir $@) && \
	x86_64-elf-gcc -c -I src/intf -ffreestanding $(patsubst build/kernel/%.o, src/implementation/kernel/%.c, $@) -o $@ 

$(x86_asm_obj): build/x86_64/%.o : src/implementation/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, src/implementation/x86_64/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(x86_kernel_obj) $(x86_ALL_obj)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(x86_kernel_obj) $(x86_ALL_obj) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso