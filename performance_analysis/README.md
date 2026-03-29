# 性能分析指南

## gprof

```
cmake -DCMAKE_CXX_FLAGS="-pg" ..
make

./tinyraytracer

gprof ./tinyraytracer gmon.out > gprof.txt
```

## perf

```
perf record -e task-clock:u ./tinyraytracer

cat /proc/sys/kernel/perf_event_paranoid

// 如果你想要进行 CPU 事件分析（但不包括原始事件和跟踪点），你可以将其设置为 1 或更低
sudo echo 1 | sudo tee /proc/sys/kernel/perf_event_paranoid

// 如果你想要完全访问（包括内核分析），可以将其设置为 -1
sudo echo -1 | sudo tee /proc/sys/kernel/perf_event_paranoid

perf report
```

[参考链接](https://blog.csdn.net/Summer0828/article/details/142208327)

## valgrind + kcachegrind

```
valgrind --tool=callgrind ./tinyraytracer
kcachegrind ./callgrind.out.15826
```