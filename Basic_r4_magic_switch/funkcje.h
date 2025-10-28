#pragma once

void ICACHE_RAM_ATTR zmienStan(){// wektor przerwania deszczomierza
  czas1 = millis();
  if (czas2 - czas1 < 9 && czas2 - czas1 > debounce){
    status1 = !status1;  
  }
  if (czas2 - czas1 > debounce || czas2 > czas1){
    czas2 = czas1;
  }  
 
}