# RayCasting

# Proje için

.cub için olması gerekenler;

- NO/SO/WE/EA/F/C değerlerinin sırası kendi araasında değişebilir, belirli bir sırayla gelmek zorunda değil. Ard arda gelmeli daha sonra harita gelecek
- NO/SO/WE/EA/F/C değerleri her biri bir satırda belirtilmeli ve satırın başında sonunda NO ve ./path arasında boşluklar tablar olabilir
- F/C değerleri 3er sayıdan oluşmalı ve bu sayılar yalnızca virgül ile ayrılabilir
- NO/SO/WE/EA değerleri aynı olamaz
- boş bir satırda sadece space tab varsa hata döndürülmeli
- haritanın çevresi 1 ler ile çevrili olmalı, ' ' karakterinin sağında solunda sadece ' ' ya da 1 olabilir her boşluğu kontorol ettim
Burada karakterin sınırda olması hata olur onuda tek olarak kontorl ettim ÖRNEK
111W1111
100001111
111111111
- birbirine bağlı olmayan iki harita olamaz sadece bir harita olacak. Haritanın ulaşılabilir olmayan kısımları olabilir

- player bir tane olacak , W- E-N-S den bir tane olacak
- haritanın içinde space olabilir, ama tab olamaz, tüm spaceleri 1 yapmak işe yarayabilir
- dosyaların uzantısı xpm mi
- dosyalar var mı

- COLOR ATAMASI YAPMADAN ÖNCE ATOİ İLE SYAILARI KONTORL ET [0,255] Kapalı aralığında olmak zorunda
color yapımı x,y,z    int color = (x << 16) | (y << 8) | z;
