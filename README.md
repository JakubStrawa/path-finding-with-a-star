#### Projekt na przedmiot PSZT implementujący i badający algorytm A*, zachłanny i brute force dla zadania znalezienia ścieżki o najmniejszej wadze od punktu A do B.
#### Krótka instrukcja:
1. Sklonuj repozytorium na swój komputer
2. Wykonaj komendę: "cmake [ścieżka do katalogu z plikami]" na przykład:
    "cmake ." (Będąc w katalogu z plikami)
    
    lub komendę: "cmake -S [katalog ze źródłami] -B [katalog gdzie ma zostać zbudowana aplikacja]", na przykład:

    "cmake -S path-finding-with-a-star-master -B path-finding-with-a-star-master" (Będąc w katalogu nadrzędnym)
3. Wykonaj komendę: "make" (w katalogu z plikami)
4. Uruchom program:
    - pathfinding_with_A_star (dla gałęzi master)
    - pathfinding_with_A_star_heuristic (dla gałęzi heuristic)
5. Ścieżkę do pliku .txt możesz zmienić w pliku main.cpp - zmienna "graphFilePath"
