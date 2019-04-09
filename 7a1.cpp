#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h> 		/* abre e le arquivos */
#include <fstream>

using namespace std;

typedef struct{
	int figurinha[681];
	int figuraTotal;
	int figuraRepetida;
}Album;

Album album;

typedef struct{
	int figurinha[5];
}Pacote;

Pacote pacote;

void inicializar(){
	//inicia album
	for(int i = 0; i < 682; i++){
		album.figurinha[i] = 0;
	}
	album.figuraTotal = 0;
	album.figuraRepetida = 0;
	//inicia pacote
	for(int i = 0; i < 5; i++){
		pacote.figurinha[i] = 0;
	}
}

void colarFigurinha(int figura){
	album.figurinha[figura]++;
}

void comprarPacote(){
	pacote.figurinha[0] = rand() % 681;
	pacote.figurinha[1] = rand() % 681;
	pacote.figurinha[2] = rand() % 681;
	pacote.figurinha[3] = rand() % 681;
	pacote.figurinha[4] = rand() % 681; 
}

// incrementar 1 no album.figurinha[x]
//	se pacote.figurinha[0] = 20
// 	=> album.figurinha[20]++;
void colarPacote(){	
	album.figurinha[pacote.figurinha[0]]++;
	album.figurinha[pacote.figurinha[1]]++;
	album.figurinha[pacote.figurinha[2]]++;
	album.figurinha[pacote.figurinha[3]]++;
	album.figurinha[pacote.figurinha[4]]++;
}

void imprimirAlbum(){
	cout << "ALBUM COPA" << endl;
	for(int i = 0; i < 682; i++){
		if(album.figurinha[i] > 0){
			cout << "Contem figurinha: " << i << endl;
		}
	}
}

// Pesquisar figura no album
// Retorna variavel tipo inteiro caso encontrar no album
int pesquisarFigurinha(int figura){
	if(album.figurinha[figura] > 0){
		return album.figurinha[figura];
	}
	else{
		return -1;
	}
}

void relatorioColadas(){
	for(int i =0; i < 682; i++){
		if(album.figurinha[i] > 0){
			cout << i << endl;
		}
	}
}

void relatorioFaltantes(){
	for(int i =0; i < 682; i++){
		if(album.figurinha[i] == 0){
			cout << i << endl;
		}
	}
}

void salvar(){
	// ponteiro file recebe handle da funcao fopen que abre arquivo
	// "w" escreve no arquivo "faltantes.txt"
	FILE *file = fopen("faltantes.txt", "w");
	// Se ele for diferente de NULL conseguimos abrir
	if(file != NULL) {
		for(int i =0; i < 682; i++){
			if(album.figurinha[i] == 0){
				//fprintf imprime variavel dentro do arquivo que file aponta
				// %i imprime o valor de i dentro do arquivo
				fprintf(file, "%i\n", i);
			}
		}
		fclose(file);
	}
	
	
	file = fopen("eu_tenho.txt", "w");
	// Se ele for diferente de NULL conseguimos abrir
	if(file != NULL) {
		for(int i =0; i < 682; i++){
			if(album.figurinha[i] > 0){
				//fprintf imprime variavel dentro do arquivo que file aponta
				// %i imprime o valor de i dentro do arquivo
				fprintf(file, "%i\n", i);
			}
		}
		fclose(file);
	}
	
	
	file = fopen("repetidas.txt", "w");
	// Se ele for diferente de NULL conseguimos abrir
	if(file != NULL) {
		for(int i =0; i < 682; i++){
			if(album.figurinha[i] > 1){
				//fprintf imprime variavel dentro do arquivo que file aponta
				// %i imprime o valor de i dentro do arquivo
				fprintf(file, "%i %i\n", i, album.figurinha[i]);
			}
		}
		fclose(file);
	}
	
	
}

void abrirAlbum(){
	int figura = 0;
	// ifstream serve para abrir arquivo pelo ponteiro infile
    ifstream infile;
    // infile vai abrir o arquivo eu_tenho.txt
    infile.open("eu_tenho.txt");
    // Se arquivo abrir e nao houver erro faça
    if(infile.is_open()){   
		//enquanto houver linha a ser lida no arquivo faça:     
        while(infile >> figura){ 
        	// "colar" ou seja... incrementar +1 na posicao da figura no vetor
			album.figurinha[figura]++;
        }
        //fechar arquivo
        infile.close();
    }
}

int main() {
	//inicia semente numero aleatorio
	srand(time(NULL));  
	
	inicializar();
	
	int opt = 0;
	do{
		cout << "\nMENU ALBUM COPA\n";
    	cout << "1 - Comprar pacote\n";
    	cout << "2 - Colar pacote\n";
    	cout << "3 - Imprimir album\n";
    	cout << "4 - Pesquisar figurinha\n";
    	cout << "5 - Relatorio figurinhas coladas\n";
    	cout << "6 - Relatorio figurinhas faltantes\n";
    	cout << "7 - Salvar\n";
    	cout << "8 - Colar Figurinha\n";
    	cout << "9 - Abrir album\n";
    	cout << "0 - Sair\n";
    	cout << "# Digite a opcao desejada: ";
    	cin >> opt;
    	if(opt == 1){
    		comprarPacote();
		}
		if(opt == 2){
    		colarPacote();
		}
		if(opt == 3){
    		imprimirAlbum();
		}
		if(opt == 4){
			int figura = 0;
			cout << "Qual figurinha voce quer pesquisar: ";
			cin >> figura;
			// x recebe retorno da funcao pesquisarFigurinha
    		int x = pesquisarFigurinha(figura);
    		if(x == -1){
    			cout << "Figurinha nao encontrada" << endl;
			}
			else{
				cout << "Figurinha encontrada!" << endl;
			}
		}
		if(opt == 5){
			relatorioColadas();
		}
		if(opt == 6){
			relatorioFaltantes();
		}
		if(opt == 7){
			salvar();
		}
		if(opt == 8){
			int figura = 0;
			cout << "Qual figurinha voce quer colar? ";
			cin >> figura;
			colarFigurinha(figura);
		}
		if(opt == 9){
			abrirAlbum();
		}
	//enquanto variavel opt for diferente de 0, repetir menu
	}while(opt != 0);
	
	return 0;
}
