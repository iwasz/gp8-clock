#include <stm32f4xx_hal.h>
//#include <stm32f4_discovery.h>
#include <stdio.h>
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_interface.h"
#include "config.h"
// TODO uniezaleznić od discovery
//#include "lis302dl_accelerometer.h"
#include "sim908_gsm.h"
#include "debugLed.h"
#include "gps/cgpsinfParse.h"
#include "obd/logic.h"
#include "obd/usartCommunication.h"
#include "multiplexer.h"

static void SystemClock_Config (void);

USBD_HandleTypeDef USBD_Device;

extern void setup ();
extern void loop ();

extern float speed, rpm;
extern GpsData gpsData;
extern ObdData obdData;
NetworkFrame networkFrame;

#define TCP_PACKET_SIZE 16
//static uint8_t packet[TCP_PACKET_SIZE + 1];

#define GSM_ENABLED
#define OBD_ENABLED

int main (void)
{
        HAL_Init ();
        SystemClock_Config ();

        debugLedInit (D2);
        debugLedInit (D3);
        debugLedInit (D4);
        debugLedInit (D5);

        /* Init Device Library */
        USBD_Init (&USBD_Device, &VCP_Desc, 0);

        /* Add Supported Class */
        USBD_RegisterClass (&USBD_Device, USBD_CDC_CLASS);

        /* Add CDC Interface Class */
        USBD_CDC_RegisterInterface (&USBD_Device, &USBD_CDC_fops);

        /* Start Device Process */
        USBD_Start (&USBD_Device);

//        if (BSP_ACCELERO_Init () != HAL_OK) {
//                /* Initialization Error */
//                Error_Handler ();
//        }

        //        TO JEST KOMUNIKACJA Z OBD
#ifdef OBD_ENABLED
        printf ("obdInitUart\n");
        obdInitUart ();
        printf ("init OK\n");

//        obdSend ((uint8_t *)"atz\r", 4);
//        TODO trzeba zweryfikować odpowiedź
//        obdReceive();
//        HAL_Delay (3000);
//        obdSend ((uint8_t *)"atz\r", 4);
//        HAL_Delay (3000);
//        obdSend ((uint8_t *)"atrv\r", 5);
//        HAL_Delay (1000);

        // Forget events
//        obdSend ((uint8_t *)"atfe\r", 5);
//        HAL_Delay (500);


//        obdSend ((uint8_t *)"AT RV\r", 6);

        HAL_Delay (1000);
        obdSend ((uint8_t *)"ATL0\r", 5);

        HAL_Delay (1000);
         obdSend ((uint8_t *)"atsp0\r", 6);

 //         HAL_Delay (1000);

        // ISO 9141-2 (5 baud init, 10.4 kbaud)
//        obdSend ((uint8_t *)"atsp4\r", 6);
//        HAL_Delay (1000);

//        obdSend ((uint8_t *)"ATKW0\r", 6);

        // FAAAAK bez tego czekania (docelowo parsowania odpowiedzi to nie zadziałą i jest SEARCING... STOPED) !?!?!?!? Czy chodzi może o line feeds - jedno z dwóch!
         // NIE działa z line feeds! DUH!

        // Napięcie
#endif

#ifndef GSM_ENABLED
         HAL_Delay (10000);
          // Zamiast niego GSM się inicjuje i to trwa.
#endif

//        TO JEST INIT MODEMU - GPS I GSM -> wszystko
#ifdef GSM_ENABLED
        sim908Init ();

        HAL_Delay (5000);
        gpsSend ((uint8_t *)"AT\r\n", 4);
        HAL_Delay (500);
        gpsSend ((uint8_t *)"AT\r\n", 4);

        debugLedOn (D2);

        HAL_Delay (500);
        gpsSend ((uint8_t *)"AT\r\n", 4);

        HAL_Delay (500);
        gpsSend ((uint8_t *)"AT+IPR?\r\n", 9);

//        HAL_Delay (500);
//        gpsSend ((uint8_t *)"AT+IPR=115200\r\n", 15);
//        HAL_Delay (500);
//        gpsSend ((uint8_t *)"AT+IPR=0\r\n", 10);

//        TO JEST POŁĄCZENIE Z NETEM
        HAL_Delay (500);
        gpsSend ((uint8_t *)"ATI\r\n", 5);
        HAL_Delay (1000);

        // Enter PIN. Karty prepaid nie mają pinu.
        gpsSend ((uint8_t *)"AT+CPIN=8690\r\n", 14);
        HAL_Delay (2000);

        // Query poin status. Czy np. trzeba podać PUK?
        gpsSend ((uint8_t *)"AT+CPIN?\r\n", 10);
        HAL_Delay (1000);

        // Jakość sygnału
        gpsSend ((uint8_t *)"AT+CSQ\r\n", 8);
        HAL_Delay (1000);

//        // Włącz transparent Mode
//        gpsSend ((uint8_t *)"AT+CIPMODE=1\r\n", 14);
//        HAL_Delay (500);

        // Czy zalogował do sieci, czy nie? +CREG: 0,1
        gpsSend ((uint8_t *)"AT+CREG?\r\n", 10);
        HAL_Delay (2000);
        gpsSend ((uint8_t *)"AT+CREG?\r\n", 10);
        HAL_Delay (2000);
        gpsSend ((uint8_t *)"AT+CREG?\r\n", 10);
        HAL_Delay (2000);
        gpsSend ((uint8_t *)"AT+CREG?\r\n", 10);
        HAL_Delay (2000);

        // Podłącz / uruchom GPRS.
        gpsSend ((uint8_t *)"AT+CGATT=1\r\n", 12);
        HAL_Delay (1000);

        // Czy urucomiono GPRS
        gpsSend ((uint8_t *)"AT+CGATT?\r\n", 11);
        HAL_Delay (1000);

        // Start Task and Set APN, USER NAME, PASSWORD
        gpsSend ((uint8_t *)"AT+CSTT=\"internet\",\"\",\"\"\r\n", 26);
        HAL_Delay (3000);

        // Bring Up Wireless Connection with GPRS or CSD
        gpsSend ((uint8_t *)"AT+CIICR\r\n", 10);
        HAL_Delay (2000);

        // Get local IP address
        gpsSend ((uint8_t *)"AT+CIFSR\r\n", 10);
        HAL_Delay (2000);

        // To są IP DNS ze strony http://biznes.t-mobile.pl/centrum-informacji/dla-klientow/faq
/*
 * TODO Po ustawieniu DNS poniższą komendą przestaje działać połączenie za pomocą CIPSTART.
 * W statusie pokazuje OK, a potem już nic (a powinno być chyba OK\r\nCONNECT OK\r\n
 *
 * UWAGA - z dnsem gugla działa.
 */
//        gpsSend ((uint8_t *)"AT+CDNSCFG=\"217.8.168.244\",\"157.25.5.18\"\r\n", 42);
        gpsSend ((uint8_t *)"AT+CDNSCFG=\"8.8.8.8\",\"8.8.4.4\"\r\n", 32);
        HAL_Delay (5000);

//        gpsSend ((uint8_t *)"AT+CIPSTART=\"TCP\",\"iwasz.ddns.net\",\"5005\"\r\n", 43);
          gpsSend ((uint8_t *)"AT+CIPSTART=\"TCP\",\"mapserver.com.pl\",\"5005\"\r\n", 45);
//        gpsSend ((uint8_t *)"AT+CIPSTART=\"TCP\",\"google.com\",\"80\"\r\n", 37);
//        gpsSend ((uint8_t *)"AT+CIPSTART=\"TCP\",\"213.158.221.251\",\"5005\"\r\n", 44);
          HAL_Delay (2000);

//        TO JEST RESET i start GPSU
          HAL_Delay (500);
        gpsSend ((uint8_t *)"ATI\r\n", 5);

        HAL_Delay (1000);
        gpsSend ((uint8_t *)"AT+CGPSPWR=1\r\n", 14);

        HAL_Delay (1000);
        gpsSend ((uint8_t *)"AT+CGPSRST?\r\n", 13);

        HAL_Delay (1000);
        gpsSend ((uint8_t *)"AT+CGPSRST=0\r\n", 14);

        HAL_Delay (2000);
#endif



                while (1) {

#ifdef GSM_ENABLED
		// Pobierz lokalizację.
                gpsSend ((uint8_t *)"AT+CGPSINF=0\r\n", 14);
//                gpsSend ((uint8_t *)"AT\r\n", 4);
                HAL_Delay (2000);

#if 1
                // todo SPRAWDZAĆ STATUS FKSUUU
//                if (gpsData.lat > 0 || gpsData.lat < 0 || gpsData.lng > 0 || gpsData.lng < 0) {

//                        gpsSend ((uint8_t *)"AT+CIPSEND=0,16\r\n", 17);
                        gpsSend ((uint8_t *)"AT+CIPSEND=16\r\n", 15);
//                        gpsSend ((uint8_t *)"AT+CIPSEND\r\n", 12);
                        HAL_Delay (5000);

//                        memcpy (packet, (uint8_t *)&gpsData.lat, 4);
//                        memcpy (packet + 4, (uint8_t *)&gpsData.lng, 4);
//                        memcpy (packet + 8, (uint8_t *)&speed, 4);
//                        memcpy (packet + 12, (uint8_t *)&rpm, 4);
////                        memset(packet, 'a', TCP_PACKET_SIZE);
////                        packet[TCP_PACKET_SIZE] = 0x1A;
//                        gpsSend (packet, TCP_PACKET_SIZE);

                        multiplexNetworkFrame (&networkFrame, &obdData, &gpsData);
                        gpsSend ((uint8_t *)&networkFrame, sizeof (networkFrame));
                        HAL_Delay (5000);
                        // MUSI ODPOWIEDZIEĆ SEND OK !!!! inaczej nie wysłało się.
//                }
#endif

#if 0
                        gpsSend ((uint8_t *)"AT+CIPSEND\r\n", 12);
                        HAL_Delay (5000);

                        gpsSend ("A\x1a", 2);
                        HAL_Delay (5000);
#endif
#endif

//                int16_t a[3];
//                BSP_ACCELERO_GetXYZ (a);
//                printf ("Accel says : x=%d, y=%d, z=%d\r\n", a[0], a[1], a[2]);



#ifdef OBD_ENABLED
                printf ("Sending via OBD...\n");
                obdSend ((uint8_t *)"0104\r", 5);
                HAL_Delay(500);
                obdSend ((uint8_t *)"0105\r", 5);
                HAL_Delay(500);
                obdSend ((uint8_t *)"010b\r", 5);
                HAL_Delay(500);
                obdSend ((uint8_t *)"010c\r", 5);
                HAL_Delay(500);
                obdSend ((uint8_t *)"010d\r", 5);
                HAL_Delay(500);
                obdSend ((uint8_t *)"010f\r", 5);
                HAL_Delay(500);
                obdSend ((uint8_t *)"0110\r", 5);
                HAL_Delay(500);
#endif
#ifndef GSM_ENABLED
                HAL_Delay(5000);
#endif
////                obdSend ((uint8_t *)"ATI\r", 4);
////                obdReceive ();
//// TODO Uwaga - za pierwszym razem on robi "searching" i to trwa. Trzeba weryfikować odpowiedź lub czekać długo. Potem odpowiedź uż jest szybko
//                HAL_Delay (5000);
//
//                // GPS. Uzyskaj dostęp do bufora, gdzie jest ostatni surowy odczyt z GPS (albo dane zebrane
//                // od czasu ostatniego odczytu). Czyli musi być już przygotowany taki bufor wcześniej.
//                // Filtruj, parsuj, obrabiaj.
//                // Wrzuć do paczki
//
//                // OBD - analogocznie do GPS.
//
//                // Uzyskaj dostęp do jakiegoś bufora z danymi z akcelerometru.
//                // Filtruj, parsuj, obrabiaj.
//                // Wrzuć do paczki
//
//
//                // Ogólnie to tu muszę mieć pracę z buforami : muszę mieć możliwość :
//                // Bokowania - mutex, żeby dane były integralne
//                // Odczytywania buforu (że są dane).
//                // Zapisywania buforu.


/*
 * Pomysły:
 * - Głowna pętla round robin, wykonuje NIEBLOKUJAce operacje na maszynie stanów / maszynach stanów. 
 * - Działanie tej maszyny jest przerywane przerwaniami z urzadzeń IO.
 * 
 * Przykładowo mamy tylko MODEM i chcemy połączyć się z IP i wyszłac kilka bajtów. Komunikacja działa tak:
 * + Wysyłamy komunikat nieblokująco za pomocą DMA.
 *   + Asynchronicznie dostajemy odpowiedź (przerwanie). Tam wykrywamy czy odpowiedź jest OK, czy nie OK.
 *   + Nie dostajemy odpowiedzi po upływie jakiegoś czasu.
 * + Musimy zaczekać jakiś czas, bo tak jest napisane w dokumentacji.
 * 
 * + Wykonujemy akcję na peripheralu (powiedzmy że tym razem blokującą).
 *   + Skąd odpowiedź?
 * 
 */


        }
}

