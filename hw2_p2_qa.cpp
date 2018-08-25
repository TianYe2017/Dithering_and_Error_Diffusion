#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "convert_data_brutal.h"
#include "hw2_p2_qa.h"


int Region_indicator(double input) 
{
	if (input < 85.0 / 255.0) 
	{
		return 1;
	}
	else if (input >= 85.0 / 255.0 & input < 170.0 / 255.0) 
	{
		return 2;
	}
	else 
	{
		return 3;
	} 
}

double Data_transform(double input) 
{
	if (input < 85.0 / 255.0)
	{
		return input / (85.0 / 255.0);
	}
	else if (input >= 85.0 / 255.0 & input < 170.0 / 255.0)
	{
		return (input - 85.0 / 255.0) / (85.0 / 255.0);
	}
	else
	{
		return (input - 170.0 / 255.0) / (85.0 / 255.0);
	}

}

int Set_gray(int indicator, bool light_or_dark) 
{
	if (indicator == 1)
	{   
		if (light_or_dark == true) 
		{
			return 85;
		}
		else
		{
			return 0;
		}
	}
	else if (indicator == 2)
	{
		if (light_or_dark == true)
		{
			return 170;
		}
		else
		{
			return 85;
		}
	}
	else
	{
		if (light_or_dark == true)
		{
			return 255;
		}
		else
		{
			return 170;
		}
	}

}


void Dithering(void) 
{
//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//
//第一部分，预处理man图像，读取，转换
	unsigned char man[512 * 512];
	FILE *fp_read = fopen("D:\\EE569image_hw2_p2\\input\\man.raw", "rb");
	if (fp_read == NULL)
	{
		printf("\nFail to find the file.");
	}
	else
	{
		printf("\nSucess to find the file:man.raw.");
	}
	fread(man, sizeof(unsigned char), 512*512, fp_read);
	fclose(fp_read);
	printf("\nman.raw in memeory.");
	//化成归一矩阵
	double man_gray[512][512];
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			man_gray[y][x] = (double)(U8_to_0_255(man[512 * y + x])) / 255.0;		
		}
	}
//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//
//第二部分，准备Dithering阈值矩阵
	double I2[2][2] = { {0,2},{3,1} };
	double TI2[2][2];
	for (int y = 0; y < 2; y++) 
	{
		for (int x = 0; x < 2; x++)
		{
			TI2[y][x] = (I2[y][x] + 0.5) / 4.0;
		}
	}
	double I4[4][4] = { {0,8,2,10},
						{12,4,14,6},
						{3,11,1,9},
						{15,7,13,5} };
	double TI4[4][4];
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			TI4[y][x] = (I4[y][x] + 0.5) / 16.0;
		}
	}
	double I8[8][8] = { {0,48,12,60,3,51,15,63},
						{32,16,44,28,35,19,47,31},
						{8,56,4,52,11,59,7,55},
						{40,24,36,20,43,27,39,23},
						{2,50,14,62,1,49,13,61},
						{34,18,46,30,33,17,45,29},
						{10,58,6,54,9,57,5,53},
						{42,26,28,22,41,25,37,21} };
	double TI8[8][8];
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			TI8[y][x] = (I8[y][x] + 0.5) / 64.0;
		}
	}
	double A4[4][4] = { {14,10,11,15},
	                    {9,3,0,4},
						{8,2,1,5},
						{13,7,6,12} };
	double TA4[4][4];
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			TA4[y][x] = (A4[y][x] + 0.5) / 16.0;
		}
	}
//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//
	int man_binary[512][512];
	unsigned char man_done[512 * 512];
