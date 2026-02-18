#include <stdio.h>
#include <stdint.h>
 
/* -------------------------------------------------
* Simulated 8-bit register
* ------------------------------------------------- */
volatile uint8_t REG8 = 0b01110110;   /* initial value */
 
/* -------------------------------------------------
* Masks
* ------------------------------------------------- */
/* RO bits: bit1 and bit2 */
#define RO_MASK  ((1U << 1) | (1U << 2))
 
/* WO bits: bit5 and bit7 */
#define WO_MASK  ((1U << 5) | (1U << 7))
 
 
/* -------------------------------------------------
* Read RO bits only
* ------------------------------------------------- */
uint8_t reg_read_ro(uint8_t ro_mask)
{
    return REG8 & ro_mask;
}
 
/* -------------------------------------------------
* Write WO bits only (preserve others)
* ------------------------------------------------- */
void reg_write_wo(uint8_t wo_mask, uint8_t value)
{
    uint8_t reg = REG8;
    reg &= (uint8_t)(~wo_mask);
    reg |= (value & wo_mask);
    REG8 = reg;
}
 
/* -------------------------------------------------
* Print 8-bit binary
* ------------------------------------------------- */
void print_bin8(uint8_t val)
{
    for (int i = 7; i >= 0; i--)
        printf("%u", (val >> i) & 1U);
}
 
/* -------------------------------------------------
* Main test
* ------------------------------------------------- */
int main(void)
{
    printf("REGISTER INITIAL VALUE : ");
    print_bin8(REG8);
    printf("\n");
 
    /* Read RO bits */
    printf("READ RO BITS           : ");
    print_bin8(reg_read_ro(RO_MASK));
    printf("\n");
 
    /* Write WO bits: set bit7, clear bit5 */
    reg_write_wo(WO_MASK, ((0U << 5)|(1U << 7)));
 
    printf("REGISTER AFTER WRITE   : ");
    print_bin8(REG8);
    printf("\n");
 
    /* Read RO bits again (unchanged) */
    printf("READ RO BITS AGAIN     : ");
    print_bin8(reg_read_ro(RO_MASK));
    printf("\n");
 
    return 0;
}