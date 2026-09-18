#include<iostream>
#include<cstring>
#include<fstream>

int file_extension_check(char *ext){
	// 1 for valid, 0 for invalid
	int len = strlen( ext);
	char *valid_extension = ".stlex";
	char *extension = &ext[ len - 6];
	return strcmp( extension, valid_extension);
}

int file_exists( char *filename){
	std::ifstream file( filename);
	return file.good();
}

int main(int argc, char **argv){

	if( ( argc < 2 || argc > 3) || file_extension_check( argv[1]) != 0){
		//Commandline arguments
		std::cerr<< "Incorrect argumentation: <build> <infile.stlex> <outfile>"<< std::endl;
		return 1;
	}

	//Default or custom output file
	char *outfile_name = "default.c";
	if( argc == 3)
		outfile_name = argv[2];

	std::ifstream infile( argv[1]);
	if( !infile.good()){ //Existence of input file
		std::cerr<< "Input file does not exist"<< std::endl;
		return 1;
	}

	std::ofstream outfile( outfile_name, std::ios::trunc);
	char ch;
	while( infile.get(ch)){
		outfile<< ch;
	}

	infile.close();
	outfile.close();
	return 1;
}
