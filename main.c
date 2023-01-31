#include <stdio.h>

#define sram_start 0x20000000U
#define sram_size (128*1024)
#define sram_end ((sram_start)+(sram_size))
#define stack_start sram_end

#define stack_msp_start stack_start
#define stack_msp_end (stack_msp_start + 512)

#define stack_psp_start stack_msp_end
#define stack_psp_end (stack_psp_start + 512)

__attribute__((naked)) void ch_sp_psp(void);
void gen_exc(void);
void SVC_Handler(void);
int fun_add(int a,int b,int c);
__attribute__((naked)) void ch_sp_psp(void)
{
	__asm volatile(".equ SRAM_END,(0x20000000+(128*1024))");
	__asm volatile(".equ PSP_START,(SRAM_END-512)");
	__asm volatile("LDR R0,=PSP_START");
	__asm volatile("MSR PSP,R0");
	__asm volatile("MOV R0,#0X02");
	__asm volatile("MSR CONTROL,R0");
	__asm volatile("BX LR");
}
void gen_exc(void)
{
	__asm volatile("SVC #0X2");
}
int main(void)
{
    /* Loop forever */
	ch_sp_psp();
	int ret=fun_add(1,2,3);
	printf("%d\n",ret);
	gen_exc();
	for(;;);
}
int fun_add(int a,int b,int c)
{
	return a+b+c;
}
void SVC_Handler(void)
{
	printf("in handler");
}
