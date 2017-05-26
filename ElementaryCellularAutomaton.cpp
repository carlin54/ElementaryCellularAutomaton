#include <iostream>
#include <Windows.h>

int ConsoleHeight(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return (csbi.srWindow.Bottom - csbi.srWindow.Top) + 1;
	
}

int ConsoleWidth(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return (csbi.srWindow.Right - csbi.srWindow.Left);
}

void array_make(bool*** make, unsigned x, unsigned y){
	make[0] = new bool*[y];
	for (unsigned i = 0; i < y; i++){
		make[0][i] = new bool[x];
	}
}

void array_init(bool*** init, bool set, unsigned x, unsigned y){
	for (unsigned i = 0; i < y; i++){
		for (unsigned j = 0; j < x; j++){
			init[0][i][j] = set;
		}
	}
}

void array_randomize(bool*** randomize, unsigned x, unsigned y){
	srand(NULL);
	for (unsigned i = 0; i < y; i++){
		for (unsigned j = 0; j < x; j++){
			if (rand() % 2){
				randomize[0][i][j] = true;
			}
			else{
				randomize[0][i][j] = false;
			}
		}
	}
}

void array_middle_row(bool*** middle, unsigned x, unsigned y){

	middle[0][0][x / 2] = true;

}

void array_print(bool*** print, unsigned x, unsigned y, char alive = '*', char dead = ' '){
	for (unsigned i = 0; i < y; i++){
		for (unsigned j = 0; j < x; j++){
			if (print[0][i][j]){
				std::cout << alive;
			}
			else{
				std::cout << dead;
			}

		}
		std::cout << std::endl;
	}
}

void array_free(bool*** free, unsigned x, unsigned y){
	for (unsigned i = 0; i < y; i++){
		delete[] free[0][i];
	}
	delete[] free[0];
}


bool apply_rule(unsigned char rule, bool* cells){
	if (cells[0] && cells[1] && cells[2]){
		return (rule >> int(7)) & 0x01;
	}
	else if (cells[0] && cells[1] && !cells[2]){
		return (rule >> int(6)) & 0x01;
	}
	else if (cells[0] && !cells[1] && cells[2]){
		return (rule >> int(5)) & 0x01;
	}
	else if (cells[0] && !cells[1] && !cells[2]){
		return (rule >> int(4)) & 0x01;
	}
	else if (!cells[0] && cells[1] && cells[2]){
		return (rule >> int(3)) & 0x01;
	}
	else if (!cells[0] && cells[1] && !cells[2]){
		return (rule >> int(2)) & 0x01;
	}
	else if (!cells[0] && !cells[1] && cells[2]){
		return (rule >> int(1)) & 0x01;
	}
	else if (!cells[0] && !cells[1] && !cells[2]){
		return (rule >> int(0)) & 0x01;
	}


}

void rule(bool*** array_to_apply, unsigned char rule, unsigned x, unsigned y){
	for (unsigned i = 1; i < y; i++){
		for (unsigned j = 1; j < x - 1; j++){
			array_to_apply[0][i][j] = apply_rule(rule, &array_to_apply[0][i - 1][j - 1]);
		}
	}

};


int main(int argv, char* argc[]){



	bool** my_array;
	unsigned x = ConsoleWidth(); unsigned y = ConsoleHeight() - 1;

	array_make(&my_array, x, y);
	
	
	bool exit = false;
	unsigned char selected_rule = 30;
	int user_input;
	while (!exit){
		array_init(&my_array, false, x, y);
		array_middle_row(&my_array, x, y);
		
		std::cout << "Enter the rule number: ";
		std::cin >> user_input;
		if (user_input == -1){
			exit = !exit;
		}else{
			selected_rule = (unsigned char)user_input;
			rule(&my_array, selected_rule, x, y);
			array_print(&my_array, x, y);
		}
			
	}

	array_free(&my_array, x, y);
	
	
	return 0;
}