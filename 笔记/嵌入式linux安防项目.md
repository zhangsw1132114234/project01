# 嵌入式Linux安防项目

------

## 一、项目功能

1. web端能通过按钮对led，beep，等传感器的控制
2. web端能够显示温湿度等传感器的信息

## 二、整体的流程图

![image-20240927164227945](./嵌入式linux安防项目.assets/image-20240927164227945.png)

## 三、协议的制定

温湿度传感器为zigbee模块

陀螺仪，加速计，led，beep为开发板上的传感器

1. 传感器上传数据（共享内存和信号量）

```c
struct zigbee_info
{
	uint8_t head[3]; //标识位: 'm' 's' 'm'  makeru-security-monitor  
	uint8_t type;	 //数据类型  'z'---zigbee  'a'---a9
	float temperature; //温度
	float humidity;  //湿度
	float tempMIN;//温度下限
	float tempMAX;//温度上限 
	float humidityMIN;   //湿度下限
	float humidityMAX;   //湿度上限
	uint32_t reserved[2]; //保留扩展位，默认填充0
};

struct a9_info{
	uint8_t head[3]; //标识位: 'm' 's' 'm'  makeru-security-monitor  
	uint8_t type;	 //数据类型  'z'---zigbee  'a'---a9
	uint32_t adc；
	short gyrox;   //陀螺仪数据
	short gyroy;
	short gyroz;
	short  aacx;  //加速计数据
	short  aacy;
	short  aacz;
	uint32_t reserved[2]; //保留扩展位，默认填充0
};

#define MONITOR_NUM 2
struct env_data
{
    struct zigbee_info	zigbee_info;
    struct a9_info 		a9_info;    
};
/* 所有区域的信息结构体*/
struct env_info_client_addr
{
    struct env_data monitor_no[MONITOR_NUM];	// home1 home2
}
```

2. 控制命令的下传（采用消息队列）

```c
/* 消息结构体*/
struct msg
{
  long type;
  long msgtype;
  unsigned char text[QUEUE_MSG_LEN];
};
type:
	1L home1
	2L home2
msgtype:
	1L: 		LED控制
	2L:			蜂鸣器控制
	3L:			四路LED灯模拟的数码管
	4L:			风扇
	5L:			温湿度最值设置
	6L-7L-8L-9L, 用于个人的扩展
	10L: 		3G通信模块-GPRS 
text:
----------------------------------------
	7	6	|  5	4	|	3	2	1	0
	 平台编号|  设备编号 |	操作设备
----------------------------------------
平台编号：
    0x00		0号-ZigBee平台 
    0x40		1号-A9/A53平台
    0x80		2号-STM32平台（可以自己扩展）
设备编号：
  ----------------------------------------		
设备编号		操作掩码	
0x00	LED      0x00 全部关闭
				0x01 全部打开
				0x02 打开LED2
				0x03 打开LED3
				0X04 打开LED4
				0x05 打开LED5
				0X10 打开流水灯
----------------------------------------
0x10	蜂鸣器	  0x00 关闭
			    0x01 打开
                 0x02 自动报警关闭
                 0x03 自动报警打开
----------------------------------------
0x20	风扇     0x00	关闭风扇
			    0x01 打开风扇
----------------------------------------			
0x30	数码管	  0x0~0xF 显示0~F数字(四盏灯，对应0000-表示0,0001-表示1....1110-表示14)
			    0x0f		关闭数码管				led2-3-4-5
----------------------------------------
```

```c
/* 消息队列的发送和接收函数*/
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);

/* 为了方便直接将发送消息队列封装成函数*/
int send_msg_queue(long type, unsigned char text)
{
    struct msg msgbuf;
    msgbuf.type = 1L;
    msgbuf.msgtype = type;
    msgbuf.text[0] = text;
    if (msgsnd(msqid, &msgbuf, sizeof(msgbuf) - sizeof(long), 0) == -1)
    {
		perror("fail to msgsnd type2");
		exit(1);
    }
    return 0;
}
```

## 四、开发板主框架的搭建

每一个功能都是一个线程

- led
- beep
- client_reauest  接收web服务端发来的控制命令
- refresh             共享内存的刷新
- sms                  3G
- sqlite                数据库
- transfer            采集zigbee和开发板传感器数据

但是这些线程需要互斥信号量去管控，比方说对共享内存的操作，一次完整的写入后才能继续进行写入

### 1.data_global

在这个文件中定义了所有的通信协议，并且声明了互斥量

```c
pthread_mutex_t mutex_client_request,
        		mutex_refresh,
        		mutex_sqlite,
	        	mutex_transfer,
	        	mutex_sms,
	        	mutex_buzzer,
	         	mutex_led;
```

### 2.main

初始化信号量

