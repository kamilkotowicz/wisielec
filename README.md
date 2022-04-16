# wisielec
Projekt na przedmiot podstawy programowania napisany w 2019 roku.

Program obsługuje grę z komputerem (w trybie łatwym i trudnym), grę dwuosobową oraz zapisywanie najlepszych wyników do pliku.

W trybie łatwym program po prostu wybiera losowe słowo.
W trybie trudnym program "oszukuje" tzn. stara się dostosowywać słowo, które wybrał, tak aby jak najbardziej zwiększyć szansę na przegraną gracza.

Algorytm gry komputera w trybie trudnym:
1.	Przy pierwszym wywołaniu rekurencji wczytaj literę od gracza. Przy kolejnym wywołaniu znajdź literę występującą w największej liczbie dozwolonych słów.
2.	Stwórz podlistę dozwolonych słów, które nie zawierają tej litery.
3.	Znajdź najczęściej występujący wzorzec ( pozycje w których haśle występuje dana litera) spośród wszystkich słów zawierających tą literę.
4.	Stwórz podlistę słów z najczęściej występującym wzorcem wystąpień danej litery.
5.	Sprawdź rekurencyjnie czy możesz wygrać jeśli zdecydujesz że litera nie występuje w haśle (zabierz jedno życie graczowi, zmień listę dozwolonych słów na podlistę z punktu 2).
6.	Sprawdź rekurencyjnie czy możesz wygrać jeśli zdecydujesz że litera występuje w słowie na pozycjach z najczęstszego wzorca (zmień listę dozwolonych słów na podlistę z punktu 4).
7.	Jeśli nie można wygrać w żaden sposób to jeśli podlista z punktu 2 jest większa od podlisty z punktu 4 to zdecyduj, że litery nie ma w haśle.
8.	W przeciwnym wypadku zdecyduj losowo czy uznać, że litera jest w haśle czy nie.