//------------------第三部分，part#1.1 ，I2 处理------------------//
	//I2
	for (int y = 0; y < 512; y += 2) 
	{
		for (int x = 0; x < 512; x += 2) 
		{
			if (man_gray[y][x] >= TI2[0][0]) 
			{
				man_binary[y][x] = 255;
			}
			else 
			{
				man_binary[y][x] = 0;
			}
			if (man_gray[y + 1][x] >= TI2[1][0])
			{
				man_binary[y + 1][x] = 255;
			}
			else
			{
				man_binary[y + 1][x] = 0;
			}
			if (man_gray[y][x + 1] >= TI2[0][1])
			{
				man_binary[y][x + 1] = 255;
			}
			else
			{
				man_binary[y][x + 1] = 0;
			}
			if (man_gray[y + 1][x + 1] >= TI2[1][1])
			{
				man_binary[y + 1][x + 1] = 255;
			}
			else
			{
				man_binary[y + 1][x + 1] = 0;
			}
		}
	}
	//回到array输出
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			man_done[512 * y + x] = Zero_255_to_U8(man_binary[y][x]);
		}
	}
	FILE *fp_write = fopen("D:\\EE569image_hw2_p2\\output\\man_I2.raw", "wb");
	if (fp_write == NULL)
	{
		printf("\nFail to create the file.");
	}
	else
	{
		printf("\nScuess to create the file.");
	}
	fwrite(man_done, sizeof(unsigned char), 512 * 512, fp_write);
	fclose(fp_write);
	printf("\n\nman_I2...done...\n.");
