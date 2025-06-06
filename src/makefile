# Compiler yang digunakan
CC = gcc

CFLAGS = -Wall -g -Iheader -std=c11

# Nama executable output (akan dibuat di direktori Makefile saat ini: if2110/src/)
TARGET = rumah_sakit_app

# --- Daftar File Source (.c) ---
# File .c yang ada di direktori yang sama dengan Makefile (if2110/src/)
SRCS_IN_SRC_DIR = main.c

# File .c yang ada di subdirektori 'c' (if2110/src/c/)
C_FILES_IN_C_SUBDIR = adt_list_obat.c \
                      adt_stack_obat.c \
                      auth.c \
                      antrian.c \
                      daftarCheckUp.c \
                      dataCheckup.c \
                      diagnosisBerobat.c \
                      help.c \
                      keluar.c \
                      lihatAntrian.c \
                      listDenah.c \
                      manager.c \
                      mapAssignDokter.c \
                      obat.c \
                      tambahDokter.c \
                      queueAntri.c \
                      pulangDok.c
                      
SRCS_FROM_C_SUBDIR = $(addprefix c/, $(C_FILES_IN_C_SUBDIR))

SRCS = $(SRCS_IN_SRC_DIR) $(SRCS_FROM_C_SUBDIR)

# --- Daftar File Objek (.o) ---
OBJS_FROM_SRC_DIR = $(SRCS_IN_SRC_DIR:.c=.o)
OBJS_FROM_C_SUBDIR = $(C_FILES_IN_C_SUBDIR:.c=.o)

# Gabung semua file objek
OBJS = $(OBJS_FROM_SRC_DIR) $(OBJS_FROM_C_SUBDIR)


# Aturan default: build executable
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: c/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean