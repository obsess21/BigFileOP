#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>

using namespace std;
//项目需求，是把文件中的内容，解析到三维数组
#define SIZE1 128
#define SIZE2 1024
#define SIZE3 1306

int main(void) {

	//连续存放的内存！！没有
	//int(*data)[SIZE2][SIZE3] = new int[SIZE1][SIZE2][SIZE3];
	
	int* (*data)[SIZE2] = new int* [SIZE1][SIZE2];
	if (data == NULL) {
		printf("内存分配失败");
		exit(1);
	}
	for (int i = 0;i < SIZE1;i++) {
		for (int j = 0;j < SIZE2; j++) {
			data[i][j] = new int[SIZE3];
		}
	}

	//方案1：一行一行读取进行操作
	FILE* fp = fopen("sask.csv", "r");
	if (fp == NULL) {
		printf("文件打开失败！\n");
		exit(1);
	}

	//申请内存
	//1.需要确定，这个文件有多大，再申请
	fseek(fp, 0, SEEK_END);//把文件内部位置移到文件尾巴
	int len = ftell(fp);
	fseek(fp, 0, SEEK_SET);//把文件内部位置移到文件头
	 

	char* men = (char*)malloc(len + 1);
	if (men == NULL) {
		printf("内存分配失败！\n");
		exit(1);
	}
	int time1 = time(NULL);
	//读文件
	int ret = fread(men, sizeof(char), len, fp);//一次全部读完
	men[ret] = 0;
	//读文件所需要得时间
	int time2 = time(NULL);
	printf("读完文件，耗时%d", time2 - time1);




	char line[1024 * 16];
	int numCount = 0;
	int lineCount = 0;
	char* p = men;
	int* pData = &data[0][0][0];
	int k1 = 0, k2 = 0, k3 = 0;
	while (*p) {
		int x = atoi(p);//把字符串转成整数
		//*pData++ = x;
		data[k1][k2][k3] = x;
		k3++;
		if (k3 >= SIZE3) {
			k3 = 0;
			k2++;
			if (k2 >= SIZE2) {
				k2 = 0;
				k1++;
				if (k1 >= SIZE1) {
					printf("数据已经存满");
				}
			}
		}
		numCount++;
		while (*p != ',' && *p != '\n')p++;
		if (*p == '\n') {
			lineCount++;
		}
		p++;
	}
	//读文件所需要得时间
	int time3 = time(NULL);
	printf("读完文件，耗时%d", time2 - time1);


	//对读到数据进行解析
	//使用c语言字符串line，创建一个C++ 字符串stream流
	/*int numCount; //C++
	stringstream stream(line);
	string num;
	while (getline(stream, num, ',')) {
		numCount++;
		//得到字串num
	}*/
	//不适用stringstream 手动解析
	//p
	return 0;
}


//进一步优化
//1.一次性把文件所有内容，都读到内存
//2.分多次读完
//决定性因素三十，这个文件有多大
//如果文件超过1G，直接申请1G会失败
//这里有个一个陷阱



//void test() {
//	char* men = (char*)malloc(1024 * 1024 * 1024 * 2);
//	if (men == NULL) {
//		printf("没有内存！");
//		exit(1);
//	}
//}

//30s左右
//没有保存到内存 假的解析