//------------------第三部分，part#1.2 ，I8 处理------------------//
    //I8
	for (int y = 0; y < 512; y += 8)
	{
		for (int x = 0; x < 512; x += 8)
		{
			if (man_gray[y][x] >= TI8[0][0])
			{
				man_binary[y][x] = 255;
			}
			else
			{
				man_binary[y][x] = 0;
			}//1
			if (man_gray[y][x + 1] >= TI8[0][1])
			{
				man_binary[y][x + 1] = 255;
			}
			else
			{
				man_binary[y][x + 1] = 0;
			}//2
			if (man_gray[y][x + 2] >= TI8[0][2])
			{
				man_binary[y][x + 2] = 255;
			}
			else
			{
				man_binary[y][x + 2] = 0;
			}//3
			if (man_gray[y][x + 3] >= TI8[0][3])
			{
				man_binary[y][x + 3] = 255;
			}
			else
			{
				man_binary[y][x + 3] = 0;
			}//4
			if (man_gray[y][x + 4] >= TI8[0][4])
			{
				man_binary[y][x + 4] = 255;
			}
			else
			{
				man_binary[y][x + 4] = 0;
			}//5
			if (man_gray[y][x + 5] >= TI8[0][5])
			{
				man_binary[y][x + 5] = 255;
			}
			else
			{
				man_binary[y][x + 5] = 0;
			}//6
			if (man_gray[y][x + 6] >= TI8[0][6])
			{
				man_binary[y][x + 6] = 255;
			}
			else
			{
				man_binary[y][x + 6] = 0;
			}//7
			if (man_gray[y][x + 7] >= TI8[0][7])
			{
				man_binary[y][x + 7] = 255;
			}
			else
			{
				man_binary[y][x + 7] = 0;
			}//8
			//------//1
			if (man_gray[y + 1][x] >= TI8[1][0])
			{
				man_binary[y + 1][x] = 255;
			}
			else
			{
				man_binary[y + 1][x] = 0;
			}//1
			if (man_gray[y + 1][x + 1] >= TI8[1][1])
			{
				man_binary[y + 1][x + 1] = 255;
			}
			else
			{
				man_binary[y + 1][x + 1] = 0;
			}//2
			if (man_gray[y + 1][x + 2] >= TI8[1][2])
			{
				man_binary[y + 1][x + 2] = 255;
			}
			else
			{
				man_binary[y + 1][x + 2] = 0;
			}//3
			if (man_gray[y + 1][x + 3] >= TI8[1][3])
			{
				man_binary[y + 1][x + 3] = 255;
			}
			else
			{
				man_binary[y + 1][x + 3] = 0;
			}//4
			if (man_gray[y + 1][x + 4] >= TI8[1][4])
			{
				man_binary[y + 1][x + 4] = 255;
			}
			else
			{
				man_binary[y + 1][x + 4] = 0;
			}//5
			if (man_gray[y + 1][x + 5] >= TI8[1][5])
			{
				man_binary[y + 1][x + 5] = 255;
			}
			else
			{
				man_binary[y + 1][x + 5] = 0;
			}//6
			if (man_gray[y + 1][x + 6] >= TI8[1][6])
			{
				man_binary[y + 1][x + 6] = 255;
			}
			else
			{
				man_binary[y + 1][x + 6] = 0;
			}//7
			if (man_gray[y + 1][x + 7] >= TI8[1][7])
			{
				man_binary[y + 1][x + 7] = 255;
			}
			else
			{
				man_binary[y + 1][x + 7] = 0;
			}//8
			//------//2
			if (man_gray[y + 2][x] >= TI8[2][0])
			{
				man_binary[y + 2][x] = 255;
			}
			else
			{
				man_binary[y + 2][x] = 0;
			}//1
			if (man_gray[y + 2][x + 1] >= TI8[2][1])
			{
				man_binary[y + 2][x + 1] = 255;
			}
			else
			{
				man_binary[y + 2][x + 1] = 0;
			}//2
			if (man_gray[y + 2][x + 2] >= TI8[2][2])
			{
				man_binary[y + 2][x + 2] = 255;
			}
			else
			{
				man_binary[y + 2][x + 2] = 0;
			}//3
			if (man_gray[y + 2][x + 3] >= TI8[2][3])
			{
				man_binary[y + 2][x + 3] = 255;
			}
			else
			{
				man_binary[y + 2][x + 3] = 0;
			}//4
			if (man_gray[y + 2][x + 4] >= TI8[2][4])
			{
				man_binary[y + 2][x + 4] = 255;
			}
			else
			{
				man_binary[y + 2][x + 4] = 0;
			}//5
			if (man_gray[y + 2][x + 5] >= TI8[2][5])
			{
				man_binary[y + 2][x + 5] = 255;
			}
			else
			{
				man_binary[y + 2][x + 5] = 0;
			}//6
			if (man_gray[y + 2][x + 6] >= TI8[2][6])
			{
				man_binary[y + 2][x + 6] = 255;
			}
			else
			{
				man_binary[y + 2][x + 6] = 0;
			}//7
			if (man_gray[y + 2][x + 7] >= TI8[2][7])
			{
				man_binary[y + 2][x + 7] = 255;
			}
			else
			{
				man_binary[y + 2][x + 7] = 0;
			}//8
			 //------//3
			if (man_gray[y + 3][x] >= TI8[3][0])
			{
				man_binary[y + 3][x] = 255;
			}
			else
			{
				man_binary[y + 3][x] = 0;
			}//1
			if (man_gray[y + 3][x + 1] >= TI8[3][1])
			{
				man_binary[y + 3][x + 1] = 255;
			}
			else
			{
				man_binary[y + 3][x + 1] = 0;
			}//2
			if (man_gray[y + 3][x + 2] >= TI8[3][2])
			{
				man_binary[y + 3][x + 2] = 255;
			}
			else
			{
				man_binary[y + 3][x + 2] = 0;
			}//3
			if (man_gray[y + 3][x + 3] >= TI8[3][3])
			{
				man_binary[y + 3][x + 3] = 255;
			}
			else
			{
				man_binary[y + 3][x + 3] = 0;
			}//4
			if (man_gray[y + 3][x + 4] >= TI8[3][4])
			{
				man_binary[y + 3][x + 4] = 255;
			}
			else
			{
				man_binary[y + 3][x + 4] = 0;
			}//5
			if (man_gray[y + 3][x + 5] >= TI8[3][5])
			{
				man_binary[y + 3][x + 5] = 255;
			}
			else
			{
				man_binary[y + 3][x + 5] = 0;
			}//6
			if (man_gray[y + 3][x + 6] >= TI8[3][6])
			{
				man_binary[y + 3][x + 6] = 255;
			}
			else
			{
				man_binary[y + 3][x + 6] = 0;
			}//7
			if (man_gray[y + 3][x + 7] >= TI8[3][7])
			{
				man_binary[y + 3][x + 7] = 255;
			}
			else
			{
				man_binary[y + 3][x + 7] = 0;
			}//8
			 //------//4
			if (man_gray[y + 4][x] >= TI8[4][0])
			{
				man_binary[y + 4][x] = 255;
			}
			else
			{
				man_binary[y + 4][x] = 0;
			}//1
			if (man_gray[y + 4][x + 1] >= TI8[4][1])
			{
				man_binary[y + 4][x + 1] = 255;
			}
			else
			{
				man_binary[y + 4][x + 1] = 0;
			}//2
			if (man_gray[y + 4][x + 2] >= TI8[4][2])
			{
				man_binary[y + 4][x + 2] = 255;
			}
			else
			{
				man_binary[y + 4][x + 2] = 0;
			}//3
			if (man_gray[y + 4][x + 3] >= TI8[4][3])
			{
				man_binary[y + 4][x + 3] = 255;
			}
			else
			{
				man_binary[y + 4][x + 3] = 0;
			}//4
			if (man_gray[y + 4][x + 4] >= TI8[4][4])
			{
				man_binary[y + 4][x + 4] = 255;
			}
			else
			{
				man_binary[y + 4][x + 4] = 0;
			}//5
			if (man_gray[y + 4][x + 5] >= TI8[4][5])
			{
				man_binary[y + 4][x + 5] = 255;
			}
			else
			{
				man_binary[y + 4][x + 5] = 0;
			}//6
			if (man_gray[y + 4][x + 6] >= TI8[4][6])
			{
				man_binary[y + 4][x + 6] = 255;
			}
			else
			{
				man_binary[y + 4][x + 6] = 0;
			}//7
			if (man_gray[y + 4][x + 7] >= TI8[4][7])
			{
				man_binary[y + 4][x + 7] = 255;
			}
			else
			{
				man_binary[y + 4][x + 7] = 0;
			}//8
			 //------//5
			if (man_gray[y + 5][x] >= TI8[5][0])
			{
				man_binary[y + 5][x] = 255;
			}
			else
			{
				man_binary[y + 5][x] = 0;
			}//1
			if (man_gray[y + 5][x + 1] >= TI8[5][1])
			{
				man_binary[y + 5][x + 1] = 255;
			}
			else
			{
				man_binary[y + 5][x + 1] = 0;
			}//2
			if (man_gray[y + 5][x + 2] >= TI8[5][2])
			{
				man_binary[y + 5][x + 2] = 255;
			}
			else
			{
				man_binary[y + 5][x + 2] = 0;
			}//3
			if (man_gray[y + 5][x + 3] >= TI8[5][3])
			{
				man_binary[y + 5][x + 3] = 255;
			}
			else
			{
				man_binary[y + 5][x + 3] = 0;
			}//4
			if (man_gray[y + 5][x + 4] >= TI8[5][4])
			{
				man_binary[y + 5][x + 4] = 255;
			}
			else
			{
				man_binary[y + 5][x + 4] = 0;
			}//5
			if (man_gray[y + 5][x + 5] >= TI8[5][5])
			{
				man_binary[y + 5][x + 5] = 255;
			}
			else
			{
				man_binary[y + 5][x + 5] = 0;
			}//6
			if (man_gray[y + 5][x + 6] >= TI8[5][6])
			{
				man_binary[y + 5][x + 6] = 255;
			}
			else
			{
				man_binary[y + 5][x + 6] = 0;
			}//7
			if (man_gray[y + 5][x + 7] >= TI8[5][7])
			{
				man_binary[y + 5][x + 7] = 255;
			}
			else
			{
				man_binary[y + 5][x + 7] = 0;
			}//8
			 //------//6
			if (man_gray[y + 6][x] >= TI8[6][0])
			{
				man_binary[y + 6][x] = 255;
			}
			else
			{
				man_binary[y + 6][x] = 0;
			}//1
			if (man_gray[y + 6][x + 1] >= TI8[6][1])
			{
				man_binary[y + 6][x + 1] = 255;
			}
			else
			{
				man_binary[y + 6][x + 1] = 0;
			}//2
			if (man_gray[y + 6][x + 2] >= TI8[6][2])
			{
				man_binary[y + 6][x + 2] = 255;
			}
			else
			{
				man_binary[y + 6][x + 2] = 0;
			}//3
			if (man_gray[y + 6][x + 3] >= TI8[6][3])
			{
				man_binary[y + 6][x + 3] = 255;
			}
			else
			{
				man_binary[y + 6][x + 3] = 0;
			}//4
			if (man_gray[y + 6][x + 4] >= TI8[6][4])
			{
				man_binary[y + 6][x + 4] = 255;
			}
			else
			{
				man_binary[y + 6][x + 4] = 0;
			}//5
			if (man_gray[y + 6][x + 5] >= TI8[6][5])
			{
				man_binary[y + 6][x + 5] = 255;
			}
			else
			{
				man_binary[y + 6][x + 5] = 0;
			}//6
			if (man_gray[y + 6][x + 6] >= TI8[6][6])
			{
				man_binary[y + 6][x + 6] = 255;
			}
			else
			{
				man_binary[y + 6][x + 6] = 0;
			}//7
			if (man_gray[y + 6][x + 7] >= TI8[6][7])
			{
				man_binary[y + 6][x + 7] = 255;
			}
			else
			{
				man_binary[y + 6][x + 7] = 0;
			}//8
			 //------//7
			if (man_gray[y + 7][x] >= TI8[7][0])
			{
				man_binary[y + 7][x] = 255;
			}
			else
			{
				man_binary[y + 7][x] = 0;
			}//1
			if (man_gray[y + 7][x + 1] >= TI8[7][1])
			{
				man_binary[y + 7][x + 1] = 255;
			}
			else
			{
				man_binary[y + 7][x + 1] = 0;
			}//2
			if (man_gray[y + 7][x + 2] >= TI8[7][2])
			{
				man_binary[y + 7][x + 2] = 255;
			}
			else
			{
				man_binary[y + 7][x + 2] = 0;
			}//3
			if (man_gray[y + 7][x + 3] >= TI8[7][3])
			{
				man_binary[y + 7][x + 3] = 255;
			}
			else
			{
				man_binary[y + 7][x + 3] = 0;
			}//4
			if (man_gray[y + 7][x + 4] >= TI8[7][4])
			{
				man_binary[y + 7][x + 4] = 255;
			}
			else
			{
				man_binary[y + 7][x + 4] = 0;
			}//5
			if (man_gray[y + 7][x + 5] >= TI8[7][5])
			{
				man_binary[y + 7][x + 5] = 255;
			}
			else
			{
				man_binary[y + 7][x + 5] = 0;
			}//6
			if (man_gray[y + 7][x + 6] >= TI8[7][6])
			{
				man_binary[y + 7][x + 6] = 255;
			}
			else
			{
				man_binary[y + 7][x + 6] = 0;
			}//7
			if (man_gray[y + 7][x + 7] >= TI8[7][7])
			{
				man_binary[y + 7][x + 7] = 255;
			}
			else
			{
				man_binary[y + 7][x + 7] = 0;
			}//8			
		}
	}
	//回到array输出
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			man_done[512 * y + x] = Zero_255_to_U8(man_binary[y][x]);
		}
	}
	fp_write = fopen("D:\\EE569image_hw2_p2\\output\\man_I8.raw", "wb");
	if (fp_write == NULL)
	{
		printf("\nFail to create the file.");
	}
	else
	{
		printf("\nScuess to create the file.");
	}
	fwrite(man_done, sizeof(unsigned char), 512 * 512, fp_write);
	fclose(fp_write);
	printf("\n\nman_I8...done...\n.");
