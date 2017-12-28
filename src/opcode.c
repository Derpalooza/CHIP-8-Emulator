#include <stdlib.h>
#include "opcode.h"

void opcode_0xxx(Chip8 *chip8) {
	switch (chip8->opcode) {
		case 0x00E0:
			// 0x00E0 - Clear the display
			for (uint8_t i = 0; i < 64; i++) {
	    	for (uint8_t j = 0; j < 32; j++) {
	    	   chip8->gfx[i][j] = 0;
					}
			}
		
			chip8->draw_flag = 1; 
			break;

		case 0x00EE:
			// 0x00EE - Return from a subroutine
			if (chip8->sp > 0) {
				chip8->sp--;
				chip8->pc = chip8->stack[chip8->sp];
			}
			break;

		default:
			printf("Unknown opcode: %#x\n", chip8->opcode);
	}
	
	chip8->pc += 2;
}

void opcode_1xxx(Chip8 *chip8) {
	// 0x1nnn - Jump to location nnn
	chip8->pc = chip8->opcode & 0x0FFF;
}

void opcode_2xxx(Chip8 *chip8) {
	// 0x2nnn - Call subroutine at nnn
	chip8->stack[chip8->sp++] = chip8->pc;
	chip8->pc = chip8->opcode & 0x0FFF;	
}

void opcode_3xxx(Chip8 *chip8) {
	// 0x3xkk - Skip next instruction if Vx = kk
	if (chip8->V[(chip8->opcode & 0x0F00) >> 8] == (chip8->opcode & 0x00FF)) {
		chip8->pc += 4;
		return;
	}
	
	chip8->pc += 2;
}

void opcode_4xxx(Chip8 *chip8) {
	// 0x4xkk - Skip next instruction if Vx != kk
	if (chip8->V[(chip8->opcode & 0x0F00) >> 8] != (chip8->opcode & 0x00FF)) {
		chip8->pc += 4;
		return;
	}

	chip8->pc += 2;
}

void opcode_5xxx(Chip8 *chip8) {
	// 0x5xy0 - Skip next instruction if Vx = Vy
	if (chip8->V[(chip8->opcode & 0x0F00) >> 8] == chip8->V[(chip8->opcode & 0x00F0) >> 4]) {
		chip8->pc += 4;
		return;
	}
	
	chip8->pc += 2;
}

void opcode_6xxx(Chip8 *chip8) {
	// 0x6xkk - Set Vx = kk
	chip8->V[(chip8->opcode & 0x0F00) >> 8] = chip8->opcode & 0x00FF;
	chip->pc += 2;
}

void opcode_7xxx(Chip8 *chip8) {
	// 0x7xkk - Set Vx = Vx + kk
	chip8->V[(chip8->opcode & 0x0F00) >> 8] += chip8->opcode & 0x00FF;
	chip->pc += 2;
}

void opcode_8xxx(Chip8 *chip8) {
	switch (chip8->opcode & 0x000F) {
		case 0x0:
			// 0x8xy0 - Set Vx = Vy
			chip8->V[(chip8->opcode & 0x0F00) >> 8] = chip8->V[(chip8->opcode & 0x00F0) >> 4];
			break;

		case 0x1:
			// 0x8xy1 - Set Vx = Vx OR Vy
			chip8->V[(chip8->opcode & 0x0F00) >> 8] |= chip8->V[(chip8->opcode & 0x00F0) >> 4];
			break;

		case 0x2:
			// 0x8xy2 - Set Vx = Vx AND Vy
			chip8->V[(chip8->opcode & 0x0F00) >> 8] &= chip8->V[(chip8->opcode & 0x00F0) >> 4];
			break;

		case 0x3:
			// 0x8xy3 - Set Vx = Vx XOR Vy
			chip8->V[(chip8->opcode & 0x0F00) >> 8] ^= chip8->V[(chip8->opcode & 0x00F0) >> 4];
      break;

		case 0x4:
			// 0x8xy4 - Set Vx = Vx + Vy, set VF = carry
			uint16_t sum = chip8->V[(chip8->opcode & 0x0F00) >> 8] + chip8->V[(chip8->opcode & 0x00F0) >> 4];

			chip8->V[0xF] = (sum > 255) ? 1 : 0;
			chip8->V[(chip8->opcode & 0x0F00) >> 8] = (uint8_t)sum;			
		  break;

		case 0x5:
			// 0x8xy5 - Set Vx = Vx - Vy, set VF = NOT borrow
			if (chip8->V[(chip8->opcode & 0x0F00) >> 8] > chip8->V[(chip8->opcode & 0x00F0) >> 4]) {
				chip8->V[0xF] = 1;
			} else {
				chip8->V[0xF] = 0;
			}
			
			chip8->V[(chip8->opcode & 0x0F00) >> 8] -= chip8->V[(chip8->opcode & 0x00F0) >> 4];
      break;

		case 0x6:
			// 0x8xy6 - Set Vx = Vx SHR 1
			chip8->V[0xF] = (chip8->V[(chip8->opcode & 0x0F00) >> 8] & 0x1) ? 1 : 0;
			chip8->V[(chip8->opcode & 0x0F00) >> 8] >>= 1;
      break;

		case 0x7:
			// 0x8xy7 - Set Vx = Vy - Vx, set VF = NOT borrow
			if (chip8->V[(chip8->opcode & 0x00F0) >> 4] > chip8->V[(chip8->opcode & 0x0F00) >> 8]) {
				chip8->V[0xF] = 1;
			} else {
				chip8->V[0xF] = 0;
			}

			chip8->V[(chip8->opcode & 0x0F00) >> 8] = chip8->V[(chip8->opcode & 0x00F0) >> 4] - chip8->V[(chip8->opcode & 0x0F00) >> 8];
      break;

		case 0xE:
			// 0x8xyE - Set Vx = Vx SHL 1
			chip8->V[0xF] = (chip8->V[(chip8->opcode & 0x0F00) >> 8] >> 7) ? 1 : 0;
			chip8->V[(chip8->opcode & 0x0F00) >> 8] <<= 2;
      break;

		default:
			printf("Unknown opcode: %#x\n", chip8->opcode);
	}
	
	chip8->pc += 2;
}

