// Suan henuz modul 1'i derleyebiliyor.
// Grup ana menuyu birlestirirken bu dosya ortak main.cpp ile degistirilecek.

#include <iostream>
#include "modul1.h"
// #include "modul2.h"
 #include "modul3.h"
// #include "modul4.h"
using namespace std;

int main() {
    ornekKitaplariYukle();

    int secim = -1;
    while (secim != 0) {
        cout << endl;
        cout << "=====================================================" << endl; // Cok sanatsal bir calisma
        cout << " KAMPUS KUTUPHANE VE OGRENCI HIZMETLERI OTOMASYONU" << endl;
        cout << "=====================================================" << endl;
        cout << "[1] MODUL 1: Bagli Listeler ve Dosya Islemleri" << endl;
        cout << "[2] MODUL 2: Yigin ve Kuyruk (henuz eklenmedi)" << endl;
        cout << "[3] MODUL 3: Siralama ve Arama Algoritmalari" << endl;
        cout << "[4] MODUL 4: Graf ve Rota Analizi (henuz eklenmedi)" << endl;
        cout << "[0] Bellegi Temizle (delete) ve Cikis" << endl;
        secim = okuTamSayi("Seciminiz: ");

        switch (secim) {
            case 1: modul1Menu(); break;
            case 3: modul3Menu(); break;
            case 2:
                cout << "[!] Bu modul henuz eklenmedi." << endl;
                break;
            case 4:
                cout << "[!] Bu modul henuz eklenmedi." << endl;
                break;
            case 0:
                break;
            default:
                cout << "[!] Gecersiz secim, 0 ile 4 arasinda bir sayi giriniz." << endl;
        }
    }

    kitapListesiniTemizle();
    cout << "Bellek temizlendi, program kapatildi." << endl;
    return 0;
}