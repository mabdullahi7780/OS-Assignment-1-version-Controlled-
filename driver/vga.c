#include "../include/driver/vga.h"
#include "../include/utils.h"
uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return (bg << 4) | (fg & 0x0F);
}
vga_entry_t vga_entry(unsigned char uc, uint8_t color)
{
    return ((vga_entry_t)color << 8) | (vga_entry_t)uc;
}
void vga_move_cursor_to(uint8_t x, uint8_t y)
{
    uint16_t pos = (y * VGA_WIDTH) + x;

    outb(VGA_HARDWARE_CURSOR_CMD_SETLOW, VGA_CRTC_INDEX_PORT);
    outb(pos & 0xFF, VGA_CRTC_DATA_PORT);

    outb(VGA_HARDWARE_CURSOR_CMD_SETHIGH, VGA_CRTC_INDEX_PORT);
    outb((pos >> 8) & VGA_HARDWARE_CURSOR_CMD_SETLOW, VGA_CRTC_DATA_PORT);
}
void vga_putentry_at(vga_entry_t entry, uint8_t x, uint8_t y)
{
    if(x> VGA_WIDTH || y> VGA_HEIGHT ){return;}
    vga_entry_t *buffer = vga_get_screen_buffer();
    buffer[(y * VGA_WIDTH) + x] = entry;
}
vga_entry_t *vga_get_screen_buffer(void)
{
    return (vga_entry_t *)0xB8000;
}