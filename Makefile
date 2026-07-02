NASM64							:=						nasm -f win64

GCC64							:=						clang

LINKER							:=						lld-link

BUILD_DIR						:=						build
CORE_DIR						:=						core
CORE_BOOT_DIR					:=						$(CORE_DIR)/boot
CORE_BOOT_UEFI_DIR				:=						$(CORE_BOOT_DIR)/uefi
CORE_COMMON_DIR					:=						$(CORE_DIR)/common
CORE_COMMON_SRC_DIR				:=						$(CORE_COMMON_DIR)/src
CORE_COMMON_INC_DIR				:=						$(CORE_COMMON_DIR)/inc

BOOTX64_FILE					:=						$(BUILD_DIR)/BOOTX64.EFI
BOOT_IMG_NAME					:=						boot.img

LINKER_FLAGS					:=						/subsystem:efi_application /entry:efi_main /nodefaultlib
GCC_FLAGS						:=						-target x86_64-pc-windows-msvc -c -ffreestanding -I $(CORE_COMMON_INC_DIR)

COMMON_C_FILES					:=						$(shell find $(CORE_COMMON_SRC_DIR) -type f -name "*.c")
COMMON_O_FILES					:=						$(COMMON_C_FILES:$(CORE_COMMON_SRC_DIR)/%.c=$(BUILD_DIR)/$(CORE_COMMON_SRC_DIR)/%.o)

all: setup boot_img clean

$(BUILD_DIR)/$(CORE_COMMON_SRC_DIR)/%.o: $(CORE_COMMON_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(GCC64) $(GCC_FLAGS) -o $@ $<

boot_img: $(COMMON_O_FILES)
	@$(NASM64) $(CORE_BOOT_UEFI_DIR)/boot.asm -o $(BUILD_DIR)/boot.obj

	@$(LINKER) $(LINKER_FLAGS) /out:$(BOOTX64_FILE) \
		$(BUILD_DIR)/boot.obj \
		$(COMMON_O_FILES)

	@truncate -s 16M $(BOOT_IMG_NAME)

	@mkfs.fat -F16 $(BOOT_IMG_NAME)

	@mmd -i $(BOOT_IMG_NAME) ::/EFI
	@mmd -i $(BOOT_IMG_NAME) ::/EFI/BOOT
	@mcopy -i $(BOOT_IMG_NAME) $(BOOTX64_FILE) ::/EFI/BOOT/

setup:
	@clear
	@mkdir -p $(BUILD_DIR)
	@rm -rf $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)

run: all
	qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd $(BOOT_IMG_NAME)