@[TOC](文章目录)

---


# 前言

为了演示[bootloader_stm32f103](https://gitee.com/eming/bootloader_stm32f103)项目差分升级功能，故有了这篇。

------

# 一、bootloader_stm32f103简介

bootloader_stm32f103恰如其名，就是一个bootloader，它支持差分升级包的IAP功能。

# 二、这个demo的主要功能

1. 先上图：

![功能演示](images\demo.gif)

2. 上图演示的基本功能：
   - 在bootloader下烧录应用程序到app分区（分区2），然后跳转到应用程序运行。
   - 烧录差分升级包到patch分区（分区3），完成差分升级。
   - 其中bootloader包含烧录分区2和分区3的命令，应用程序只包含烧录分区3功能。
   
3. 涉及的命令说明：

   - `ymodem app`，烧录应用程序到app分区，bootloader收到这个命令后，会先擦除分区，因此需要等待片刻。然后发送ymodem文件（这里是uold_1024k.bin）到开发板。发送完成后，开发板会复位跳转到应用程序运行。

   - `ymodem patch`，烧录应用程序到patch分区，bootloader收到这个命令后，同样会先擦除分区。然后发送ymodem文件（这里是patch_1024k.bin）到开发板。发送完成后，开发板会复位开始升级。

---
# 三、demo工程说明

1. 为了演示差分升级功能，工程需要编译2次（***使用Rebuild按钮***），第一次产生的文件将作为基础文件，第二次编译对比前次的文件生成差分包。

2. 在工程目录tools下有生成所有文件的工具软件和脚本文件，这些脚本文件将在编译过程中调用，如下图
![脚本演示](images\bat.jpg)

3. 两次编译产生的固件，唯一的区别就是编译*时间不同*，这点将在运行时打印出来。同时正是因为差别很小，可以看到最后产生的差分升级包（patch_1024k.bin）很小，只有几百字节。

4. 注意，为了正确编译，需要将`fromelf`命令路径加入系统环境变量，这个文件在`keil\ARM\ARMCC\bin`目录下。

#  四、项目地址

```
https://gitee.com/eming/bootloader_stm32f103  
https://gitee.com/eming/demo_stm32f103
```

