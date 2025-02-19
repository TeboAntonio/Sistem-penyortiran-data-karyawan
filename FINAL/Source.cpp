#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Fungsi clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Struct: Karyawan
struct Karyawan {
    string nama;
    int gaji;
    string kontrak;
    int lamaKontrak;
};

// Stack: KaryawanStack
class KaryawanStack {
private:
    // Struct dan Pointer: Node
    struct Node {
        Karyawan karyawan; // Struct: Karyawan
        Node* next; // Pointer: next
        Node(const Karyawan& k) : karyawan(k), next(nullptr) {}
    };
    Node* top; // Pointer: top

public:
    KaryawanStack() : top(nullptr) {}

    void push(const Karyawan& karyawan) {
        Node* newNode = new Node(karyawan); // Pointer: newNode
        newNode->next = top; // Pointer: next
        top = newNode; // Pointer: top
    }

    void pop() {
        if (top == nullptr) {
            cout << "Stack kosong, tidak ada karyawan yang bisa dihapus." << endl;
            return;
        }

        Node* temp = top; // Pointer: temp
        top = top->next; // Pointer: next
        delete temp; // Menghapus node
    }

    void remove(const string& nama) {
        Node* current = top;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (current->karyawan.nama == nama) {
                if (previous == nullptr) {
                    top = current->next;
                }
                else {
                    previous->next = current->next;
                }
                delete current;
                break;
            }
            previous = current;
            current = current->next;
        }
    }

    void printKaryawanStack() const {
        Node* current = top; // Pointer: current
        cout << left << setw(20) << "Nama" << setw(10) << "Gaji" << setw(15) << "Kontrak" << setw(15) << "Lama Kontrak" << endl;
        cout << "-------------------------------------------------------------" << endl;
        while (current != nullptr) {
            cout << left << setw(20) << current->karyawan.nama
                << setw(10) << current->karyawan.gaji
                << setw(15) << current->karyawan.kontrak;
            if (current->karyawan.kontrak == "sementara") {
                cout << setw(15) << current->karyawan.lamaKontrak;
            }
            else {
                cout << setw(15) << "-";
            }
            cout << endl;
            current = current->next; // Pointer: next
        }
    }

    // Searching: cariKaryawan
    Karyawan* cariKaryawan(const string& nama) const {
        Node* current = top; // Pointer: current
        while (current != nullptr) {
            if (current->karyawan.nama == nama) {
                return &current->karyawan; // Pointer: Mengembalikan alamat struct Karyawan
            }
            current = current->next; // Pointer: next
        }
        return nullptr;
    }

    void kurangiLamaKontrak(int timeElapsed) {
        Node* current = top; // Pointer: current
        while (current != nullptr) {
            if (current->karyawan.kontrak == "sementara") {
                current->karyawan.lamaKontrak -= timeElapsed;
            }
            current = current->next; // Pointer: next
        }
    }

    void hapusKaryawanByTime() {
        Node* current = top; // Pointer: current
        Node* previous = nullptr; // Pointer: previous

        while (current != nullptr) {
            if (current->karyawan.kontrak == "sementara" && current->karyawan.lamaKontrak <= 0) {
                if (previous == nullptr) {
                    top = current->next; // Pointer: next
                }
                else {
                    previous->next = current->next; // Pointer: next
                }
                Node* toDelete = current; // Pointer: toDelete
                current = current->next; // Pointer: next
                delete toDelete; // Menghapus node
            }
            else {
                previous = current;
                current = current->next; // Pointer: next
            }
        }
    }
};

// Fungsi perbandingan untuk sorting
bool compareByGaji(const Karyawan& a, const Karyawan& b) {
    return a.gaji < b.gaji;
}

bool compareByNama(const Karyawan& a, const Karyawan& b) {
    return a.nama < b.nama;
}

bool compareByKontrak(const Karyawan& a, const Karyawan& b) {
    return a.kontrak < b.kontrak;
}

bool compareByLamaKontrak(const Karyawan& a, const Karyawan& b) {
    return a.lamaKontrak < b.lamaKontrak;
}

