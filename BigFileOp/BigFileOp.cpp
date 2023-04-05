#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>

using namespace std;
//��Ŀ�����ǰ��ļ��е����ݣ���������ά����
#define SIZE1 128
#define SIZE2 1024
#define SIZE3 1306

int main(void) {

	//������ŵ��ڴ棡��û��
	//int(*data)[SIZE2][SIZE3] = new int[SIZE1][SIZE2][SIZE3];
	
	int* (*data)[SIZE2] = new int* [SIZE1][SIZE2];
	if (data == NULL) {
		printf("�ڴ����ʧ��");
		exit(1);
	}
	for (int i = 0;i < SIZE1;i++) {
		for (int j = 0;j < SIZE2; j++) {
			data[i][j] = new int[SIZE3];
		}
	}

	//����1��һ��һ�ж�ȡ���в���
	FILE* fp = fopen("sask.csv", "r");
	if (fp == NULL) {
		printf("�ļ���ʧ�ܣ�\n");
		exit(1);
	}

	//�����ڴ�
	//1.��Ҫȷ��������ļ��ж��������
	fseek(fp, 0, SEEK_END);//���ļ��ڲ�λ���Ƶ��ļ�β��
	int len = ftell(fp);
	fseek(fp, 0, SEEK_SET);//���ļ��ڲ�λ���Ƶ��ļ�ͷ
	 

	char* men = (char*)malloc(len + 1);
	if (men == NULL) {
		printf("�ڴ����ʧ�ܣ�\n");
		exit(1);
	}
	int time1 = time(NULL);
	//���ļ�
	int ret = fread(men, sizeof(char), len, fp);//һ��ȫ������
	men[ret] = 0;
	//���ļ�����Ҫ��ʱ��
	int time2 = time(NULL);
	printf("�����ļ�����ʱ%d", time2 - time1);




	char line[1024 * 16];
	int numCount = 0;
	int lineCount = 0;
	char* p = men;
	int* pData = &data[0][0][0];
	int k1 = 0, k2 = 0, k3 = 0;
	while (*p) {
		int x = atoi(p);//���ַ���ת������
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
					printf("�����Ѿ�����");
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
	//���ļ�����Ҫ��ʱ��
	int time3 = time(NULL);
	printf("�����ļ�����ʱ%d", time2 - time1);


	//�Զ������ݽ��н���
	//ʹ��c�����ַ���line������һ��C++ �ַ���stream��
	/*int numCount; //C++
	stringstream stream(line);
	string num;
	while (getline(stream, num, ',')) {
		numCount++;
		//�õ��ִ�num
	}*/
	//������stringstream �ֶ�����
	//p
	return 0;
}


//��һ���Ż�
//1.һ���԰��ļ��������ݣ��������ڴ�
//2.�ֶ�ζ���
//������������ʮ������ļ��ж��
//����ļ�����1G��ֱ������1G��ʧ��
//�����и�һ������



//void test() {
//	char* men = (char*)malloc(1024 * 1024 * 1024 * 2);
//	if (men == NULL) {
//		printf("û���ڴ棡");
//		exit(1);
//	}
//}

//30s����
//û�б��浽�ڴ� �ٵĽ���