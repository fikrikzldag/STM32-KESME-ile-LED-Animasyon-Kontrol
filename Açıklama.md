Bu projede, STM32F407G-DISC1 geliştirme kartı üzerindeki USER butonunu (PA0) 
kullanarak kesme (interrupt) tabanlı bir LED kontrol sistemi geliştirilmiştir. 
Ana programda sadece yeşil (GPIO_PIN_12) ve mavi (GPIO_PIN_15) LED'ler yanmaktadır. 
Butona her basıldığında, kesme mekanizması devreye girerek ana döngüyü geçici olarak keser 
ve butonun kaç kez basıldığına bağlı olarak farklı LED animasyonları çalıştırır. 
Örneğin, butona bir kez basıldığında LED'ler sırayla yanıp sönerken, 
iki kez basıldığında ters yönde bir animasyon gerçekleşir.

KART ÜZERİNDE GÖSTERİMİ : 
https://youtube.com/shorts/_vOtHr54e1Y?si=nsP41BzNN7jOBPLb 
