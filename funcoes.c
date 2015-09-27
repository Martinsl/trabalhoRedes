#include <stdio.h>
#include <stdint.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Tipos
#define NACK 0x0
#define ACK 0x1
#define CD 0x3
#define LS 0x4
#define PUT 0x5
#define GET 0x6
#define OK 0x8
#define TAM 0x9
#define SHOW 0xA
#define ERROR 0xE
#define END 0xF



/* Delimitador Inicio 8
 *	Tamanho 6
 *	seq 6
 *	tipo 4
 *	dado ...
 *	paridade 8  (vertical)
 */
typedef struct packet {
	uint8_t begin;// = 01111110;
	uint8_t tamSeq;
	uint8_t seqType;
	int dado;	// = 0x0;					// teste com inteiro para enviar no minimo 8bytes por packet
	uint8_t paridade;
};



uint8_t calcParity(uint8_t *tamSeq, uint8_t *seqType) { //TODO: ADD DATA XOR
	// int x = (number >> (8*n)) & 0xff   Separa bytes de um inteiro
	return *tamSeq ^ *seqType;
}

uint8_t buildTamSeq(uint8_t tam, uint8_t seq) {
	return (tam <<= 2) | (seq >>= 4);
}

uint8_t buildSeqType(uint8_t seq, uint8_t type) {
	return (seq <<= 4) | type;
}

int main(int argc, char *argv[]) {
	uint8_t tamSeq = 0x6D;  // 01101101
	uint8_t seqType = 0xBA; // 10111010
	uint8_t tam = 0x3D; // 00111101
	uint8_t seq = 0x29; // 00101001
	uint8_t type = 0x3; // 00000011

	printf("tamSeq: %u\n", buildTamSeq(tam, seq)); // MUST print 246
	printf("seqType: %u\n", buildSeqType(seq, type)); // MUST print 147
	printf("Paridade: %u\n", calcParity(&tamSeq, &seqType)); // MUST print 215
	return EXIT_SUCCESS;
}