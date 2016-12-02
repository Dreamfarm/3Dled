#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_yuvY(uint8_t *yuv_y){
	for ( int i = 0; i < 16;i++){
		for(int j = 0; j< 16; j++)
		{
			if(yuv_y[i*16 + j] > 0)
				printf("%d ",yuv_y[i*16 + j]);
			else
				printf("  ");
		}
		printf("\n");
	}
}

bool get_font_mode(const char *input_wchar, uint8_t *output_buf){
		FILE* fphzk = NULL;
	int i, j, k;
	long offset = 0;
	int flag;
	unsigned char buffer[32];
	unsigned char *wchar = (unsigned char *)input_wchar;
	unsigned char key[8] = {
		0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
	};
	fphzk = fopen("hzk16", "rb");
	if(fphzk == NULL){
		fprintf(stderr, "error hzk16\n");
		return false;
	}
		for(int l = 0; l < 10; l++){
			offset = (94*(unsigned int)(wchar[0]-0xa0-1)+(wchar[1]-0xa0-1))*32;
			fseek(fphzk, offset, SEEK_SET);
			fread(buffer, 1, 32, fphzk);
			for(k=0; k<16; k++){
				for(j=0; j<2; j++){
					for(i=0; i<8; i++){
						flag = buffer[k*2+j]&key[i];
						output_buf[8*j+i + k*16] = flag ? 1:0;
					}
				}
			}
		}
	fclose(fphzk);
	fphzk = NULL;
	return true;
	}
int main(void)
{
	uint8_t yuv_y[16*16];
	get_font_mode("йт",yuv_y);	//input GB2312,UTF-8 will fail
	print_yuvY(yuv_y);
	return 0;
}
