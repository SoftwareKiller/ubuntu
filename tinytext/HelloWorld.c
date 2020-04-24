char* str = "Hello world!\n";

void print()
{
    asm("movl $13,%%edx \n\t"
        "movl %0,%%ecx \n\t"
        "movl $0,%%ebx \n\t"
        "movl $4,%%eax \n\t"
        "int $0x80      \n\t"  /* 0x80是系统中断 */
       ::"r" (str):"edx", "ecx", "ebx");
}

void exit()
{
    asm("movl $42, %ebx \n\t"
        "movl $1, %eax \n\t"
        "int $0x80     \n\t");
}

void start()
{
    print();
    exit();
}

