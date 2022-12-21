/* Program: ATM RABBANI.cpp
* Deskripsi: Desimal to Romawi
* Nama: 
  > Mochamad Fathur Rabbani
  > Muhammad Hanif
  > Yusuf
* Tanggal/versi: 01/11/2022
*/


#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include "windows.h"

using namespace std;

struct Date{
	int year;
	int mount;
	int day;
};


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
int saldoMin = 50000;
void Header(string title);
/*Procedure untuk menampilkan header sebagai tampilan, kata kata yang ditampilkan akan masuk ke dalam variabel
I.S : Header tidak Muncul di layar
F.S : Header sudah mucnul di layar
*/

void headerLogin(char flag);
/*Procedure untuk menampilkan header login sesuai dengan flag nya. jika flag e maka headerLogin untuk email, selainnya maka untuk memasukkan PIN
I.S = Header Login tidak tampil di layar
F.S = Header login sudah tampil di layar
*/
void gotoxy(int x, int y);
void uiPenarikan(int tunai);

int menuPenarikan();
/*Procedure untuk menampilkan menu melakukan penarikan langsung, menu ini akan muncul setelah nasabah melakukan log in 
I.S : Menu penarikan tidak tampil di layar
F.S : Menu penarikan tidak tampil di layar*/
int menuLainnya();
/*Procedure untuk menamilkan menu lainnya, seperti: 
1. Transfer 
2. Informasi
3. Ubah PIN 
4. Penarikan 
I.S : Menu Lainnya tidak tampil di layar
F.S : Menu lainnya sudah mincul di layar*/

void uiUbah();
/*Procedure untuk menampilkan user interface untuk ubah PIN
I.S : Tampilan UI ubah PIN tidak tampil di layar
F.S : Tampilan Ui ubah PIN sudah tampil di layar*/
void uiInformasi();
/*Procedure untuk menampilkan user interface untuk Informasi Nasabah
I.S : Tampilan UI Informasi Nasabah tidak tampil di layar
F.S : Tampilan Ui Informasi Nasabah sudah tampil di layar*/
void uiTransfer();
/*Procedure untuk menampilkan user interface untuk Transfer
I.S : Tampilan UI Transfer tidak tampil di layar
F.S : Tampilan Ui Transfer sudah tampil di layar*/
void Transfer(Nasabah target, int nominal);
/*Procedure untuk melakukan transfer kepada Nasabah target sejumlah nomina
I.S : Transfer belum terjadi
F.S : Transfer sudah terjadi, jumlah saldo Nasabah Target bertambah sesuai nominal sedangkan jumlah saldo user
berkurang sesuai nominal*/
void uiPenarikan();
/*Procedure untuk menampilkan user interface untuk Penarikan Custom
I.S : Tampilan UI Penarikan tidak tampil di layar
F.S : Tampilan Ui Penarikan sudah tampil di layar*/
int cekRekening(Nasabah penerima);
/*Fungsi untuk melakukan pengecekan nomor rekening dari Nasabah penerima. fungsi akan mengembalikan nilai 0 jika 
rekening tidak terdaftar pada database dan akan mengembalikan nilai 1 jika terdaftar pada database
*/
int cekSaldo(Nasabah nb, int tunai);
int isNominalTF(int nominal);
/*Fungsi untuk melakukan pengecekan nominal Transfer apakah valid (>= Rp.10000) atau tidak. Fungsi akan mengembalikan nilai 
0 jika tidak valid. dan fungsi akan mengembalikan nilai 1 jika valid */

int isNominalTR(int nominal);
/*Fungsi untuk melakukan pengecekan nominal Transfer apakah valid (nominal % 50 == 0 AND nominal >= 50) atau tidak. Fungsi akan mengembalikan nilai 
0 jika tidak valid. dan fungsi akan mengembalikan nilai 1 jika valid */

