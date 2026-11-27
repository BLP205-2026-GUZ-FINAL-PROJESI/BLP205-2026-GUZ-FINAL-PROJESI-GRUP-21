// Nisa Medine Kuzay ---- Modul 3: Dizi uzerinde Bubble Sort, Insertion Sort, Quick Sort ve Binary Search
// Kitaplar once bagli listeden diziye aktarilir, siralama bu dizi uzerinde yapilir.

#include <iostream>
#include <string>
#include "modul1.h"
#include "modul3.h"
using namespace std;

struct KitapKaydi {
    int id;
    string ad;
    string yazar;
    int sayfa;
};


// Bagli listedeki kitaplari yeni bir diziye kopyalar, boyut parametresine eleman sayisini yazar
// Liste bos ise NULL doner. Donen dizi delete[] ile silinmelidir.
KitapKaydi* listedenDiziyeAktar(int& boyut) {
    boyut = 0;
    Kitap* gezen = kitapBas;
    while (gezen != NULL) {
        boyut++;
        gezen = gezen->next;
    }
    if (boyut == 0) {
        return NULL;
    }
    KitapKaydi* dizi = new KitapKaydi[boyut];
    gezen = kitapBas;
    int i = 0;
    while (gezen != NULL) {
        dizi[i].id = gezen->id;
        dizi[i].ad = gezen->ad;
        dizi[i].yazar = gezen->yazar;
        dizi[i].sayfa = gezen->sayfa;
        i++;
        gezen = gezen->next;
    }
    return dizi;
}

// Diziyi baska bir diziye kopyalar, iki siralamanin ayni veriyle baslamasi icin kullanilir
KitapKaydi* diziyiKopyala(const KitapKaydi* kaynak, int boyut) {
    KitapKaydi* kopya = new KitapKaydi[boyut];
    for (int i = 0; i < boyut; i++) {
        kopya[i] = kaynak[i];
    }
    return kopya;
}

// Dizinin icerigini tablo seklinde yazdirir
void diziyiYazdir(const KitapKaydi* dizi, int boyut) {
    for (int i = 0; i < boyut; i++) {
        cout << "  " << (i + 1) << ". ID: " << dizi[i].id
             << " | Ad: " << dizi[i].ad
             << " | Sayfa: " << dizi[i].sayfa << endl;
    }
}

// Iki elemanin yerini degistirir, ayni indeks ise sayac artmaz
void takasYap(KitapKaydi* dizi, int a, int b, long& takasSayisi) {
    if (a == b) {
        return;
    }
    KitapKaydi gecici = dizi[a];
    dizi[a] = dizi[b];
    dizi[b] = gecici;
    takasSayisi++;
}


void bubbleSort(KitapKaydi* dizi, int boyut, long& karsilastirma, long& takas) {
    karsilastirma = 0;
    takas = 0;
    for (int i = 0; i < boyut - 1; i++) {
        bool degisti = false;
        for (int j = 0; j < boyut - 1 - i; j++) {
            karsilastirma++;
            if (dizi[j].sayfa > dizi[j + 1].sayfa) {
                takasYap(dizi, j, j + 1, takas);
                degisti = true;
            }
        }
        // Tur boyunca takas olmadiysa dizi zaten siralidir
        if (!degisti) {
            break;
        }
    }
}

void insertionSort(KitapKaydi* dizi, int boyut, long& karsilastirma, long& kaydirma) {
    karsilastirma = 0;
    kaydirma = 0;
    for (int i = 1; i < boyut; i++) {
        KitapKaydi anahtar = dizi[i];
        int j = i - 1;
        while (j >= 0) {
            karsilastirma++;
            if (dizi[j].sayfa > anahtar.sayfa) {
                dizi[j + 1] = dizi[j];
                kaydirma++;
                j--;
            } else {
                break;
            }
        }
        dizi[j + 1] = anahtar;
    }
}

// Son elemani pivot alir, pivot yerine yerlestirilir ve pivotun indeksi doner
int bolumle(KitapKaydi* dizi, int alt, int ust, long& karsilastirma, long& takas) {
    int pivot = dizi[ust].id;
    int i = alt - 1;
    for (int j = alt; j < ust; j++) {
        karsilastirma++;
        if (dizi[j].id <= pivot) {
            i++;
            takasYap(dizi, i, j, takas);
        }
    }
    takasYap(dizi, i + 1, ust, takas);
    return i + 1;
}

void quickSortYinelemeli(KitapKaydi* dizi, int alt, int ust, long& karsilastirma, long& takas) {
    if (alt < ust) {
        int pivotIndeksi = bolumle(dizi, alt, ust, karsilastirma, takas);
        quickSortYinelemeli(dizi, alt, pivotIndeksi - 1, karsilastirma, takas);
        quickSortYinelemeli(dizi, pivotIndeksi + 1, ust, karsilastirma, takas);
    }
}