// Fungsi input karyawan
void inputKaryawan(vector<Karyawan>& karyawanList, queue<Karyawan>& karyawanQueue) {
    int jumlahKaryawan;
    cout << "Masukkan jumlah karyawan: ";
    cin >> jumlahKaryawan;

    // Array: karyawanList
    for (int i = 0; i < jumlahKaryawan; ++i) {
        Karyawan karyawan;
        cout << "Masukkan nama karyawan: ";
        cin >> ws; // to ignore leading whitespace
        getline(cin, karyawan.nama);
        cout << "Masukkan gaji karyawan: ";
        cin >> karyawan.gaji;
        cout << "Masukkan status kontrak (tetap/sementara): ";
        cin >> ws;
        getline(cin, karyawan.kontrak);
        if (karyawan.kontrak == "sementara") {
            cout << "Masukkan lama kontrak (dalam bulan): ";
            cin >> karyawan.lamaKontrak;
        }
        else {
            karyawan.lamaKontrak = 0; // untuk kontrak tetap, lama kontrak diatur menjadi 0
        }
        karyawanList.push_back(karyawan); // Menambahkan ke array (vector)
        karyawanQueue.push(karyawan); // Queue: Menambahkan karyawan ke queue
    }
}

// Fungsi sorting dengan selection sort
void selectionSort(vector<Karyawan>& karyawanList, bool (*compare)(const Karyawan&, const Karyawan&)) {
    int n = karyawanList.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (compare(karyawanList[j], karyawanList[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(karyawanList[i], karyawanList[minIndex]);
        }
    }
}

// Menu utama
void menu() {
    cout << "+-------------------------------------------------------------+" << endl;
    cout << "|                SYSTEM PENYORTIRAN DATA KARYAWAN             |" << endl;
    cout << "+-------------------------------------------------------------+\n" << endl;
    cout << "\n=== Menu Utama ===" << endl;
    cout << "1. Input Data Karyawan" << endl;
    cout << "2. Cetak Data Karyawan" << endl;
    cout << "3. Sorting Data Karyawan" << endl;
    cout << "4. Cari Karyawan" << endl;
    cout << "5. Hapus Karyawan" << endl;
    cout << "6. Time Skip" << endl;
    cout << "7. Keluar" << endl;
    cout << "Pilih opsi: ";
}

// Menu sorting
void menuSort() {
    cout << "\n=== Pilihan Sorting ===" << endl;
    cout << "1. Berdasarkan Gaji" << endl;
    cout << "2. Berdasarkan Nama" << endl;
    cout << "3. Berdasarkan Jenis Kontrak" << endl;
    cout << "4. Berdasarkan Lama Kontrak" << endl;
    cout << "Pilih opsi: ";
}

// Fungsi time skip
void timeSkip(queue<Karyawan>& karyawanQueue, KaryawanStack& karyawanStack, vector<Karyawan>& karyawanList, int& currentTime) {
    int skipTime;
    cout << "Masukkan jumlah bulan untuk time skip: ";
    cin >> skipTime;
    currentTime += skipTime;

    // Mengurangi lama kontrak
    karyawanStack.kurangiLamaKontrak(skipTime);

    // Menghapus karyawan yang kontraknya habis
    karyawanStack.hapusKaryawanByTime();

    // Queue: Menghapus karyawan dari queue jika kontraknya habis
    queue<Karyawan> tempQueue;
    while (!karyawanQueue.empty()) {
        Karyawan& k = karyawanQueue.front();
        karyawanQueue.pop();
        if (k.kontrak == "sementara") {
            k.lamaKontrak -= skipTime;
            if (k.lamaKontrak > 0) {
                tempQueue.push(k);
            }
            else {
                // Menghapus dari array
                karyawanList.erase(remove_if(karyawanList.begin(), karyawanList.end(), [&](const Karyawan& karyawan) {
                    return karyawan.nama == k.nama;
                    }), karyawanList.end());
            }
        }
        else {
            tempQueue.push(k);
        }
    }
    swap(karyawanQueue, tempQueue);
}

int main() {
    vector<Karyawan> karyawanList; // Array: karyawanList
    queue<Karyawan> karyawanQueue; // Queue: karyawanQueue
    KaryawanStack karyawanStack; // Stack: karyawanStack
    int currentTime = 0; // waktu saat ini dalam bulan

    while (true) {
        clearScreen();
        menu();
        int pilihan;
        cin >> pilihan;

        clearScreen(); // Clear screen after choosing an option
        if (pilihan == 1) {
            inputKaryawan(karyawanList, karyawanQueue);
            while (!karyawanQueue.empty()) {
                Karyawan karyawan = karyawanQueue.front();
                karyawanQueue.pop();
                if (karyawanStack.cariKaryawan(karyawan.nama) == nullptr) {
                    karyawanStack.push(karyawan);
                }
            }
        }
        else if (pilihan == 2) {
            karyawanStack.printKaryawanStack();
            cin.ignore(); // Ignore newline character
            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.get(); // Wait for user to press Enter
        }
        else if (pilihan == 3) {
            menuSort();
            int sortPilihan;
            cin >> sortPilihan;
            switch (sortPilihan) {
            case 1:
                selectionSort(karyawanList, compareByGaji);
                break;
            case 2:
                selectionSort(karyawanList, compareByNama);
                break;
            case 3:
                selectionSort(karyawanList, compareByKontrak);
                break;
            case 4:
                selectionSort(karyawanList, compareByLamaKontrak);
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
            }
            cout << "Data karyawan setelah sorting:" << endl;
            cout << left << setw(20) << "Nama" << setw(10) << "Gaji" << setw(15) << "Kontrak" << setw(15) << "Lama Kontrak" << endl;
            cout << "-------------------------------------------------------------" << endl;
            for (const auto& karyawan : karyawanList) {
                cout << left << setw(20) << karyawan.nama
                    << setw(10) << karyawan.gaji
                    << setw(15) << karyawan.kontrak;
                if (karyawan.kontrak == "sementara") {
                    cout << setw(15) << karyawan.lamaKontrak;
                }
                else {
                    cout << setw(15) << "-";
                }
                cout << endl;
            }
            cin.ignore(); // Ignore newline character
            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.get(); // Wait for user to press Enter
        }
        else if (pilihan == 4) {
            string namaCari;
            cout << "\nMasukkan nama karyawan yang ingin dicari: ";
            cin >> ws;
            getline(cin, namaCari);

            Karyawan* karyawanDitemukan = karyawanStack.cariKaryawan(namaCari);
            if (karyawanDitemukan) {
                cout << "Karyawan ditemukan: " << endl;
                cout << "+-------------------------------------------------------------+" << endl;
                cout << "|" << left << setw(20) << " Nama" << "|" << setw(10) << " Gaji" << "|" << setw(14) << " Kontrak" << "|" << setw(14) << " Lama Kontrak" << "|" << endl;
                cout << "+-------------------------------------------------------------+" << endl;
                cout << "| " << left << setw(19) << karyawanDitemukan->nama
                    << "| " << setw(9) << karyawanDitemukan->gaji
                    << "| " << setw(13) << karyawanDitemukan->kontrak;
                if (karyawanDitemukan->kontrak == " sementara") {
                    cout << "| " << setw(13) << karyawanDitemukan->lamaKontrak << "|";
                }
                else {
                    cout << "| " << setw(13) << "-" << "|";
                }
                cout << endl;
            }
            else {
                cout << "Karyawan dengan nama " << namaCari << " tidak ditemukan." << endl;
            }
            cin.ignore(); // Ignore newline character
            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.get();
        }
        else if (pilihan == 5) {
            string namaCari;
            cout << "\nMasukkan nama karyawan yang ingin dihapus: ";
            cin >> ws;
            getline(cin, namaCari);

            Karyawan* karyawanDitemukan = karyawanStack.cariKaryawan(namaCari);
            if (karyawanDitemukan) {
                // Menghapus dari array
                karyawanList.erase(remove_if(karyawanList.begin(), karyawanList.end(), [&](const Karyawan& karyawan) {
                    return karyawan.nama == namaCari;
                    }), karyawanList.end());

                // Menghapus dari stack
                karyawanStack.remove(namaCari);

                // Menghapus dari queue
                queue<Karyawan> tempQueue;
                while (!karyawanQueue.empty()) {
                    Karyawan& k = karyawanQueue.front();
                    if (k.nama != namaCari) {
                        tempQueue.push(k);
                    }
                    karyawanQueue.pop();
                }
                karyawanQueue = tempQueue;
                cout << "Karyawan " << namaCari << " berhasil dihapus." << endl;
            }
            else {
                cout << "Karyawan dengan nama " << namaCari << " tidak ditemukan." << endl;
            }
            cin.ignore(); // Ignore newline character
            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.get(); // Wait for user to press Enter
        }
        else if (pilihan == 6) {
            timeSkip(karyawanQueue, karyawanStack, karyawanList, currentTime);
            cin.ignore(); // Ignore newline character
            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.get(); // Wait for user to press Enter
        }
        else if (pilihan == 7) {
            break;
        }
        else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            cin.ignore(); // Ignore newline character
            cout << "\nTekan Enter untuk kembali ke menu...";
            cin.get(); // Wait for user to press Enter
        }
    }

    return 0;
}
