☄️ Particle Collision Simulator (C++ & SFML)
Simulasi ini adalah proyek yang menguji dan membandingkan efisiensi algoritma deteksi tabrakan di lingkungan dua dimensi. Program ini menggunakan C++ dan library SFML untuk visualisasi dan manajemen game loop.

🌟 Tentang Program
Program ini mensimulasikan sekumpulan partikel (bola) berwarna-warni yang bergerak secara acak, memantul satu sama lain, dan mematuhi hukum fisika dasar. Fokus utama proyek ini adalah kemampuan untuk beralih secara real-time antara dua metode deteksi tabrakan yang berbeda untuk membandingkan kinerja (FPS).


🛠️ Tools & Technologies

Bahasa Pemrograman: C++ 


Library Grafis: SFML 2.6.1+ 


Version Control: Git 


Metode Pelaporan: README.md sebagai laporan. 

🎯 Fitur Utama
1. Perbandingan Algoritma Deteksi Tabrakan
Program mendukung dua mode deteksi tabrakan yang dapat dialihkan pengguna:

⚔️ Brute Force (O(N²)): Metode dasar yang membandingkan setiap partikel dengan setiap partikel lainnya. Digunakan sebagai patokan untuk mengukur kompleksitas.


🌳 Quadtree (O(N log N)): Struktur data hierarkis spasial yang digunakan untuk secara signifikan mengurangi jumlah perbandingan tabrakan, meningkatkan kinerja saat jumlah partikel besar.

2. Interaktivitas & Debugging Real-Time (Key Features)

Mode Switcher (Tombol TAB): Pengguna dapat menekan tombol TAB pada keyboard untuk langsung beralih antara mode BRUTE FORCE dan QUADTREE.

FPS Tracker: Menampilkan Frames Per Second (FPS) secara real-time di sudut kiri atas layar. Nilai ini sangat penting untuk membandingkan kinerja kedua mode tabrakan.


Indikator Mode & Partikel: Teks di layar menampilkan Mode yang sedang aktif dan Jumlah Partikel yang ada di simulasi.

3. Dinamika Partikel

Spawn On Click: Klik di mana saja pada layar untuk menambahkan partikel baru dengan kecepatan, ukuran, dan warna acak.



Ukuran dan Kecepatan Bervariasi: Setiap bola memiliki radius, massa, dan kecepatan awal yang berbeda, memastikan lingkungan simulasi yang dinamis.


5 Pilihan Warna: Partikel diinisialisasi secara acak dengan salah satu dari lima warna: Merah, Biru, Hijau, Pink, atau Ungu.

🚀 Cara Menjalankan Program
Prasyarat
Anda memerlukan compiler C++ (seperti g++ atau MSVC) dan library SFML yang telah dikonfigurasi.


Penting (WSL/Linux): Pastikan Anda telah menginstal library font standar Linux, seperti fonts-dejavu-core, agar FPS Tracker dan teks mode dapat ditampilkan dengan benar.

Kompilasi dan Eksekusi
Gunakan konfigurasi tasks.json Anda (yang telah disesuaikan untuk SFML dan LD_LIBRARY_PATH) untuk mengompilasi dan menjalankan program.

Contoh Perintah Kompilasi (Linux/MinGW):

Bash

g++ main.cpp -o sfml_sim -lsfml-graphics -lsfml-window -lsfml-system
./sfml_sim
Instruksi Saat Program Berjalan:

Klik Kiri: Tambahkan partikel baru.

Tekan TAB: Beralih antara mode BRUTE FORCE dan QUADTREE untuk mengamati perubahan pada nilai FPS secara real-time.
