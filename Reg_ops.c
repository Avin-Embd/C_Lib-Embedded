/**
 * @file reg_ops.c
 * @brief Implementation of utility functions for register operations
 */

#include "reg_ops.h"

/**
 * @brief Print register value in detailed format
 * @param value Register value to display
 * @param label Description label
 */
void print_register_data_bin(uint32_t value, const char* label) 
{
    printf("%s: 0x%08X\n", label, value);
    printf("Binary: ");
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
    printf("\n");
}


int main()
{
    uint32_t simulated_register = 0x12345678;
    uint32_t *reg_address = &simulated_register;
    
    printf("=== REGISTER READ/WRITE DEMONSTRATION ===\n\n");
    
    // Initial state
    print_register_data_bin(*reg_address, "Initial Register");
    
    // WRITE OPERATION: Write 8 bits (0xCD from 0xABCD) starting from bit 10
    uint32_t write_data = 0xABCD;
    printf("WRITE: Writing 8 bits (0xCD from 0x%04X) to bits 10-17\n", write_data);
    REG_WRITE_BITS(reg_address, 10, 8, write_data);
    print_register_data_bin(*reg_address, "After Write");
    
    // READ OPERATION: Read the same 8 bits back
    printf("READ: Reading 8 bits from bits 10-17\n");
    uint32_t read_value = REG_READ_BITS(reg_address, 10, 8);
    printf("Read value: 0x%02X\n", read_value);
    printf("Expected:   0xCD\n\n");
    
    // Another WRITE: Write 4 bits to a different location
    printf("WRITE: Writing 4 bits (0xF) to bits 24-27\n");
    REG_WRITE_BITS(reg_address, 24, 4, 0xF);
    print_register_data_bin(*reg_address, "After Second Write");
    
    // READ: Read those 4 bits
    printf("READ: Reading 4 bits from bits 24-27\n");
    read_value = REG_READ_BITS(reg_address, 24, 4);
    printf("Read value: 0x%X\n", read_value);
    printf("Expected:   0xF\n\n");
    
    // READ: Read a larger range spanning both writes
    printf("READ: Reading 12 bits from bits 14-25 (spans both writes)\n");
    read_value = REG_READ_BITS(reg_address, 14, 12);
    printf("Read value: 0x%03X\n", read_value);
    print_register_data_bin(*reg_address, "Final Register State");


    uint32_t test_reg = 0x12345678;
    
    printf("=== BIT MANIPULATION TEST ===\n");
    print_register_data_bin(test_reg, "Initial");
    
    // Set bit 0
    REG_SET_BIT(&test_reg, 0);
    print_register_data_bin(test_reg, "After SET bit 0");
    
    // Clear bit 4  
    REG_CLEAR_BIT(&test_reg, 4);
    print_register_data_bin(test_reg, "After CLEAR bit 4");
    
    // Toggle bit 31
    REG_TOGGLE_BIT(&test_reg, 31);
    print_register_data_bin(test_reg, "After TOGGLE bit 31");


        // Clear all bits
    REG_CLEAR_ALL(&test_reg);
    print_register_data_bin(test_reg, "After CLEAR ALL bits");
    
    // Test toggle all on a pattern
    test_reg = 0xAAAAAAAA;  // Alternating pattern
    print_register_data_bin(test_reg, "Pattern 0xAAAAAAAA");
    
    REG_TOGGLE_ALL(&test_reg);
    print_register_data_bin(test_reg, "After TOGGLE ALL bits");
    
    REG_TOGGLE_ALL(&test_reg);
    print_register_data_bin(test_reg, "After TOGGLE ALL again");
    
    return 0;
}