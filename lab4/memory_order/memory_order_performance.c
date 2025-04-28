#include &lt;stdio.h&gt;
#include &lt;stdatomic.h&gt;
#include &lt;threads.h&gt;
#include &lt;time.h&gt;

#define NUM_ITERATIONS 1000000
#define NUM_THREADS 4

// 共享计数器
atomic_int counter_relaxed = 0;
atomic_int counter_seq_cst = 0;

// 使用relaxed内存序的线程函数
int thread_relaxed(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        atomic_fetch_add_explicit(&counter_relaxed, 1, memory_order_relaxed);
    }
    return 0;
}

// 使用sequential consistency内存序的线程函数
int thread_seq_cst(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        atomic_fetch_add_explicit(&counter_seq_cst, 1, memory_order_seq_cst);
    }
    return 0;
}

// 测量执行时间的辅助函数
double measure_time(thrd_t* threads, int (*thread_func)(void*)) {
    clock_t start = clock();
    
    // 创建线程
    for (int i = 0; i < NUM_THREADS; i++) {
        thrd_create(&threads[i], thread_func, NULL);
    }
    
    // 等待所有线程完成
    for (int i = 0; i < NUM_THREADS; i++) {
        thrd_join(threads[i], NULL);
    }
    
    clock_t end = clock();
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    thrd_t threads_relaxed[NUM_THREADS];
    thrd_t threads_seq_cst[NUM_THREADS];
    
    printf("开始性能测试...\n");
    
    // 测试relaxed内存序
    printf("测试 memory_order_relaxed...\n");
    double time_relaxed = measure_time(threads_relaxed, thread_relaxed);
    
    // 测试sequential consistency内存序
    printf("测试 memory_order_seq_cst...\n");
    double time_seq_cst = measure_time(threads_seq_cst, thread_seq_cst);
    
    // 打印结果
    printf("\n结果：\n");
    printf("memory_order_relaxed:\n");
    printf("  时间: %.4f 秒\n", time_relaxed);
    printf("  最终计数器值: %d\n", atomic_load(&counter_relaxed));
    
    printf("\nmemory_order_seq_cst:\n");
    printf("  时间: %.4f 秒\n", time_seq_cst);
    printf("  最终计数器值: %d\n", atomic_load(&counter_seq_cst));
    
    printf("\n性能差异：\n");
    printf("seq_cst 比 relaxed 慢 %.2f%%\n", 
           ((time_seq_cst - time_relaxed) / time_relaxed) * 100);
    
    return 0;
}