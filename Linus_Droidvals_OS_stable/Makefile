x86_kernel_source := $(shell find src/implementation/kernel -name *.cpp)
x86_kernel_obj := $(patsubst src/implementation/kernel/%.cpp, build/kernel/%.o, $(x86_kernel_source))

x86_CPP_source := $(shell find src/implementation/x86_64 -name *.cpp)
x86_CPP_obj := $(patsubst src/implementation/x86_64/%.cpp, build/x86_64/%.o, $(x86_CPP_source))

x86_asm_source := $(shell find src/implementation/x86_64 -name *.asm)
x86_asm_obj := $(patsubst src/implementation/x86_64/%.asm, build/x86_64/%.o, $(x86_asm_source))

x86_ALL_obj := $(x86_CPP_obj) $(x86_asm_obj) 

$(x86_CPP_obj): build/x86_64/%.o : src/implementation/x86_64/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -c -I src/intf -ffreestanding -nostdlib -fno-exceptions -fno-rtti $(patsubst build/x86_64/%.o, src/implementation/x86_64/%.cpp, $@) -o $@ 

$(x86_kernel_obj): build/kernel/%.o : src/implementation/kernel/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -c -I src/intf -ffreestanding -nostdlib -fno-exceptions -fno-rtti $(patsubst build/kernel/%.o, src/implementation/kernel/%.cpp, $@) -o $@ 

$(x86_asm_obj): build/x86_64/%.o : src/implementation/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, src/implementation/x86_64/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(x86_kernel_obj) $(x86_ALL_obj)
	mkdir -p dist/x86_64 && \
	x86_64-elf-ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(x86_kernel_obj) $(x86_ALL_obj) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso