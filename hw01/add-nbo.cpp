#include <stddef.h> // for size_t
#include <stdint.h> // for uint8_t
#include <stdio.h> // for printf
#include <netinet/in.h>
#include <stdlib.h>

void dump(void* p, size_t n) {
	uint8_t* u8 = static_cast<uint8_t*>(p);
	size_t i = 0;
	while (true) {
		printf("%02X ", *u8++);
		if (++i >= n) break;
		if (i % 8 == 0)
			printf("\n");
	}
	printf("\n");
}

void read_file(const char *filename, uint8_t *buf, int bufsize){
    FILE *fp = fopen(filename, "r");
	; 
	if (fp == NULL){
		printf("error at opening file\n");
		exit(0);
	}
	fread(buf, 1, bufsize, fp);
	//dump(buf,bufsize);
	fclose(fp);
	fp = NULL;
}


uint32_t my_ntohl(uint8_t *buf1) {
	uint32_t* p1 = reinterpret_cast<uint32_t*>(buf1);
	uint32_t res = ((*p1 & 0xff) << 24) | ((*p1&0xff00) << 8)|((*p1&0xff0000) >> 8) |((*p1&0xff000000) >> 24);
	return res;
}
uint32_t addnbo(uint8_t *buf1, uint8_t *buf2){
	uint32_t n1 = my_ntohl(buf1); // TODO
	uint32_t n2 = my_ntohl(buf2);
	uint32_t sum = n1+n2;
	return sum;
}

int main(int argc, char *argv[]) {
	
	if (argc < 3){
		printf("syntax : add-nbo <file1> <file2>\n");
		exit(1);
	} 
	uint8_t buf1[4],buf2[4];
	read_file(argv[1], buf1, 4);
	read_file(argv[2], buf2, 4);
	//1000(0x3e8) + 500(0x1f4) = 1500(0x5dc)
	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", my_ntohl(buf1),my_ntohl(buf1),my_ntohl(buf2),my_ntohl(buf2),addnbo(buf1,buf2),addnbo(buf1,buf2));
}
