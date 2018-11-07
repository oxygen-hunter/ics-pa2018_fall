struct CacheLine {
	bool valid; //1 when CacheLine is valid, 0 when CacheLine is invalid
	
	uint8_t data[64]; //data area who has 64 byte
}
