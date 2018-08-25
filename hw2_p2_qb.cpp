#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "convert_data_brutal.h"
#include "hw2_p2_qb.h"
#include "border.h"

double Restrict_to_0_1(double x) 
{
	if (x > 1.0) 
	{
		return 1;
	}
	else if (x < 0.0) 
	{
		return 0.0;
	}
	else 
	{
		return x;
	}

}


void Error_diffusion(void) 
{

//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//
//第一部分，预处理man图像，读取，转换
	double threshold = 0.5;
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
	fread(man, sizeof(unsigned char), 512 * 512, fp_read);
	fclose(fp_read);
	printf("\nman.raw in memeory.");
	//化成归一数组
	double man_gray[512 * 512];
	for (int i = 0; i < 512 * 512; i++)
	{	
		man_gray[i] = (double)(U8_to_0_255(man[i])) / 255.0;		
	}
//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//
//第二部分，准备Error矩阵
	double FSED1[3][3] = { {0,0,0},{0,0,7},{3,5,1} };
	double FSED2[3][3] = { {0,0,0},{7,0,0},{1,5,3} };
	for (int y = 0; y < 3; y++) 
	{
		for (int x = 0; x < 3; x++) 
		{
			FSED1[y][x] = FSED1[y][x] / 16.0;
			FSED2[y][x] = FSED2[y][x] / 16.0;
		}
	}
	double JJNED1[5][5] = { {0,0,0,0,0},
						    {0,0,0,0,0},
						    {0,0,0,7,5},
						    {3,5,7,5,3},
						    {1,3,5,3,1} };
	double JJNED2[5][5] = { { 0,0,0,0,0 },
	                        { 0,0,0,0,0 },
	                        { 5,7,0,0,0 },
	                        { 3,5,7,5,3 },
	                        { 1,3,5,3,1 } };
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			JJNED1[y][x] = JJNED1[y][x] / 48.0;
			JJNED2[y][x] = JJNED2[y][x] / 48.0;
		}
	}
	double STUCKIED1[5][5] = { { 0,0,0,0,0 },
	                           { 0,0,0,0,0 },
	                           { 0,0,0,8,4 },
	                           { 2,4,8,4,2 },
	                           { 1,2,4,2,1 } };
	double STUCKIED2[5][5] = { { 0,0,0,0,0 },
	                           { 0,0,0,0,0 },
	                           { 4,8,0,0,0 },
	                           { 2,4,8,4,2 },
	                           { 1,2,4,2,1 } };
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			STUCKIED1[y][x] = STUCKIED1[y][x] / 42.0;
			STUCKIED2[y][x] = STUCKIED2[y][x] / 42.0;
		}
	}
	double N1[5][5] = { {0,0,0,0,0},
						   {0,0,0,0,0},
						   {0,0,0,4,2},
						   {1,2,4,2,1},
						   {0,0,0,0,0} };
	double N2[5][5] = { { 0,0,0,0,0 },
	                    { 0,0,0,0,0 },
	                    { 2,4,0,0,0 },
	                    { 1,2,4,2,1 },
	                    { 0,0,0,0,0 } };
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			N1[y][x] = N1[y][x] / 16.0;
			N2[y][x] = N2[y][x] / 16.0;
		}
	}



