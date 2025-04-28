#include &lt;stdio.h&gt;
#include &lt;stdatomic.h&gt;
#include &lt;threads.h&gt;
#include &lt;stdbool.h&gt;

// 共享变量
atomic_int x = 0;
atomic_int y = 0;
int r1 = 0;
int r2 = 0;

// 线程1的函数
int thread1(void* arg) {
    // Store-Store 顺序
    atomic_store_explicit(&x, 1, memory_order_release);
    atomic_store_explicit(&y, 1, memory_order_release);
    return 0;
}

// 线程2的函数
int thread2(void* arg) {
    // Load-Load 顺序
    r1 = atomic_load_explicit(&y, memory_order_acquire);
    r2 = atomic_load_explicit(&x, memory_order_acquire);
    return 0;
}

int main() {
    thrd_t t1, t2;
    
    // 创建线程
    thrd_create(&t1, thread1, NULL);
    thrd_create(&t2, thread2, NULL);
    
    // 等待线程完成
    thrd_join(t1, NULL);
    thrd_join(t2, NULL);
    
    // 打印结果
    printf("r1 = %d, r2 = %d\n", r1, r2);
    
    return 0;
}