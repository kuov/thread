# thread
说明文档

1，编译运行
   程序编译环境:ubuntu16.04,g++(支持c++11),make
   进入相应目录运行:make clean && make 之后会生成相应的运行程序
   ./thread1 or ./thread2 即可运行程序1和程序2，若没有运行权限请自行添加

2,运行结果
   1，多核多线程
   
     ![image](https://github.com/kuov/thread/blob/master/1.png)
     
   2，多核单线程
   
     ![image](https://github.com/kuov/thread/blob/master/2.png)

   3，单核多线程
   
     ![image](https://github.com/kuov/thread/blob/master/3.png)

   4，单核单线程
   
     ![image](https://github.com/kuov/thread/blob/master/4.png)



3,原因分析
   1，多CPU情况
      多cpu情况下，多线程处理数量多于单线程的数量，说明多CPU多线程下可以充分发挥CPU性能
   2，单CPU情况
      单CPU情况下，多线程慢于单线程数量，说明在单CPU多线程下会降低CPU处理效率，因为此情况所有的线程都运行与同一CPU上，线程切换需要耗费时间，所以降低了CPU效率，而单一线程不需要切换，反而性能更高
