# IoT-Monitoreo-Nivel-Caudal
**Prueba de Concepto: Sistema IoT para Monitoreo de Nivel y Caudal usando MQTT, Node-RED y Power BI**

Este proyecto implementa un sistema IoT completamente simulado para monitorear el nivel de agua y estimar el caudal mediante una ESP32 en Wokwi, un flujo complejo en Node-RED, transporte MQTT y visualización en Power BI. La solución además registra datos en Google Sheets, genera un archivo TXT local y envía alertas automáticas a Telegram.

---

# Funcionamiento General

1. La ESP32 lee el valor del potenciómetro (sensor virtual de nivel).  
2. Publica el nivel por MQTT usando HiveMQ.  
3. Node-RED:
   - Calcula el caudal usando curvas de calibración.
   - Redondea y formatea las variables.
   - Envía los datos hacia:
     - Dashboard Node-RED
     - Google Sheets 
     - Power BI Streaming Dataset
     - Archivo `.txt`
     - Bot de Telegram
4. Power BI grafica los datos en tiempo real.
5. Google Sheets almacena históricamente cada registro.
6. El bot de Telegram envía actualizaciones cada 10 segundos.

---

## Cómo Ejecutar el Proyecto

### 1. Ejecutar la ESP32 en Wokwi
- Abrir https://wokwi.com  
- Crear un proyecto ESP32
- Armar el siguiente circuito

![Flujo Node-RED](circuit-wokwi.png)

- Copiar el contenido de `sketch.ino`
- Dar clic en **Start the simulation**  

---

### 2. Importar el flujo en Node-RED
- Abrir Node-RED  
- Menú **Import**  
- Cargar `Industria 4.json`  
- Hacer deploy  
- Ver dashboard en:  
  http://localhost:1880/ui

---

### 3. Power BI
- Crear un **Streaming Dataset**  
- Copiar la URL del endpoint  
- Colocarla en el nodo HTTP de Node-RED (luego de la función 8) 

---

### 4. Telegram Bot
- Crear bot con BotFather  
- Insertar token y chatId en los nodos correspondientes  

---

## 🔗 Video de demostración
*(Insertar URL aquí)*

---

## Autor(es)
- Ronald Garcés
- [Wilmer Olivarez]

---