//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//***//
//第三部分，准备扩边矩阵备用
	double man_gray_1[514 * 514];
	double man_gray_2[516 * 516];
	double man_gray_3[516 * 516];
	double man_gray_4[516 * 516];
	double temp[514 * 514];
	Border_extend_double(man_gray, man_gray_1, 512, 512);
	Border_extend_double(man_gray, temp, 512, 512);
	Border_extend_double(temp, man_gray_2, 514, 514);
	Border_extend_double(temp, man_gray_3, 514, 514);
	Border_extend_double(temp, man_gray_4, 514, 514);
	double man_gray_matrix_1[514][514];
	for (int y = 1; y <= 513; y++)
	{
		for (int x = 0; x < 514; x++)
		{   		
			man_gray_matrix_1[y][x] = 1.0 - (double)(y - 1)/512.0;
			//printf("\n %lf", man_gray_matrix_1[y][x]);
		}
	}
	for (int y = 0; y < 514; y++)
	{
		for (int x = 0; x < 514; x++)
		{   		
			man_gray_matrix_1[y][x] = man_gray_1[514 * y + x];
			//printf("\n %lf", man_gray_matrix_1[y][x]);
		}
	}
	double man_gray_matrix_2[516][516];
	for (int y = 2; y <= 514; y++)
	{
		for (int x = 0; x < 516; x++)
		{
			man_gray_matrix_2[y][x] = 1.0 - (double)(y - 1) / 512.0;
			//printf("\n %lf", man_gray_matrix_1[y][x]);
		}
	}
	for (int y = 0; y < 516; y++)
	{
		for (int x = 0; x < 516; x++)
		{
			man_gray_matrix_2[y][x] = man_gray_2[516 * y + x];
		}
	}
	double man_gray_matrix_3[516][516];
	for (int y = 2; y <= 514; y++)
	{
		for (int x = 0; x < 516; x++)
		{
			man_gray_matrix_3[y][x] = 1.0 - (double)(y - 1) / 512.0;
			//printf("\n %lf", man_gray_matrix_1[y][x]);
		}
	}
	for (int y = 0; y < 516; y++)
	{
		for (int x = 0; x < 516; x++)
		{
			man_gray_matrix_3[y][x] = man_gray_3[516 * y + x];
		}
	}
	double man_gray_matrix_4[516][516];
	for (int y = 2; y <= 514; y++)
	{
		for (int x = 0; x < 516; x++)
		{
			man_gray_matrix_4[y][x] = 1.0 - (double)(y - 1) / 512.0;
			//printf("\n %lf", man_gray_matrix_1[y][x]);
		}
	}
	for (int y = 0; y < 516; y++)
	{
		for (int x = 0; x < 516; x++)
		{
			man_gray_matrix_4[y][x] = man_gray_4[516 * y + x];
		}
	}
	int man_binary[512][512];
	unsigned char man_done[512 * 512];

