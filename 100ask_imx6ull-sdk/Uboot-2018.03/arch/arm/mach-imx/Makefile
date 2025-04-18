#
# (C) Copyright 2000-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# (C) Copyright 2011 Freescale Semiconductor, Inc.
#
# SPDX-License-Identifier:	GPL-2.0+
#

ifeq ($(SOC),$(filter $(SOC),mx25 mx35 mx5 mx6 mx7 imx8m vf610))
obj-y	= iomux-v3.o
endif

ifeq ($(SOC),$(filter $(SOC),imx8m))
obj-$(CONFIG_IMX_BOOTAUX) += imx_bootaux.o
obj-y += mmc_env.o
obj-$(CONFIG_FEC_MXC) += mac.o
obj-$(CONFIG_SYS_I2C_MXC) += i2c-mxv7.o
obj-$(CONFIG_SECURE_BOOT) += hab.o
obj-$(CONFIG_IMX_VIDEO_SKIP) += video.o
obj-y += cpu.o
endif

ifeq ($(SOC),$(filter $(SOC),mx5 mx6))
obj-y	+= cpu.o speed.o
obj-$(CONFIG_GPT_TIMER) += timer.o
obj-$(CONFIG_SYS_I2C_MXC) += i2c-mxv7.o
endif
ifeq ($(SOC),$(filter $(SOC),mx7 mx6 mxs mx7ulp imx8m imx8))
obj-y	+= misc.o
obj-$(CONFIG_CMD_PRIBLOB) += priblob.o
obj-$(CONFIG_SPL_BUILD)	+= spl.o
endif
ifeq ($(SOC),$(filter $(SOC),mx7))
obj-y 	+= cpu.o
obj-$(CONFIG_SYS_I2C_MXC) += i2c-mxv7.o
obj-y += mmc_env.o
obj-$(CONFIG_FSL_MFGPROT) += cmd_mfgprot.o
endif
ifeq ($(SOC),$(filter $(SOC),mx6 mx7))
obj-y 	+= cache.o init.o
obj-$(CONFIG_FEC_MXC) += mac.o
obj-$(CONFIG_IMX_VIDEO_SKIP) += video.o
obj-$(CONFIG_IMX_RDC) += rdc-sema.o
ifneq ($(CONFIG_SPL_BUILD),y)
obj-$(CONFIG_IMX_BOOTAUX) += imx_bootaux.o
endif
obj-$(CONFIG_SATA) += sata.o
obj-$(CONFIG_SECURE_BOOT)    += hab.o
obj-$(CONFIG_SYSCOUNTER_TIMER) += syscounter.o
obj-$(CONFIG_IMX_TRUSTY_OS) += trusty.o
endif
ifeq ($(SOC),$(filter $(SOC),mx7ulp))
obj-y  += cache.o
obj-$(CONFIG_IMX_VIDEO_SKIP) += video.o
obj-$(CONFIG_SECURE_BOOT) += hab.o
endif
ifeq ($(SOC),$(filter $(SOC),vf610))
obj-y += ddrmc-vf610.o
endif
ifeq ($(SOC),$(filter $(SOC),imx8))
obj-$(CONFIG_HAVE_SC_FIRMWARE) += sci/
ifneq ($(CONFIG_SPL_BUILD),y)
obj-$(CONFIG_IMX_BOOTAUX) += imx_bootaux.o
endif
obj-$(CONFIG_IMX_VIDEO_SKIP) += video.o
obj-y  += misc.o
endif
ifneq ($(CONFIG_SPL_BUILD),y)
obj-$(CONFIG_CMD_BMODE) += cmd_bmode.o
obj-$(CONFIG_CMD_HDMIDETECT) += cmd_hdmidet.o
obj-$(CONFIG_CMD_DEKBLOB) += cmd_dek.o
obj-$(CONFIG_CMD_NANDBCD)  += cmd_nandbcb.o
obj-$(CONFIG_IMX_VSERVICE) += imx_vservice.o
endif

PLUGIN = board/$(BOARDDIR)/plugin

ifeq ($(CONFIG_USE_IMXIMG_PLUGIN),y)

$(PLUGIN).o: $(PLUGIN).S FORCE
	$(Q)mkdir -p $(dir $@)
	$(call if_changed_dep,as_o_S)

$(PLUGIN).bin: $(PLUGIN).o FORCE
	$(Q)mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --gap-fill 0xff $< $@
else

$(PLUGIN).bin:

endif

quiet_cmd_cpp_cfg = CFGS    $@
      cmd_cpp_cfg = $(CPP) $(cpp_flags) -x c -o $@ $<

IMX_CONFIG = $(CONFIG_IMX_CONFIG:"%"=%).cfgtmp

$(IMX_CONFIG): %.cfgtmp: % FORCE
	$(Q)mkdir -p $(dir $@)
	$(call if_changed_dep,cpp_cfg)

MKIMAGEFLAGS_u-boot.imx = -n $(filter-out %$(PLUGIN).bin $(QSPI_HEADER) $< $(PHONY),$^) -T imximage \
	-e $(CONFIG_SYS_TEXT_BASE)
u-boot.imx: MKIMAGEOUTPUT = u-boot.imx.log

