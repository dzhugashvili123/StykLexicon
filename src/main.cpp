#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include<string>
#include<cctype>

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

enum Token_Type{
	SEMI,
	NUMBER,	//Whole number

	PLUS, MINUS, MUL, DIV,
	L_PAREN, R_PAREN,


	KEYWORD,
	COMMENT_DELIMITER,
	RETURN,
};

class Token{
	public:
		Token_Type type;
		std::string data = "";
	
		Token(Token_Type type, std::string data = ""){
			this->type = type;
			this->data = data;
		}
};

int is_number( std::string &buffer){
	//0 for invalid number
	int len = buffer.length();

	if(buffer ==  "" || buffer == "\t" || buffer == "\n")
		return 0;
	
	for(int i=0; i<len; i++){
		if( !std::isdigit( buffer.at(i)))
			return 0;
	}
	return 1;
}

class Tokeniser{
	public:
		void tokeniser(std::ifstream &infile, std::vector<Token> &token_stream){
			std::string buffer = "";
			char ch;

			while( infile.get(ch)){
				if( ch == ' ' || ch == '\t' || ch == '\n' || ch == ';' ){
					if( buffer == "return"){
							token_stream.push_back( Token( Token_Type::RETURN));
						
					}

					if( is_number( buffer)){
							token_stream.push_back( Token( Token_Type::NUMBER, buffer));
					}
				
					if( ch == ';')
						token_stream.push_back( Token( Token_Type::SEMI));
					
					buffer = "";
					
				}
				else
					buffer = buffer + ch;
			}
		
		}

		void token_stream_display(std::vector<Token> &token_stream){
			for( const auto &tok : token_stream){
				const char *verbose;
				switch(tok.type){
					case Token_Type::SEMI:	verbose = "SEMICOLON";	break;
					case Token_Type::NUMBER:	verbose = "NUMBER";	break;
					case Token_Type::PLUS:
					case Token_Type::MINUS:
					case Token_Type::MUL:
					case Token_Type::DIV: verbose = "OPERATOR";	break;
					case Token_Type::L_PAREN:	verbose = "(";	break;
					case Token_Type::R_PAREN:	verbose = ")";	break;
					case Token_Type::COMMENT_DELIMITER:	verbose = "//";	break;
					case Token_Type::RETURN:	verbose = "RETURN";	break;

				}
				std::cout<< "< "<< verbose<< ">";
			}
			std::cout<< std::endl;
		}
};

class Parser{
	public:
		Parser(std::vector<Token> &token_stream){
			this->stream_size = token_stream.size();
		}
		void parse_stream(std::vector<Token> &token_stream){
			
		}

	private:
		int curr_index = 0;
		int stream_size;

		void stream_last_token(){
			if( curr_index < stream_size-1)
				return;
			std::cerr<< "End of token stream : Parser error";
			exit(0);
		}

		int validate_expression(std::vector<Token> &token_stream, int index){
			// int val_index = curr_index;
			if( ( token_stream.at(index)).type == Token_Type::NUMBER){
				stream_last_token();
				if( ( token_stream.at( ++index)).type == Token_Type::PLUS || ( token_stream.at( ++index)).type == Token_Type::MINUS || ( token_stream.at( ++index)).type == Token_Type::MUL || ( token_stream.at( ++index)).type == Token_Type::DIV){
					stream_last_token();
					return validate_expression( token_stream, ++index);
				}
				else
					return 1;
			}

			return 0;
		}

		int validate_return(std::vector<Token> &token_steam){

		}

};

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

	std::vector<Token> token_stream;
	Tokeniser tokeniser;
	tokeniser.tokeniser( infile, token_stream);
	std::cout<< token_stream.size()<< std::endl;
	tokeniser.token_stream_display( token_stream);

	infile.close();
	outfile.close();
	return 1;
}
