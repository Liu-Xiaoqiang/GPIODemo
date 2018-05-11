#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

/*
 * Class:     com_chipsee_gpiodemo_HardwareControler
 * Method:    setGPIOValue
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_chipsee_gpiodemo_HardwareControler_setGPIOValue
  (JNIEnv *env, jclass c, jint pin, jint value)
{
	/* we only support gpio0-gpio9999*/
	int ret,fd;
	char pinPath[50]="0";
	char valueStr[5]="0";
	//ret = snprintf(pinPath,sizeof(pinPath),"/sys/class/gpio/gpio%d/value",pin);
	ret = snprintf(pinPath,sizeof(pinPath),"/dev/chipsee-gpio%d",pin);
	if (ret <0 ){
		printf("Error to prase gpio path\n");
		return ret;
	}
		
	ret = snprintf(valueStr,sizeof(valueStr),"%d",value);
	if (ret <0 ){
		printf("Error to prase gpio value\n");
		return ret;
	}

	fd = open(pinPath,O_RDWR);
	if(fd < 0){
		  printf("Fail to open %s.\n",pinPath);
		  return fd;
	} else {
		  ret = write(fd, valueStr, sizeof(valueStr));
		  if(ret < 0){
			  printf("Fail to write value!!");
			  close(fd);
			  return ret;
		  }
	}
	close(fd);
	return 0;
}

/*
 * Class:     com_chipsee_gpiodemo_HardwareControler
 * Method:    getGPIOValue
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_chipsee_gpiodemo_HardwareControler_getGPIOValue
  (JNIEnv *env, jclass c, jint pin)
{
	int ret,fd;
	char pinPath[50]="0";
	char valueStr[5]="0";
	//ret = snprintf(pinPath,sizeof(pinPath),"/sys/class/gpio/gpio%d/value",pin);
	ret = snprintf(pinPath,sizeof(pinPath),"/dev/chipsee-gpio%d",pin);
	if (ret <0 ){
		printf("Error to prase gpio value\n");
		return ret;
	}

	fd = open(pinPath,O_RDONLY);
	if(fd < 0){
		printf("Fail to open %s.\n",pinPath);
		return fd;
	} else {
		ret = read(fd, valueStr, sizeof(valueStr));
		if(ret < 0){
			printf("Fail to write value!!");
			close(fd);
			return ret;
		}
	}
	close(fd);
	return atoi(valueStr);
}

/*
 * Class:     com_chipsee_gpiodemo_HardwareControler
 * Method:    buzzer_open
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_chipsee_gpiodemo_HardwareControler_buzzer_1open
  (JNIEnv *env, jclass c)
{
	int ret,fd;
	char pinPath[20]="/dev/buzzer";
	char valueStr[5]="1";
	
	fd = open(pinPath,O_RDWR);
	if(fd < 0){
		  printf("Fail to open %s.\n",pinPath);
		  return fd;
	} else {
		  ret = write(fd, valueStr, sizeof(valueStr));
		  if(ret < 0){
			  printf("Fail to write value!!");
			  close(fd);
			  return ret;
		  }
	}
	close(fd);
	return 0;
}

/*
 * Class:     com_chipsee_gpiodemo_HardwareControler
 * Method:    buzzer_close
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_chipsee_gpiodemo_HardwareControler_buzzer_1close
  (JNIEnv *env, jclass c)
{
	int ret,fd;
	char pinPath[20]="/dev/buzzer";
	char valueStr[5]="0";
	
	fd = open(pinPath,O_RDWR);
	if(fd < 0){
		  printf("Fail to open %s.\n",pinPath);
		  return fd;
	} else {
		  ret = write(fd, valueStr, sizeof(valueStr));
		  if(ret < 0){
			  printf("Fail to write value!!");
			  close(fd);
			  return ret;
		  }
	}
	close(fd);
	return 0;
}


/*
 * Class:     com_chipsee_gpiodemo_HardwareControler
 * Method:    i2c_open
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_chipsee_gpiodemo_HardwareControler_i2c_1open
  (JNIEnv *env, jclass c, jstring devname)
{
	int fd;
	const char *str;
	str = (*env)->GetStringUTFChars(env, devname, 0);
	if((fd = open(str,O_RDWR)) < 0){
		printf("Open i2c dev %s fail!!\n", str);
		return -1;
	}
	(*env)->ReleaseStringUTFChars(env, devname, str);
	return fd;
}

/*
 * Class:     com_chipsee_gpiodemo_HardwareControler
 * Method:    i2c_set_slave_addr_bits
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_chipsee_gpiodemo_HardwareControler_i2c_1set_1slave_1addr_1bits
  (JNIEnv *env, jclass c, jint fd, jint n)
{
	
	if((ioctl(fd,I2C_TENBIT,n)) < 0){
		printf("Set 7bit mode Error!!\n");
		close(fd);
		return -1;
	}	
	return 0;
}

/*
 * Class:     com_chipsee_gpiodemo_HardwareControler
 * Method:    i2c_set_slave_addr
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_com_chipsee_gpiodemo_HardwareControler_i2c_1set_1slave_1addr
  (JNIEnv *env, jclass c, jint fd, jint slave_addr)
{
	if((ioctl(fd,I2C_SLAVE,slave_addr)) < 0){
		printf("Set %d slave_addr error!!\n",slave_addr);
		close(fd);
		return -1;
	}
	return 0;  
}

/*
 * Class:     com_chipsee_gpiodemo_HardwareControler
 * Method:    i2c_read
 * Signature: (IILjava/lang/String;Ljava/lang/String;I)I
 */