//------------------第三部分，part#2.1 ，I4 处理------------------//
    //I4
	for (int y = 0; y < 512; y += 4)
	{
		for (int x = 0; x < 512; x += 4)
		{
			if (man_gray[y][x] >= TI4[0][0])
			{
				man_binary[y][x] = 255;
			}
			else
			{
				man_binary[y][x] = 0;
			}
			if (man_gray[y][x + 1] >= TI4[0][1])
			{
				man_binary[y][x + 1] = 255;
			}
			else
			{
				man_binary[y][x + 1] = 0;
			}
			if (man_gray[y][x + 2] >= TI4[0][2])
			{
				man_binary[y][x + 2] = 255;
			}
			else
			{
				man_binary[y][x + 2] = 0;
			}
			if (man_gray[y][x + 3] >= TI4[0][3])
			{
				man_binary[y][x + 3] = 255;
			}
			else
			{
				man_binary[y][x + 3] = 0;
			}
			//-----//
			if (man_gray[y + 1][x] >= TI4[1][0])
			{
				man_binary[y + 1][x] = 255;
			}
			else
			{
				man_binary[y + 1][x] = 0;
			}
			if (man_gray[y + 1][x + 1] >= TI4[1][1])
			{
				man_binary[y + 1][x + 1] = 255;
			}
			else
			{
				man_binary[y + 1][x + 1] = 0;
			}
			if (man_gray[y + 1][x + 2] >= TI4[1][2])
			{
				man_binary[y + 1][x + 2] = 255;
			}
			else
			{
				man_binary[y + 1][x + 2] = 0;
			}
			if (man_gray[y + 1][x + 3] >= TI4[1][3])
			{
				man_binary[y + 1][x + 3] = 255;
			}
			else
			{
				man_binary[y + 1][x + 3] = 0;
			}
			//-----//
			if (man_gray[y + 2][x] >= TI4[2][0])
			{
				man_binary[y + 2][x] = 255;
			}
			else
			{
				man_binary[y + 2][x] = 0;
			}
			if (man_gray[y + 2][x + 1] >= TI4[2][1])
			{
				man_binary[y + 2][x + 1] = 255;
			}
			else
			{
				man_binary[y + 2][x + 1] = 0;
			}
			if (man_gray[y + 2][x + 2] >= TI4[2][2])
			{
				man_binary[y + 2][x + 2] = 255;
			}
			else
			{
				man_binary[y + 2][x + 2] = 0;
			}
			if (man_gray[y + 2][x + 3] >= TI4[2][3])
			{
				man_binary[y + 2][x + 3] = 255;
			}
			else
			{
				man_binary[y + 2][x + 3] = 0;
			}
			//-----//
			if (man_gray[y + 3][x] >= TI4[3][0])
			{
				man_binary[y + 3][x] = 255;
			}
			else
			{
				man_binary[y + 3][x] = 0;
			}
			if (man_gray[y + 3][x + 1] >= TI4[3][1])
			{
				man_binary[y + 3][x + 1] = 255;
			}
			else
			{
				man_binary[y + 3][x + 1] = 0;
			}
			if (man_gray[y + 3][x + 2] >= TI4[3][2])
			{
				man_binary[y + 3][x + 2] = 255;
			}
			else
			{
				man_binary[y + 3][x + 2] = 0;
			}
			if (man_gray[y + 3][x + 3] >= TI4[3][3])
			{
				man_binary[y + 3][x + 3] = 255;
			}
			else
			{
				man_binary[y + 3][x + 3] = 0;
			}
		}
	}
	//回到array输出
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			man_done[512 * y + x] = Zero_255_to_U8(man_binary[y][x]);
		}
	}
	fp_write = fopen("D:\\EE569image_hw2_p2\\output\\man_I4.raw", "wb");
	if (fp_write == NULL)
	{
		printf("\nFail to create the file.");
	}
	else
	{
		printf("\nScuess to create the file.");
	}
	fwrite(man_done, sizeof(unsigned char), 512 * 512, fp_write);
	fclose(fp_write);
	printf("\n\nman_I4...done...\n.");
