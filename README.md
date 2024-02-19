# Mathematical_Expression_Evaluator
(third Effective Programming Techniques project)

Program umożliwia wczytywanie formuł matematycznych, interpretowanie ich w
postaci drzewa i wykorzystanie drzewa do wyliczenia wartości formuły. 
Formuły matematyczne są podawane na wejście programu w postaci prefiksowej. 
Komunikacja z programem odbywa się za pośrednictwem konsoli.

Polecenia, które można wprowadzić do konsoli:
enter <formula> - wykonanie powoduje próbę stworzenia drzewa na podstawie podanego
wyrażenia. Jeżeli wyrażenie nie może zostać wczytane, bo posiada błędy, program 
uzupełnia drzewo tak, żeby drzewo było prawidłowe.
vars – wypisuje wszystkie zmienne z aktualnie wprowadzonego drzewa. Każda zmienna jest
wypisywana jeden raz, nawet jeśli występuje w drzewie więcej razy.
print – wypisuje aktualnie wprowadzone drzewo w postaci prefiksowej
comp <var0> <var1>…<varN> – wyliczenie wartości wprowadzonej formuły, gdzie <var0>
<var1>…<varN> to wartości dla kolejnych zmiennych występujących w drzewie. Wartości
odpowiadają zmiennym w kolejności w jakiej zmienne są wypisywane przez polecenie vars.
join <formula> - wykonanie powoduje próbę stworzenia drzewa na podstawie podanego
wyrażenia. Następnie stworzone drzewo jest doklejane do istniejącego drzewa.

Wyrażenie może zawierać symbole operacji, zmienne i liczby
Obsługiwane typy operacji: +, -, *, /, sin, cos.
Nazwy zmiennych składają się z liter dużych i małych i cyfr.
Jeśli w ciągu znaków znajduje się niedozwolona wartość np. „$”, to ignorujemy ją.
W nazwie zmiennej musi wystąpić co najmniej jedna litera.
Liczby składają się wyłącznie z cyfr i mogą być jedynie dodatnie.
Przyjmujemy, że poszczególne człony wyrażenia są oddzielane od siebie co najmniej jedną spacją.
Program poprawia wyrażenia poprzez uzupełnienie brakujących elementów i pominięcie nadmiarowych. 
Na przykład, jeśli zostanie wprowadzone wyrażenie „+ + +”, to takie wyrażenie zostanie naprawione do: „ + 1 + 1 + 1 1”. 
Łączenie drzew: Jeżeli łączymy drzewo A z drzewem B, to znaczy, że zamiast ostatniego z liści drzewa A  wstawiamy korzeń drzewa B. 

W implementacji użyto trzech głównych klas: 
Mediator
Tree
Node
