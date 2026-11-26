// BLP Veri Yapilari Final Projesi 1. Modul Baslangici
// Modul 1: Cift yonlu dogrusal bagli liste (kitap katalogu)
// Bu dosya ilk surumdur, baslangic ve son ekleme, ileri ve geri listeleme, bellek temizleme.

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Kitap kaydi ayni zamanda listenin dugumudur
struct Kitap {
    int id;
    string ad;
    string yazar;
    int sayfa;
    Kitap* next;
    Kitap* prev;
};

// Listenin ilk ve son dugumu
Kitap* kitapBas = NULL;
Kitap* kitapSon = NULL;

// ---------- Yardimci fonksiyonlar

// Klavyeden tam sayi okur, gecersiz girdide tekrar sorar
int okuTamSayi(const string& mesaj) {
    string satir;
    int deger;
    while (true) {
        cout << mesaj;
        getline(cin, satir);
        istringstream iss(satir);
        if ((iss >> deger) && (iss >> ws).eof()) {
            return deger;
        }
        cout << "[!] Gecersiz giris, lutfen bir sayi giriniz." << endl;
    }
}

// Klavyeden bos olmayan bir metin okur
string okuMetin(const string& mesaj) {
    string satir;
    while (true) {
        cout << mesaj;
        getline(cin, satir);
        if (!satir.empty()) {
            return satir;
        }
        cout << "[!] Bos giris kabul edilmez." << endl;
    }
}

// Verilen ID listede var mi kontrol eder
bool idVarMi(int id) {
    Kitap* gezen = kitapBas;
    while (gezen != NULL) {
        if (gezen->id == id) {
            return true;
        }
        gezen = gezen->next;
    }
    return false;
}

// Yeni bir kitap dugumu olusturur, baglantilari NULL baslatir
Kitap* kitapOlustur(int id, const string& ad, const string& yazar, int sayfa) {
    Kitap* yeni = new Kitap;
    yeni->id = id;
    yeni->ad = ad;
    yeni->yazar = yazar;
    yeni->sayfa = sayfa;
    yeni->next = NULL;
    yeni->prev = NULL;
    return yeni;
}

// ---------- Ekleme islemleri

// Kitabi listenin basina ekler, basarili ise true doner
bool kitapBasaEkle(int id, const string& ad, const string& yazar, int sayfa) {
    if (idVarMi(id)) {
        cout << "[!] Bu ID zaten kayitli: " << id << endl;
        return false;
    }
    Kitap* yeni = kitapOlustur(id, ad, yazar, sayfa);
    if (kitapBas == NULL) {
        // Liste bos ise yeni dugum hem bas hem son olur
        kitapBas = yeni;
        kitapSon = yeni;
    } else {
        yeni->next = kitapBas;
        kitapBas->prev = yeni;
        kitapBas = yeni;
    }
    cout << "[+] Kitap basa eklendi: ID " << id << endl;
    return true;
}

// Kitabi listenin sonuna ekler, basarili ise true doner
bool kitapSonaEkle(int id, const string& ad, const string& yazar, int sayfa) {
    if (idVarMi(id)) {
        cout << "[!] Bu ID zaten kayitli: " << id << endl;
        return false;
    }
    Kitap* yeni = kitapOlustur(id, ad, yazar, sayfa);
    if (kitapSon == NULL) {
        kitapBas = yeni;
        kitapSon = yeni;
    } else {
        yeni->prev = kitapSon;
        kitapSon->next = yeni;
        kitapSon = yeni;
    }
    cout << "[+] Kitap sona eklendi: ID " << id << endl;
    return true;
}

// ---------- Listeleme islemleri

void kitapYazdir(const Kitap* k) {
    cout << "ID: " << k->id
         << " | Ad: " << k->ad
         << " | Yazar: " << k->yazar
         << " | Sayfa: " << k->sayfa << endl;
}

// next baglantisi ile bastan sona listeler
void kitaplariIleriListele() {
    if (kitapBas == NULL) {
        cout << "[!] Katalog bos, listelenecek kitap yok." << endl;
        return;
    }
    cout << "--- Kitaplar (bastan sona) ---" << endl;
    Kitap* gezen = kitapBas;
    while (gezen != NULL) {
        kitapYazdir(gezen);
        gezen = gezen->next;
    }
}

