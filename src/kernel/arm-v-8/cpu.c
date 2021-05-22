#include "cpu.h"
#include "../../lib/debug/debug.h"

#define EXPECTED_IMPLEMENTER "Arm Limited"

void cpu_info()
{
    debug(DBG_BOTH, "=== CPU INFO ===\n");

    long midr;
    asm volatile(
        //Read Main ID Register
        "mrs %0, midr_el1\n"
        : "=g"(midr)
    );

    //Bits 'x' through 'y' (x:y)
    //31:24
    int implementer = (midr >> 24) & 0x00ffffff;
    //23:20
    int variant = (midr >> 20) & 0x00f;
    //19:16
    int architecture = (midr >> 16) & 0xf;
    //15:4
    int part_num = ((midr >> 4) & 0xff00) >> 8; //((midr >> 4) & 0xff00) = 0xfd00 (this holds true for qemu's raspi3 emulator, V. 4.2.1), then we perform a right shift to discard of the lower bits (00)
    //3:0
    int revision = (midr) & 0x000000ff;

    //Log the information and perform some sanity checks
    debug(DBG_BOTH, "Contents of the midr register: 0x%x\n", midr);
    (implementer == 0x41) ? debug(DBG_BOTH, "Implementer: %s\n", EXPECTED_IMPLEMENTER) : debug(DBG_BOTH, "Unknown implementer: %x (Expected %s)\n", implementer, EXPECTED_IMPLEMENTER);
    (architecture == 0xf) ? debug(DBG_BOTH, "Architecture: 0x%x\n", architecture) : debug(DBG_BOTH, "Incorrect architecture version 0x%x (Expected 0xf)\n", architecture); //0xf = Architectural features are individually identified in the ID_* registers, see 'ID registers'. (To be added in V01D's next commit)
    debug(DBG_BOTH, "Variant: 0x%x\n", variant);
    debug(DBG_BOTH, "PartNum: 0x%x\n", part_num);
    debug(DBG_BOTH, "Revision: 0x%x\n", revision);
}