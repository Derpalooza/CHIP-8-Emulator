#include <time.h>

#include "chip8.h"
#include "opcode.h"

static const uint8_t s_fontset[] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0,		// 0
	0x20, 0x60, 0x20, 0x20, 0x70,		// 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0,		// 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0,		// 3
  0x90, 0x90, 0xF0, 0x10, 0x10,		// 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0,		// 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0,		// 6
  0xF0, 0x10, 0x20, 0x40, 0x40,		// 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0,		// 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0,		// 9
  0xF0, 0x90, 0xF0, 0x90, 0x90,		// A
  0xE0, 0x90, 0xE0, 0x90, 0xE0,		// B
  0xF0, 0x80, 0x80, 0x80, 0xF0,		// C
  0xE0, 0x90, 0x90, 0x90, 0xE0,		// D
  0xF0, 0x80, 0xF0, 0x80, 0xF0,		// E
  0xF0, 0x80, 0xF0, 0x80, 0x80,		// F
};

static uint8_t draw_flag;

void chip8_init(Chip8 *chip8) {
	// Reset main registers
	chip8->pc = 0x200;
	chip8->opcode = 0;
	chip8->I = 0;
	chip8->sp = 0;
	chip8->draw_flag = 0;

	// Reset timers
	chip8->delay_timer = 0;
	chip8->sound_timer = 0;

	// Clear graphics buffer
	for (uint8_t i = 0; i < 64; i++) {
		for (uint8_t j = 0; j < 32; j++) {
			chip8->gfx[i][j] = 0;
		}
	}

	// Clear stack and general purpose registers
	for (uint8_t i = 0; i < 16; i++) {
		chip8->V[i] = 0;
		chip8->stack[i] = 0;
	}

	// Clear memory
	for (uint8_t i = 0; i < 4096; i++) {
		chip8->memory[i] = 0;
	}
	
	for (uint8_t i = 0; i < 80; i++) {
		chip8->memory[i] = s_fontset[i];
	}	

	// Seed the random number generator
	srand(time(NULL));
}

void chip8_load() {}

void chip8_run_cycle() {}