// prev baglantisi ile sondan basa listeler
void kitaplariGeriListele() {
    if (kitapSon == NULL) {
        cout << "[!] Katalog bos, listelenecek kitap yok." << endl;
        return;
    }
    cout << "--- Kitaplar (sondan basa) ---" << endl;
    Kitap* gezen = kitapSon;
    while (gezen != NULL) {
        kitapYazdir(gezen);
        gezen = gezen->prev;
    }
}

// ---------- Bellek temizleme

// Listedeki tum dugumleri  delete eder
void kitapListesiniTemizle() {
    Kitap* gezen = kitapBas;
    while (gezen != NULL) {
        Kitap* silinecek = gezen;
        gezen = gezen->next;
        delete silinecek;
    }
    kitapBas = NULL;
    kitapSon = NULL;
}

// ---------- Ornek veri ve menu

void ornekKitaplariYukle() {
    kitapSonaEkle(101, "Algoritmalar", "Ali Yilmaz", 350);
    kitapSonaEkle(102, "Veri Yapilari", "Ayse Demir", 420);
    kitapSonaEkle(103, "C++ ile Programlama", "Mehmet Kaya", 280);
    kitapSonaEkle(104, "Isletim Sistemleri", "Zeynep Arslan", 510);
}

void kitapBasaEkleMenu() {
    int id = okuTamSayi("Kitap ID: ");
    string ad = okuMetin("Kitap adi: ");
    string yazar = okuMetin("Yazar adi: ");
    int sayfa = okuTamSayi("Sayfa sayisi: ");
    if (sayfa <= 0) {
        cout << "[!] Sayfa sayisi pozitif olmalidir." << endl;
        return;
    }
    kitapBasaEkle(id, ad, yazar, sayfa);
}

void kitapSonaEkleMenu() {
    int id = okuTamSayi("Kitap ID: ");
    string ad = okuMetin("Kitap adi: ");
    string yazar = okuMetin("Yazar adi: ");
    int sayfa = okuTamSayi("Sayfa sayisi: ");
    if (sayfa <= 0) {
        cout << "[!] Sayfa sayisi pozitif olmalidir." << endl;
        return;
    }
    kitapSonaEkle(id, ad, yazar, sayfa);
}

void modul1Menu() {
    int secim = -1;
    while (secim != 0) {
        cout << endl;
        cout << "--- [MODUL 1: BAGLI LISTELER & DOSYA ISLEMLERI] ---" << endl;
        cout << "1. Kitap Basa Ekle" << endl;
        cout << "2. Kitap Sona Ekle" << endl;
        cout << "3. Kitap Araya Ekle (Hedef ID Oncesine)" << endl;
        cout << "4. Kitap Sil (ID ile)" << endl;
        cout << "5. Kitaplari Bastan Sona Listele" << endl;
        cout << "6. Kitaplari Sondan Basa Listele" << endl;
        cout << "7. Katalog Istatistik Analizi" << endl;
        cout << "8. Duyuru Panosu" << endl;
        cout << "9. Dosyaya Yaz ve Dosyadan Oku" << endl;
        cout << "0. Ana Menuye Don" << endl;
        secim = okuTamSayi("Alt Seciminiz: ");

        switch (secim) {
            case 1: kitapBasaEkleMenu(); break;
            case 2: kitapSonaEkleMenu(); break;
            case 5: kitaplariIleriListele(); break;
            case 6: kitaplariGeriListele(); break;
            case 3:
            case 4:
            case 7:
            case 8:
            case 9:
                cout << "[!] Bu ozellik henuz eklenmedi." << endl;
                break;
            case 0:
                break;
            default:
                cout << "[!] Gecersiz secim, 0 ile 9 arasinda bir sayi giriniz." << endl;
        }
    }
}

// Gecici  modul tek basina denenebilsin diye var, entegrasyonda ana programdaki menu kullanilcak
int main() {
    ornekKitaplariYukle();
    modul1Menu();
    kitapListesiniTemizle();
    return 0;
}