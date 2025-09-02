//twi0_bare.c
#include "twi0_bare.h"

// Tiny, crude timeout to avoid hanging forever on bus errors
static inline bool _wait_wif(void) {
    uint32_t guard = 100000UL; // ~a few ms worst-case; adjust if needed
    while (!(TWI0.MSTATUS & TWI_WIF_bm)) {
        if (--guard == 0) return false;
    }
    return true;
}

void TWI0_bare_init_100k(void)
{
    // PA2 = SDA, PA3 = SCL (external 4.7k pull-ups required)
    // Pins can stay as inputs; TWI controls the drivers.

    // BAUD formula (approx): BAUD = F_CPU/(2*Fscl) - 5  (ignore Trise)
    // For 100 kHz @ 3.333 MHz: BAUD ? 3333333/(2*100000)-5 ? 11
    TWI0.MBAUD = 11;

    // Master Control A:
    //  - SMEN: Smart mode (auto-ACK handling)
    //  - ENABLE: enable master
    TWI0.MCTRLA = TWI_ENABLE_bm | TWI_SMEN_bm; // WIEN/QCEN/FMPEN left 0

    // Force bus state to IDLE (required on tiny/mega 0/1 to start clean)
    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
}

bool TWI0_bare_start_write(uint8_t addr7)
{
    // Write address (R/W = 0)
    TWI0.MADDR = (addr7 << 1) | 0;
    if (!_wait_wif()) return false;

    // Check ACK from slave
    if (TWI0.MSTATUS & TWI_RXACK_bm) {
        // NACK: send STOP
        TWI0.MCTRLB = TWI_MCMD_STOP_gc;
        return false;
    }
    return true;
}

bool TWI0_bare_write(uint8_t byte)
{
    TWI0.MDATA = byte;
    if (!_wait_wif()) return false;

    if (TWI0.MSTATUS & (TWI_BUSERR_bm | TWI_ARBLOST_bm)) {
        TWI0.MCTRLB = TWI_MCMD_STOP_gc;
        return false;
    }
    if (TWI0.MSTATUS & TWI_RXACK_bm) {
        // Slave NACKed this byte
        TWI0.MCTRLB = TWI_MCMD_STOP_gc;
        return false;
    }
    return true;
}

void TWI0_bare_stop(void)
{
    TWI0.MCTRLB = TWI_MCMD_STOP_gc;
}
