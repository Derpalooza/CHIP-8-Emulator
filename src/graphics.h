#pragma once

#include <stdbool.h>

// Handles the graphical side of the emulator

void graphics_init();

void graphics_blit(bool value, uint8_t x, uint8_t y);

void graphics_update();

void graphics_close();