int isDateSame(Nasabah update);
/*Fungsi untuk melakukan pengecekan Date / Tanggal lahir Nasabah update dengan Nasabah user apakah sama atau tidak.
Fungsi akan mengembalikan nilai 0 jika berbeda, dan fungsi akan mengembalikan nilai 1 jika sama*/
int isPinLama(Nasabah update);
/*Fungsi untuk melakukan pengecekan apakah pin dari Nasabah update sama dengan Nasabah user. 
Fungsi akan mengembalikan nilai 0 jika berbeda, dan fungsi akan mengembalikan nilai 1 jika sama*/
void updatePIN(Nasabah update);
/*Prosedur untuk melakukan perubahan PIN Nasabah user menjadi PIN Nasabah update. 
I.S : PIN Nasabah user masih sama 
F:S : PIN Nasabah user sudah terupdate / berunbah*/
int logIn();
/*Fungsi untuk menampung seluruh kegiatan log in, fungsi akan mengembalikan nilai 0 jika log in gagal, dan fungsi akan mengembalikan
nilai 1 jika log in berhasil*/

void error(string keterangan);


int main() {
	system("color 1F");
	headerLogin('e');
	if(!logIn()){
		return 0;
	} else{
		system("cls");
		penarikan: 
		char option =  menuPenarikan();
		system("cls");
		while(true){
			switch(option){
				case '1':  uiPenarikan(50000);break;
				case '2': uiPenarikan(100000);break;
				case '3': uiPenarikan(200000);break;
				case '4': uiPenarikan(500000);break;
				case '5': 
					while(true){
						lain:
						int opt = menuLainnya();
						system("cls");
						switch(opt){
							case '1': 
								uiTransfer();
								break;
							case '2':
								uiInformasi();
								break;
							case '3':
								uiUbah();
								break;
							case '4':
								uiPenarikan();
								break;
							case '5':
								system("cls");goto penarikan;
							default:system("cls"); error("INPUT SALAH, HARAP MASUKKAN KEMBALI"); goto lain;
						}
						system("cls");
						goto lain;
						
					}
				default:system("cls"); gotoxy(0,30);cout << "INPUT SALAH, HARAP MASUKKAN KEMBALI";gotoxy(0,0); goto penarikan;
			}
			system("cls");
			goto penarikan;
		}
	}
}

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

void headerLogin(char flag){
	system("cls");
	printf("\n");
	printf("========================================================================================================================================================================");
	printf("\t\t\t\t                                             SELAMAT DATANG");
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
	cin >> (*baru).email;fflush(stdin);
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
	cin >> (*baru).PIN;fflush(stdin);
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
	Nasabah du,baru;
	rewind(data);
	user.saldo = user.saldo - tunai;
	while (fread(&du,recsize,1,data) == 1){
			if(strcmp(du.email,user.email) == 0){
					strcpy(du.email,user.email);
					strcpy(du.kodeBank,user.kodeBank);
					strcpy(du.nama,user.nama);
					strcpy(du.noRekening,user.noRekening);
					strcpy(du.PIN,user.PIN);
					du.status = user.status;
					du.saldo = user.saldo;
					du.tanggalLahir.day = user.tanggalLahir.day;
					du.tanggalLahir.mount = user.tanggalLahir.mount;
					du.tanggalLahir.year = user.tanggalLahir.year;
					fseek(data, -recsize, SEEK_CUR);
					fwrite(&du,recsize,1,data);
					break;
				} 
	}
	
} 

void tambahSaldo(int tunai, Nasabah nacabah){
	Nasabah du;
	rewind(data);
	int p = 1;
	while (fread(&du,recsize,1,data) == 1 && p){
			if(strcmp(du.email,nacabah.email)== 0){
					Nasabah baru;
					du.saldo = du.saldo + tunai;
					strcpy(baru.email,du.email);
					strcpy(baru.kodeBank,du.kodeBank);
					strcpy(baru.nama,du.nama);
					strcpy(baru.noRekening,du.noRekening);
					strcpy(baru.PIN,du.PIN);
					baru.status = du.status;
					baru.saldo = du.saldo;
					baru.tanggalLahir.day = du.tanggalLahir.day;
					baru.tanggalLahir.mount = du.tanggalLahir.mount;
					baru.tanggalLahir.year = du.tanggalLahir.year;
					fseek(data, -recsize, SEEK_CUR);
					fwrite(&baru,recsize,1,data);
					p = 0;
					break;
				} 
	}
} 

