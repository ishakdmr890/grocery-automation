#include <iostream>
#include <locale.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;

void Ekleme(string urunlerad[], string urunler[], float fiyat[], float kilo[], int& sayac);
void Arama(string urunlerad[], string urunler[], int sayac);
void Listeleme(string urunler[], int sayac);
void Silme(string urunlerad[], string urunler[], float fiyat[], float kilo[], int& sayac);
void SatisYap(string urunlerad[],string urunler[], float fiyat[], float kilo[], int sayac);
void Kaydetme(string urunler[],int sayac);

int main(){
    string urunlerad[100],urunler[100];
    int sayac=0;
    float fiyat[100];
    float kilo[100];
    int secim;
    do {
        cout << "\n--- MANAV OTOMASYONU ---"<<endl;
        cout << "1- Urun Ekle"<<endl;
        cout << "2- Urun Ara"<<endl;
        cout << "3- Urunleri Listele"<<endl;
        cout << "4- Urun Sil"<<endl;
        cout << "5- Satis Yap"<<endl;
        cout << "0- Cikis"<<endl;
        cout << "Seciminiz: "<<endl;
        cin >> secim;

        switch (secim) {
            case 1:
                Ekleme(urunlerad, urunler, fiyat, kilo, sayac);
                break;
            case 2:
                Arama(urunlerad, urunler, sayac);
                break;
            case 3:
                Listeleme(urunler, sayac);
                break;
            case 4:
                Silme(urunlerad, urunler, fiyat, kilo, sayac);
                break;
            case 5:
                SatisYap(urunlerad, urunler, fiyat, kilo, sayac);
                break;
            case 0:
                cout << "Programdan cikiliyor..."<<endl;
                break;
            default:
                cout << "Gecersiz secim!"<<endl;
                break;
        }
    } while (secim!=0);
    return 0;
}

void Kaydetme(string urunler[],int sayac){
    ofstream yiyecekler("yiyecekler.dat");
    if (yiyecekler.is_open())
    {
        for (int i = 0; i < sayac; i++)
        {
            yiyecekler<<urunler[i]<<endl;
        }
        yiyecekler.close();
    }
}

void Ekleme(string urunlerad[], string urunler[], float fiyat[], float kilo[], int& sayac){
    system("cls");
    string urunAdi;
    cout << "Urun giriniz: ";
    cin >> urunAdi;
    for (int i = 0; i < sayac; i++)
    {
        if (urunlerad[i]==urunAdi)
        {
            system("cls");
            cout<<"Bu urun var, baska urun ismi giriniz...."<<endl;
            return;
        }   
    }
    urunlerad[sayac] = urunAdi;
    cout<<"Fiyat giriniz (TL/kg) : ";
    cin>>fiyat[sayac];
    cout<<"Kilo giriniz : ";
    cin>>kilo[sayac];
    stringstream ss;       // Floatı string dizisinde göstermek içi lazım yoksa olmuyor
    ss << fixed << setprecision(2)<< urunlerad[sayac]   << " : "<<fiyat[sayac]<< " (TL/KG) : "<<kilo[sayac]<< " Kilo.";
    urunler[sayac] = ss.str();
    sayac++;
    Kaydetme(urunler, sayac);
    system("cls");
}

void Arama(string urunlerad[], string urunler[], int sayac){
    system("cls");
    string urun;
    cout<<endl<<"----- Arama yeri -----"<<endl;
    cout<<"Urun adi giriniz : ";
    cin>>urun;
    bool bulundu = false;

    for (int i = 0; i < sayac; i++) {
        if (urun == urunlerad[i]) {
            cout << "Aradiginiz urun: " << urunler[i] << endl;
            bulundu = true;
            break;
        }
    }

    if (!bulundu) {
        cout << "Boyle bir urun yok.\n";
    }
}

void Listeleme(string urunler[], int sayac){
    system("cls");
    if (sayac == 0) {
        system("cls");
        cout << "Liste bos.\n";
        return;
    }
    cout<<endl<<"----- LISTELEME ----- : "<<endl;
    for (int i = 0; i < sayac; i++)
    {
        cout<<urunler[i]<<endl;
    }
    Kaydetme(urunler, sayac);
}

void Silme(string urunlerad[], string urunler[], float fiyat[], float kilo[], int& sayac){
    string urun;
    cout<<endl<<"----- SILMEK ISTEDIGINIZ URUN -----"<<endl;
    cout<<"Sileceginiz urun adi : "<<endl;
    cin>>urun;
    bool bulundu = false;

    for (int i = 0; i < sayac; i++) {
        if (urunlerad[i] == urun) {
            for (int j = i; j < sayac - 1; j++) {
                urunlerad[j] = urunlerad[j + 1];
                urunler[j]   = urunler[j + 1];
                fiyat[j]     = fiyat[j + 1];
                kilo[j]      = kilo[j + 1];
            }
            sayac--;
            bulundu = true;
            cout << "Urun silindi.\n";
            break;
        }
    }

    if (!bulundu) {
        cout << "Boyle bir urun bulunamadi.\n";
    }
    Kaydetme(urunler, sayac);
}

void SatisYap(string urunlerad[], string urunler[],float fiyat[], float kilo[], int sayac)
{
    system("cls");
    string secilen;
    float satilanKilo;
    bool bulundu = false;
    if (sayac == 0) {
        cout << "Urun yok!" << endl;
        return;
    }
    cout << endl << "--- URUNLER ---" << endl;
    for (int i = 0; i < sayac; i++) {
        cout << urunler[i] << endl;
    }
    cout << endl << "Satilacak urun adi: ";
    cin >> secilen;
    for (int i = 0; i < sayac; i++) {
        if (urunlerad[i] == secilen) {
            bulundu = true;

            cout << "Satilacak kilo: ";
            cin >> satilanKilo;

            if (satilanKilo <= 0) {
                cout << "Gecersiz kilo!" << endl;
                return;
            }

            if (satilanKilo > kilo[i]) {
                cout << "Yetersiz stok! Mevcut: "
                     << kilo[i] << " KG" << endl;
                return;
            }
            float tutar = satilanKilo * fiyat[i];
            kilo[i] -= satilanKilo;
            stringstream ss;
            ss << fixed << setprecision(2)<< urunlerad[i] << " : "<< fiyat[i] << " TL/KG : "<< kilo[i] << " KG (KALAN)";
            urunler[i] = ss.str();
            Kaydetme(urunler, sayac);
            cout << fixed << setprecision(2);
            cout << "Satis basarili! Tutar: "<< tutar << " TL" << endl;
            return;
        }
    }
    if (!bulundu) {
        cout << "Urun bulunamadi!" << endl;
    }
}