static void SystemClock_Config (void)
{
        /*
         * Power interface clock enable. This is quivalent to RCC_AHB1PeriphClockCmd (xxx)
         * which seems to be now obsolete.
         */
        __HAL_RCC_PWR_CLK_ENABLE ();

        /*
         * The voltage scaling allows optimizing the power consumption when the device is
         * clocked below the maximum system frequency.
         *
         * To dotyczy zasilania rdzenia (1.2V). Default is 1 (full voltage), min volatge
         * to będzie opcja 3.
         *
         * Można to ustawienie zmienić *tylko* gdy PLL off, a źródłem jest bezpośrednio HSE
         * lub HSI. Nowe ustawienie zaczyna działać kiedy włączy się PLL (poraz pierwszy lub
         * spowrotem).
         */
        __HAL_PWR_VOLTAGESCALING_CONFIG (PWR_REGULATOR_VOLTAGE_SCALE1);

        RCC_OscInitTypeDef rccOscInitStruct;
        rccOscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE; // HSE, HSI, LSE, LSI, NONE
        rccOscInitStruct.HSEState = RCC_HSE_ON;                   // ON, OFF, BYPASS
        rccOscInitStruct.HSIState = RCC_HSI_OFF;
        rccOscInitStruct.LSEState = RCC_LSE_OFF;
        rccOscInitStruct.LSIState = RCC_LSI_OFF;
        rccOscInitStruct.PLL.PLLState = RCC_PLL_ON;               // On / Off
        rccOscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;       // HSE or HSI
        rccOscInitStruct.PLL.PLLM = 16;                           // Between 0 and 63
        rccOscInitStruct.PLL.PLLN = 336;                          // Betwen 192 and 432
        rccOscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;                // RCC_PLLP_DIV2, RCC_PLLP_DIV4, RCC_PLLP_DIV6, RCC_PLLP_DIV8
        rccOscInitStruct.PLL.PLLQ = 7;                            // Between 4 and 15.

        if (HAL_RCC_OscConfig (&rccOscInitStruct) != HAL_OK) {
                Error_Handler ();
        }

        // Only for STM32F42x ad 3x
        // if (HAL_PWREx_EnableOverDrive () != HAL_OK) {
        //         Error_Handler ();
        // }

        RCC_ClkInitTypeDef rccClkInitStruct;

        // ClockType mówi które zegary konfigurujemy. W tym przypadku konfigurujemy wszytskie.
        rccClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
        rccClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; // HSI, HSE lub PLL
        rccClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
        rccClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
        rccClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

        if (HAL_RCC_ClockConfig (&rccClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
                Error_Handler ();
        }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void Error_Handler (void)
{
        /* User may add here some code to deal with this error */
        while (1) {
        }
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
        /* User can add his own implementation to report the file name and line number,
         ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

        /* Infinite loop */
        while (1)
        {
        }
}
#endif

