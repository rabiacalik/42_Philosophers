# 42_Philosophers
part 2 project

![Uploading autodraw 8_8_2023.png…]()


- girilen argüman sayısının 5 veya 6 olması gerek bunlar filozof sayısı , ölüm süresi(ne kadar aç kalabilir), yemek yeme ve uyuma süreleri en son arguman ise
isteğe bağlı olarak girilen her filozofun yemesi gereken öğün sayısıdır.

- filozof sayısı kadar çatal olmalı filozofların sayısı birden başlamalı, bir filozofun yemek yiyebilmesi için iki çatala ihtiyacı vardır. eğer programı çalıştırırken bir filozof girilirse bir çatalı olur ve yemek yiyemeden ölür.

- programda usleep() yerine my_sleep adında bir fonksiyon kullanmamın nedeni programda usleep in bazı yerlerde yanlış çalışması. örnek olarak usleep(1000); kadar bekletmek istiyorsam bunu birden 1000 kadar bekletmek yerine my_sleep ile 100 er şekilde 10 kere bekletiyorum.

-  thread ler yani iş parçacıkları ortak alanları kullanırlar. Bu ortak alanları kullanırlarken karışıklık olmaması için mutexleri kullanıyoruz. Örnek olarak, iki flozofolsun bu flizofların ikisine de aralarında  olan çatalları almaları için istek geliyor. ikiside hamle yapıp çatallı almaya çalışıyorlar ama biri diğerinden önce alıyor ve diğer filozof çatalı alamıyor ama daha öncesinde orada bir çatal vardı. Bunu bilgisayardaki bellek yönetiminin simüle edilmiş hali olarak düşünebilirsiniz. Bu sorunun yaşanmaması için çatalı alan filozof mutexi kilitler ve diğer filozofda kilitleme için bekler çatalı alan filozofumuz kilidi bıraktığı an diğer filozof çatalı alır. Sıra bekliyor gibi düşünülebilir.

- Eğer tüm filozoflar aynı anda sağ çatallarını alırlarsa ne olur, eğer hepsi sağ çatalını veya sol çatallarını alırlarsa diğer çatalı bulamıcaklar çünkü hepsi birer çatal almışlar yani hepsi açlıktan ölücek. Bunun olmaması için çift sayılı filozofları biraz bekletiyoruz ki bu sonuçla karşılaşmayalım.

- filozoflar yemeklerni yedikten sonra acıkmaya başlamazlar, Pdf de yazana göre filozoflar yemek yemeye başladıkları andan itibaren acıkmaya başlarlar.

- ölüm süresi, yemek yeme + uyuma  sürelerinden az olursa Örnek 4 300 200 200 ; filozoflar ölür.