//------------------第三部分，part#2.2 ，A4 处理------------------//
	//A4
	for (int y = 0; y < 512; y += 4)
	{
		for (int x = 0; x < 512; x += 4)
		{
			if (man_gray[y][x] >= TA4[0][0])
			{
				man_binary[y][x] = 255;
			}
			else
			{
				man_binary[y][x] = 0;
			}
			if (man_gray[y][x + 1] >= TA4[0][1])
			{
				man_binary[y][x + 1] = 255;
			}
			else
			{
				man_binary[y][x + 1] = 0;
			}
			if (man_gray[y][x + 2] >= TA4[0][2])
			{
				man_binary[y][x + 2] = 255;
			}
			else
			{
				man_binary[y][x + 2] = 0;
			}
			if (man_gray[y][x + 3] >= TA4[0][3])
			{
				man_binary[y][x + 3] = 255;
			}
			else
			{
				man_binary[y][x + 3] = 0;
			}
			//-----//
			if (man_gray[y + 1][x] >= TA4[1][0])
			{
				man_binary[y + 1][x] = 255;
			}
			else
			{
				man_binary[y + 1][x] = 0;
			}
			if (man_gray[y + 1][x + 1] >= TA4[1][1])
			{
				man_binary[y + 1][x + 1] = 255;
			}
			else
			{
				man_binary[y + 1][x + 1] = 0;
			}
			if (man_gray[y + 1][x + 2] >= TA4[1][2])
			{
				man_binary[y + 1][x + 2] = 255;
			}
			else
			{
				man_binary[y + 1][x + 2] = 0;
			}
			if (man_gray[y + 1][x + 3] >= TA4[1][3])
			{
				man_binary[y + 1][x + 3] = 255;
			}
			else
			{
				man_binary[y + 1][x + 3] = 0;
			}
			//-----//
			if (man_gray[y + 2][x] >= TA4[2][0])
			{
				man_binary[y + 2][x] = 255;
			}
			else
			{
				man_binary[y + 2][x] = 0;
			}
			if (man_gray[y + 2][x + 1] >= TA4[2][1])
			{
				man_binary[y + 2][x + 1] = 255;
			}
			else
			{
				man_binary[y + 2][x + 1] = 0;
			}
			if (man_gray[y + 2][x + 2] >= TA4[2][2])
			{
				man_binary[y + 2][x + 2] = 255;
			}
			else
			{
				man_binary[y + 2][x + 2] = 0;
			}
			if (man_gray[y + 2][x + 3] >= TA4[2][3])
			{
				man_binary[y + 2][x + 3] = 255;
			}
			else
			{
				man_binary[y + 2][x + 3] = 0;
			}
			//-----//
			if (man_gray[y + 3][x] >= TA4[3][0])
			{
				man_binary[y + 3][x] = 255;
			}
			else
			{
				man_binary[y + 3][x] = 0;
			}
			if (man_gray[y + 3][x + 1] >= TA4[3][1])
			{
				man_binary[y + 3][x + 1] = 255;
			}
			else
			{
				man_binary[y + 3][x + 1] = 0;
			}
			if (man_gray[y + 3][x + 2] >= TA4[3][2])
			{
				man_binary[y + 3][x + 2] = 255;
			}
			else
			{
				man_binary[y + 3][x + 2] = 0;
			}
			if (man_gray[y + 3][x + 3] >= TA4[3][3])
			{
				man_binary[y + 3][x + 3] = 255;
			}
			else
			{
				man_binary[y + 3][x + 3] = 0;
			}
		}
	}
	//回到array输出
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			man_done[512 * y + x] = Zero_255_to_U8(man_binary[y][x]);
		}
	}
	fp_write = fopen("D:\\EE569image_hw2_p2\\output\\man_A4.raw", "wb");
	if (fp_write == NULL)
	{
		printf("\nFail to create the file.");
	}
	else
	{
		printf("\nScuess to create the file.");
	}
	fwrite(man_done, sizeof(unsigned char), 512 * 512, fp_write);
	fclose(fp_write);
	printf("\n\nman_A4...done...\n.");