void quickSort(KitapKaydi* dizi, int boyut, long& karsilastirma, long& takas) {
    karsilastirma = 0;
    takas = 0;
    quickSortYinelemeli(dizi, 0, boyut - 1, karsilastirma, takas);
}

// Bulunursa indeksi, bulunamazsa -1 doner. adimSayisi kac orta eleman bakildigini verir.
int ikiliArama(const KitapKaydi* dizi, int boyut, int hedefId, int& adimSayisi) {
    int alt = 0;
    int ust = boyut - 1;
    adimSayisi = 0;
    while (alt <= ust) {
        adimSayisi++;
        int orta = alt + (ust - alt) / 2;
        if (dizi[orta].id == hedefId) {
            return orta;
        } else if (dizi[orta].id < hedefId) {
            alt = orta + 1;
        } else {
            ust = orta - 1;
        }
    }
    return -1;
}

// Bubble Sort ve Insertion Sort sonuclarini yan yana karsilastirir
void bubbleVeInsertionKarsilastir() {
    int boyut;
    KitapKaydi* asil = listedenDiziyeAktar(boyut);
    if (asil == NULL) {
        cout << "[!] Katalog bos, siralanacak kitap yok." << endl;
        return;
    }

    cout << endl << "Siralamadan once (" << boyut << " kitap):" << endl;
    diziyiYazdir(asil, boyut);

    KitapKaydi* bubbleDizi = diziyiKopyala(asil, boyut);
    KitapKaydi* insertionDizi = diziyiKopyala(asil, boyut);
    long bubbleKars, bubbleTakas, insKars, insKaydirma;

    bubbleSort(bubbleDizi, boyut, bubbleKars, bubbleTakas);
    insertionSort(insertionDizi, boyut, insKars, insKaydirma);

    cout << endl << "Bubble Sort sonucu (sayfa sayisina gore):" << endl;
    diziyiYazdir(bubbleDizi, boyut);
    cout << "  Karsilastirma: " << bubbleKars << " | Takas: " << bubbleTakas << endl;

    cout << endl << "Insertion Sort sonucu (sayfa sayisina gore):" << endl;
    diziyiYazdir(insertionDizi, boyut);
    cout << "  Karsilastirma: " << insKars << " | Kaydirma: " << insKaydirma << endl;

    delete[] asil;
    delete[] bubbleDizi;
    delete[] insertionDizi;
}

// Quick Sort ile ID'ye gore siralar, sonra Binary Search ile arama yapar
void quickSortVeBinarySearch() {
    int boyut;
    KitapKaydi* dizi = listedenDiziyeAktar(boyut);
    if (dizi == NULL) {
        cout << "[!] Katalog bos, siralanacak kitap yok." << endl;
        return;
    }

    cout << endl << "Siralamadan once (" << boyut << " kitap):" << endl;
    diziyiYazdir(dizi, boyut);

    long karsilastirma, takas;
    quickSort(dizi, boyut, karsilastirma, takas);

    cout << endl << "Quick Sort sonucu (ID'ye gore):" << endl;
    diziyiYazdir(dizi, boyut);
    cout << "  Karsilastirma: " << karsilastirma << " | Takas: " << takas << endl;

    cout << endl << "Binary Search denemesi" << endl;
    int hedef = -1;
    while (hedef != 0) {
        hedef = okuTamSayi("Aranacak kitap ID (0 = menuye don): ");
        if (hedef == 0) {
            break;
        }
        int adim;
        int sonuc = ikiliArama(dizi, boyut, hedef, adim);
        if (sonuc >= 0) {
            cout << "[+] ID " << hedef << " bulundu: " << dizi[sonuc].ad
                 << " (" << dizi[sonuc].yazar << "), dizi indeksi " << sonuc
                 << ", adim sayisi " << adim << endl;
        } else {
            cout << "[!] ID " << hedef << " bulunamadi, adim sayisi " << adim << endl;
        }
    }

    delete[] dizi;
}

void modul3Menu() {
    int secim = -1;
    while (secim != 0) {
        cout << endl;
        cout << "--- [MODUL 3: SIRALAMA VE ARAMA ALGORITMALARI] ---" << endl;
        cout << "1. Bubble Sort vs Insertion Sort (Sayfa Sayisina Gore Karsilastirma)" << endl;
        cout << "2. Quick Sort (ID'ye Gore) ve Binary Search (Ikili Arama)" << endl;
        cout << "0. Ana Menuye Don" << endl;
        secim = okuTamSayi("Alt Seciminiz: ");

        switch (secim) {
            case 1: bubbleVeInsertionKarsilastir(); break;
            case 2: quickSortVeBinarySearch(); break;
            case 0: break;
            default:
                cout << "[!] Gecersiz secim, 0 ile 2 arasinda bir sayi giriniz." << endl;
        }
    }
}