int logIn(){
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
		headerLogin('f');	
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

void uiPenarikan(int tunai){
	if(cekSaldo(user,tunai)){
		Header("PENARIKAN DANA");
		cout << "\n\n\t\t\t\t\t JUMLAH SALDO :" << user.saldo;
		cout << "\n\t\t\t\t\t TUNAI YANG AKAN DITARIK :" << tunai;
		kurangSaldo(tunai);
		cout << "\n\t\t\t\t\t JUMLAH SALDO SEKARANG :" << user.saldo << endl;system("pause");
	} else {
		error("SALDO TIDAK MENCUKUPI UNTUK MELAKUKAN PENARIKAN TUNAI");
		system("pause");
	}
	
}

int menuPenarikan(){
	char option;
	printf("========================================================================================================================================================================");
	printf("\n\t\t\t\t                                             SELAMAT DATANG");
	printf("\n\t\t\t\t                                                   DI");
	printf("\n\t\t\t\t                                           BANK ATM ROBBANI\n");
	printf("========================================================================================================================================================================");
	printf("\n\n\n\n");
	printf("\t\t\t\t\t                                 MENU UTAMA");
	printf("\n\t\t\t\t                                            HAI, %s\n", user.nama);
	printf("\n\n\n\t\t\t\t\t\t[1]<===\tPENARIKAN RP.50.000,\t\t\t PENARIKAN RP.100.000--->[2]");
	printf("\n\n\n\t\t\t\t\t\t[3]<===\tPENARIKAN RP.200.000,\t\t\t PENARIKAN RP.500.000--->[4]");
	printf("\n\n\n\t\t\t\t\t\t[5]<---\tMENU LAINNYA");
	printf("\n\n\n\t\t\t\t\t\tPILIHAN ANDA : "); cin >> option;
	return option;
}

int menuLainnya(){
	char option;
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
	if(cekSaldo(user,0)){
	
	Nasabah penerima;
	int nominal;
	char choice;
	Header("TRANSFER");
	cout << "\n\n\t\t\t\t\t\t MASUKKAN NO REKENING TUJUAN : "; cin >> penerima.noRekening;
	cout << endl;
	if(cekRekening(penerima) == 1){
		TARGET:
		cout <<"\n\t\t\t\t\t\t\t TARGET : " <<  target.nama << endl;
		cout <<"\t\t\t\t\t\t\t MASUKKAN JUMLAH SALDO YANG AKAN DI TRANSFER : "; cin >> nominal;
		if(isNominalTF(nominal)){
		if(cekSaldo(user,nominal)){
			cout << "\t\t\t\t\t\t\t YAKIN ? (SELAIN Y MAKA TRANSFER AKAN DIBATALKAN)";cin >> choice;
			if(choice == 'y' || choice == 'Y' ){
				Transfer(target,nominal);
			}else {
				cout << "TRANSFER AKAN DIBATALKAN" << endl;
				system("pause");
			}
		} else {
			cout << "SALDO TIDAK MENCUKUPI UNTUK MELAKUKAN TRANSFER" << endl;
			system("pause");
		}
			error("NOMINAL TERLALU KECIL, HARAP MASUKKAN KEMBALI");
			goto TARGET;
		}
	} else {
		system("cls");
		gotoxy(0,20);
		cout << "NO REKENING TIDAK DITEMUKAN";
		gotoxy(0,0);
		uiTransfer();
	}
	}else {
		error("SALDO YANG DIMILIKI TIDAK MENCUKUPI UNTUK MELAKUKAN TRANSFER");
		system("pause");
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

int isNominalTF(int nominal){
	if(nominal > 10000){
		return 1;
	} else{
		return 0;
	}
}
int isNominalTR(int nominal){
	if(nominal >= 50000 && nominal % 50000 == 0){
		return 1;
	} else{
		return 0;
	}
}

void uiInformasi(){
			Header("INFORMASI");
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
		Header("UBAH PIN");	
		cout << "\n\t\t\t\t\t\t\t MASUKKAN TANGGAL LAHIR : " << endl;
		cout << "\t\t\t\t\t\t\t HARI  : "; cin >> update.tanggalLahir.day;
		cout << "\t\t\t\t\t\t\t BULAN : "; cin >> update.tanggalLahir.mount;
		cout << "\t\t\t\t\t\t\t TAHUN : "; cin >> update.tanggalLahir.year;
		if(isDateSame(update)){
			system("cls");
			Header("UBAH PIN");
			input:
			cout << "\n\t\t\t\t\t\t\t MASUKKAN PIN LAMA : " ;
			cin >> update.PIN;
			if(isPinLama(update)){
				cout << "\n\t\t\t\t\t\t\t MASUKKAN PIN BARU : " ;
				cin >> update.PIN;
				updatePIN(update);
			} else {
				gotoxy(0,25);
				cout << "PIN YANG DIMASUKKAN SALAH, HARAP MASUKKAN KEMBALI";
				goto input;
			}
		} else {
			system("cls");
			gotoxy(0,25);
			cout << "TANGGAL LAHIR YANG DIMASUKKAN BERBEDA, HARAP GANTI KEMBALI";
			uiUbah();
		}
}

void uiPenarikan(){
	TARIK:
	int nominal;
	system("cls");
	Header("PENARIKAN DANA");
	cout << "\t\t\t\t\t\t\t\ SALDO : "; cin >> nominal;
	if(isNominalTR(nominal)){
		if(cekSaldo(user,nominal)){
			kurangSaldo(nominal);
			cout << "\t\t\t\t\t\t\t\ PENARIKAN BERHASIL , SALDO SISA ANDA  : " << user.saldo;
		} else{
		} error("SALDO TIDAK MENCUKUPI ");
		system("pause");
	}else {
		error("NOMINAL TIDAK VALID, HARAP MASUKKAN KEMBALI");
		system("pause");
		goto TARIK;
	}
	
	
}

int cekSaldo(Nasabah nb, int nominal){
	if((nb.saldo-nominal) >= saldoMin){
		return 1;
	} else {
		return 0;
	}
}

void Transfer(Nasabah target, int saldo){
	Nasabah pengirim,penerima;
	tambahSaldo(saldo, target);
	kurangSaldo(saldo);
}

int isDateSame(Nasabah update){
	if(update.tanggalLahir.day == user.tanggalLahir.day && update.tanggalLahir.mount == user.tanggalLahir.mount && update.tanggalLahir.year == user.tanggalLahir.year){
		return 1;
	} else{
		return 0;
	}
}

int isPinLama(Nasabah update){
	if(strcmp(update.PIN,user.PIN) == 0){
		return 1;
	} else {
		return 0;
	}
}

void updatePIN(Nasabah update){
	rewind(data);
	Nasabah baru,du;
	while (fread(&du,recsize,1,data) == 1 ){
			if(strcmp(du.email,user.email)== 0){
					strcpy(baru.email,du.email);
					strcpy(baru.kodeBank,du.kodeBank);
					strcpy(baru.nama,du.nama);
					strcpy(baru.noRekening,du.noRekening);
					strcpy(baru.PIN,update.PIN);
					baru.status = du.status;
					baru.saldo = du.saldo;
					baru.tanggalLahir.day = du.tanggalLahir.day;
					baru.tanggalLahir.mount = du.tanggalLahir.mount;
					baru.tanggalLahir.year = du.tanggalLahir.year;
					fseek(data, -recsize, SEEK_CUR);
					fwrite(&baru,recsize,1,data);
					fread(&user,recsize,1,data);
					break;
				} 
	
}


}

void Header(string title){
	printf("========================================================================================================================================================================");
	cout << "\t\t\t\t\t\t\t\t\t " << title << endl;
	printf("========================================================================================================================================================================");
}

void error(string keterangan){
	gotoxy(0,30);cout << keterangan ;gotoxy(0,0); 
}

