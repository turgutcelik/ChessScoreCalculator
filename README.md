# Chess Score Calculator
## Açıklama

Bu proje, satranç oyununda taşların (siyah, beyaz) mevcut durumuna dayalı olarak puanlarını hesaplar. Satrançta her taş belirli bir puana sahiptir. Tüm taşların tehdit durumları kontrol edilir. Kontrol edilen koşullar, bir piyon tarafından tehdit edilme, bir at tarafından tehdit edilme ve bir vezir tarafından tehdit edilme durumudur. Bir satranç taşı, aynı türden birden fazla taş tarafından tehdit edilebilir (örneğin, bir beyaz taş iki siyah piyon tarafından tehdit edilebilir) veya aynı anda birden fazla türdeki taşlar tarafından tehdit edilebilir. Bu durumda, tehdit durumu sadece bir kez göz önünde bulundurulur ve puanlaması buna göre hesaplanır. **Tablo1**'de görüldüğü gibi siyah ve beyaz taşların puanları belirlenmiştir. Tehdit altındaki bir taşın puanı yarıya düşer. Bir oyuncunun puanı, taşlarının toplam puanından oluşur. Siyah ve beyaz taşlar için iki ayrı puan hesaplanır.  
<br/>
| Taş İsmi    | Kısaltma    | Puanı    | 
|:-----------|:-----------|:-----------|
| Piyon    | **♙**ps, ♙pb      | 1      | 
| At      | **♞** as, ♘ab      | 3      |
| Fil      | **♝**fs, ♗fb      | 3      | 
| Kale      | **♜**ks, ♖kb      | 5      | 
| Vezir      | **♛**vs, ♕vb      | 9      | 
| Şah      | **♚**ss, ♔sb      | 100      | 

**Tablo1:** Satranç taş isimleri, kısaltmaları ve puanları<br/>

Kısaltmalarda taş isimlerinin baş harfi ön ek, taşların renklerinin baş harfi son ek olarak yazılmıştır.<br/>
pb: **p**iyon+**b**eyaz<br/>
ps: **p**iyon+**s**iyah

## Derleme
### Gereksinimler
•	C++ derleyici (Dev-C++, Visual Studio vb.)<br/>
•	C++ çalışma zamanı kütüphaneleri
#### Adım 1: Kodu İndirme
•	GitHub sayfasından kodu indirin.<br/>
•	Kodu ZIP olarak indirirseniz, ZIP dosyasını açın ve kodu uygun bir klasöre çıkarın.
#### Adım 2: Satranç Tahtası Dosyası Oluşturma
•	Dilediğiniz isimde örneğin, "chess_board.txt" adında bir metin belgesi oluşturun. Metin belgesini kodun bulunduğu dizinde oluşturun.<br/>
•	Metin belgesine taşların konumlarını girin. Buradaki siyah ve beyaz taşların tehdit durumlarına göre toplam puanları hesaplanacaktır. Figür1 örnek bir satranç durumunu, Figür2 ise bu durumun metin belgesine girilmiş halini gösterir. Başlangıç durumu olduğu için hiçbir taş tehdit altında değildir.<br/><br/>
![Ekran Alıntısı3](https://github.com/turgutcelik/ChessScoreCalculator/assets/106097128/e87271f4-9618-4109-b725-ed06c209ddf4)
<br/>
**Figür1:** Başlangıç durumu<br/><br/>
![Ekran Alıntısı6](https://github.com/turgutcelik/ChessScoreCalculator/assets/106097128/b3d9ce11-b6ee-44c1-a44e-3ec92f28e614)<br/>
**Figür2:** Başlangıç durumunun metin dosyasındaki temsili<br/>

#### Adım 3: Kodu Derleme
• Kodun bulunduğu dizine gidin.<br/>
• C++ derleyicinizi kullanarak programı derleyin. 


## Örnek Uygulama
Figür3 oyundaki mevcut durumu, Figür4 ise bu durumun metin belgesine girilmiş halini gösterir.

![board1](https://github.com/turgutcelik/ChessScoreCalculator/assets/106097128/729cee83-30e7-4570-97fa-18cecf98e432)<br/>
**Figür3:** Tehdit altındaki durum<br/>
![Ekran Alıntısı8](https://github.com/turgutcelik/ChessScoreCalculator/assets/106097128/e1990317-ba10-4b15-8871-51bce732937c)<br/>
**Figür4:** Tehdit altındaki durumun metin dosyasındaki temsili<br/>

![xx](https://github.com/turgutcelik/ChessScoreCalculator/assets/106097128/fed60098-d9ff-4cca-932a-88ffd649af7a)<br/>
**Figür5:** Sonuç

