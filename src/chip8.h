#pragma once

typedef struct Chip8 {
	uint16_t opcode;				// Current opcode
	uint8_t memory[4096];		// CHIP-8 main memory

	uint8_t V[16];					// 16 general purpose 8-bit registers

	uint16_t I;							// Index register
	uint16_t pc;						// Program counter register

	uint8_t gfx[64][32];		// Graphics buffer

	uint8_t delay_timer;		// Delay timer
	uint8_t sound_timer;		// Sound timer

	uint16_t stack[16];			// Stack
	uint16_t sp;						// Stack pointer

	uint8_t key[16];				// Key mapping
} Chip8;

// Initialize the emulator
void chip8_init(Chip8 *chip8);

// Load a ROM into emulator memory
void chip8_load();

// Run a single CPU cycle
void chip8_run_cycle();
