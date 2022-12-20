#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include "windows.h"

using namespace std;

typedef struct{
	int year;
	int mount;
	int day;
}Date;

void header(string title){
	printf("========================================================================================================================================================================");
	cout << "\t\t\t\t\t\t\t\t\t " << title << endl;
	printf("========================================================================================================================================================================");
}

struct Nasabah{
	char nama[30] ;
	char kodeBank[7] ;
	char noRekening [13] ;
	char PIN [10];
	char email [30] ;
	int saldo;
	int status;
	Date tanggalLahir;
};

FILE *data = fopen("nasabah.bin", "rb+");
Nasabah user,target;
int recsize = sizeof(Nasabah);

void gotoxy();
void ui_penarikan(int tunai);
int menuPenarikan();
int menuLainnya();
void uiUbah();
void uiPENARIKAN();
void uiInformasi();
void uiTransfer();
void Transfer(Nasabah target, int saldo);
void uiPenarikan();
int cekRekening(Nasabah penerima);
int cekSaldo(Nasabah nb, int tunai);
int cekDate(Nasabah update);
int isPinLama(Nasabah update);
void updatePin(Nasabah update);

void gotoxy(int x, int y){
	COORD coord;
	coord.X=x;
	coord.Y=y;

SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void insertData(Nasabah input, Nasabah datas){
					strcpy(input.email,datas.email);
					strcpy(input.kodeBank,datas.kodeBank);
					strcpy(input.nama,datas.nama);
					strcpy(input.noRekening,datas.noRekening);
					strcpy(input.PIN,datas.PIN);
					input.status = datas.status;
					input.saldo = datas.saldo;
					input.tanggalLahir.day = datas.tanggalLahir.day;
					input.tanggalLahir.mount = datas.tanggalLahir.mount;
					input.tanggalLahir.year = datas.tanggalLahir.year;
					fseek(data, -recsize, SEEK_CUR);
					fwrite(&input,recsize,1,data);
}

void header_login(char flag){
	system("cls");
	printf("\n");
	printf("========================================================================================================================================================================");
	printf("\n\t\t\t\t                                             SELAMAT DATANG");
	printf("\n\t\t\t\t                                                   DI");
	printf("\n\t\t\t\t                                           BANK ATM ROBBANI\n");
	printf("========================================================================================================================================================================");
	if(flag == 'e'){
		printf("\n\n\n\n\t\t\t\t\t\t\t    SILAHKAN MASUKKAN EMAIL ANDA \n\t\t");
	} else {
		printf("\n\n\n\n\t\t\t\t\t\t\t    SILAHKAN MASUKKAN PIN ANDA \n\t\t");
	}
}


void inputEmail(Nasabah * baru){
	cin >> (*baru).email;
}

int cekEmail(Nasabah baru){
	rewind(data);
	while (fread(&user,recsize,1,data) == 1){
			if(strcmp(user.email,baru.email)== 0){
					return 1;
				} 
	}
	return 0;
}

void inputPIN(Nasabah * baru){
	cin >> (*baru).PIN;
}

void tarik(int tunai){
	user.saldo = user.saldo - tunai;
}

void cekSaldo(int tunai){
	if(user.saldo <= tunai){
		cout << "DANA TIDAK MENCUKUPI";
	} else {
		ui_penarikan(tunai);
	}
}

int cekPIN(Nasabah baru){
	if(strcmp(baru.PIN,user.PIN) == 0){
		return 1;
	} else {
		return 0 ;
	}
}

int menu_penarikan();
void kurangSaldo(int tunai){
	Nasabah du;
	rewind(data);
	int p = 1;
	while (fread(&du,recsize,1,data) == 1 && p ==1){
			if(strcmp(du.email,user.email)== 0){
					Nasabah baru;
					user.saldo = user.saldo - tunai;
					strcpy(baru.email,user.email);
					strcpy(baru.kodeBank,user.kodeBank);
					strcpy(baru.nama,user.nama);
					strcpy(baru.noRekening,user.noRekening);
					strcpy(baru.PIN,user.PIN);
					baru.status = user.status;
					baru.saldo = user.saldo;
					baru.tanggalLahir.day = user.tanggalLahir.day;
					baru.tanggalLahir.mount = user.tanggalLahir.mount;
					baru.tanggalLahir.year = user.tanggalLahir.year;
					fseek(data, -recsize, SEEK_CUR);
					fwrite(&baru,recsize,1,data);
					p = 0;
					break;
				} 
	}
	
} 

void tambahSaldo(int tunai, Nasabah nacabah){
	Nasabah du;
	rewind(data);
	int p = 1;
	while (fread(&du,recsize,1,data) == 1 && p == 1){
			if(strcmp(du.email,nacabah.email)== 0){
					Nasabah baru;
					nacabah.saldo = nacabah.saldo + tunai;
					strcpy(baru.email,nacabah.email);
					strcpy(baru.kodeBank,nacabah.kodeBank);
					strcpy(baru.nama,nacabah.nama);
					strcpy(baru.noRekening,nacabah.noRekening);
					strcpy(baru.PIN,nacabah.PIN);
					baru.status = nacabah.status;
					baru.saldo = nacabah.saldo;
					baru.tanggalLahir.day = nacabah.tanggalLahir.day;
					baru.tanggalLahir.mount = nacabah.tanggalLahir.mount;
					baru.tanggalLahir.year = nacabah.tanggalLahir.year;
					fseek(data, -recsize, SEEK_CUR);
					fwrite(&baru,recsize,1,data);
					p = 0;
					break;
				} 
	}
} 
				

int log_in(){
	int count = 0;
	Nasabah baru;
	string pin;
	while(count <=2) {
	gotoxy(59,14);
	inputEmail(&baru);	
	if(cekEmail(baru)){
		// Jika email tersebut ada dan benar 
		count = 0;
		system("cls");
		header_login('f');	
		while(count <= 2){
			gotoxy(59,14);
			inputPIN(&baru);
			if(cekPIN(baru)){ 
				return 1;
			} else {
				cout << "WRONG PIN, TRY AGAIN" << endl;
				count++;
			}
		}
		
	} else {
		cout << "WRONG EMAIL, TRY AGAIN" << endl;
		count++;
	}
}
	return 0;
}

void ui_penarikan(int tunai){
	header("PENARIKAN DANA");
	cout << "\n\n\t\t\t\t\t JUMLAH SALDO :" << user.saldo;
	cout << "\n\t\t\t\t\t TUNAI YANG AKAN DITARIK :" << tunai;
	kurangSaldo(tunai);
	cout << "\n\t\t\t\t\t JUMLAH SALDO SEKARANG :" << user.saldo << endl;system("pause");
}


int main() {
	system("color 1F");
	header_login('e');
	if(!log_in()){
		return 0;
	} else{
		system("cls");
		penarikan: 
		enum option{P50=1,P100,P200,P500,LAINNYA};
		int option =  menuPenarikan();
		system("cls");
		while(true){
			switch(option){
				case P50:  ui_penarikan(50000);break;
				case P100: ui_penarikan(100000);break;
				case P200: ui_penarikan(200000);break;
				case P500: ui_penarikan(500000);break;
				case LAINNYA: 
					enum option{TRANSFER=1,INFORMASI,UBAH,PENARIKAN,lAINNYA};
					while(true){
						lain:
						int opt = menuLainnya();
						system("cls");
						switch(opt){
							case TRANSFER: 
								uiTransfer();
								break;
							case INFORMASI:
								uiInformasi();
								break;
							case UBAH:
								uiUbah();
								break;
							case PENARIKAN:
								uiPenarikan();
							default:system("cls"); gotoxy(0,30);cout << "Input Salah, harap masukkan kembali";gotoxy(0,0); goto lain;
						}
						system("cls");
						goto lain;
						
					}
				default:system("cls"); gotoxy(0,30);cout << "Input Salah, harap masukkan kembali";gotoxy(0,0); goto penarikan;
			}
			system("cls");
			goto penarikan;
		}
	}
}

int menuPenarikan(){
	int option;
	printf("========================================================================================================================================================================");
	printf("\n\t\t\t\t                                             SELAMAT DATANG");
	printf("\n\t\t\t\t                                                   DI");
	printf("\n\t\t\t\t                                           BANK ATM ROBBANI\n");
	printf("========================================================================================================================================================================");
	printf("\n\n\n\n");
	printf("\t\t\t\t                                 MENU UTAMA\n\t\t\t\t\t\t");
	printf("\n\t\t\t\t                                            HAI, %s\n", user.nama);
	printf("\n\n\n\t\t\t\t\t\t[1]<===\tPENARIKAN RP.50.000,\t\t\t PENARIKAN RP.100.000--->[2]");
	printf("\n\n\n\t\t\t\t\t\t[3]<===\tPENARIKAN RP.200.000,\t\t\t PENARIKAN RP.500.000--->[4]");
	printf("\n\n\n\t\t\t\t\t\t[5]<---\tMENU LAINNYA");
	printf("\n\n\n\t\t\t\t\t\tPILIHAN ANDA : "); cin >> option;
	return option;
}

int menuLainnya(){
	int option;
	printf("========================================================================================================================================================================");
	printf("\n\t\t\t\t                                             MENU LAINNYA");
	printf("\n\t\t\t\t                                                   DI");
	printf("\n\t\t\t\t                                           BANK ATM ROBBANI\n");
	printf("========================================================================================================================================================================");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t                                 MENU UTAMA\n");
	printf("\n\n\n\t\t\t\t\t\t[1]<===\tTRANSFER \t\t\t INFORMASI SALDO--->[2]");
	printf("\n\n\n\t\t\t\t\t\t[3]<===\tUBAH PIN,\t\t\t PENARIKAN TUNAI--->[4]");
	printf("\n\n\n\t\t\t\t\t\t[5]<---\tKEMBALI");
	printf("\n\n\n\t\t\t\t\t\tPILIHAN ANDA : "); cin >> option;
	return option;
}

void uiTransfer(){
	Nasabah penerima;
	int saldo;
	char choice;
	header("TRANSFER");
	cout << "\n\n\t\t\t\t\t\t MASUKKAN NO REKENING TUJUAN : "; cin >> penerima.noRekening;
	cout << endl;
	if(cekRekening(penerima) == 1){
		cout <<"\n\t\t\t\t\t\t\t TARGET : " <<  target.nama << endl;
		cout <<"\t\t\t\t\t\t\t MASUKKAN JUMLAH SALDO YANG AKAN DI TRANSFER : "; cin >> saldo;
		if(cekSaldo(user,saldo)){
			cout << "\t\t\t\t\t\t\t YAKIN ? (SELAIN Y MAKA TRANSFER AKAN DIBATALKAN)";cin >> choice;
			if(choice == 'y' || choice == 'Y' ){
				Transfer(target,saldo);
			}else {
				cout << "TRANSFER AKAN DIBATALKAN" << endl;
				system("pause");
			}
		} else {
			cout << "SALDO TIDAK MENCUKUPI UNTUK MELAKUKAN TRANSFER" << endl;
			system("pause");
		}
	} else {
		system("cls");
		gotoxy(0,20);
		cout << "NO REKENING TIDAK DITEMUKAN";
		gotoxy(0,0);
		uiTransfer();
	}
}

int cekRekening(Nasabah penerima){
	rewind(data);
	while (fread(&target,recsize,1,data) == 1)
    {
    	if(strcmp(target.noRekening, penerima.noRekening) == 0){
    		return 1;
		}
    }
    return 0;
}

void uiInformasi(){
			header("INFORMASI");
			cout << "EMAIL				" << user.email << "\n" ; 
			cout << "KODE BANK			" << user.kodeBank << "\n" ; 
			cout << "NAMA				" << user.nama << "\n" ; 
			cout << "NO REKENING			" << user.noRekening << "\n" ; 
			cout << "PIN				" << user.PIN << "\n" ; 
			cout << "SALDO				" << user.saldo << "\n" ; 
			cout << "STATUS				" << user.status << "\n" ; 
			cout << "Tanggal Lahir			" << user.tanggalLahir.day << "/" << user.tanggalLahir.mount << "/" << user.tanggalLahir.year; 
			system("pause");
}

void uiUbah(){
		Nasabah update;
		header("UBAH PIN");	
		cout << "\n\t\t\t\t\t\t\t MASUKKAN TANGGAL LAHIR : " << endl;
		cout << "\t\t\t\t\t\t\t HARI  : "; cin >> update.tanggalLahir.day;
		cout << "\t\t\t\t\t\t\t BULAN : "; cin >> update.tanggalLahir.mount;
		cout << "\t\t\t\t\t\t\t TAHUN : "; cin >> update.tanggalLahir.year;
		if(cekDate(update)){
			system("cls");
			header("UBAH PIN");
			cout << "\n\t\t\t\t\t\t\t MASUKKAN PIN LAMA : " << endl; cin >> update.PIN;
			if(isPinLama(update)){
				cout << "\n\t\t\t\t\t\t\t MASUKKAN PIN BARU : " << endl; cin >> update.PIN;
				updatePIN(update);
			}
		} else {
			system("cls");
			gotoxy(0,25);
			cout << "TANGGAL LAHIR YANG DIMASUKKAN BERBEDA, HARAP GANTI KEMBALI";
			uiUbah();
		}
}

void uiPenarikan(){
	cout << "informasi";
}

int cekSaldo(Nasabah nb, int tunai){
	if(nb.saldo < tunai){
		return 0;
	} else {
		return 1;
	}
}

void Transfer(Nasabah target, int saldo){
	Nasabah pengirim,penerima;
	tambahSaldo(saldo, target);
	kurangSaldo(saldo);
}

int cekDate(Nasabah update){
	if(update.tanggalLahir.day == user.tanggalLahir.day && update.tanggalLahir.mount == user.tanggalLahir.mount && update.tanggalLahir.year == user.tanggalLahir.year){
		return 1;
	} else{
		return 0;
	}
}

int isPinLama(Nasabah update){
	if(update.PIN == user.PIN){
		return 1;
	} else {
		return 0;
	}
}