//------------------第四部分，part#1 ，FSED 处理------------------//	
	double error = 0.0;
	double temp1 = 0.0;	
	for (int y = 1; y <= 512; y++) 
	{
		for (int x = 1; x <= 512; x++) 
		{   
			
            if (y % 2 == 1) //用FSED1
			{   
				temp1 = man_gray_matrix_1[y][x];
				if (man_gray_matrix_1[y][x] > threshold) 
				{  
					man_gray_matrix_1[y][x] = 1;
					error = temp1 - 1.0;
				}
				else
				{
					man_gray_matrix_1[y][x] = 0;
					error = temp1 - 0.0;
				}//得到error		
				man_gray_matrix_1[y][x + 1] += FSED1[1][2] * error;
				man_gray_matrix_1[y + 1][x - 1] += FSED1[2][0] * error;
				man_gray_matrix_1[y + 1][x] += FSED1[2][1] * error;
				man_gray_matrix_1[y + 1][x + 1] += FSED1[2][2] * error;
				//限制
				/*man_gray_matrix_1[y][x + 1] = Restrict_to_0_1(man_gray_matrix_1[y][x + 1]);
				man_gray_matrix_1[y + 1][x - 1] = Restrict_to_0_1(man_gray_matrix_1[y + 1][x - 1]);
				man_gray_matrix_1[y + 1][x] = Restrict_to_0_1(man_gray_matrix_1[y + 1][x]);
				man_gray_matrix_1[y + 1][x + 1] = Restrict_to_0_1(man_gray_matrix_1[y + 1][x + 1]); */
			}
			else//用FSED2
			{
				temp1 = man_gray_matrix_1[y][513 - x];
				if (man_gray_matrix_1[y][513 - x] > threshold)
				{
					man_gray_matrix_1[y][513 - x] = 1;
					error = temp1 - 1.0;
				}
				else
				{
					man_gray_matrix_1[y][513 - x] = 0;
					error = temp1 - 0.0;
				}//得到error	
				man_gray_matrix_1[y][512 - x] += FSED2[1][0] * error;
				man_gray_matrix_1[y + 1][512 - x] += FSED2[2][0] * error;
				man_gray_matrix_1[y + 1][513 - x] += FSED2[2][1] * error;
				man_gray_matrix_1[y + 1][514 - x] += FSED2[2][2] * error;
				//限制
				/*man_gray_matrix_1[y][512 - x] = Restrict_to_0_1(man_gray_matrix_1[y][512 - x]);
				man_gray_matrix_1[y + 1][512 - x] = Restrict_to_0_1(man_gray_matrix_1[y + 1][512 - x]);
				man_gray_matrix_1[y + 1][513 - x] = Restrict_to_0_1(man_gray_matrix_1[y + 1][513 - x]);
				man_gray_matrix_1[y + 1][514 - x] = Restrict_to_0_1(man_gray_matrix_1[y + 1][514 - x]);*/
			}
		}
	}
	for (int y = 1; y <= 512; y++) 
	{
		for (int x = 1; x <= 512; x++) 
		{   
			if (man_gray_matrix_1[y][x] == 0) 
			{
				man_binary[y - 1][x - 1] = 0;
			}
			else 
			{
				man_binary[y - 1][x - 1] = 255;
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
	FILE *fp_write = fopen("D:\\EE569image_hw2_p2\\output\\man_error_fsed.raw", "wb");
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
	printf("\n\nman_error_fsed...done...\n.");

	
//------------------第四部分，part#2 ，JJNED 处理------------------//	
	for (int y = 2; y <= 513; y++)
	{
		for (int x = 2; x <= 513; x++)
		{

			if (y % 2 == 0) //用JJNED1
			{
				temp1 = man_gray_matrix_2[y][x];
				if (man_gray_matrix_2[y][x] > threshold)
				{
					man_gray_matrix_2[y][x] = 1;
					error = temp1 - 1;
				}
				else
				{
					man_gray_matrix_2[y][x] = 0;
					error = temp1 - 0;
				}//得到error		
				man_gray_matrix_2[y][x + 1] += JJNED1[2][3] * error;
				man_gray_matrix_2[y][x + 2] += JJNED1[2][4] * error;
				man_gray_matrix_2[y + 1][x - 2] += JJNED1[3][0] * error;
				man_gray_matrix_2[y + 1][x - 1] += JJNED1[3][1] * error;
				man_gray_matrix_2[y + 1][x] += JJNED1[3][2] * error;
				man_gray_matrix_2[y + 1][x + 1] += JJNED1[3][3] * error;
				man_gray_matrix_2[y + 1][x + 2] += JJNED1[3][4] * error;
				man_gray_matrix_2[y + 2][x - 2] += JJNED1[4][0] * error;
				man_gray_matrix_2[y + 2][x - 1] += JJNED1[4][1] * error;
				man_gray_matrix_2[y + 2][x] += JJNED1[4][2] * error;
				man_gray_matrix_2[y + 2][x + 1] += JJNED1[4][3] * error;
				man_gray_matrix_2[y + 2][x + 2] += JJNED1[4][4] * error;
				//限制
				/*man_gray_matrix_2[y][x + 1] = Restrict_to_0_1(man_gray_matrix_2[y][x + 1]);
				man_gray_matrix_2[y][x + 2] = Restrict_to_0_1(man_gray_matrix_2[y][x + 2]);
				man_gray_matrix_2[y + 1][x - 2] = Restrict_to_0_1(man_gray_matrix_2[y + 1][x - 2]);
				man_gray_matrix_2[y + 1][x - 1] = Restrict_to_0_1(man_gray_matrix_2[y + 1][x - 1]);
				man_gray_matrix_2[y + 1][x] = Restrict_to_0_1(man_gray_matrix_2[y + 1][x]);
				man_gray_matrix_2[y + 1][x + 1] = Restrict_to_0_1(man_gray_matrix_2[y + 1][x + 1]);
				man_gray_matrix_2[y + 1][x + 2] = Restrict_to_0_1(man_gray_matrix_2[y + 1][x + 2]);
				man_gray_matrix_2[y + 2][x - 2] = Restrict_to_0_1(man_gray_matrix_2[y + 2][x - 2]);
				man_gray_matrix_2[y + 2][x - 1] = Restrict_to_0_1(man_gray_matrix_2[y + 2][x - 1]);
				man_gray_matrix_2[y + 2][x] = Restrict_to_0_1(man_gray_matrix_2[y + 2][x]);
				man_gray_matrix_2[y + 2][x + 1] = Restrict_to_0_1(man_gray_matrix_2[y + 2][x + 1]);
				man_gray_matrix_2[y + 2][x + 2] = Restrict_to_0_1(man_gray_matrix_2[y + 2][x + 2]);*/
			}
			else//用JJNED2
			{
				temp1 = man_gray_matrix_2[y][515 - x];
				if (man_gray_matrix_2[y][515 - x] > threshold)
				{
					man_gray_matrix_2[y][515 - x] = 1;
					error = temp1 - 1;
				}
				else
				{
					man_gray_matrix_2[y][515 - x] = 0;
					error = temp1 - 0;
				}//得到error	
				man_gray_matrix_2[y][513 - x] += JJNED2[2][0] * error;
				man_gray_matrix_2[y][514 - x] += JJNED2[2][1] * error;
				man_gray_matrix_2[y + 1][513 - x] += JJNED2[3][0] * error;
				man_gray_matrix_2[y + 1][514 - x] += JJNED2[3][1] * error;
				man_gray_matrix_2[y + 1][515 - x] += JJNED2[3][2] * error;
				man_gray_matrix_2[y + 1][516 - x] += JJNED2[3][3] * error;
				man_gray_matrix_2[y + 1][517 - x] += JJNED2[3][4] * error;
				man_gray_matrix_2[y + 2][513 - x] += JJNED2[4][0] * error;
				man_gray_matrix_2[y + 2][514 - x] += JJNED2[4][1] * error;
				man_gray_matrix_2[y + 2][515 - x] += JJNED2[4][2] * error;
				man_gray_matrix_2[y + 2][516 - x] += JJNED2[4][3] * error;
				man_gray_matrix_2[y + 2][517 - x] += JJNED2[4][4] * error;
				////限制
				//man_gray_matrix_2[y][513 - x] = Restrict_to_0_1(man_gray_matrix_2[y][513 - x]);
				//man_gray_matrix_2[y][514 - x] = Restrict_to_0_1(man_gray_matrix_2[y][514 - x]);
				//man_gray_matrix_2[y + 1][513 - x] = Restrict_to_0_1(man_gray_matrix_2[y + 1][513 - x]);
				//man_gray_matrix_2[y + 1][514 - x] = Restrict_to_0_1(man_gray_matrix_2[y + 1][514 - x]);
				//man_gray_matrix_2[y + 1][515 - x] = Restrict_to_0_1(man_gray_matrix_2[y + 1][515 - x]);
				//man_gray_matrix_2[y + 1][516 - x] = Restrict_to_0_1(man_gray_matrix_2[y + 1][516 - x]);
				//man_gray_matrix_2[y + 1][517 - x] = Restrict_to_0_1(man_gray_matrix_2[y + 1][517 - x]);
				//man_gray_matrix_2[y + 2][513 - x] = Restrict_to_0_1(man_gray_matrix_2[y + 2][513 - x]);
				//man_gray_matrix_2[y + 2][514 - x] = Restrict_to_0_1(man_gray_matrix_2[y + 2][514 - x]);
				//man_gray_matrix_2[y + 2][515 - x] = Restrict_to_0_1(man_gray_matrix_2[y + 2][515 - x]);
				//man_gray_matrix_2[y + 2][516 - x] = Restrict_to_0_1(man_gray_matrix_2[y + 2][516 - x]);
				//man_gray_matrix_2[y + 2][517 - x] = Restrict_to_0_1(man_gray_matrix_2[y + 2][517 - x]);

			}
		}
	}
	for (int y = 2; y <= 513; y++)
	{
		for (int x = 2; x <= 513; x++)
		{
			if (man_gray_matrix_2[y][x] == 0)
			{
				man_binary[y - 2][x - 2] = 0;
			}
			else
			{
				man_binary[y - 2][x - 2] = 255;
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
	fp_write = fopen("D:\\EE569image_hw2_p2\\output\\man_error_jjned.raw", "wb");
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
	printf("\n\nman_error_jjned...done...\n.");

//------------------第四部分，part#3 ，STUCKI 处理------------------//	
	for (int y = 2; y <= 513; y++)
	{
		for (int x = 2; x <= 513; x++)
		{

			if (y % 2 == 0) //用STUCKIED1
			{
				temp1 = man_gray_matrix_3[y][x];
				if (man_gray_matrix_3[y][x] > threshold)
				{
					man_gray_matrix_3[y][x] = 1;
					error = temp1 - 1;
				}
				else
				{
					man_gray_matrix_3[y][x] = 0;
					error = temp1 - 0;
				}//得到error		
				man_gray_matrix_3[y][x + 1] += STUCKIED1[2][3] * error;
				man_gray_matrix_3[y][x + 2] += STUCKIED1[2][4] * error;
				man_gray_matrix_3[y + 1][x - 2] += STUCKIED1[3][0] * error;
				man_gray_matrix_3[y + 1][x - 1] += STUCKIED1[3][1] * error;
				man_gray_matrix_3[y + 1][x] += STUCKIED1[3][2] * error;
				man_gray_matrix_3[y + 1][x + 1] += STUCKIED1[3][3] * error;
				man_gray_matrix_3[y + 1][x + 2] += STUCKIED1[3][4] * error;
				man_gray_matrix_3[y + 2][x - 2] += STUCKIED1[4][0] * error;
				man_gray_matrix_3[y + 2][x - 1] += STUCKIED1[4][1] * error;
				man_gray_matrix_3[y + 2][x] += STUCKIED1[4][2] * error;
				man_gray_matrix_3[y + 2][x + 1] += STUCKIED1[4][3] * error;
				man_gray_matrix_3[y + 2][x + 2] += STUCKIED1[4][4] * error;
			}
			else//用STUCKIED2
			{
				temp1 = man_gray_matrix_3[y][515 - x];
				if (man_gray_matrix_3[y][515 - x] > threshold)
				{
					man_gray_matrix_3[y][515 - x] = 1;
					error = temp1 - 1;
				}
				else
				{
					man_gray_matrix_3[y][515 - x] = 0;
					error = temp1 - 0;
				}//得到error	
				man_gray_matrix_3[y][513 - x] += STUCKIED2[2][0] * error;
				man_gray_matrix_3[y][514 - x] += STUCKIED2[2][1] * error;
				man_gray_matrix_3[y + 1][513 - x] += STUCKIED2[3][0] * error;
				man_gray_matrix_3[y + 1][514 - x] += STUCKIED2[3][1] * error;
				man_gray_matrix_3[y + 1][515 - x] += STUCKIED2[3][2] * error;
				man_gray_matrix_3[y + 1][516 - x] += STUCKIED2[3][3] * error;
				man_gray_matrix_3[y + 1][517 - x] += STUCKIED2[3][4] * error;
				man_gray_matrix_3[y + 2][513 - x] += STUCKIED2[4][0] * error;
				man_gray_matrix_3[y + 2][514 - x] += STUCKIED2[4][1] * error;
				man_gray_matrix_3[y + 2][515 - x] += STUCKIED2[4][2] * error;
				man_gray_matrix_3[y + 2][516 - x] += STUCKIED2[4][3] * error;
				man_gray_matrix_3[y + 2][517 - x] += STUCKIED2[4][4] * error;
			}
		}
	}
	for (int y = 2; y <= 513; y++)
	{
		for (int x = 2; x <= 513; x++)
		{
			if (man_gray_matrix_3[y][x] == 0)
			{
				man_binary[y - 2][x - 2] = 0;
			}
			else
			{
				man_binary[y - 2][x - 2] = 255;
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
	fp_write = fopen("D:\\EE569image_hw2_p2\\output\\man_error_stuckied.raw", "wb");
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
	printf("\n\nman_error_stuckied...done...\n.");

	//------------------第四部分，part#4 ，N 处理------------------//	
	for (int y = 2; y <= 513; y++)
	{
		for (int x = 2; x <= 513; x++)
		{

			if (y % 2 == 0) //N1
			{
				temp1 = man_gray_matrix_4[y][x];
				if (man_gray_matrix_4[y][x] > threshold)
				{
					man_gray_matrix_4[y][x] = 1;
					error = temp1 - 1;
				}
				else
				{
					man_gray_matrix_4[y][x] = 0;
					error = temp1 - 0;
				}//得到error		
				man_gray_matrix_4[y][x + 1] += N1[2][3] * error;
				man_gray_matrix_4[y][x + 2] += N1[2][4] * error;
				man_gray_matrix_4[y + 1][x - 2] += N1[3][0] * error;
				man_gray_matrix_4[y + 1][x - 1] += N1[3][1] * error;
				man_gray_matrix_4[y + 1][x] += N1[3][2] * error;
				man_gray_matrix_4[y + 1][x + 1] += N1[3][3] * error;
				man_gray_matrix_4[y + 1][x + 2] += N1[3][4] * error;
			}
			else//用STUCKIED2
			{
				temp1 = man_gray_matrix_4[y][515 - x];
				if (man_gray_matrix_4[y][515 - x] > threshold)
				{
					man_gray_matrix_4[y][515 - x] = 1;
					error = temp1 - 1;
				}
				else
				{
					man_gray_matrix_4[y][515 - x] = 0;
					error = temp1 - 0;
				}//得到error	
				man_gray_matrix_4[y][513 - x] += N2[2][0] * error;
				man_gray_matrix_4[y][514 - x] += N2[2][1] * error;
				man_gray_matrix_4[y + 1][513 - x] += N2[3][0] * error;
				man_gray_matrix_4[y + 1][514 - x] += N2[3][1] * error;
				man_gray_matrix_4[y + 1][515 - x] += N2[3][2] * error;
				man_gray_matrix_4[y + 1][516 - x] += N2[3][3] * error;
				man_gray_matrix_4[y + 1][517 - x] += N2[3][4] * error;
			}
		}
	}
	for (int y = 2; y <= 513; y++)
	{
		for (int x = 2; x <= 513; x++)
		{
			if (man_gray_matrix_4[y][x] == 0)
			{
				man_binary[y - 2][x - 2] = 0;
			}
			else
			{
				man_binary[y - 2][x - 2] = 255;
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
	fp_write = fopen("D:\\EE569image_hw2_p2\\output\\man_error_N.raw", "wb");
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
	printf("\n\nman_error_N...done...\n.");





}


