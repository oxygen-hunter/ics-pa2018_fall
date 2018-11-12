struct CacheLine {
	bool valid; //1 when CacheLine is valid, 0 when CacheLine is invalid
	uint32_t sign; //to sign which if this cache matches address
	uint8_t data[64]; //data area who has 64 B
}
