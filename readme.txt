PENJELASAN PROGRAM
   Program ini memiliki dua pilihan algoritma yaitu
   - Brute Force: Mencoba semua kombinasi 
   - Optimized: memutus cabang pencarian yang sudah pasti tidak akan memberikan hasil yang benar
   Program menggunakan multithreading agar GUI tidak freeze dan menampilkan live update
   setiap t ms sesuai pilihan user melalui slider.

REQUIREMENT
- gtkmm4
- C++23 

Instalasi di macOS
brew install gtkmm4

Instalasi di Linux
sudo apt install libgtk-4-dev

Instalasi di Windows
Melalui MSYS2 terminal
pacman -S mingw-w64-x86_64-gtk4 mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config


CARA COMPILE
cd src
g++ -std=c++23  -o tucil  gui.cpp $(pkg-config --cflags --libs gtkmm-4.0)

CARA MENJALANKAN
1 cd bin
2 ./tucil
3 Gunakan tombol "Load txt" untuk memuat file input atau langsung ketik di bagian atas
4 Atur slider:
   - "Output Interval in Cases" Frekuensi output (setiap berapa kasus ditampilkan) (disarankan menggunakan > 20000 k)
   - "Output Interval in Milliseconds" Frekuensi update output dalam ms (disarankan menggunakan > 1000ms)
Pilih algoritma:
   - "Process" Menggunakan algoritma Brute Force
   - "Optimized Process" Menggunakan algoritma yang lebih efisien
Gunakan tombol "Save Output" untuk menyimpan hasil ke file txt

Identitas
Nama  : Ahmad Fauzan Putra
NIM   : 13524141
Kelas : K3