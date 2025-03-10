#include <stdio.h>

unsigned int campesino_ruso(unsigned int i, unsigned int j){
	unsigned int res = 0;
		while (j > 1) {
			if (j & 1) {
				res += i;
				j -= 1;
			} else {
				i *= 2;
				j /= 2;
			}
		}
	return res + i;
}

int main(){
	/* printf("%d", campesino_ruso(105,68)); */
	printf("%d", 68 & 1);
	return 0;
}