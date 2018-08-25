//Date:February 3,2017
//Name:Tian Ye
//ID:2581-2031-06
//Email:tye459@usc.edu


#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "convert_data_brutal.h"


int U8_to_0_255(unsigned char cmos_data)
{
	if (cmos_data == 0x00) 
	{
		return 0;
	}
	if (cmos_data == 0x01) 
	{
		return 1;
	}
	if (cmos_data == 0x02)
	{
		return 2;
	}
	if (cmos_data == 0x03)
	{
		return 3;
	}
	if (cmos_data == 0x04)
	{
		return 4;
	}
	if (cmos_data == 0x05)
	{
		return 5;
	}
	if (cmos_data == 0x06)
	{
		return 6;
	}
	if (cmos_data == 0x07)
	{
		return 7;
	}
	if (cmos_data == 0x08)
	{
		return 8;
	}
	if (cmos_data == 0x09)
	{
		return 9;
	}
	if (cmos_data == 0x0A)
	{
		return 10;
	}
	if (cmos_data == 0x0B)
	{
		return 11;
	}
	if (cmos_data == 0x0C)
	{
		return 12;
	}
	if (cmos_data == 0x0D)
	{
		return 13;
	}
	if (cmos_data == 0x0E)
	{
        return 14;
	}
	if (cmos_data == 0x0F)
	{
		return 15;
	}
	if (cmos_data == 0x10)
	{
		return 16;
	}
	if (cmos_data == 0x11)
	{
		return 17;
	}
	if (cmos_data == 0x12)
	{
		return 18;
	}
	if (cmos_data == 0x13)
	{
		return 19;
	}
	if (cmos_data == 0x14)
	{
		return 20;
	}
	if (cmos_data == 0x15)
	{
		return 21;
	}
	if (cmos_data == 0x16)
	{
		return 22;
	}
	if (cmos_data == 0x17)
	{
		return 23;
	}
	if (cmos_data == 0x18)
	{
		return 24;
	}
	if (cmos_data == 0x19)
	{
		return 25;
	}
	if (cmos_data == 0x1A)
	{
		return 26;
	}
	if (cmos_data == 0x1B)
	{
		return 27;
	}
	if (cmos_data == 0x1C)
	{
		return 28;
	}
	if (cmos_data == 0x1D)
	{
		return 29;
	}
	if (cmos_data == 0x1E)
	{
		return 30;
	}
	if (cmos_data == 0x1F)
	{
		return 31;
	}
	if (cmos_data == 0x20)
	{
		return 32;
	}
	if (cmos_data == 0x21)
	{
		return 33;
	}
	if (cmos_data == 0x22)
	{
		return 34;
	}
	if (cmos_data == 0x23)
	{
		return 35;
	}
	if (cmos_data == 0x24)
	{
		return 36;
	}
	if (cmos_data == 0x25)
	{
		return 37;
	}
	if (cmos_data == 0x26)
	{
		return 38;
	}
	if (cmos_data == 0x27)
	{
		return 39;
	}
	if (cmos_data == 0x28)
	{
		return 40;
	}
	if (cmos_data == 0x29)
	{
		return 41;
	}
	if (cmos_data == 0x2A)
	{
		return 42;
	}
	if (cmos_data == 0x2B)
	{
		return 43;
	}
	if (cmos_data == 0x2C)
	{
		return 44;
	}
	if (cmos_data == 0x2D)
	{
		return 45;
	}
	if (cmos_data == 0x2E)
	{
		return 46;
	}
	if (cmos_data == 0x2F)
	{
		return 47;
	}
	if (cmos_data == 0x30)
	{
		return 48;
	}
	if (cmos_data == 0x31)
	{
		return 49;
	}
	if (cmos_data == 0x32)
	{
		return 50;
	}
	if (cmos_data == 0x33)
	{
		return 51;
	}
	if (cmos_data == 0x34)
	{
		return 52;
	}
	if (cmos_data == 0x35)
	{
		return 53;
	}
	if (cmos_data == 0x36)
	{
		return 54;
	}
	if (cmos_data == 0x37)
	{
		return 55;
	}
	if (cmos_data == 0x38)
	{
		return 56;
	}
	if (cmos_data == 0x39)
	{
		return 57;
	}
	if (cmos_data == 0x3A)
	{
		return 58;
	}
	if (cmos_data == 0x3B)
	{
		return 59;
	}
	if (cmos_data == 0x3C)
	{
		return 60;
	}
	if (cmos_data == 0x3D)
	{
		return 61;
	}
	if (cmos_data == 0x3E)
	{
		return 62;
	}
	if (cmos_data == 0x3F)
	{
		return 63;
	}
	if (cmos_data == 0x40)
	{
		return 64;
	}
	if (cmos_data == 0x41)
	{
		return 65;
	}
	if (cmos_data == 0x42)
	{
		return 66;
	}
	if (cmos_data == 0x43)
	{
		return 67;
	}
	if (cmos_data == 0x44)
	{
		return 68;
	}
	if (cmos_data == 0x45)
	{
		return 69;
	}
	if (cmos_data == 0x46)
	{
		return 70;
	}
	if (cmos_data == 0x47)
	{
		return 71;
	}
	if (cmos_data == 0x48)
	{
		return 72;
	}
	if (cmos_data == 0x49)
	{
		return 73;
	}
	if (cmos_data == 0x4A)
	{
		return 74;
	}
	if (cmos_data == 0x4B)
	{
		return 75;
	}
	if (cmos_data == 0x4C)
	{
		return 76;
	}
	if (cmos_data == 0x4D)
	{
		return 77;
	}
	if (cmos_data == 0x4E)
	{
		return 78;
	}
	if (cmos_data == 0x4F)
	{
		return 79;
	}
	if (cmos_data == 0x50)
	{
		return 80;
	}
	if (cmos_data == 0x51)
	{
		return 81;
	}
	if (cmos_data == 0x52)
	{
		return 82;
	}
	if (cmos_data == 0x53)
	{
		return 83;
	}
	if (cmos_data == 0x54)
	{
		return 84;
	}
	if (cmos_data == 0x55)
	{
		return 85;
	}
	if (cmos_data == 0x56)
	{
		return 86;
	}
	if (cmos_data == 0x57)
	{
		return 87;
	}
	if (cmos_data == 0x58)
	{
		return 88;
	}
	if (cmos_data == 0x59)
	{
		return 89;
	}
	if (cmos_data == 0x5A)
	{
		return 90;
	}
	if (cmos_data == 0x5B)
	{
		return 91;
	}
	if (cmos_data == 0x5C)
	{
		return 92;
	}
	if (cmos_data == 0x5D)
	{
		return 93;
	}
	if (cmos_data == 0x5E)
	{
		return 94;
	}
	if (cmos_data == 0x5F)
	{
		return 95;
	}
	if (cmos_data == 0x60)
	{
		return 96;
	}
	if (cmos_data == 0x61)
	{
		return 97;
	}
	if (cmos_data == 0x62)
	{
		return 98;
	}
	if (cmos_data == 0x63)
	{
		return 99;
	}
	if (cmos_data == 0x64)
	{
		return 100;
	}
	if (cmos_data == 0x65)
	{
		return 101;
	}
	if (cmos_data == 0x66)
	{
		return 102;
	}
	if (cmos_data == 0x67)
	{
		return 103;
	}
	if (cmos_data == 0x68)
	{
		return 104;
	}
	if (cmos_data == 0x69)
	{
		return 105;
	}
	if (cmos_data == 0x6A)
	{
		return 106;
	}
	if (cmos_data == 0x6B)
	{
		return 107;
	}
	if (cmos_data == 0x6C)
	{
		return 108;
	}
	if (cmos_data == 0x6D)
	{
		return 109;
	}
	if (cmos_data == 0x6E)
	{
		return 110;
	}
	if (cmos_data == 0x6F)
	{
		return 111;
	}
	if (cmos_data == 0x70)
	{
		return 112;
	}
	if (cmos_data == 0x71)
	{
		return 113;
	}
	if (cmos_data == 0x72)
	{
		return 114;
	}
	if (cmos_data == 0x73)
	{
		return 115;
	}
	if (cmos_data == 0x74)
	{
		return 116;
	}
	if (cmos_data == 0x75)
	{
		return 117;
	}
	if (cmos_data == 0x76)
	{
		return 118;
	}
	if (cmos_data == 0x77)
	{
		return 119;
	}
	if (cmos_data == 0x78)
	{
		return 120;
	}
	if (cmos_data == 0x79)
	{
		return 121;
	}
	if (cmos_data == 0x7A)
	{
		return 122;
	}
	if (cmos_data == 0x7B)
	{
		return 123;
	}
	if (cmos_data == 0x7C)
	{
		return 124;
	}
	if (cmos_data == 0x7D)
	{
		return 125;
	}
	if (cmos_data == 0x7E)
	{
		return 126;
	}
	if (cmos_data == 0x7F)
	{
		return 127;
	}
	if (cmos_data == 0x80)
	{
		return 128;
	}
	if (cmos_data == 0x81)
	{
		return 129;
	}
	if (cmos_data == 0x82)
	{
		return 130;
	}
	if (cmos_data == 0x83)
	{
		return 131;
	}
	if (cmos_data == 0x84)
	{
		return 132;
	}
	if (cmos_data == 0x85)
	{
		return 133;
	}
	if (cmos_data == 0x86)
	{
		return 134;
	}
	if (cmos_data == 0x87)
	{
		return 135;
	}
	if (cmos_data == 0x88)
	{
		return 136;
	}
	if (cmos_data == 0x89)
	{
		return 137;
	}
	if (cmos_data == 0x8A)
	{
		return 138;
	}
	if (cmos_data == 0x8B)
	{
		return 139;
	}
	if (cmos_data == 0x8C)
	{
		return 140;
	}
	if (cmos_data == 0x8D)
	{
		return 141;
	}
	if (cmos_data == 0x8E)
	{
		return 142;
	}
	if (cmos_data == 0x8F)
	{
		return 143;
	}
	if (cmos_data == 0x90)
	{
		return 144;
	}
	if (cmos_data == 0x91)
	{
		return 145;
	}
	if (cmos_data == 0x92)
	{
		return 146;
	}
	if (cmos_data == 0x93)
	{
		return 147;
	}
	if (cmos_data == 0x94)
	{
		return 148;
	}
	if (cmos_data == 0x95)
	{
		return 149;
	}
	if (cmos_data == 0x96)
	{
		return 150;
	}
	if (cmos_data == 0x97)
	{
		return 151;
	}
	if (cmos_data == 0x98)
	{
		return 152;
	}
	if (cmos_data == 0x99)
	{
		return 153;
	}
	if (cmos_data == 0x9A)
	{
		return 154;
	}
	if (cmos_data == 0x9B)
	{
		return 155;
	}
	if (cmos_data == 0x9C)
	{
		return 156;
	}
	if (cmos_data == 0x9D)
	{
		return 157;
	}
	if (cmos_data == 0x9E)
	{
		return 158;
	}
	if (cmos_data == 0x9F)
	{
		return 159;
	}
	if (cmos_data == 0xA0)
	{
		return 160;
	}
	if (cmos_data == 0xA1)
	{
		return 161;
	}
	if (cmos_data == 0xA2)
	{
		return 162;
	}
	if (cmos_data == 0xA3)
	{
		return 163;
	}
	if (cmos_data == 0xA4)
	{
		return 164;
	}
	if (cmos_data == 0xA5)
	{
		return 165;
	}
	if (cmos_data == 0xA6)
	{
		return 166;
	}
	if (cmos_data == 0xA7)
	{
		return 167;
	}
	if (cmos_data == 0xA8)
	{
		return 168;
	}
	if (cmos_data == 0xA9)
	{
		return 169;
	}
	if (cmos_data == 0xAA)
	{
		return 170;
	}
	if (cmos_data == 0xAB)
	{
		return 171;
	}
	if (cmos_data == 0xAC)
	{
		return 172;
	}
	if (cmos_data == 0xAD)
	{
		return 173;
	}
	if (cmos_data == 0xAE)
	{
		return 174;
	}
	if (cmos_data == 0xAF)
	{
		return 175;
	}
	if (cmos_data == 0xB0)
	{
		return 176;
	}
	if (cmos_data == 0xB1)
	{
		return 177;
	}
	if (cmos_data == 0xB2)
	{
		return 178;
	}
	if (cmos_data == 0xB3)
	{
		return 179;
	}
	if (cmos_data == 0xB4)
	{
		return 180;
	}
	if (cmos_data == 0xB5)
	{
		return 181;
	}
	if (cmos_data == 0xB6)
	{
		return 182;
	}
	if (cmos_data == 0xB7)
	{
		return 183;
	}
	if (cmos_data == 0xB8)
	{
		return 184;
	}
	if (cmos_data == 0xB9)
	{
		return 185;
	}
	if (cmos_data == 0xBA)
	{
		return 186;
	}
	if (cmos_data == 0xBB)
	{
		return 187;
	}
	if (cmos_data == 0xBC)
	{
		return 188;
	}
	if (cmos_data == 0xBD)
	{
		return 189;
	}
	if (cmos_data == 0xBE)
	{
		return 190;
	}
	if (cmos_data == 0xBF)
	{
		return 191;
	}
	if (cmos_data == 0xC0)
	{
		return 192;
	}
	if (cmos_data == 0xC1)
	{
		return 193;
	}
	if (cmos_data == 0xC2)
	{
		return 194;
	}
	if (cmos_data == 0xC3)
	{
		return 195;
	}
	if (cmos_data == 0xC4)
	{
		return 196;
	}
	if (cmos_data == 0xC5)
	{
		return 197;
	}
	if (cmos_data == 0xC6)
	{
		return 198;
	}
	if (cmos_data == 0xC7)
	{
		return 199;
	}
	if (cmos_data == 0xC8)
	{
		return 200;
	}
	if (cmos_data == 0xC9)
	{
		return 201;
	}
	if (cmos_data == 0xCA)
	{
		return 202;
	}
	if (cmos_data == 0xCB)
	{
		return 203;
	}
	if (cmos_data == 0xCC)
	{
		return 204;
	}
	if (cmos_data == 0xCD)
	{
		return 205;
	}
	if (cmos_data == 0xCE)
	{
		return 206;
	}
	if (cmos_data == 0xCF)
	{
		return 207;
	}
	if (cmos_data == 0xD0)
	{
		return 208;
	}
	if (cmos_data == 0xD1)
	{
		return 209;
	}
	if (cmos_data == 0xD2)
	{
		return 210;
	}
	if (cmos_data == 0xD3)
	{
		return 211;
	}
	if (cmos_data == 0xD4)
	{
		return 212;
	}
	if (cmos_data == 0xD5)
	{
		return 213;
	}
	if (cmos_data == 0xD6)
	{
		return 214;
	}
	if (cmos_data == 0xD7)
	{
		return 215;
	}
	if (cmos_data == 0xD8)
	{
		return 216;
	}
	if (cmos_data == 0xD9)
	{
		return 217;
	}
	if (cmos_data == 0xDA)
	{
		return 218;
	}
	if (cmos_data == 0xDB)
	{
		return 219;
	}
	if (cmos_data == 0xDC)
	{
		return 220;
	}
	if (cmos_data == 0xDD)
	{
		return 221;
	}
	if (cmos_data == 0xDE)
	{
		return 222;
	}
	if (cmos_data == 0xDF)
	{
		return 223;
	}
	if (cmos_data == 0xE0)
	{
		return 224;
	}
	if (cmos_data == 0xE1)
	{
		return 225;
	}
	if (cmos_data == 0xE2)
	{
		return 226;
	}
	if (cmos_data == 0xE3)
	{
		return 227;
	}
	if (cmos_data == 0xE4)
	{
		return 228;
	}
	if (cmos_data == 0xE5)
	{
		return 229;
	}
	if (cmos_data == 0xE6)
	{
		return 230;
	}
	if (cmos_data == 0xE7)
	{
		return 231;
	}
	if (cmos_data == 0xE8)
	{
		return 232;
	}
	if (cmos_data == 0xE9)
	{
		return 233;
	}
	if (cmos_data == 0xEA)
	{
		return 234;
	}
	if (cmos_data == 0xEB)
	{
		return 235;
	}
	if (cmos_data == 0xEC)
	{
		return 236;
	}
	if (cmos_data == 0xED)
	{
		return 237;
	}
	if (cmos_data == 0xEE)
	{
		return 238;
	}
	if (cmos_data == 0xEF)
	{
		return 239;
	}
	if (cmos_data == 0xF0)
	{
		return 240;
	}
	if (cmos_data == 0xF1)
	{
		return 241;
	}
	if (cmos_data == 0xF2)
	{
		return 242;
	}
	if (cmos_data == 0xF3)
	{
		return 243;
	}
	if (cmos_data == 0xF4)
	{
		return 244;
	}
	if (cmos_data == 0xF5)
	{
		return 245;
	}
	if (cmos_data == 0xF6)
	{
		return 246;
	}
	if (cmos_data == 0xF7)
	{
		return 247;
	}
	if (cmos_data == 0xF8)
	{
		return 248;
	}
	if (cmos_data == 0xF9)
	{
		return 249;
	}
	if (cmos_data == 0xFA)
	{
		return 250;
	}
	if (cmos_data == 0xFB)
	{
		return 251;
	}
	if (cmos_data == 0xFC)
	{
		return 252;
	}
	if (cmos_data == 0xFD)
	{
		return 253;
	}
	if (cmos_data == 0xFE)
	{
		return 254;
	}
	if (cmos_data == 0xFF)
	{
		return 255;
	}//if
	return true;
}//function


unsigned char Zero_255_to_U8(int array_data)
{   
	if (array_data >= 0 && array_data <= 255) 
	{
		return consult_table[array_data];
	}
	else if (array_data < 0)
	{  
		return 0x00;
	}
	else 
	{
		return 0xFF;
	}
}