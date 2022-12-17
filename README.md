# The Ticketing App -  Mihai Rosu

Structura aplicatiei:

clasa Bilet
- clasa Eveniment
- clasa Locatie
   - clasa Zona
      - clasa Rand
         - clasa Scaun 


Bilet
Atribute:
  Unique ID - identificatorul unic
  Pret - pretul biletului
  Nume Participant - numele participantului
  Locatie - obiect locatie pentru care biletul este generat
  Eveniment - obiect eveniment pentru care biletul este generat

Eveniment
Atribute:
  Denumire - numele evenimentului
  Data - data evenimentului
  Ora - ora evenimentului


Locatie
Atribute:
  Denumire - numele locatiei
  Numar Zone - numarul de zone din locatie
  Numar Zone Cu Scaune Libere - numarul de zone cu scaune libere
  Zone - zonele din locatie
  
Functii:
  Capacitate locatie
  Numar Locuri libere
  Acces la scaunele libere dintr-o anumita zona sau din locatie
  Acces la randurile cu scaune libere dintr-o anumite zona
  
  
  
Zona
Atribute:
  Denumire - numele zonei
  Numar Randuri - numarul de randuri pe zona
  Numar Randuri Libere - numarul de randuri libere in zona
  Randuri - randurile din zona  



Rand
Atribute:
  Numar Rand - identificatorul randului
  Numar Scaune - numarul de scaune pe rand
  Numar Scaune Libere - numarul de scaune libere pe rand
  Scaune - scaunele de pe rand



Scaun
Atribute:
  Codificare - identificatorul scaunului
  Ocupat - statrea scaunului (ocupat, neocupat)
