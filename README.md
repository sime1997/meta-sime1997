**Zadatak**. U ovom zadatku treba napisati niz metafunkcija. 
Cilj je da se glavni program kompilira (i izvršava) i stoga se glavni program
ne smije mijenjati. Tokom razvoja koda komentirajte one dijelove glavnog 
programa koji još ne funkcioniraju. U završnoj verziji ukloniti sve komentare iz
`main()` bez obzira da li se kod kompilira ili ne. 

-  Napisati metafunkciju `RemoveReference` koja uklanja referencu 
   s danog tipa ( std to radi `remove_reference<>`). Dodati i `_t` alias template.
   Ne koristiti metafunkcije iz zaglavlja `<type_traits>`.
-  Napisati metafunkciju `AddLValueReference` koja na tip dodaje lijevu referencu.
   Za tip `void`  vraća `void` jer ne postoji    referenca na `void`. Dodati i `_t` alias template.
   Ne koristiti metafunkcije iz zaglavlja `<type_traits>`.
-  Napisati metafunkciju `IsArray` koja vraća `true` ako je tip polje, a inače vraća `false`. 
   Uključiti ograničena polja (tip T[N]) i neograničena polja (tip T[]). Dodati i predložak vatijable `_v`.
   Ne koristiti metafunkcije iz zaglavlja `<type_traits>`.
-  Definirati operator zbrajanja općenito različitih polja `std::array<T>` i
   `std::array<S>`. Definirati povratnu vrijednost operatora kao `std::array<V>` 
    tako da `V` bude egzaktno tip koji proizvodi zbrajanje objekta tipa `T` i `S`.
    Iz standardne biblioteke koristiti samo `std::declval<>`.
-  Potrebno je napisati metafunkciju `IsBaseOf<B,D>` (u STL-u `std::is_base_of<B,D>`)
   koja ispituje je li klasa `B` **javna bazna** klasa za `D`. 
    Temelj na kojem se bazira razlikovanje je preopterećenje funkcija. Ako imamo
    pokazivač na klasu `D` tada je njegova konverzija u pokazivač na baznu klasu 
    bolja od konverzije u pokazivač na `void`. Na taj način možemo razlikovati klasu 
    koja ima odgovarajuću bazu od one koja ju nema.  
    Iz `<type_traits>` koristiti samo `std::is_class<>` te `std::true_type` i `std::false_type`. 
    Ne kopirati rješenje iz cppreference.com (0 bodova) koje funkcionira i s privatnom bazom i 
    s ambivalentnom bazom!
-   Potrebno je napraviti funkciju koja vrši sigurnu konverziju 
    `safe_cast<To, From>()`. Sigurnost ovdje znači da se u debug načinu 
    kod zaustavlja u slučaju greške pomoću `assert` makroa. 
    Treba se osigurati sljedeće ponašanje i reagirati na sljedeće moguće grešake:
    1. Kod konverzije pokazivača treba provjeravati (samo u debug načinu, pomoću `assert` makroa)
       da imamo posla s pokazivačima na objekte iz istog lanca nasljeđivanja.
       Konverzije u pokazivač na `void` i obratno se ne dozvoljavaju. 
    2. Kod konverzije `long double` i `double` u `double` ili `float`  gubitak preciznosti se tolerira osim 
       kada je `From` vrijednost suviše velika za `To` tip pa se dobiva `Inf` ili `NaN`. To se detektira
       pomoću `assert` makroa.
    3. Kod svih ostalih aritmetičkih konverzija gubitak preciznosti se **ne tolerira**.
    4. Kod konverzije pokazivača u cjelobrojni tip treba provjeriti da je 
       tip u koji se vrši konverzija `uintptr_t` ili `intptr_t`. To su jedina dva cjelobrojna tipa 
       koja garantiraju da mogu čuvati vrijednost pokazivača. Obratne konverzije se isto dozvoljavaju.
    5. Ako su tipovi isti samo vrati vrijednost.
    6. U slučaju drugih konverzija funkcija  `safe_cast<To, From>()` se ne kompilira!