QSPI_HEADER_SOURCE = board/freescale/common/qspi_header
QSPI_HEADER = qspi_header
QSPI_HEADER_OFF = 1
QSPI_UBOOT_OFF = 4
ifeq ($(SOC),$(filter $(SOC),mx7))
QSPI_HEADER_OFF = 0
QSPI_UBOOT_OFF = 1
endif

ifeq ($(CONFIG_QSPI_BOOT),y)
$(QSPI_HEADER): $(QSPI_HEADER_SOURCE) FORCE
	@cp $< $@

else
$(QSPI_HEADER):

endif

u-boot.imx: u-boot.bin $(IMX_CONFIG) $(PLUGIN).bin $(QSPI_HEADER) FORCE
	$(call if_changed,mkimage)
ifeq ($(CONFIG_QSPI_BOOT),y)
	@awk '{s="0000000"$$1;l=length(s);if(!((NR-1)%4))printf "%08x ",(NR-1)*4; \
		for(i=1;i<8;i+=2)printf " %s",substr(s,l-i,2);if(!(NR%4))printf "\n";}' \
		$(QSPI_HEADER) > qspi.tmp
	@xxd -r qspi.tmp qspi.bin
	@dd if=$@ of=u-boot.tmp bs=1k seek=$(QSPI_UBOOT_OFF)
	@dd if=qspi.bin of=u-boot.tmp bs=1k seek=$(QSPI_HEADER_OFF) conv=notrunc
	@mv u-boot.tmp $@
	@rm qspi.tmp qspi.bin
	@echo "Packed QSPI header with $@"
endif

ifeq ($(CONFIG_OF_SEPARATE),y)
MKIMAGEFLAGS_u-boot-dtb.imx = -n $(filter-out %$(PLUGIN).bin $(QSPI_HEADER) $< $(PHONY),$^) -T imximage \
	-e $(CONFIG_SYS_TEXT_BASE)
u-boot-dtb.imx: MKIMAGEOUTPUT = u-boot-dtb.imx.log

u-boot-dtb.imx: u-boot-dtb.bin $(IMX_CONFIG) $(PLUGIN).bin $(QSPI_HEADER) FORCE
	$(call if_changed,mkimage)
ifeq ($(CONFIG_QSPI_BOOT),y)
	@awk '{s="0000000"$$1;l=length(s);if(!((NR-1)%4))printf "%08x ",(NR-1)*4; \
		for(i=1;i<8;i+=2)printf " %s",substr(s,l-i,2);if(!(NR%4))printf "\n";}' \
		$(QSPI_HEADER) > qspi.tmp
	@xxd -r qspi.tmp qspi.bin
	@dd if=$@ of=u-boot.tmp bs=1k seek=$(QSPI_UBOOT_OFF)
	@dd if=qspi.bin of=u-boot.tmp bs=1k seek=$(QSPI_HEADER_OFF) conv=notrunc
	@mv u-boot.tmp $@
	@rm qspi.tmp qspi.bin
	@echo "Packed QSPI header with $@"
endif
endif

MKIMAGEFLAGS_SPL = -n $(filter-out $(PLUGIN).bin $< $(PHONY),$^) -T imximage \
	-e $(CONFIG_SPL_TEXT_BASE)

SPL: MKIMAGEOUTPUT = SPL.log

SPL: spl/u-boot-spl.bin $(IMX_CONFIG) $(PLUGIN).bin FORCE
	$(call if_changed,mkimage)

MKIMAGEFLAGS_u-boot.uim = -A arm -O U-Boot -a $(CONFIG_SYS_TEXT_BASE) \
		-e $(CONFIG_SYS_TEXT_BASE) -C none -T firmware

u-boot.uim: u-boot.bin FORCE
	$(call if_changed,mkimage)

OBJCOPYFLAGS += -I binary -O binary --pad-to=$(CONFIG_SPL_PAD_TO)
append = cat $(filter-out $< $(PHONY), $^) >> $@

quiet_cmd_pad_cat = CAT     $@
cmd_pad_cat = $(cmd_objcopy) && $(append) || rm -f $@

u-boot-with-spl.imx: SPL u-boot.uim FORCE
	$(call if_changed,pad_cat)

u-boot-with-nand-spl.imx: spl/u-boot-nand-spl.imx u-boot.uim FORCE
	$(call if_changed,pad_cat)

quiet_cmd_u-boot-nand-spl_imx = GEN     $@
cmd_u-boot-nand-spl_imx = (printf '\000\000\000\000\106\103\102\040\001' && \
	dd bs=1015 count=1 if=/dev/zero 2>/dev/null) | cat - $< > $@

spl/u-boot-nand-spl.imx: SPL FORCE
	$(call if_changed,u-boot-nand-spl_imx)

targets += $(addprefix ../../../,$(IMX_CONFIG) SPL u-boot.uim spl/u-boot-nand-spl.imx)

obj-$(CONFIG_ARM64) += sip.o

obj-$(CONFIG_MX5) += mx5/
obj-$(CONFIG_MX6) += mx6/
obj-$(CONFIG_MX7) += mx7/
obj-$(CONFIG_ARCH_MX7ULP) += mx7ulp/
obj-$(CONFIG_IMX8) += imx8/
obj-$(CONFIG_IMX8M) += imx8m/
