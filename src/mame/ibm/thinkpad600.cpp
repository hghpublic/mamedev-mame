// license:BSD-3-Clause
// copyright-holders:
/*************************************************************************************************************
Skeleton driver for IBM ThinkPad 600 series.
The IBM ThinkPad 600 series was a series of notebook computers introduced in 1998 by IBM as an lighter and 
slimmer alternative to the 770 series. Three models were produced, the 600, 600E, and 600X.

Hardware for the 600E model.
  Main PCB:
    -Intel Pentium II 366 Mobile MMC-2 (PMG36602002AA).
       There were options for Pentium II at either 300 MHz, 366 MHz, or 400 MHz
    -Texas Instruments PCIbus SN104698GFN.
    -Intel PCIset FW82371EB (PCI-TO-ISA / IDE XCELERATOR PIIX4)
    -NeoMagic MagicMedia 256AV NM2200C-A.
    -Crystal CS4610C-CQ (CrystalClear SoundFusion PCI Audio Accelerator).
    -Crystal CS4239-KQ (CrystalClear Portable ISA Audio System).
    -National Semiconductor PC97338VJG (ACPI 1.0 and PC98/99 Compliant SuperI/O).
    -Hitachi HD64F3437TF.
    -Atmel 24C01A (SEEPROM).
    -Other chips: IMI-SG577DYB, TI SN75LVDS84, 4 x IBM 0364164PT3B (64 MB of RAM on the motherboard),
                  IBM 20H2987, IBM 10L3953, Motorola MC145583V, Maxim MAX1632EAI, etc.
   Modem PCB:
    -Epson 11J9289.
    -Five IS62LV256L-15T (isn't it too much RAM for a modem?).
    -Atmel ATF1500AL.
    -TI TCM320AC36C (Voice-Band Audio Processor [VBAPE]).
    -Large BGA chip silkscreened "IPI I8L7360 F27904A".

Hardware for the 600 model.
  Main PCB:
    -Intel Pentium II 300 Mobile MMC-1 (PMD30005002AA).
       There were options for Pentium MMX at 233 MHz and Pentium II at 233, 266 or 300 MHz.
    -Texas Instruments PCIbus PCI1250AGFN.
    -Intel PCIset FW82371AB.
    -NeoMagic MagicMedia 128XD NM2160B.
    -Crystal CS4237-KQ (CrystalClear Advanced Audio System with 3D Sound).
    -National Semiconductor PC97338VJG (ACPI 1.0 and PC98/99 Compliant SuperI/O).
    -Hitachi HD64F3437TF.
    -Atmel 24C01A (SEEPROM).
    -Other chips: IMI-SG571BYB, TI SN75LVDS84, 4 x Mitsubishi M5M4V64S40ATP (64 MB of RAM on the motherboard),
                  IBM 20H2987, IBM 10L3932, Maxim MAX1631EAI, etc.
   Modem PCB (same as 600E model):
    -Epson 11J9289.
    -Five IS62LV256L-15T (isn't it too much RAM for a modem?).
    -Atmel ATF1500AL.
    -TI TCM320AC36C (Voice-Band Audio Processor [VBAPE]).
    -Large BGA chip silkscreened "IPI I8L7360 F27904A".

*************************************************************************************************************/

#include "emu.h"
#include "cpu/h8/h8325.h"
#include "cpu/i386/i386.h"
#include "machine/pci.h"
#include "speaker.h"


namespace {

class thinkpad600_state : public driver_device
{
public:
	thinkpad600_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
	{ }

	void thinkpad600e(machine_config &config);
	void thinkpad600(machine_config &config);

private:
	required_device<cpu_device> m_maincpu;
	void thinkpad600_base(machine_config &config);
};


static INPUT_PORTS_START(thinkpad600)
INPUT_PORTS_END

void thinkpad600_state::thinkpad600_base(machine_config &config)
{
	PCI_ROOT(config, "pci", 0);
	// ...

	H8325(config, "mcu", XTAL(16'000'000)); // Actually an Hitachi HD64F3437TF, unknown clock

	SPEAKER(config, "lspeaker").front_left();
	SPEAKER(config, "rspeaker").front_right();
}

void thinkpad600_state::thinkpad600e(machine_config &config)
{
	PENTIUM2(config, m_maincpu, 366'000'000); // Intel Pentium II 366 Mobile MMC-2 (PMG36602002AA)

	thinkpad600_base(config);
}

void thinkpad600_state::thinkpad600(machine_config &config)
{
	PENTIUM2(config, m_maincpu, 300'000'000); // Intel Pentium II 300 Mobile MMC-1 (PMD30005002AA)

	thinkpad600_base(config);
}


ROM_START(thinkpad600e)
	ROM_REGION( 0x80000, "maincpu", 0 )
	ROM_LOAD( "e28f004b5t80-10l1056_rev15_h0399m.u60", 0x00000, 0x80000, CRC(fba7567b) SHA1(a84e7d4e5740150e78e5002714c9125705f3356a) ) // BIOS

	ROM_REGION(0x0f780, "mcu", 0)
	ROM_LOAD( "hd64f3437tf-10l1057_rev04_h0499m.u39",  0x00000, 0x0f780, CRC(c21c928b) SHA1(33e3e6966f003655ffc2f3ac07772d2d3245740d) )

	ROM_REGION(0x00080, "seeprom", 0)
	ROM_LOAD( "atmel_24c01a.u98",                      0x00000, 0x00080, CRC(7ce51001) SHA1(6f25666373a6373ce0014c04df73a066f4da938b) )

	ROM_REGION(0x00c39, "plds", 0)
	ROM_LOAD( "atf1500al-modemboard.u12",              0x00000, 0x00c39, CRC(7ecd4b79) SHA1(b69ef5fe227b466f331f863ba20efd7e23056809) ) // On modem PCB
ROM_END

ROM_START(thinkpad600)
	ROM_REGION( 0x80000, "maincpu", 0 )
	ROM_LOAD( "tms28f004b_18l9949_rev16-i2298m.u76",   0x00000, 0x80000, CRC(00a52b32) SHA1(08db425b8edb3a036f22beb588caa6f050fc8eb2) ) // BIOS

	ROM_REGION(0x0f780, "mcu", 0)
	ROM_LOAD( "hd64f3437tf_10l9950_rev08_i2798m.u32",  0x00000, 0x0f780, CRC(546ec51c) SHA1(5d9b4be590307c4059ff11c434d0901819427649) )

	ROM_REGION(0x00080, "seeprom", 0)
	ROM_LOAD( "atmel_24c01a.u49",                      0x00000, 0x00080, CRC(9a2e2a18) SHA1(29e2832c97bc93debb4fb09fcbed582335b57efe) )

	ROM_REGION(0x00c39, "plds", 0)
	ROM_LOAD( "atf1500al-modemboard.u12",              0x00000, 0x00c39, CRC(7ecd4b79) SHA1(b69ef5fe227b466f331f863ba20efd7e23056809) ) // On modem PCB
ROM_END

} // anonymous namespace

//    YEAR, NAME,         PARENT, COMPAT, MACHINE,      INPUT,       CLASS,             INIT,       COMPANY, FULLNAME,        FLAGS
COMP( 1999, thinkpad600e, 0,      0,      thinkpad600e, thinkpad600, thinkpad600_state, empty_init, "IBM",   "ThinkPad 600E", MACHINE_IS_SKELETON )
COMP( 1998, thinkpad600,  0,      0,      thinkpad600,  thinkpad600, thinkpad600_state, empty_init, "IBM",   "ThinkPad 600",  MACHINE_IS_SKELETON )