void opcode_9xxx(Chip8 *chip8) {
	// 0x9xy0 - Skip next instruction if Vx != Vy
	if (chip8->V[(chip8->opcode & 0x0F00) >> 8] != chip8->V[(chip8->opcode & 0x00F0) >> 4]) {
		chip8->pc += 4;
		return;
	}
	
	chip8->pc += 2;
}

void opcode_Axxx(Chip8 *chip8) {
	// 0xAnnn - Set I = nnn
	chip8->I = chip8->opcode & 0x0FFF;
	chip8->pc += 2;
}

void opcode_Bxxx(Chip8 *chip8) {
	// 0xBnnn - Jump to location nnn + V0
	chip8->pc = (chip8->opcode & 0x0FFF) + chip8->V[0];
}

void opcode_Cxxx(Chip8 *chip8) {
	// 0xCxkk - Set Vx = random byte AND kk
	chip8->V[(chip8->opcode & 0x0F00) >> 8] = (rand & 0xFF) & (chip8->opcode & 0xFF);
	chip8->pc += 2;
}

void opcode_Dxxx(Chip8 *chip8) {
	// Dxyn - Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
	int X = V[(chip8->opcode & 0x0F00) >> 8];
	int Y = V[(chip8->opcode & 0x00F0) >> 4];
	int N = (chip8->opcode & 0x000F);

	uint8_t sprite[N];

	V[0xF] = 0;

	for (uint8_t i = 0; i < N; i++) {
		sprite[i] = chip8->memory[I + i];
	}

	for (uint8_t y = 0; y < N; y++) {
		for (uint8_t x = 0; x < 8; x++) {
			if (sprite[y] & (0x80 >> x) == 1) {
				if (chip8->gfx[X + x][Y + y] == 1) {
					V[0xF] = 1;
				}
				chip8->gfx[X + x][Y + y] ^= 1
			}
		}
	}

	draw_flag = 1;
	chip8->pc += 2;
}

void opcode_Exxx(Chip8 *chip8) {
	switch (chip8->opcode & 0xFF) {
		case 0x9E:
			// Ex9E - Skip next instruction if key with the value of Vx is pressed
			// TODO
			break;

		case 0xA1:
			// ExA1 - Skip next instruction if key with the value of Vx is not pressed
			// TODO
			break;

		default:
			printf("Unknown opcode: %#x\n", chip8->opcode);
	}
	
	chip8->pc += 2;
}

void opcode_Fxxx(Chip8 *chip8) {
	switch (chip8->opcode & 0xFF) {
		case 0x07:
			// Fx07 - Set Vx = delay timer value
			V[(chip8->opcode & 0x0F00) >> 8] = chip8->delay_timer;
			break;

    case 0x0A:
			// 0xFx0A - Wait for a key press, store the value of the key in Vx
			// TODO
      break;

    case 0x15:
			// 0xFx15 - Set delay timer = Vx
			chip8->delay_timer = V[(chip8->opcode & 0x0F00) >> 8];
      break;

    case 0x18:
			// 0xFx18 - Set sound timer = Vx
			chip8->sound_timer = V[(chip8->opcode & 0x0F00) >> 8];
      break;

		case 0x1E:
			// 0xFx1E - Set I = I + Vx
			chip8->I += V[(chip8->opcode & 0x0F00) >> 8];
      break;    

		case 0x29:
      // 0xFx29 - Set I = location of sprite for digit Vx
			chip8->I = 5 * V[(chip8->opcode & 0x0F00) >> 8];
			break;

		case 0x33:
			// 0xFx33 - Store BCD representation of Vx in memory locations I, I+1, and I+2
      // TODO
			break;

		case 0x55:
      // 0xFx55 - Store registers V0 through Vx in memory starting at location I
			X = (chip8->opcode & 0x0F00) >> 8;

			for (uint8_t i = 0; i < X; i++) {
				chip8->memory[I + i] = chip8->V[i];
			}
			break;    

		case 0x65:
      // 0xFx65 - Read registers V0 through Vx from memory starting at location I
			X = (chip8->opcode & 0x0F00) >> 8;
			
			for (uint8_t i = 0; i < X; i++) {
				chip8->V[i] = chip8->memory[I + i];
			}
			break;

		default:
			printf("Unknown opcode: %#x\n", chip8->opcode);
	}
	
	chip8->pc += 2;
}

