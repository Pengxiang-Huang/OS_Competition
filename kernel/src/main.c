

#define __module_name__ 	"main"

#include "printf.h"
#include "panic.h"
#include "types.h"
#include "loader.h"
#include "proc.h"
#include "mm/framealloc.h"
#include "pid_allocator.h"
#include "mm/pagetable.h"
#include "mm/kmalloc.h"
#include "riscv.h"
#include "mm/MapArea.h"
#include "mm/MemorySet.h"

extern uint64 app_0_start;
extern uint64 app_0_end;

void main(int num_core) {
    printf("[kernel] num of cores: %d \n", num_core);  // 通过寄存器entry.S中设置的寄存器a0来传这个num_core参数
    initmalloc();
    test_alloc();
    load();    // 将应用程序load到主内存中

    map_kernel();
    printf("[kernel] ready to activate mm!\n");
    activate_mm();

    printf("[kernel] ok to activate mm! Back to Kernel!\n");

    test_page_table();



    printf("[kernel] hello man!\n");

    init_app(0); // 初始化App，包括初始化其trap上下文，将trap上下文放到用户栈中。
    run_app(0);

    panic("[kernel] If this is printed, sth must get wrong!\n");
    while (1) {}
}

void test_alloc(){
  uint32 frame1 = get_frame();
  uint32 frame2 = get_frame();
  uint32 frame3 = get_frame();
  printf("[kernel] frame1, frame2, frame3 is %d %d %d\n", frame1, frame2, frame3);
  free_frame(frame1);
  free_frame(frame2);
  uint32 frame4 = get_frame();
  printf("[kernel] frame4 is %d\n", frame4);
}
