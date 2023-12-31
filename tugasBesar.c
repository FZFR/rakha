#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct shoesandcare
{
    int id,sepatuId,stok,kategori,kategori2,jenis,tagihan,saldo;
    float harga;
    char nama[50], password[50], username[50],feedback[100],userNameCus[20],passwordCus[20],metodePembayaran[50], sepatu[50],targetUsername[50],targetPassword[50];
}data;

void admin();
void adminOptions();
void hapusAkun();
void ubahPasswordCust();
void addStok();
void viewOrder();
void viewFeedBack();
void viewUcust();
void user();
void userReg();
void userLogin();
void menuCustomer();
void viewShoes();
void searchShoes();
void checkOut();
void ubahPassUser();
void addFeedback();
void outro();


int main(){
    system("cls");

    int pilihan;

    printf("-----Shoes&Care-----\n");
    printf("Silahkan untuk memilih opsi yang diinginkan.\n");
    printf("1. Admin.\n");
    printf("2. User.\n");
    printf("3. Keluar dari program.\n");
    printf("Pilihan : ");
    scanf("%d", &pilihan);

    switch (pilihan)
    {
    case 1:
        system("cls");
        admin();
        break;
    case 2:
        system("cls");
        user();
        break;
    case 3:
        system("cls");
        outro();
        return 0;
    default:
        system("cls");
        printf("Mohon untuk memilih pilihan yang telah disediakan.");
        break;
    }
}

void admin(){
    int returnAdm;
    int attempts = 0;
    int adminOpts;
    char adminUsername[50], adminPassword[50];

    system("cls");

    while (attempts < 3)
    {
        printf("Admin Login.\n");
        printf("Username : ");
        scanf("%s", &adminUsername);
        printf("Password : ");
        scanf("%s", &adminPassword);

        if (strcmp(adminUsername, "admin") == 0 && strcmp(adminPassword, "admin") == 0)
        {
            printf("Login sukses.\n");
            printf("Enter angka apa saja untuk melanjutkan.\n");
            scanf("%d", &adminOpts);

            adminOptions();
        }
            else
        {
            attempts++;
            printf("Username atau password anda salah.\n");
            printf("Sisa kesempatan anda untuk log in : %d\n", 3 - attempts);
        }
    }

    if (attempts == 3){

        system("cls");

        printf("Anda telah gagal log in sebanyak 3 kali.\n");
        printf("Enter 1 agar anda diredirect ke halaman utama.\n");
        scanf("%d", &returnAdm);

        switch (returnAdm)
        {
        case 1:
            main();
            break;
        
        default:
            break;
        }
    }
}

void adminOptions(){

    
    int pilihan;
    system("cls");
    printf("======Menu Admin======\n");
    printf("1. Hapus akun costumer\n");
    printf("2. Ubah password costumer\n");
    printf("3. Menambahkan stok\n");
    printf("4. Melihat orderan\n");
    printf("5. Melihat feedback\n");
    printf("6. Lihat Akun Customer.\n");
    printf("7. Menu Sebelumnya.\n");
    printf("8. Log Out.\n");
    printf("Pilihan : ");
    scanf("%d", &pilihan);

    switch (pilihan){

        case 1:
          system("cls");
          hapusAkun();
        break;

        case 2:
          system("cls");
          ubahPasswordCust();
        break;

        case 3:
          system("cls");
          addStok();
        break;
          
        case 4:
          system("cls");
          viewOrder();
        break;

        case 5:
          system("cls");
          viewFeedBack();
        break;

        case 6:
          system("cls");
          viewUcust();
        break;

        case 7:
          system("cls");
          main();
        break;
          
        case 8:
          system("cls");
          main();
        break;
        default:
        printf("Mohon untuk memilih menu yang ada");
        break;

}
}

void hapusAkun(){
    FILE *f_daftarakun, *f_temp;
   

    f_daftarakun = fopen("akuncus.dat", "rb");
    f_temp = fopen("temp.dat", "wb");

    if (f_daftarakun == NULL || f_temp == NULL) {
        perror("Error Membuka File");
        return;
    }

    printf("Masukkan username customer yang ingin dihapus: ");
    getchar(); 
    gets(data.targetUsername);

    while (fread(&data, sizeof(data), 1, f_daftarakun) == 1) {
        if (strcmp(data.userNameCus, data.targetUsername) != 0) {
            fwrite(&data, sizeof(data), 1, f_temp);
        }
    }

    fclose(f_daftarakun);
    fclose(f_temp);

    remove("akuncus.dat");
    rename("temp.dat", "akuncus.dat");

    printf("Akun customer dengan username %s telah dihapus.\n", data.targetUsername);
    system("pause");
    adminOptions();
}

