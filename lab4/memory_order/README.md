# Memory Order 实验

本实验展示了C11中不同内存序（memory order）的使用方法和性能影响。

## 文件说明

1. `memory_order_example.c`：展示了基本的memory order用法
   - 使用 `memory_order_release` 和 `memory_order_acquire` 来保证存储-加载顺序
   - 演示了如何在多线程环境中正确使用原子操作

2. `memory_order_performance.c`：比较不同memory order的性能
   - 对比 `memory_order_relaxed` 和 `memory_order_seq_cst` 的性能差异
   - 使用多线程进行大量原子操作来测试性能

## 内存序类型说明

C11定义了以下几种内存序：

1. `memory_order_relaxed`：最宽松的内存序，只保证原子性
2. `memory_order_acquire`：用于加载操作，建立获取屏障
3. `memory_order_release`：用于存储操作，建立释放屏障
4. `memory_order_acq_rel`：组合了acquire和release语义
5. `memory_order_seq_cst`：最严格的内存序，保证全序关系

## 编译和运行

```bash
# 编译示例程序
gcc -o example memory_order_example.c -pthread
gcc -o performance memory_order_performance.c -pthread

# 运行示例程序
./example
./performance
```

## 预期结果

1. `memory_order_example`：
   - 展示了不同线程间的内存操作顺序
   - 可能观察到不同的执行结果

2. `memory_order_performance`：
   - 显示relaxed内存序通常比sequential consistency更快
   - 性能差异可能因硬件架构而异

## 注意事项

1. 不同的内存序会影响程序的正确性和性能
2. 选择合适的内存序对于并发程序至关重要
3. 过度使用严格的内存序可能导致性能下降