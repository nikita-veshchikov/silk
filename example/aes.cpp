// AES-128 functions

#include "aes.hpp"

using namespace std;

//128 bit AES
	
U8 Cr; // current round
	
void keyExpansion(U8 key [][Ncols], U8 w[][Ncols*(Nr+1)]){		
		
	U8 Rcon [] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F};
	U8 temp[Nrows];
	U8 tmp;
		
	for(U8 i = 0; i < Nrows; i++){
		for(U8 j = 0; j < Ncols; j++){
			w[i][j] = key[i][j]; 
		}
	}
		
	for(U8 i = Ncols; i < (Ncols*(Nr+1)); i++){
			
		for(U8 j = 0; j < Nrows; j++){
			temp[j] = w[j][i-1]; 
		}
			
		if((i % Ncols) == 0){
				
			//RotWord(temp)
			tmp = temp[0];
			temp[0] = temp[1];
			temp[1] = temp[2];
			temp[2] = temp[3];
			temp[3] = tmp;
			
			//SubWord()
			temp[0] = sBox[temp[0]];
			temp[1] = sBox[temp[1]];
			temp[2] = sBox[temp[2]];
			temp[3] = sBox[temp[3]];
			
			temp[0] = (temp[0] ^ Rcon[(i/4)-1]);
		}
			
		for(U8 j = 0; j < Nrows; j++){
			w[j][i] = (w[j][i-4] ^ temp[j]); 
		}
	}
		
	//return w;
}
	
void subBytes(U8 state [][Ncols]){	
	for(U8 i = 0; i < Nrows; i++){
		for(U8 j = 0; j < Ncols; j++){
			state[i][j] = sBox[state[i][j]]; 
		}
	}
}
	
void shiftRows(U8 state [][Ncols]){
		
	U8 tmp;
		
	tmp = state[1][0];
	state[1][0] = state[1][1];
	state[1][1] = state[1][2];
	state[1][2] = state[1][3];
	state[1][3] = tmp;
		
	tmp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = tmp;
	tmp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = tmp;
		
	tmp = state[3][0];
	state[3][0] = state[3][3];
	state[3][3] = state[3][2];
	state[3][2] = state[3][1];
	state[3][1] = tmp;
	
}

void mixColumns(U8 state [][Ncols]){
		
	U8 tmp[4];
		
	for(U8 i = 0; i < Ncols; i++){
			
		tmp[0] = (mCM2[state[0][i]]) ^ (mCM3[state[1][i]]) ^ (state[2][i]) ^ (state[3][i]);
		tmp[1] = (state[0][i]) ^ (mCM2[state[1][i]]) ^ (mCM3[state[2][i]]) ^ (state[3][i]);
		tmp[2] = (state[0][i]) ^ (state[1][i]) ^ (mCM2[state[2][i]]) ^ (mCM3[state[3][i]]);
		tmp[3] = (mCM3[state[0][i]]) ^ (state[1][i]) ^ (state[2][i]) ^ (mCM2[state[3][i]]);
			
		state[0][i] = tmp[0];
		state[1][i] = tmp[1];
		state[2][i] = tmp[2];
		state[3][i] = tmp[3];
	}
}
	
void addRoundKey(U8 state [][Ncols], U8 w [][Ncols * (Nr +1)]){
		
	for(U8 i = 0; i < Nrows; i++){
		for(U8 j = 0; j < Ncols; j++){
			state[i][j] = state[i][j] ^ w[i][(Cr*4)+j]; 
		}
	}
	
	Cr++;
}

void cipher(U8 state [Nrows][Ncols], U8 key [][Ncols]){
	Cr = 0;
	
	U8 w [Nrows][Ncols * (Nr +1)];
	keyExpansion(key,w);
	
	addRoundKey(state,w);
	for(U8 i=0;i<9;++i){
		subBytes(state);
		shiftRows(state);
		mixColumns(state);
		addRoundKey(state,w);
	}
	//last round
	subBytes(state);
	shiftRows(state);
	addRoundKey(state,w);
}

void print(U8 state [Nrows][Ncols]){
	for(U8 i=0; i < Nrows; i++){
		for(U8 j=0; j < Ncols; j++){
			printf("%02X ", (int)state[i][j]);
		}
		cout << endl;
	}
}

void printKey(U8 k [][Ncols * (Nr +1)]){
	for(U8 i=0; i < Nrows; i++){
		for(U8 j=0; j < Ncols * (Nr +1); j++){
			printf("%02X ", (int)k[i][j]);
		}
		cout << endl;
	}
}
