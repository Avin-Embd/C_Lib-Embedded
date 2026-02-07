/**
 * @file reg_ops.h
 * @brief Simple register bit manipulation macros - READ and WRITE only
 */

#ifndef REG_OPS_H
#define REG_OPS_H

#include <stdint.h>
#include <stdio.h>

// Constants
#define MAX_BITS 32
#define MIN_BITS 1

// Parameter validation
#define BIT_CHECK(bit) ((bit) < MAX_BITS)

// Bit Parameter validation macro
#define BIT_ERROR(bit) (printf("Bit Error: bit=%d (must be 0-31)\n", (int)(bit)), 0)

// SET BIT MACRO - Set specific bit to 1
#define REG_SET_BIT(address, bit) \
    (BIT_CHECK(bit) ? \
     (*(volatile uint32_t*)(uintptr_t)(address) |= (1U << (bit)), 1) : \
     BIT_ERROR(bit))

// CLEAR BIT MACRO - Clear specific bit to 0
#define REG_CLEAR_BIT(address, bit) \
    (BIT_CHECK(bit) ? \
     (*(volatile uint32_t*)(uintptr_t)(address) &= ~(1U << (bit)), 1) : \
     BIT_ERROR(bit))

// TOGGLE BIT MACRO - Toggle bit (0->1, 1->0)
#define REG_TOGGLE_BIT(address, bit) \
    (BIT_CHECK(bit) ? \
     (*(volatile uint32_t*)(uintptr_t)(address) ^= (1U << (bit)), 1) : \
     BIT_ERROR(bit))
    

// ALL BITS OPERATIONS (32-BIT REGISTER)
#define REG_SET_ALL(address) \
    (*(volatile uint32_t*)(uintptr_t)(address) = 0xFFFFFFFFU)

#define REG_CLEAR_ALL(address) \
    (*(volatile uint32_t*)(uintptr_t)(address) = 0x00000000U)

#define REG_TOGGLE_ALL(address) \
    (*(volatile uint32_t*)(uintptr_t)(address) ^= 0xFFFFFFFFU)


// Parameter validation macro
#define PARAM_CHECK(sb, nb) ((((sb) + (nb)) <= (MAX_BITS) && (nb > 0)))

// Safe bit mask creation (handles 32-bit overflow)
#define CREATE_BIT_MASK(nb) ((nb) == 32 ? 0xFFFFFFFFU : ((1U << (nb)) - 1))

// Error reporting macros
#define READ_ERROR(sb, nb) \
    (printf("Read Error: start_bit=%d, num_bits=%d\n", (int)(sb), (int)(nb)), 0)

#define WRITE_ERROR(sb, nb, data) \
    (printf("Write Error: start_bit=%d, num_bits=%d, data=0x%X\n", \
            (int)(sb), (int)(nb), (uint32_t)(data)), 0)

// Core bit extraction macro
#define BIT_EXTRACT(addr, sb, nb) \
    ((*(volatile uint32_t*)(uintptr_t)(addr) >> (sb)) & CREATE_BIT_MASK(nb))

// Core bit write expression macro
#define BIT_WRITE_EXPR(addr, sb, nb, data) \
    ({ \
        volatile uint32_t* reg_ptr = (volatile uint32_t*)(uintptr_t)(addr); \
        uint32_t bit_mask = CREATE_BIT_MASK(nb); \
        uint32_t position_mask = bit_mask << (sb); \
        uint32_t shifted_data = ((data) & bit_mask) << (sb); \
        *reg_ptr = (*reg_ptr & ~position_mask) | shifted_data; \
        1; \
    })

// ========================================
// MAIN MACROS - ONLY TWO YOU NEED
// ========================================

/**
 * @brief Read specified bits from a register
 * @param address Pointer to the register
 * @param start_bit Starting bit position (0-31)  
 * @param num_bits Number of bits to read (1-32)
 * @return Value of the specified bits (right-aligned)
 */
#define REG_READ_BITS(address, start_bit, num_bits) \
    (PARAM_CHECK(start_bit, num_bits) ? \
     BIT_EXTRACT(address, start_bit, num_bits) : \
     READ_ERROR(start_bit, num_bits))

/**
 * @brief Write data to specified bits in a register
 * @param address Pointer to the register
 * @param start_bit Starting bit position (0-31)
 * @param num_bits Number of bits to write (1-32) 
 * @param data Data to write (only lower num_bits will be used)
 * @return 1 on success, 0 on error
 */
#define REG_WRITE_BITS(address, start_bit, num_bits, data) \
    (PARAM_CHECK(start_bit, num_bits) ? \
     BIT_WRITE_EXPR(address, start_bit, num_bits, data) : \
     WRITE_ERROR(start_bit, num_bits, data))

// Function prototypes (implemented in .c file)
void print_register_detailed(uint32_t value, const char* label);

#endif // REG_OPS_H