void ubahPasswordCust(){
    FILE *f_daftarakun;
    
    f_daftarakun = fopen("akuncus.dat", "rb+");

    if (f_daftarakun == NULL) {
        perror("Error Membuka File");
        return;
    }

    while (fread(&data, sizeof(data), 1, f_daftarakun) == 1) {
        if (strcmp(data.userNameCus, data.targetUsername) == 0) {
            printf("Masukkan password baru: ");
            gets(data.passwordCus);
            fseek(f_daftarakun, -sizeof(data), SEEK_CUR);
            fwrite(&data, sizeof(data), 1, f_daftarakun);
            printf("Berhasil mengganti password!\n");
            fclose(f_daftarakun);
            system("pause");
            adminOptions();  
            return;
        }
    }

    printf("Username tidak ditemukan.\n");
    fclose(f_daftarakun);
    system("pause");
    adminOptions();  
}

void addStok(){
    FILE *f_daftarSepatu;
    f_daftarSepatu = fopen("daftar_sepatu.dat", "ab");

    if (f_daftarSepatu == NULL) {
        printf("Error: Gagal membuka file daftar_sepatu.dat\n");
        return;
    }

    printf("Masukkan ID Sepatu: ");
    scanf("%d", &data.sepatuId);
    getchar(); 
    printf("Masukkan Kategori (Male/Female): ");
    gets(data.kategori);
    
    if (strcmp(data.kategori, "Male") == 0) {
        printf("Masukkan Jenis Sepatu (Sneaker Boots): ");
    } else if (strcmp(data.kategori, "Female") == 0) {
        printf("Masukkan Jenis Sepatu (Flat Shoes/High Heel/Sandal): ");
    } else {
        printf("Kategori tidak valid.\n");
        fclose(f_daftarSepatu);
        return;
    }

    gets(data.jenis);
    printf("Masukkan Harga Sepatu: ");
    scanf("%f", &data.harga);
    printf("Masukkan Stok Sepatu: ");
    scanf("%d", &data.stok);

    fwrite(&data, sizeof(data), 1, f_daftarSepatu);
    fclose(f_daftarSepatu);

    printf("Data sepatu berhasil ditambahkan.\n");
    system("pause");
    adminOptions();
}
void viewOrder(){
    FILE *f_order;
    f_order = fopen("orderan.dat", "rb");

    if (f_order == NULL)
    {
        printf("Error: Gagal membuka file orderan.dat\n");
        return;
    }

    printf("===== Daftar Orderan =====\n");

    while (fread(&data, sizeof(data), 1, f_order) == 1)
    {
        printf("ID Sepatu: %d\n", data.sepatuId);
        printf("Kategori: %s\n", data.kategori);
        printf("Jenis: %s\n", data.jenis);
        printf("Harga: %.2f\n", data.harga);
        printf("Jumlah: %d\n", data.stok);
        printf("Total Harga: %.2f\n", data.harga * data.stok);
        printf("Metode Pembayaran: %s\n", data.metodePembayaran);
        printf("\n");
    }

    fclose(f_order);
    system("pause");
    adminOptions();
}

void viewFeedBack(){
    FILE *f_feedback;
    f_feedback = fopen("feedback.dat", "rb");

    if (f_feedback == NULL)
    {
        printf("Error: Gagal membuka file feedback.dat\n");
        return;
    }

    printf("===== Daftar Feedback =====\n");

    while (fread(&data, sizeof(data), 1, f_feedback) == 1)
    {
        printf("%s\n", data.feedback);
    }

    fclose(f_feedback);
    system("pause");
    adminOptions();
}

