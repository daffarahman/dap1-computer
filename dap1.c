// dap-1
// simple virtual computer inspired by tom scott's video https://www.youtube.com/watch?v=Z5JC9Ve1sfI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define usint unsigned short int
#define ll long long

typedef struct
{
    usint pc;
    usint prev;
    usint a;
    bool pc_set;
    usint mem[0xff];
} CPU;

void cpu_init(CPU *cpu)
{
    cpu->pc = 0;
    cpu->prev = 0;
    cpu->a = 0;
    cpu->pc_set = false;
    memset(cpu->mem, 0, sizeof cpu->mem);
}

void cpu_step(CPU *cpu)
{
    if(cpu->pc == 0xff) cpu->pc = 0;

    usint opcode = cpu->prev;
    usint param = cpu->mem[cpu->pc];

    if(cpu->pc_set)
    {
        cpu->pc_set = false;

        // LOAD
        if(opcode == 0x1) cpu->a = cpu->mem[param];
        // ADD
        if(opcode == 0xb) cpu->a += cpu->mem[param];
        // STORE
        if(opcode == 0x4) cpu->mem[param] = cpu->a;
        // JUMP
        if(opcode == 0xd) cpu->pc = param - 1;
    }
    else
    {
        cpu->prev = param;
        cpu->pc_set = true;
    }

    cpu->pc += 1;
}

void cpu_display(CPU *cpu, usint start, usint end)
{
    printf("[pc: %x a:%x ", cpu->pc, cpu->a);
    printf("%x.%x]\n", start, end);
    for(usint i=start;i<=end;i++)
    {
		if(i % 16 == 0) printf("\n[%04x]: ", i);

        if(cpu->pc == i) printf("[%02x] ", cpu->mem[i]);
        else printf("%02x ", cpu->mem[i]);
	}
}

void cpu_read_from_file(CPU *cpu, const char* filename, usint starting_address)
{
	FILE *file = fopen(filename, "r");
	int i = 0;
	int idx = starting_address;
	fscanf(file, "%x", &cpu->mem[idx]);
	while(!feof(file))
	{
		idx++;
		fscanf(file, "%x", &cpu->mem[idx]);
	}
	fclose(file);
}

int main(int argc, char* argv[])
{
    CPU cpu;
    cpu_init(&cpu);

	if(argc > 1) cpu_read_from_file(&cpu, argv[1], 0);

    while(true)
    {
        system("cls");
        cpu_display(&cpu, 0, 0xff);

        if(getchar() == '\n') {
            cpu_step(&cpu);
        } 
    }

    return 0;
}
