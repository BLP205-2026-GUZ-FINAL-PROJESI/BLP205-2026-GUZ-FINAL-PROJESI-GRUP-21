// Idil Derin Yarcin : MODUL 4: GRAF (GRAPH) VERI YAPISI & KAMPUS ROTA ANALIZI
// Dugumler: kampus birimleri, kenar agirliklari: yuruyus mesafesi (metre)
// Graf 2 boyutlu komsuluk matrisi ile tutulur (0 = dogrudan yol yok).

#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <limits>

using namespace std;

const int N = 6;
const int INF = numeric_limits<int>::max();

const string birimler[N] = {
    "Merkez Kutuphane",
    "MYO Bilgisayar Laboratuvari",
    "Muhendislik Binasi",
    "Ogrenci Isleri",
    "Yemekhane ve Sosyal Alan",
    "Konferans Salonu"
};

// Yurume mesafeleri (metre). Graf yonsuz oldugu icin matris simetrik.
const int komsuluk[N][N] = {
    //  0    1    2    3    4    5
    {   0, 150, 200, 100,   0,   0 },  // 0 Merkez Kutuphane
    { 150,   0, 120,   0,   0,   0 },  // 1 MYO Bilgisayar Lab.
    { 200, 120,   0,   0, 180,   0 },  // 2 Muhendislik Binasi
    { 100,   0,   0,   0,  90, 250 },  // 3 Ogrenci Isleri
    {   0,   0, 180,  90,   0, 140 },  // 4 Yemekhane ve Sosyal Alan
    {   0,   0,   0, 250, 140,   0 }   // 5 Konferans Salonu
};

//Yardimci fonksiyonlar

void girdiTemizle() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void birimleriListele() {
    cout << "\n  Kampus Birimleri:\n";
    for (int i = 0; i < N; i++)
        cout << "  " << i + 1 << ". " << birimler[i] << "\n";
}

// Kullanicidan bina (birim) alir
int birimSec(const string& mesaj) {
    int s;
    while (true) {
        birimleriListele();
        cout << "  " << mesaj << " (1-" << N << "): ";
        if (cin >> s && s >= 1 && s <= N) return s - 1;
        cout << "  [!] Gecersiz secim, tekrar deneyin.\n";
        girdiTemizle();
    }
}

//Komsuluk Matrisi

void matrisYazdir() {
    cout << "\n  Komsuluk Matrisi (mesafe, metre; 0 = dogrudan yol yok)\n\n";
    cout << "  " << setw(6) << " ";
    for (int j = 0; j < N; j++) cout << setw(6) << ("B" + to_string(j + 1));
    cout << "\n  " << string(6 + 6 * N, '-') << "\n";
    for (int i = 0; i < N; i++) {
        cout << "  " << setw(4) << ("B" + to_string(i + 1)) << " |";
        for (int j = 0; j < N; j++) cout << setw(6) << komsuluk[i][j];
        cout << "\n";
    }
    cout << "\n  Birim kodlari:\n";
    for (int i = 0; i < N; i++)
        cout << "  B" << i + 1 << " = " << birimler[i] << "\n";
}

//BFS (Genislik Oncelikli Arama)

void bfs(int baslangic) {
    bool ziyaret[N] = { false };
    queue<int> kuyruk;

    ziyaret[baslangic] = true;
    kuyruk.push(baslangic);

    cout << "\n  BFS Gezinme Sirasi:\n  ";
    bool ilk = true;
    while (!kuyruk.empty()) {
        int u = kuyruk.front();
        kuyruk.pop();
        if (!ilk) cout << " -> ";
        cout << birimler[u];
        ilk = false;

        for (int v = 0; v < N; v++) {
            if (komsuluk[u][v] != 0 && !ziyaret[v]) {
                ziyaret[v] = true;
                kuyruk.push(v);
            }
        }
    }
    cout << "\n";
}

//DFS (Derinlik Oncelikli Arama) 

void dfsOzyinele(int u, bool ziyaret[], bool& ilk) {
    ziyaret[u] = true;
    if (!ilk) cout << " -> ";
    cout << birimler[u];
    ilk = false;

    for (int v = 0; v < N; v++)
        if (komsuluk[u][v] != 0 && !ziyaret[v])
            dfsOzyinele(v, ziyaret, ilk);
}

