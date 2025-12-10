# C Dilinde Sıralama Algoritmaları Performans Karşılaştırıcısı

## 📊 Proje Özeti (1. Aşama)

Bu proje, C programlama dilini kullanarak, farklı teorik zaman karmaşıklıklarına sahip temel sıralama algoritmalarının büyük veri kümeleri üzerindeki **gerçek zamanlı performansını** bilimsel yöntemlerle karşılaştırmak amacıyla geliştirilmiştir.

**Kapsanan Algoritmalar:**
* $O(n^2)$ Sınıfı: Insertion Sort (Ekleme Sıralaması)
* $O(n \log n)$ Sınıfı: Merge Sort (Birleştirme Sıralaması) ve Quick Sort (Hızlı Sıralama)

---

## 🛠️ Teknik Özellikler ve Metodoloji

Proje, performans analizinin güvenilirliğini sağlamak için C diline özgü kritik teknikler kullanır:

1.  **Yüksek Hassasiyetli Zamanlama:** Standart C `time()` yerine, mikrosaniye çözünürlük sağlayan **`gettimeofday()`** fonksiyonu kullanılmıştır. Bu, hızlı algoritmalar arasındaki küçük farkları doğru ölçmek için hayati önem taşır.
2.  **Dinamik Yönetim:** Farklı $N$ değerlerinde (1.000, 10.000, 50.000) rastgele veri setleri oluşturmak için **`malloc()`** ve bellek sızıntısını önlemek için **`free()`** kullanılmıştır.
3.  **Modülerlik:** Tüm algoritmalar, **fonksiyon işaretçileri** kullanılarak tek bir genel test fonksiyonu (`measure_performance`) üzerinden çağrılır.

---

## 🚀 Çalıştırma Talimatları (GCC Kullanımı)

Kodu derlemek ve çalıştırmak için:

```bash
# 1. Kodu derle
gcc main.c -o sorting_app -lm 

# 2. Uygulamayı çalıştır
./sorting_app