void viewUcust(){

    FILE *f_daftarakun;
    
    f_daftarakun = fopen("akuncus.dat", "rb");

    if (f_daftarakun == NULL)
    {
        perror("Error Membuka File");
        return;
    }

    int found = 0;

    while (fread(&data, sizeof(data), 1, f_daftarakun) == 1)
    {
        if (strcmp(data.userNameCus, data.targetUsername) == 0)
        {
            printf("===== Akun Customer =====\n");
            printf("Username: %s\n", data.userNameCus);
            printf("Password: %s\n", data.passwordCus);
            printf("Saldo: %d\n", data.saldo);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Maaf, akun customer dengan username %s tidak ditemukan.\n", data.targetUsername);
    }

    fclose(f_daftarakun);
    system("pause");
    adminOptions();
}

void user(){
    system("cls");

    int pilihan;

    printf("-----Shoes&Care-----\n");
    printf("Silahkan untuk memilih opsi yang diinginkan.\n");
    printf("1. Register.\n");
    printf("2. Login.\n");
    printf("3. Keluar dari program.\n");
    printf("Pilihan : ");
    scanf("%d", &pilihan);

    switch (pilihan)
    {
    case 1:
        system("cls");
        userReg();
        break;
    case 2:
        system("cls");
        userLogin();
        break;
    case 3:
        system("cls");
        outro();
        return 0;
    default:
        system("cls");
        printf("Mohon untuk memilih pilihan yang telah disediakan.");
        break;
    }
}

void viewShoes(){
    FILE *f_daftarSepatu;
    f_daftarSepatu = fopen("daftar_sepatu.dat", "rb");

    if (f_daftarSepatu == NULL)
    {
        printf("Error: Gagal membuka file daftar_sepatu.dat\n");
        return;
    }

    printf("===== Daftar Sepatu =====\n");

    while (fread(&data, sizeof(data), 1, f_daftarSepatu) == 1)
    {
        printf("ID Sepatu: %d\n", data.sepatuId);
        printf("Nama: %s\n", data.nama);
        printf("Kategori: %s\n", data.kategori);
        printf("Jenis: %s\n", data.jenis);
        printf("Harga: %.2f\n", data.harga);
        printf("Stok: %d\n", data.stok);
        printf("\n");
    }

    fclose(f_daftarSepatu);
    system("pause");
    adminOptions();
}

void searchShoes(){
    
    FILE *f_daftarSepatu;
    char keyword[50],field[50];
    f_daftarSepatu = fopen("daftar_sepatu.dat", "rb");

    if (f_daftarSepatu == NULL) {
        printf("Error: Gagal membuka file daftar_sepatu.dat\n");
        return;
    }

    printf("===== Hasil Pencarian =====\n");

    while (fread(&data, sizeof(data), 1, f_daftarSepatu) == 1) {
        if (strcmp(field, "kategori") == 0) {
            if (strcmp(data.kategori, keyword) == 0) {
                printf("ID Sepatu: %d\n", data.sepatuId);
                printf("Nama: %s\n", data.nama);
                printf("Kategori: %s\n", data.kategori);
                printf("Jenis: %s\n", data.jenis);
                printf("Harga: %.2f\n", data.harga);
                printf("Stok: %d\n", data.stok);
                printf("\n");
            }
        } else if (strcmp(field, "jenis") == 0) {
            if (strcmp(data.jenis, keyword) == 0) {
                printf("ID Sepatu: %d\n", data.sepatuId);
                printf("Nama: %s\n", data.nama);
                printf("Kategori: %s\n", data.kategori);
                printf("Jenis: %s\n", data.jenis);
                printf("Harga: %.2f\n", data.harga);
                printf("Stok: %d\n", data.stok);
                printf("\n");
            }
        }
    }

    fclose(f_daftarSepatu);
}

void userReg(){
    system("cls");
    printf("== Registrasi Customer ==\n");
    FILE *f_daftarakun;
    f_daftarakun = fopen("akuncus.dat", "ab");
    
    if (f_daftarakun == NULL) {
        perror("Error Membuka File");
        return;
    }else{

    printf("Username baru : ");
    gets(data.userNameCus);
    printf("\nPassword baru : ");
    gets(data.passwordCus);
    fwrite(&data, sizeof(data), 1, f_daftarakun)==1;
    }
    fclose(f_daftarakun);

    system("cls");
    printf("Berhasil Membuat Akun!!\n");
    system("pause");

   
    userLogin(3); 
}

void userLogin(){
    int attempts = 3;
    int success = 0;
    

    while (attempts > 0 && success == 0)
    {
        system("cls");
        printf("----------------------\n");
        printf("\tLOGIN\n");
        printf("----------------------\n");

        printf("\nMasukkan Username : ");
        gets(data.targetUsername);
        printf("\nMasukkan Password : ");
        gets(data.targetPassword);

        FILE *f_daftarakun;
        f_daftarakun = fopen("akuncus.dat", "rb");

        if (f_daftarakun == NULL)
        {
            perror("Error Membuka File");
            return;
        }

        while (fread(&data, sizeof(data), 1, f_daftarakun) == 1)
        {
            if (strcmp(data.targetUsername, data.userNameCus) == 0 && strcmp(data.targetPassword, data.passwordCus) == 0)
            {
                printf("Login berhasil!!\n");
                success = 1;
                system("pause");
                menuCustomer();
                break;
            }
        }

        fclose(f_daftarakun);

        if (success != 1)
        {
            attempts--;
            printf("Username atau Password Salah, sisa kesempatan login: %d\n", attempts);
            system("pause");
        }
    }

    if (attempts == 0)
    {
        printf("Kesempatan login habis.\n");
        system("pause");
        main();
    }
}

void menuCustomer(){
    
    system("cls");
    int pilihan;
    
    printf("1.Lihat Sepatu\n");
    printf("2.Cari Sepatu\n");
    printf("3.Check Out\n");
    printf("4.Ubah Password\n");
    printf("5.Feed Back\n");
    printf("6.Kembali\n");
    printf("7.Selesai");
    scanf("%d",&pilihan);
    
    switch(pilihan){
        case 1:
        system("cls");
        viewShoes();
        break;
        case 2:
        system("cls");
        searchShoes();
        break;
        case 3:
        system("cls");
        checkOut();
        break;
        case 4:
        system("cls");
        ubahPassUser();
        break;
        case 5:
        system("cls");
        addFeedback();
        break;
        case 6:
        system("cls");
        main();
        break;
        case 7:
        system("cls");
        printf("Thanks You !! ");
        main();
        break;
        default:
        printf("Data yang anda masukan tidak valid");
        system("pause");
        menuCustomer();
        break;
    }
}



void checkOut(){

    printf("===== Check Out =====\n");
    printf("Ringkasan Pesanan:\n");
    printf("ID Sepatu: %d\n", data.sepatuId);
    printf("Kategori: %s\n", data.kategori);
    printf("Jenis: %s\n", data.jenis);
    printf("Harga: %.2f\n", data.harga);

    float totalHarga = data.harga * data.stok;
    printf("Total Harga: %.2f\n", totalHarga);

    char metodePembayaran[50];
    printf("Masukkan metode pembayaran (Contoh: Kartu Kredit): ");
    scanf("%s", metodePembayaran);

    printf("===== Bukti Transaksi =====\n");
    printf("ID Sepatu: %d\n", data.sepatuId);
    printf("Kategori: %s\n", data.kategori);
    printf("Jenis: %s\n", data.jenis);
    printf("Harga: %.2f\n", data.harga);
    printf("Jumlah: %d\n", data.stok);
    printf("Total Harga: %.2f\n", totalHarga);
    printf("Metode Pembayaran: %s\n", metodePembayaran);

    FILE *f_order;
    f_order = fopen("orderan.dat", "ab");

    if (f_order != NULL)
    {
        fwrite(&data, sizeof(data), 1, f_order);
        fclose(f_order);
    }
    else
    {
        printf("Gagal menyimpan data transaksi.\n");
    }
    memset(&data, 0, sizeof(data));

    printf("Transaksi selesai.\n");
    system("pause");
    menuCustomer();
}

void ubahPassUser(){
    
    printf("== Ganti Password Customer ==");
    FILE *f_daftarakun;
    f_daftarakun = fopen("akuncus.dat", "rb+");
    if (f_daftarakun == NULL)
    {
        perror("Error Membuka File");
        return;
    }

    printf("\nMasukkan username customer: ");
    gets(data.targetUsername);
    while (fread(&data, sizeof(data), 1, f_daftarakun) == 1)
    {
        if (strcmp(data.userNameCus, data.feedback) == 0)
        {
            printf("Masukkan password baru: ");
            gets(data.passwordCus);
            fseek(f_daftarakun, -sizeof(data), SEEK_CUR);
            fwrite(&data, sizeof(data), 1, f_daftarakun);
            printf("Berhasil mengganti password!\n");
            fclose(f_daftarakun);
            system("pause");
            menuCustomer();
        }
    }
    printf("Username tidak ditemukan.\n");

    fclose(f_daftarakun);
    system("pause");
    menuCustomer();
}

void addFeedback(){
    FILE *f_feedback;
    f_feedback = fopen("feedback.dat", "ab");

    if (f_feedback == NULL)
    {
        printf("Error: Gagal membuka file feedback.dat\n");
        return;
    }

    printf("Masukkan Feedback Anda (maksimum 100 karakter):\n");
    getchar();
    fgets(data.feedback, sizeof(data.feedback), stdin);

    fwrite(&data, sizeof(data), 1, f_feedback);
    fclose(f_feedback);

    printf("Feedback Anda telah disimpan. Terima kasih!\n");
    system("pause");
    menuCustomer();
}


void outro(){
    printf("Terima kasih telah menggunakan aplikasi kami");
    return 0;
}
