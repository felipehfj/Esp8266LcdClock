# Projeto de Relógio com WiFi

Este projeto é um relógio que se conecta à internet para obter a hora atual. Ele usa um módulo WiFi para se conectar à internet e um cliente NTP para obter a hora atual. A hora é então exibida em um display LCD.

## Como usar

1. Conecte o módulo WiFi e o display LCD ao seu microcontrolador.
2. Carregue o código para o microcontrolador.
3. O relógio deve começar a exibir a hora atual.

## Código

O código principal está contido no arquivo `main.cpp`. Ele começa conectando-se à rede WiFi especificada e configurando o cliente NTP. Em seguida, ele inicializa o display LCD e entra em um loop onde atualiza a hora a cada meio segundo e a exibe no display LCD.

Aqui está um trecho do código:

```cpp
void loop()
{
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  int currentYear = ptm->tm_year + 1900;
  String currentDate = String(monthDay) + "/" + String(currentMonth) + "/" + String(currentYear);

  lcd.setCursor(0, 0);
  lcd.print("DATE:" + currentDate);
  lcd.setCursor(0, 1);
  lcd.print("TIME:" + formattedTime);
  lcd.setCursor(15, 1);
  delay(500);
}
```

## Dependências

Este projeto depende das seguintes bibliotecas:

- WiFi
- NTPClient
- LiquidCrystal_I2C

Certifique-se de instalá-las antes de tentar compilar e carregar o código.

## Contribuições

Contribuições para este projeto são bem-vindas. Se você encontrar um bug ou tem uma sugestão de melhoria, sinta-se à vontade para abrir uma issue ou enviar um pull request.