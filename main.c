#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h> // Yüksek hassasiyetli zamanlama için kritik kütüphane

// ==============================================================================
// 1. Yardımcı Fonksiyonlar ve Zaman Ölçümü
// ==============================================================================

/**
 * Yüksek hassasiyetli zamanı saniye cinsinden döndürür.
 * sys/time.h kütüphanesini kullanır.
 */
double get_time_in_seconds()
{
    struct timeval t;
    // gettimeofday, zamanı saniye (tv_sec) ve mikrosaniye (tv_usec) olarak döndürür.
    gettimeofday(&t, NULL);
    // Toplam zamanı double türünde saniyeye çevirip döndürürüz.
    return (double)t.tv_sec + (double)t.tv_usec / 1000000.0;
}

/**
 * İki tam sayı değerini yer değiştirmek için kullanılır (Pointer kullanımı).
 */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ==============================================================================
// 2. Sıralama Algoritmaları
// ==============================================================================

/**
 * Insertion Sort (Ekleme Sıralaması) Algoritması.
 * Zaman Karmaşıklığı: O(n^2).
 */
void insertion_sort(int arr[], int n)
{
    int i, key, j;
    // Diziyi ikinci elemandan (index 1) başlayarak dolaş
    for (i = 1; i < n; i++)
    {
        key = arr[i]; // Mevcut elemanı anahtar olarak al
        j = i - 1;

        // Anahtarı, kendinden önceki sıralı kısımda doğru yerine kaydır
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j]; // Elemanı bir sağa kaydır (Sağa kaydırma mantığı)
            j = j - 1;
        }
        arr[j + 1] = key; // Anahtarı doğru konuma yerleştir
    }
}

// ------------------------------------------------------------------------------

/**
 * Merge Sort (Birleştirme Sıralaması) için birleştirme (merge) yardımcı fonksiyonu.
 */
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1; // Sol alt dizinin boyutu
    int n2 = r - m;     // Sağ alt dizinin boyutu

    // Geçici alt diziler oluştur
    int L[n1], R[n2];

    // Verileri geçici dizilere kopyala
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Geçici dizileri ana diziye (arr) birleştir (Karşılaştırma mantığı)
    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Kalan elemanları kopyala
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

/**
 * Merge Sort (Birleştirme Sıralaması) Algoritması.
 * Zaman Karmaşıklığı: O(n log n).
 */
void merge_sort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Tam ortayı bul (m) (Bölme Mantığı)
        int m = l + (r - l) / 2;

        // Özyinelemeli olarak sol ve sağ yarıyı sırala
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        // Sıralanmış yarıları birleştir
        merge(arr, l, m, r);
    }
}

// ------------------------------------------------------------------------------

/**
 * Quick Sort (Hızlı Sıralama) için bölme (partition) yardımcı fonksiyonu.
 */
int partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // Pivot olarak son elemanı seç
    int i = (low - 1);     // Küçük elemanın indexi

    for (int j = low; j <= high - 1; j++)
    {
        // Eğer mevcut eleman pivottan küçükse
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]); // Elemanı küçükler grubuna taşı
        }
    }
    swap(&arr[i + 1], &arr[high]); // Pivotu doğru konuma yerleştir
    return (i + 1);                // Pivotun doğru konumunu döndür
}

/**
 * Quick Sort (Hızlı Sıralama) Algoritması.
 * Zaman Karmaşıklığı: O(n log n) (Ortalama).
 */
void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        // Bölüm indexi (pivotun doğru konumu)
        int pi = partition(arr, low, high);

        // Özyinelemeli olarak sol ve sağ alt dizileri sırala
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// ==============================================================================
// 3. Performans Karşılaştırma Mekanizması
// ==============================================================================

/**
 * Belirtilen sıralama fonksiyonunun performansını ölçer.
 * Fonksiyon işaretçisi (void (*sort_func)(int[], int, int)) kullanır.
 */
void measure_performance(void (*sort_func)(int[], int, int), int arr[], int n, const char *name)
{

    // Dinamik Bellek Yönetimi: Verinin kopyasını oluştur (Orjinal veri bozulmasın)
    int *data_copy = (int *)malloc(n * sizeof(int));
    if (data_copy == NULL)
    {
        perror("Bellek ayırma hatası");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        data_copy[i] = arr[i];
    }

    // Zaman ölçümüne başla
    double start = get_time_in_seconds();

    // Sıralama Fonksiyonunu Çalıştır
    sort_func(data_copy, 0, n - 1);

    // Zaman ölçümünü bitir
    double end = get_time_in_seconds();

    // Sonuçları yazdır
    printf("%-30s | %.6f\n", name, end - start);

    // Belleği serbest bırak (free)
    free(data_copy);
}

// ==============================================================================
// 4. Ana Program (main) - Test ve Karşılaştırma
// ==============================================================================

int main()
{
    // Rastgele sayı üretimi için seed ayarı
    srand(time(0));

    // Test edilecek veri kümeleri (N)
    int data_sizes[] = {1000, 10000, 50000};
    int num_sets = sizeof(data_sizes) / sizeof(data_sizes[0]);

    printf("--- C Dili Sıralama Algoritmaları Performans Karşılaştırıcısı ---\n");

    for (int i = 0; i < num_sets; i++)
    {
        int size = data_sizes[i];

        printf("\n##################################\n");
        printf("## Veri Kümesi Büyüklüğü: N = %d ##\n", size);
        printf("##################################\n");

        // Dinamik olarak bellek ayır (malloc)
        int *random_data = (int *)malloc(size * sizeof(int));
        if (random_data == NULL)
        {
            perror("Bellek ayırma hatası");
            return 1;
        }

        // Veri Setini Rastgele Sayılarla Doldur
        for (int j = 0; j < size; j++)
        {
            random_data[j] = rand() % (size * 10);
        }

        printf("%-30s | %-15s\n", "Algoritma Adı", "Süre (saniye)");
        printf("-------------------------------------------------\n");

        // --- Insertion Sort (O(n^2)) ---
        // Insertion Sort farklı prototipe sahip olduğundan, özel bir kopyalama ve zamanlama gerekir.
        int *ins_copy = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++)
            ins_copy[j] = random_data[j];

        double start = get_time_in_seconds();
        insertion_sort(ins_copy, size);
        double end = get_time_in_seconds();
        printf("%-30s | %.6f\n", "Insertion Sort (O(n^2))", end - start);
        free(ins_copy);

        // --- Merge Sort (O(n log n)) ---
        // measure_performance fonksiyon işaretçisi kullanılarak çağrılır.
        measure_performance(merge_sort, random_data, size, "Merge Sort (O(n log n))");

        // --- Quick Sort (O(n log n)) ---
        measure_performance(quick_sort, random_data, size, "Quick Sort (O(n log n))");

        // Ana veri belleğini serbest bırak
        free(random_data);
    }

    printf("\nKarşılaştırma tamamlandı.\n");
    return 0;
}
