# Particle Collision Simulator (C++ & SFML)

Simulasi ini adalah proyek yang menguji dan membandingkan efisiensi algoritma deteksi tabrakan di lingkungan dua dimensi. Program ini menggunakan **C++** dan *library* **SFML** untuk visualisasi dan manajemen *game loop*.

##  Tentang Program

[cite_start]Program ini mensimulasikan sekumpulan partikel (bola) berwarna-warni yang bergerak secara acak, memantul satu sama lain, dan mematuhi hukum fisika dasar[cite: 1, 2]. [cite_start]Fokus utama proyek ini adalah kemampuan untuk **beralih secara *real-time* antara dua metode deteksi tabrakan** yang berbeda untuk membandingkan kinerja (FPS)[cite: 3].

###  Tools & Technologies

  * [cite_start]**Bahasa Pemrograman:** C++ [cite: 1]
  * [cite_start]**Library Grafis:** SFML 2.6.1+ [cite: 1]
  * [cite_start]**Version Control:** Git [cite: 1]
  * [cite_start]**Metode Pelaporan:** README.md sebagai laporan. [cite: 1]

-----

##  Fitur Utama

### 1\. Perbandingan Algoritma Deteksi Tabrakan

Program mendukung dua mode deteksi tabrakan yang dapat dialihkan pengguna:

  * ** Brute Force (O(N²)):** Metode dasar yang membandingkan setiap partikel dengan setiap partikel lainnya. [cite_start]Digunakan sebagai patokan untuk mengukur kompleksitas[cite: 1].
  * [cite_start]** Quadtree (O(N log N)):** Struktur data hierarkis spasial yang digunakan untuk secara signifikan **mengurangi jumlah perbandingan** tabrakan, meningkatkan kinerja saat jumlah partikel besar[cite: 1].

### 2\. Interaktivitas & Debugging Real-Time (Key Features)

  * [cite_start]**Mode Switcher (Tombol TAB):** Pengguna dapat menekan tombol **TAB** pada *keyboard* untuk langsung beralih antara mode **BRUTE FORCE** dan **QUADTREE**[cite: 3].
  * **FPS Tracker:** Menampilkan *Frames Per Second* (FPS) secara *real-time* di sudut kiri atas layar. [cite_start]Nilai ini sangat penting untuk membandingkan kinerja kedua mode tabrakan[cite: 3].
  * [cite_start]**Indikator Mode & Partikel:** Teks di layar menampilkan **Mode** yang sedang aktif dan **Jumlah Partikel** yang ada di simulasi[cite: 3].

### 3\. Dinamika Partikel

  * [cite_start]**Spawn On Click:** Klik di mana saja pada layar untuk menambahkan partikel baru dengan kecepatan, ukuran, dan warna acak[cite: 1, 3].
  * [cite_start]**Ukuran dan Kecepatan Bervariasi:** Setiap bola memiliki radius, massa, dan kecepatan awal yang berbeda, memastikan lingkungan simulasi yang dinamis[cite: 1, 2].
  * [cite_start]**5 Pilihan Warna:** Partikel diinisialisasi secara acak dengan salah satu dari lima warna: Merah, Biru, Hijau, Pink, atau Ungu[cite: 2].

-----

##  Cara Menjalankan Program

### Prasyarat

Anda memerlukan *compiler* C++ (seperti g++ atau MSVC) dan *library* SFML yang telah dikonfigurasi.

  * [cite_start]**Penting (WSL/Linux):** Pastikan Anda telah menginstal *library* font standar Linux, seperti **`fonts-dejavu-core`**, agar FPS Tracker dan teks mode dapat ditampilkan dengan benar[cite: 3].

### Kompilasi dan Eksekusi

Gunakan konfigurasi `tasks.json` Anda (yang telah disesuaikan untuk SFML dan LD\_LIBRARY\_PATH) untuk mengompilasi dan menjalankan program.

**Contoh Perintah Kompilasi (Linux/MinGW):**

```bash
g++ main.cpp -o sfml_sim -lsfml-graphics -lsfml-window -lsfml-system
./sfml_sim
```

**Instruksi Saat Program Berjalan:**

1.  **Klik Kiri:** Tambahkan partikel baru.
2.  **Tekan TAB:** Beralih antara mode **BRUTE FORCE** dan **QUADTREE** untuk mengamati perubahan pada nilai FPS secara *real-time*.


10/11/2025 : Memahami konsep yang ingin digunakan untuk final project strukdat

14/11/2025 : Mencoba untuk membuat layar dengan fitur ketika melakukan klik pada mouse akan menambahkan jumlah bola, dan memberikan bentuk dan warna yang berbeda untuk tiap bola

16/11/2025: Mencoba untuk menggunakan Quadtree dan Brute Force

19/11/2025: Membuat Readme

25/11/2025 : Memberikan fitur tambahan untuk mengubah antara quadtree dan bruteforce menggunakan tab

29/11/2025 : Menambahkan fitur untuk melihat mode apa yang sedang digunakan, jumlah partikel (bola) yang berada pada layar, serta memberikan fps tracker

07/12/2025 : Mengubah jumlah awal bola menjadi 700 agar dapat terlihat perbedaan yang signifikan pada quadtree dan bruteforce

##  Demonstrasi Simulasi

(![2025-12-1312-04-02-ezgif com-optimize (1)](https://github.com/user-attachments/assets/29df67bb-97db-434e-a96f-f24ebe917281)
)
