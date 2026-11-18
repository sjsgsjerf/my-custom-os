#include <stddef.h>
#include <stdint.h>

static volatile uint16_t* const VGA_BUFFER = (uint16_t*)0xB8000;
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | ((uint16_t)color << 8);
}

static void terminal_clear(uint8_t color) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            VGA_BUFFER[y * VGA_WIDTH + x] = vga_entry(' ', color);
        }
    }
}

static void terminal_write_at(const char* str, size_t x, size_t y, uint8_t color) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (x + i >= VGA_WIDTH) break;
        VGA_BUFFER[y * VGA_WIDTH + (x + i)] = vga_entry((unsigned char)str[i], color);
    }
}

void kernel_main(void) {
    uint8_t color = 0x0F;
    terminal_clear(color);
    terminal_write_at("Hello from my-custom-os!", 0, 0, 0x0B);
    terminal_write_at("Minimal x86 Multiboot kernel booted successfully.", 0, 1, 0x07);
}
