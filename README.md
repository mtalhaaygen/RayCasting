# RayCasting

# Proje için

.cub için olması gerekenler;

- [x] NO/SO/WE/EA/F/C değerlerinin sırası kendi araasında değişebilir, belirli bir sırayla gelmek zorunda değil. Ard arda gelmeli daha sonra harita gelecek
- [x] NO/SO/WE/EA/F/C değerleri her biri bir satırda belirtilmeli ve satırın başında sonunda NO ve ./path arasında boşluklar tablar olabilir
- [x] F/C değerleri 3er sayıdan oluşmalı ve bu sayılar yalnızca virgül ile ayrılabilir
- [x] NO/SO/WE/EA değerlerinden iki tane olunca hata vermeli
- [X] player bir tane olacak , W- E-N-S den bir tane olacak
- [X] NO/SO/WE/EA değerlerinden biri eksik olunca hata vermeli
- [x] NO/SO/WE/EA değerleri aynı olamaz
- [x] dosyaların uzantısı xpm mi
- [ ] dosyalar var mı? mlx_xpm_to_img ile kontrol edeceğiz

- [x] boş bir satırda sadece space tab varsa hata döndürülmeli

- [x] haritanın çevresi 1 ler ile çevrili olmalı, ' ' karakterinin sağında solunda sadece ' ' ya da 1 olabilir her boşluğu kontorol et
Burada karakterin sınırda olması hata olur onuda tek olarak kontorl ettim ÖRNEK
111W1111
100001111
111111111
- [x] ayrıca haritada yabancı bir karakter var mı onuda kontrol et
- [x] haritanın satır sonlarındaki \n den sonraki karakterler 1 mi kontrol ettikten sonra haritada tüm satırları aynı genişliğe ulaştırmak için tüm satırların sonuna yeteri kadar space at. Daha sonra check_wall fonksiyonu ile harita kontrolü tamamlanmış oluyor

- [x] birbirine bağlı olmayan iki harita olamaz sadece bir harita olacak. Haritanın ulaşılabilir olmayan kısımları olabilir

- [x] haritanın içinde space olabilir, ama tab olamaz, tüm spaceleri 1 yapmak işe yarayabilir

- [x] COLOR ATAMASI YAPMADAN ÖNCE ATOİ İLE SYAILARI KONTORL ET [0,255] Kapalı aralığında olmak zorunda
color yapımı x,y,z    int color = (x << 16) | (y << 8) | z;
