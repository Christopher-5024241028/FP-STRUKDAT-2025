# ☄️ Particle Collision Simulator (C++ & SFML)

Simulasi ini adalah proyek sederhana yang menunjukkan dasar-dasar fisika komputer, khususnya deteksi dan respons tabrakan antarlingkaran (bola) menggunakan C++ dan *library* **SFML** (Simple and Fast Multimedia Library) untuk rendering.

## 🌟 Tentang Program

Program ini mensimulasikan sekumpulan partikel (bola) berwarna-warni yang bergerak secara acak di dalam batas jendela. Bola-bola ini mematuhi hukum kekekalan momentum dasar (tabrakan elastis), memantul satu sama lain dan juga dari dinding pembatas.

### 🛠️ Tools & Technologies

  * **Bahasa Pemrograman:** C++
  * **Library Grafis:** SFML 2.6.1+
  * **Version Control:** Git
  * **Metode Pelaporan:** README.md sebagai laporan.

## 🎯 Fitur Utama

### 1\. Dinamika Fisika Real-Time

  * **Tabrakan Elastis:** Simulasi menerapkan respons tabrakan elastis, di mana momentum dan energi kinetik dipertahankan setelah dua bola bertabrakan.
  * **Batasan Dinding:** Bola memantul dari batas jendela simulasi.

### 2\. Variasi Partikel

  * **Ukuran Beragam:** Setiap bola memiliki **radius dan massa yang berbeda-beda** yang dihasilkan secara acak saat dibuat.
  * **Kecepatan Awal Acak:** Setiap bola diberi **kecepatan awal yang bervariasi** untuk menghasilkan gerakan yang lebih dinamis.
  * **5 Pilihan Warna:** Bola diinisialisasi secara acak dengan salah satu dari lima warna:
      * 🔴 Merah
      * 🔵 Biru
      * 🟢 Hijau
      * 🌸 Pink
      * 🟣 Ungu

### 3\. Interaktivitas Pengguna

  * **Inisialisasi Awal:** Program memulai dengan sejumlah kecil partikel yang bergerak secara acak di tengah layar.
  * **Spawn On Click:** Pengguna dapat **mengklik di mana saja pada layar** untuk secara instan menambahkan bola baru ke simulasi, dengan warna, ukuran, dan kecepatan awal yang acak.

### 4\. Implementasi Algoritma

Proyek ini bertujuan untuk mengimplementasikan dan membandingkan dua metode utama untuk deteksi tabrakan:

  * **Brute Force (Saat Ini Diimplementasikan):** Metode ini membandingkan **setiap partikel** dengan **setiap partikel lainnya** di setiap *frame* (`O(N^2)`).
  * **Quadtree (Target Implementasi Min):** Struktur data hierarkis spasial yang digunakan untuk secara signifikan **mengurangi jumlah perbandingan** tabrakan, meningkatkan kinerja saat jumlah partikel besar.

## 🚀 Cara Menjalankan Program

### Prasyarat

Anda memerlukan *compiler* C++ (seperti g++ atau MSVC) dan *library* SFML yang telah dikonfigurasi di lingkungan pengembangan Anda (seperti VS Code dengan WSL/MinGW).

### Kompilasi dan Eksekusi

Gunakan *tool chain* C++ Anda (misalnya, `tasks.json` di VS Code) untuk mengompilasi `main.cpp` dan menautkannya dengan *library* SFML (`-lsfml-graphics`, `-lsfml-window`, `-lsfml-system`).

**Contoh Perintah Kompilasi (Linux/MinGW):**

```bash
g++ main.cpp -o sfml_sim -lsfml-graphics -lsfml-window -lsfml-system
./sfml_sim
```

## 📝 Project Monitoring (Laporan)

Laporan proyek ini diwakili oleh file **`README.md`** ini. Setiap *commit* ke repositori ini mencerminkan kemajuan implementasi dan *debugging* fitur simulasi partikel.


