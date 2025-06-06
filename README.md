# SISTEM MANAJEMEN RUMAH SAKIT NIMONS
## Kelompok L - K04

Selamat datang di repositori Sistem Manajemen Rumah Sakit NIMONS! Proyek ini adalah implementasi fungsi ADT dalam bahasa C yang dikembangkan sebagai bagian dari Tugas Besar mata kuliah IF1210 Algoritma dan Pemrograman

**Anggota Kelompok**
Francis Galton - 18221072
Rafael Sean Hadipranoto - 18224100
Rashid May - 18222014
Derren Christopher Boenardi - 18224040
Sri Laksmi Purwoningtyas - 18221009
Geodipa Afatha Ryu M.F.Z. - 18224124


## Deskripsi Proyek

Sistem Rumah Sakit NIMONS adalah aplikasi berbasis C yang mensimulasikan beberapa fungsi dasar manajemen rumah sakit, termasuk pendaftaran pengguna (pasien, dokter, manajer), pendaftaran check-up oleh pasien, diagnosis dan pengobatan oleh dokter, serta beberapa fitur administratif oleh manajer.

## Fitur Utama

Sistem ini memiliki beberapa fitur utama yang dikelompokkan berdasarkan peran pengguna:

**Fitur Umum (Sebelum Login):**
1.  **LOGIN (F01):** Memungkinkan pengguna yang sudah terdaftar untuk masuk ke sistem.
2.  **REGISTER PASIEN (F02):** Memungkinkan pengguna baru untuk mendaftar sebagai pasien.
3.  **LUPA PASSWORD (F04):** 
4.  **HELP (F05):** Menampilkan daftar perintah yang tersedia.
5.  **KELUAR (F18):** Keluar dari aplikasi.

**Fitur Umum (Setelah Login):**
1.  **LIHAT DENAH (F06):** Menampilkan denah visual dari semua ruangan rumah sakit.
2.  **LIHAT RUANGAN (F06):** Menampilkan detail spesifik sebuah ruangan, termasuk dokter yang bertugas dan pasien yang sedang "di dalam ruangan"
3.  **HELP (F05):** Menampilkan daftar perintah yang relevan dengan peran pengguna.
4.  **LOGOUT (F03):** Keluar dari sesi pengguna saat ini.
5.  **EXIT (F18):** Keluar dari aplikasi.

**Fitur Manager:**
1.  **LIHAT USER (F07):** Menampilkan daftar semua pengguna (pasien, dokter, manajer) beserta detailnya, termasuk penyakit yang sedang diderita pasien (jika ada). Dapat diurutkan berdasarkan ID atau Username.
2.  **LIHAT PASIEN (F07):** Menampilkan daftar khusus pasien beserta detail penyakitnya.
3.  **LIHAT DOKTER (F07):** Menampilkan daftar khusus dokter.
4.  **CARI USER (F08):** Mencari pengguna berdasarkan ID atau nama.
5.  **CARI PASIEN (F08):** Mencari pasien berdasarkan ID, nama, atau penyakit.
6.  **CARI DOKTER (F08):** Mencari dokter berdasarkan ID atau nama.
7.  **LIHAT SEMUA ANTRIAN (F09):** Menampilkan status semua ruangan, termasuk dokter, pasien "di dalam ruangan", dan pasien "di antrian luar".
8.  **TAMBAH DOKTER (F10):** Memungkinkan manajer untuk mendaftarkan dokter baru ke sistem.
9.  **ASSIGN DOKTER (F10):** Memungkinkan manajer untuk menugaskan dokter ke ruangan tertentu.

**Fitur Dokter:**
1.  **DIAGNOSIS PASIEN (F11):** Dokter mendiagnosis pasien terdepan dari antriannya.
2.  **BERI PENGOBATAN (F12 / NGOBATIN):** Dokter memberikan resep obat kepada pasien yang baru saja didiagnosis. Resep ini (daftar obat dan urutannya) disimpan untuk pasien tersebut. Pasien kemudian dikeluarkan dari antrian dokter.

**Fitur Pasien:**
1.  **SELESAI CHECK-UP/PULANG (F13):** Pasien meminta untuk pulang. Sistem akan mengecek apakah semua obat di resep sudah diminum dan apakah urutan minumnya benar.
2.  **DAFTAR CHECK-UP (F14):** Pasien mendaftarkan diri untuk check-up, memasukkan data vital, dan memilih dokter/ruangan untuk masuk ke antrian.
3.  **LIHAT ANTRIAN (F15):** Pasien melihat status antriannya sendiri, termasuk dokter, ruangan, dan apakah dia sudah dianggap "di dalam ruangan" atau masih di antrian luar.
4.  **MINUM OBAT (F16):** Pasien meminum obat berikutnya dari resep aktifnya. Obat yang diminum akan dipindahkan dari "resep aktif" ke "isi perut" (stack).
5.  **MINUM PENAWAR (F17):** Pasien mengeluarkan obat terakhir yang diminum dari "isi perut" dan mengembalikannya ke "resep aktif" (inventaris obat yang bisa diminum lagi).

## Cara Kompilasi dan Menjalankan

1.  **Prasyarat:**
    *   Pastikan Anda memiliki compiler C (seperti GCC) yang terinstal.
    *   Pastikan `make` utility terinstal (misalnya, dari MinGW/MSYS2 di Windows, atau build-essential di Linux).

2.  **Kompilasi:**
    *   Buka terminal atau command prompt.
    *   Navigasikan ke direktori `src` dalam proyek ini (tempat `Makefile` berada).
    *   Jalankan perintah:
        ```bash
        make
        ```
    *   Ini akan mengompilasi semua file source dan menghasilkan executable bernama `rumah_sakit_app.exe` (atau `rumah_sakit_app` di Linux/macOS) di dalam direktori `src`.

3.  **Menjalankan Program:**
    *   Setelah kompilasi berhasil, jalankan executable dari direktori `src`:
        ```bash
        ./rumah_sakit_app.exe  # Untuk Windows (Git Bash, MSYS2, atau jika di PATH)
        # atau
        # ./rumah_sakit_app      # Untuk Linux/macOS
        ```

4.  **Membersihkan File Hasil Kompilasi:**
    *   Untuk menghapus file objek (`.o`) dan executable, jalankan:
        ```bash
        make clean
        ```

## Catatan Tambahan

*   Data pengguna, penyakit, obat, dan resep saat ini di-hardcode dalam program dan akan direset setiap kali program dijalankan ulang. Tidak ada persistensi data (penyimpanan ke file).
*   Model antrian yang digunakan adalah "Satu Queue Total" per ruangan, di mana "pasien di dalam ruangan" adalah interpretasi tampilan dari beberapa pasien terdepan di queue tersebut.

## Kontribusi

Silakan merujuk ke log commit Git untuk melihat kontribusi masing-masing anggota tim pada fitur-fitur yang ada.