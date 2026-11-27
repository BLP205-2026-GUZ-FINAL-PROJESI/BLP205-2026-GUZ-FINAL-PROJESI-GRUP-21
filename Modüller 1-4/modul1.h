// BLP 205 Veri Yapilari Final Projesi
// Modul 1'in baslik (header/h) dosyasidir | diger modullerin kullanacagi tanimlar buradadir | Sude Tandogan
// bu sekilde kod devamli yeniden kullanilabiliyor


#ifndef MODUL1_H
#define MODUL1_H

#include <string>

// Kitap kaydi ayni zamanda cift yonlu listenin dugumudur
struct Kitap {
    int id;
    std::string ad;
    std::string yazar;
    int sayfa;
    Kitap* next;
    Kitap* prev;
};

// Listenin ilk ve son dugumu (tanimlari modul1.cpp icinde yer aliyro)
extern Kitap* kitapBas;
extern Kitap* kitapSon;

// Ortak girdi fonksiyonlari  
int okuTamSayi(const std::string& mesaj);
std::string okuMetin(const std::string& mesaj);

// Liste islemleri temelleri
bool idVarMi(int id);
bool kitapBasaEkle(int id, const std::string& ad, const std::string& yazar, int sayfa);
bool kitapSonaEkle(int id, const std::string& ad, const std::string& yazar, int sayfa);
void kitaplariIleriListele();
void kitaplariGeriListele();
void kitapListesiniTemizle();

// Ornek veri ve menumuz
void ornekKitaplariYukle();
void modul1Menu();

#endif