JNIEXPORT jstring JNICALL Java_com_chipsee_gpiodemo_HardwareControler_i2c_1read
  (JNIEnv *env, jclass c, jint fd, jint slave_addr, jstring addr, jint n)
{
	int ret;
	const char *data_addr;
	unsigned char readbuf[n];
	data_addr = (*env)->GetStringUTFChars(env, addr, 0);
	
	// 封装读操作的i2c_msg消息，共2个，一个是数据地址（写），一个加了读取数据的标志。
	struct i2c_msg msg[2] = {
		{
			.addr = slave_addr,
			.len = 1,
			.buf = (unsigned char *)data_addr,
		},
		{
			.addr = slave_addr,
			.flags = I2C_M_RD,
			.len = n,
			.buf = readbuf,
		}
	};
	
	// 封装data供ioctl使用
	struct i2c_rdwr_ioctl_data data = {
		.msgs = msg,
		.nmsgs = 1,
	};
	
	// 读操作1，先写读取从机数据的数据地址，封装在第一个msg消息的writebuf中
	ret = ioctl(fd, I2C_RDWR, &data);
	if(ret<0){
		printf("<<READ>> : write wri_add error.\n");
		close(fd);
		return NULL;
	}
	
	sleep(1);	//针对HDC1080 不加这个，读取不了数据
	
	// 读操作2，再通过第二个msg(带I2C_M_RD标志，代表要从从机接收数据到主机)来操作。
	data.msgs = &msg[1];
	ret = ioctl(fd, I2C_RDWR, &data);
	if(ret<0){
		printf("<<READ>> : read data error.\n");
		close(fd);
		return NULL;
	}
	(*env)->ReleaseStringUTFChars(env, addr, data_addr);
	return (*env)->NewStringUTF(env, (const char *)readbuf);
}

/*
 * Class:     com_chipsee_gpiodemo_HardwareControler
 * Method:    i2c_write
 * Signature: (IILjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_com_chipsee_gpiodemo_HardwareControler_i2c_1write
  (JNIEnv *env, jclass c, jint fd, jint slave_addr, jstring buf, jint n)
{
	int ret;
	const char *writebuf;
	writebuf = (*env)->GetStringUTFChars(env, buf, 0);
	struct i2c_msg msg[1] = {
		{
		.addr = slave_addr,
		.len = n,
		.buf = (unsigned char *)writebuf,
		}
	};
		
	struct i2c_rdwr_ioctl_data data = {
		.msgs = msg,
		.nmsgs = 1,
	};
	
	ret = ioctl(fd,I2C_RDWR,&data);
	if(ret < 0){
		printf("<<WRITE>> : write data error!!\n");
		close(fd);
		return -1;
	}else{
		printf("<<WRITE>> : Successed write %d data.\n",ret);
	}
	(*env)->ReleaseStringUTFChars(env, buf, writebuf);
	return ret;
}

/*
 * Class:     com_chipsee_gpiodemo_HardwareControler
 * Method:    i2c_close
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_chipsee_gpiodemo_HardwareControler_i2c_1close
  (JNIEnv *env, jclass c, jint fd)
{
	close(fd);
}
