#include <stdio.h>

typedef struct{
	int year;
	int mount;
	int day;
}Date;


typedef struct{
	int hour;
	int minute;
	int second;
}Time;


typedef struct{
	int jumlahUang;
	int pecahan50;
	int pecahan100;
}mesinATM;


typedef struct{
	char Nama;
	char kodeBank;
	char NoRekening;
	char PIN;
	char Email;
	int saldo;
	Date tanggalLahir;
}Nasabah;


//Modul Login
void inputEmail(Nasabah *user);
/* prosedur untuk mengisi Email
I.S : PIN Nasabah belum diketahui
F.S : PIN Nasabah sudah diketahui */
 
 
//Modul PIN
void inputPIN(Nasabah *user);
/* prosedur untuk mengisi PIN
I.S : PIN Nasabah belum diketahui
F.S : PIN Nasabah sudak diketahui */


//Modul Transfer
void Transfer(Nasabah *user, Nasabah *target, int nominal);
/* prosedur untuk Transfer dari user ke target denga jumlah Dana tertentu
I.S : Dana belum terTransfer ke Rekening target
F.S : Dana sudah tertransfer ke Rekening target sesuai jumlah nominal dan Rekening user berkurang sesuai jumlah nominal */


//Modul Penarikan
void inputDana(int *Dana);
/* prosedur untuk mengisi dana/jumlah uang untuk kebutuhan tertentu
I.S : Dana yang di inputkan belum diketahui
F.S : Dana yang di inputkan sudah di ketahui */


int cekEmail(char Email);
/* fungsi untuk melakukan pengecekan apakah Email yang di inputkan ada atau tidak. jika ada, maka akan mengembalikan nilai 1, 
jika tidak maka akan mengembalikan nilai 0. */ 


int cekPIN(Nasabah *user, char PIN);
/* fungsi untuk melakukan pengecekan apakah PIN yang di masukkan sesuai denga user. jika PIN sesuai maka akan mengembalikan nilai 1,
jika PIN tidak sesuai maka akan mengembalikan nilai 0. */


void inputRekening(Nasabah *Rekening);
/* prosedur untuk mengimputkan nomor Rekening
I.S nomor Rekening belum diketahui
F.S nomor Rekening sudah diketahui */


int cekRekening(Nasabah *Rekening);
/* fungsi untuk mengecek Rekening dari suatu database, apakah ada atau tidak ada. jika ada maka fungsi akan mengembalikan nilai 1,
jika tidak ada maka fungsi akan mengembalikan nilai 0. */


int cekSaldo(Nasabah user, Nasabah target, int Saldo);
/* fungsi untuk melakukan pengecekan saldo ketika user melakukan Transfer. jika jumlah saldo yang di Tranfer < jumlah saldo maka saldo user
(-jumlah Transvfer) > 50 maka akan mengembalikan nilai 1,  jika sebaliknya akan mengembalikan nilai 0. */


void UpdatePIN(Nasabah *user, char PINbaru);
/* prosedur untuk mengubah PIN nasabah user
I.S : PIN masih sama
F.S : PIN sudah tertukar */


void UpdateEmail(Nasabah *user, char Emailbaru);
/* prosedur untuk mengubah PIN Nasabah
I.S : Email masih sama
F.S : Email sudah Tertukar */


void UpdateSaldo(Nasabah *user, int Saldo);
/* prosedur umtuk mengubah Saldo Nasabah user
I.S : Saldo masih sama
F.S : Saldo sudah tertukar */


void InputDate(Nasabah *user);
/* prosedur untuk mengimputkan tanggal lahir
I.S : Data tanggal lahir belum ada
F.S : Data tanggal lahir sudah ada */





