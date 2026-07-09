CC = arm-none-eabi-gcc
MACH = cortex-m4
CFLAGS = -c -mcpu=$(MACH) -mthumb -Wall -std=gnu11 -O0 -g
LDFLAGS = -nostdlib -T stm32_ls.ld -Wl,-Map=final.map
OPENOCD_SCRIPTS = /usr/share/openocd/scripts


all : main.o led.o traffic.o stm32_startup.o final.elf

main.o : main.c
	$(CC) $(CFLAGS) $^ -o $@

led.o : led.c
	$(CC) $(CFLAGS) $^ -o $@

traffic.o : traffic.c
	$(CC) $(CFLAGS) $^ -o $@

stm32_startup.o : stm32_startup.c
	$(CC) $(CFLAGS) $^ -o $@

final.elf : main.o led.o traffic.o stm32_startup.o
	$(CC) $(LDFLAGS) $^ -o $@

clean :
	rm -rf *.o *.elf

download : 
	openocd -s $(OPENOCD_SCRIPTS) -f board/stm32f4discovery.cfg