//------------------第三部分，part#3 ，4阶 处理------------------//
	
	for (int y = 0; y < 512; y += 4)
	{
		for (int x = 0; x < 512; x += 4)
		{   
			if (Data_transform(man_gray[y][x]) > TI4[0][0]) 
			{   
				bool lord = true;
				man_binary[y][x] = Set_gray(Region_indicator(man_gray[y][x]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y][x] = Set_gray(Region_indicator(man_gray[y][x]), lord);
			}
			if (Data_transform(man_gray[y][x + 1]) > TI4[0][1])
			{
				bool lord = true;
				man_binary[y][x + 1] = Set_gray(Region_indicator(man_gray[y][x + 1]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y][x + 1] = Set_gray(Region_indicator(man_gray[y][x + 1]), lord);
			}
			if (Data_transform(man_gray[y][x + 2]) > TI4[0][2])
			{
				bool lord = true;
				man_binary[y][x + 2] = Set_gray(Region_indicator(man_gray[y][x + 2]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y][x + 2] = Set_gray(Region_indicator(man_gray[y][x + 2]), lord);
			}
			if (Data_transform(man_gray[y][x + 3]) > TI4[0][3])
			{
				bool lord = true;
				man_binary[y][x + 3] = Set_gray(Region_indicator(man_gray[y][x + 3]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y][x + 3] = Set_gray(Region_indicator(man_gray[y][x + 3]), lord);
			}
			//-----//
			if (Data_transform(man_gray[y + 1][x]) > TI4[1][0])
			{
				bool lord = true;
				man_binary[y + 1][x] = Set_gray(Region_indicator(man_gray[y + 1][x]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 1][x] = Set_gray(Region_indicator(man_gray[y + 1][x]), lord);
			}
			if (Data_transform(man_gray[y + 1][x + 1]) > TI4[1][1])
			{
				bool lord = true;
				man_binary[y + 1][x + 1] = Set_gray(Region_indicator(man_gray[y + 1][x + 1]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 1][x + 1] = Set_gray(Region_indicator(man_gray[y + 1][x + 1]), lord);
			}
			if (Data_transform(man_gray[y + 1][x + 2]) > TI4[1][2])
			{
				bool lord = true;
				man_binary[y + 1][x + 2] = Set_gray(Region_indicator(man_gray[y + 1][x + 2]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 1][x + 2] = Set_gray(Region_indicator(man_gray[y + 1][x + 2]), lord);
			}
			if (Data_transform(man_gray[y + 1][x + 3]) > TI4[1][3])
			{
				bool lord = true;
				man_binary[y + 1][x + 3] = Set_gray(Region_indicator(man_gray[y + 1][x + 3]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 1][x + 3] = Set_gray(Region_indicator(man_gray[y + 1][x + 3]), lord);
			}
			//-----//
			if (Data_transform(man_gray[y + 2][x]) > TI4[2][0])
			{
				bool lord = true;
				man_binary[y + 2][x] = Set_gray(Region_indicator(man_gray[y + 2][x]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 2][x] = Set_gray(Region_indicator(man_gray[y + 2][x]), lord);
			}
			if (Data_transform(man_gray[y + 2][x + 1]) > TI4[2][1])
			{
				bool lord = true;
				man_binary[y + 2][x + 1] = Set_gray(Region_indicator(man_gray[y + 2][x + 1]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 2][x + 1] = Set_gray(Region_indicator(man_gray[y + 2][x + 1]), lord);
			}
			if (Data_transform(man_gray[y + 2][x + 2]) > TI4[2][2])
			{
				bool lord = true;
				man_binary[y + 2][x + 2] = Set_gray(Region_indicator(man_gray[y + 2][x + 2]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 2][x + 2] = Set_gray(Region_indicator(man_gray[y + 2][x + 2]), lord);
			}
			if (Data_transform(man_gray[y + 2][x + 3]) > TI4[2][3])
			{
				bool lord = true;
				man_binary[y + 2][x + 3] = Set_gray(Region_indicator(man_gray[y + 2][x + 3]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 2][x + 3] = Set_gray(Region_indicator(man_gray[y + 2][x + 3]), lord);
			}
			//-----//
			if (Data_transform(man_gray[y + 3][x]) > TI4[3][0])
			{
				bool lord = true;
				man_binary[y + 3][x] = Set_gray(Region_indicator(man_gray[y + 3][x]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 3][x] = Set_gray(Region_indicator(man_gray[y + 3][x]), lord);
			}
			if (Data_transform(man_gray[y + 3][x + 1]) > TI4[3][1])
			{
				bool lord = true;
				man_binary[y + 3][x + 1] = Set_gray(Region_indicator(man_gray[y + 3][x + 1]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 3][x + 1] = Set_gray(Region_indicator(man_gray[y + 3][x + 1]), lord);
			}
			if (Data_transform(man_gray[y + 3][x + 2]) > TI4[3][2])
			{
				bool lord = true;
				man_binary[y + 3][x + 2] = Set_gray(Region_indicator(man_gray[y + 3][x + 2]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 3][x + 2] = Set_gray(Region_indicator(man_gray[y + 3][x + 2]), lord);
			}
			if (Data_transform(man_gray[y + 3][x + 3]) > TI4[3][3])
			{
				bool lord = true;
				man_binary[y + 3][x + 3] = Set_gray(Region_indicator(man_gray[y + 3][x + 3]), lord);
			}
			else
			{
				bool lord = false;
				man_binary[y + 3][x + 3] = Set_gray(Region_indicator(man_gray[y + 3][x + 3]), lord);
			}
		}
	}
	//回到array输出
	for (int y = 0; y < 512; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			man_done[512 * y + x] = Zero_255_to_U8(man_binary[y][x]);
		}
	}
	fp_write = fopen("D:\\EE569image_hw2_p2\\output\\man_quad_gray_levels.raw", "wb");
	if (fp_write == NULL)
	{
		printf("\nFail to create the file.");
	}
	else
	{
		printf("\nScuess to create the file.");
	}
	fwrite(man_done, sizeof(unsigned char), 512 * 512, fp_write);
	fclose(fp_write);
	printf("\n\nman_quad_gray_levels...done...\n.");


}
