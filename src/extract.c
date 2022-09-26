// *** Work in progress ***

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	
	if (argc != 5 || argc == 1 || strcmp(argv[1], "help") == 0) {
		fprintf(stderr, "USAGE: %s [file] [ind_min] [ind_max] [format]\n", argv[0]);
		fprintf(stderr, "This program reads binary [file] with jack connection coefficients\n");
		fprintf(stderr, "and prints coefficients (and partitiions) from [ind_min] to [ind_max]\n");
		fprintf(stderr, "in decimal ([format] = d) or hexadecimal ([format] = x) format.\n");
		fflush(stderr);
		return -1;
	}
	
	char* filename = argv[1];
	int   ind_min  = atoi(argv[2]);
	int   ind_max  = atoi(argv[3]);
	char  format   = argv[4][0];
	
	const int header_size = 8;
	
	FILE* file = fopen(filename, "rb");
	int header[header_size] = { };
	fread(header, sizeof(int), header_size, file);
	
	int N = header[0];
	int M = header[1];
	int big_int_type = header[2];
	int big_int_size = header[3];
	
	// Sorry for this mess
	char bi_fmt[] = "BAD FORMAT";
	char of_fmt[200] = "BAD FORMAT";

	if (big_int_type == sizeof(uint8_t) && format == 'd')  strcpy(of_format, "  OF");
	if (big_int_type == sizeof(uint8_t) && format == 'x')  strcpy(of_format, " OF");
	if (big_int_type == sizeof(uint16_t) && format == 'd') strcpy(of_format, "     OF");
	if (big_int_type == sizeof(uint16_t) && format == 'x') strcpy(of_format, "   OF");
	if (big_int_type == sizeof(uint32_t) && format == 'd') strcpy(of_format, "   OVERFLOW");
	if (big_int_type == sizeof(uint32_t) && format == 'x') strcpy(of_format, " OVERFLOW");
	if (big_int_size == sizeof(uint64_t) && format == 'u')  strcpy(of_format, "             OVERFLOW");
	if (big_int_size == sizeof(uint64_t) && format == 'x')  strcpy(of_format, "         OVERFLOW");
	if (big_int_size == 2 * sizeof(uint64_t) && format == 'x') strcpy(of_format, "                          OVERFLOW");
	if (big_int_size == 4 * sizeof(uint64_t) && format == 'x') strcpy(of_format, "                                                            OVERFLOW");
	if (big_int_size == 8 * sizeof(uint64_t) && format == 'x') strcpy(of_format, "                                                                                                                                OVERFLOW");

	if (big_int_type == sizeof(uint8_t) && format == 'd') strcpy(bi_fmt, ":%03" PRIu8);
	if (big_int_type == sizeof(uint8_t) && format == 'x') strcpy(bi_fmt, ":%02" PRIx8);
	if (big_int_type == sizeof(uint16_t) && format == 'd') strcpy(bi_fmt, ":%06" PRIu16);
	if (big_int_type == sizeof(uint16_t) && format == 'x') strcpy(bi_fmt, ":%04" PRIx16);
	if (big_int_type == sizeof(uint32_t) && format == 'd') strcpy(bi_fmt, ":%010" PRIu32);
	if (big_int_type == sizeof(uint32_t) && format == 'x') strcpy(bi_fmt, ":%08" PRIx32);
	if (big_int_size > sizeof(uint32_t) && format == 'u') strcpy(bi_fmt, ":%020" PRIu64);
	if (big_int_size > sizeof(uint32_t) && format == 'x') strcpy(bi_fmt, ":%16" PRIx32);
	//
	
	
	int size_of_element = N * sizeof(int) + N * big_int_type * big_int_size;
	
	unsigned char buffer[(ind_max - ind_min + 1) * size_of_element];
	
	fseek(file, header_size + ind_min * size_of_element, SEEK_SET);	
	fread(buffer, sizeof(buffer), 1, file);
	fclose(file);
	
	for (int i = 0; i < ind_max - ind_min + 1; i++) {
		//
		int* partition = (int*)(buffer + i * size_of_element);
		unsigned char* polynomial = (unsigned char*)(buffer + i * size_of_element + sizeof(int) * N);
		
		printf("[");
		for (int k = 0; k < N; k++) 
			printf("%3d", partition[k]);
		printf("]  ");
		
		//
		for (int k = 0; k < N; k++) {
			 for (int j = big_int_size - 1; j >= 0; j--) {
				 if (big_int_type == sizeof(uint8_t))
					 printf(":");
			 } 
			 printf(" ");
		}	
		printf("\n");
	}
	
	return 0;
}