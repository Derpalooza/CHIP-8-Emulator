#pragma once

#include "chip8.h"

// Functions to handle opcodes

void opcode_0xxx(Chip8 *chip8);
void opcode_1xxx(Chip8 *chip8);
void opcode_2xxx(Chip8 *chip8);
void opcode_3xxx(Chip8 *chip8);
void opcode_4xxx(Chip8 *chip8);
void opcode_5xxx(Chip8 *chip8);
void opcode_6xxx(Chip8 *chip8);
void opcode_7xxx(Chip8 *chip8);
void opcode_8xxx(Chip8 *chip8);
void opcode_9xxx(Chip8 *chip8);
void opcode_Axxx(Chip8 *chip8);
void opcode_Bxxx(Chip8 *chip8);
void opcode_Cxxx(Chip8 *chip8);
void opcode_Dxxx(Chip8 *chip8);
void opcode_Exxx(Chip8 *chip8);
void opcode_Fxxx(Chip8 *chip8);