void dfs(int baslangic) {
    bool ziyaret[N] = { false };
    bool ilk = true;
    cout << "\n  DFS Gezinme Sirasi:\n  ";
    dfsOzyinele(baslangic, ziyaret, ilk);
    cout << "\n";
}

//Dijkstra (Baslangic dugumden diger dugumlere en kisa yollari bulma!)

void yolYazdir(int onceki[], int hedef) {
    if (onceki[hedef] == -1) {
        cout << birimler[hedef];
        return;
    }
    yolYazdir(onceki, onceki[hedef]);
    cout << " -> " << birimler[hedef];
}

void dijkstra(int baslangic, int hedef) {
    int mesafe[N];
    int onceki[N];
    bool kesin[N];

    for (int i = 0; i < N; i++) {
        mesafe[i] = INF;
        onceki[i] = -1;
        kesin[i] = false;
    }
    mesafe[baslangic] = 0;

    for (int adim = 0; adim < N; adim++) {
        // Henuz kesinlesmemis en kucuk mesafeli dugum
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!kesin[i] && mesafe[i] != INF && (u == -1 || mesafe[i] < mesafe[u]))
                u = i;
        if (u == -1) break;  // kalan dugumlere ulasilamiyor
        kesin[u] = true;

        for (int v = 0; v < N; v++) {
            if (komsuluk[u][v] != 0 && !kesin[v] &&
                mesafe[u] + komsuluk[u][v] < mesafe[v]) {
                mesafe[v] = mesafe[u] + komsuluk[u][v];
                onceki[v] = u;
            }
        }
    }

    cout << "\n  Baslangic : " << birimler[baslangic];
    cout << "\n  Hedef     : " << birimler[hedef] << "\n";

    if (mesafe[hedef] == INF) {
        cout << "\n  Bu iki birim arasinda yol bulunamadi.\n";
        return;
    }

    cout << "\n  En kisa mesafe: " << mesafe[hedef] << " metre\n";
    cout << "  Izlenen rota  : ";
    yolYazdir(onceki, hedef);
    cout << "\n";
}

//Modul menusu

void modul4() {
    int secim;
    do {
        cout << "\n  --- [MODUL 4: GRAF (GRAPH) VERI YAPISI & KAMPUS ROTA ANALIZI] ---\n";
        cout << "  1. Kampus Binalari Komsuluk Matrisini Goruntule (2B Dizi)\n";
        cout << "  2. Graf BFS (Genislik Oncelikli Arama) Gezinmesi\n";
        cout << "  3. Graf DFS (Derinlik Oncelikli Arama) Gezinmesi\n";
        cout << "  4. Iki Kampus Binasi Arasi En Kisa Rota (Dijkstra Algoritmasi)\n";
        cout << "  0. Ana Menuye Don\n";
        cout << "  Alt Seciminiz: ";

        if (!(cin >> secim)) {
            girdiTemizle();
            cout << "  [!] Lutfen sayi girin.\n";
            secim = -1;
            continue;
        }

        switch (secim) {
            case 1:
                matrisYazdir();
                break;
            case 2:
                bfs(birimSec("Baslangic birimi"));
                break;
            case 3:
                dfs(birimSec("Baslangic birimi"));
                break;
            case 4: {
                int b = birimSec("Baslangic birimi");
                int h = birimSec("Hedef birimi");
                dijkstra(b, h);
                break;
            }
            case 0:
                cout << "  Ana menuye donuluyor...\n";
                break;
            default:
                cout << "  [!] Gecersiz secim.\n";
        }
    } while (secim != 0);
}

// Bagimsiz test icin main. Ana programa entegre ederken main silinecek!
int main() {
    int secim;
    do {
        cout << "\n  ------------------------------------------------------------\n";
        cout << "  4. Modul 4: Graf & Kampus Rota Analizi\n";
        cout << "  0. Cikis\n";
        cout << "  Seciminiz: ";
        if (!(cin >> secim)) { girdiTemizle(); secim = -1; continue; }
        if (secim == 4) modul4();
    } while (secim != 0);
    return 0;
}
