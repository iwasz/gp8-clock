EESchema Schematic File Version 4
LIBS:gp8-clock-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L iwasz-kicad:MCP73833 U5
U 1 1 56375CE9
P 4475 3800
F 0 "U5" H 4525 3900 60  0000 C CNN
F 1 "MCP73833" V 4425 3800 60  0000 C CNN
F 2 "ref-packages:MSOP10" H 4525 3850 60  0001 C CNN
F 3 "http://pl.farnell.com/microchip/mcp73833-fci-un/ic-charge-control-li-ion-1a-msop/dp/1605576" H 4525 3850 60  0001 C CNN
	1    4475 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 3600 2425 3600
$Comp
L gp8-clock-rescue:CP-RESCUE-gp8-clock C15
U 1 1 56375D12
P 2425 3875
F 0 "C15" H 2543 3921 50  0000 L CNN
F 1 "10µF" H 2543 3829 50  0000 L CNN
F 2 "w_smd_cap:c_tant_B" H 2463 3725 30  0001 C CNN
F 3 "" H 2425 3875 60  0000 C CNN
	1    2425 3875
	1    0    0    -1  
$EndComp
Wire Wire Line
	2425 3600 2425 3725
$Comp
L power:+5V #PWR027
U 1 1 56375D1B
P 2250 3600
F 0 "#PWR027" H 2250 3450 50  0001 C CNN
F 1 "+5V" H 2250 3740 50  0000 C CNN
F 2 "" H 2250 3600 60  0000 C CNN
F 3 "" H 2250 3600 60  0000 C CNN
	1    2250 3600
	0    -1   -1   0   
$EndComp
Connection ~ 2425 3600
$Comp
L power:GND #PWR028
U 1 1 56375D22
P 2425 4100
F 0 "#PWR028" H 2425 3850 50  0001 C CNN
F 1 "GND" H 2425 3950 50  0000 C CNN
F 2 "" H 2425 4100 60  0000 C CNN
F 3 "" H 2425 4100 60  0000 C CNN
	1    2425 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2425 4025 2425 4100
Wire Wire Line
	3875 3700 3700 3700
Wire Wire Line
	3700 3700 3700 3600
Connection ~ 3700 3600
Wire Wire Line
	3300 3800 3400 3800
Wire Wire Line
	3300 3900 3550 3900
$Comp
L power:GND #PWR029
U 1 1 56375D4C
P 3800 4400
F 0 "#PWR029" H 3800 4150 50  0001 C CNN
F 1 "GND" H 3800 4250 50  0000 C CNN
F 2 "" H 3800 4400 60  0000 C CNN
F 3 "" H 3800 4400 60  0000 C CNN
	1    3800 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3875 4000 3800 4000
Wire Wire Line
	3800 4000 3800 4225
$Comp
L gp8-clock-rescue:R-RESCUE-gp8-clock R28
U 1 1 56375D6C
P 4475 4225
F 0 "R28" V 4555 4225 50  0000 C CNN
F 1 "3k3" V 4475 4225 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 4405 4225 30  0001 C CNN
F 3 "" H 4475 4225 30  0000 C CNN
	1    4475 4225
	0    1    1    0   
$EndComp
Wire Wire Line
	5025 4000 5075 4000
Wire Wire Line
	5075 4000 5075 4225
Wire Wire Line
	5075 4225 4625 4225
Wire Wire Line
	3800 4225 4325 4225
Connection ~ 3800 4225
Text Notes 4325 4425 0    60   ~ 0
300mA
$Comp
L gp8-clock-rescue:CONN_01X03-RESCUE-gp8-clock P1
U 1 1 56375D79
P 5450 3400
F 0 "P1" V 5415 3206 50  0000 R CNN
F 1 "CONN_01X03" V 5323 3206 50  0000 R CNN
F 2 "w_pin_strip:pin_strip_3" H 5450 3400 60  0001 C CNN
F 3 "" H 5450 3400 60  0000 C CNN
	1    5450 3400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5150 3700 5025 3700
Connection ~ 5150 3600
$Comp
L power:GND #PWR030
U 1 1 56375D84
P 5550 3650
F 0 "#PWR030" H 5550 3400 50  0001 C CNN
F 1 "GND" H 5644 3613 50  0000 L CNN
F 2 "" H 5550 3650 60  0000 C CNN
F 3 "" H 5550 3650 60  0000 C CNN
	1    5550 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5025 3800 5275 3800
$Comp
L gp8-clock-rescue:SPST-RESCUE-gp8-clock SW2
U 1 1 563D0B61
P 6200 3125
F 0 "SW2" H 6200 3225 50  0000 C CNN
F 1 "power" H 6200 3300 50  0000 C CNN
F 2 "w_pin_strip:pin_strip_2" H 6200 3125 60  0001 C CNN
F 3 "http://lispol.pl/product,2183,wylacznik_kolyskowy_mini_czarny.html" H 6200 3125 60  0001 C CNN
F 4 "Włącznik zasilania, kołyskowy." H 6200 3125 60  0001 C CNN "Opis"
	1    6200 3125
	1    0    0    -1  
$EndComp
$Comp
L iwasz-kicad:test-double P4
U 1 1 56855A2D
P 3400 4000
F 0 "P4" H 3775 4000 60  0000 C CNN
F 1 "test-double" H 3600 3900 60  0001 C CNN
F 2 "iwasz:testpad-2p" H 3500 3850 60  0001 C CNN
F 3 "" H 3500 3850 60  0000 C CNN
	1    3400 4000
	0    1    1    0   
$EndComp
$Comp
L iwasz-kicad:test-double P5
U 1 1 56855B2B
P 3550 4000
F 0 "P5" H 3925 4000 60  0000 C CNN
F 1 "test-double" H 3750 3900 60  0001 C CNN
F 2 "iwasz:testpad-2p" H 3650 3850 60  0001 C CNN
F 3 "" H 3650 3850 60  0000 C CNN
	1    3550 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 4000 3400 3800
Connection ~ 3400 3800
Wire Wire Line
	3550 4000 3550 3900
Connection ~ 3550 3900
Wire Wire Line
	5150 3125 5150 3600
Wire Wire Line
	5450 3800 5450 3600
Wire Wire Line
	5025 3600 5150 3600
Wire Wire Line
	5550 3650 5550 3600
$Comp
L gp8-clock-rescue:TLV70012DDC-RESCUE-gp8-clock U6
U 1 1 58BD09B0
P 7850 3825
F 0 "U6" H 7850 4233 50  0000 C CNN
F 1 "MIC5504" H 7850 4142 50  0000 C CNN
F 2 "w_smd_trans:sot23-5" H 7850 4051 50  0000 C CIN
F 3 "http://pl.farnell.com/microchip/mic5504-3-3ym5-tr/ldo-volt-reg-0-3a-3-3v-sot-23/dp/2510377" H 7850 3825 50  0001 C CNN
F 4 "0.42" H 7850 3825 60  0001 C CNN "price1"
F 5 "0.32" H 7850 3825 60  0001 C CNN "price2"
	1    7850 3825
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR031
U 1 1 58BD09B4
P 7850 4275
F 0 "#PWR031" H 7850 4025 50  0001 C CNN
F 1 "GND" H 7855 4102 50  0000 C CNN
F 2 "" H 7850 4275 50  0000 C CNN
F 3 "" H 7850 4275 50  0000 C CNN
	1    7850 4275
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 3775 8350 3775
Wire Wire Line
	6700 3775 7300 3775
Wire Wire Line
	7850 4125 7850 4275
Wire Wire Line
	7300 3925 7400 3925
Connection ~ 7300 3775
Connection ~ 7300 3925
Wire Wire Line
	8350 3975 8350 3775
Connection ~ 8350 3775
Wire Wire Line
	7300 4275 7850 4275
$Comp
L gp8-clock-rescue:C-RESCUE-gp8-clock C16
U 1 1 58BD09B7
P 7300 4125
AR Path="/58BD09B7" Ref="C16"  Part="1" 
AR Path="/56372EC6/58BD09B7" Ref="C16"  Part="1" 
F 0 "C16" H 7415 4171 50  0000 L CNN
F 1 "1µF, X5R, X7R, 25V" H 7415 4080 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 7338 3975 50  0001 C CNN
F 3 "http://pl.farnell.com/walsin/0603x105k250ct/cap-mlcc-x5r-1uf-25v-0603-reel/dp/2495417" H 7300 4125 50  0001 C CNN
F 4 "0.08" H 7300 4125 60  0001 C CNN "price1"
F 5 "0.04" H 7300 4125 60  0001 C CNN "price2"
	1    7300 4125
	1    0    0    -1  
$EndComp
$Comp
L gp8-clock-rescue:C-RESCUE-gp8-clock C17
U 1 1 58BD09B8
P 8350 4125
AR Path="/58BD09B8" Ref="C17"  Part="1" 
AR Path="/56372EC6/58BD09B8" Ref="C17"  Part="1" 
F 0 "C17" H 8465 4171 50  0000 L CNN
F 1 "1µF, X5R, X7R, 25V" H 8465 4080 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 8388 3975 50  0001 C CNN
F 3 "http://pl.farnell.com/walsin/0603x105k250ct/cap-mlcc-x5r-1uf-25v-0603-reel/dp/2495417" H 8350 4125 50  0001 C CNN
F 4 "0.05" H 8350 4125 60  0001 C CNN "price1"
F 5 "0.02" H 8350 4125 60  0001 C CNN "price2"
	1    8350 4125
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR032
U 1 1 58BD09B9
P 8475 3775
F 0 "#PWR032" H 8475 3625 50  0001 C CNN
F 1 "+3.3V" V 8490 3903 50  0000 L CNN
F 2 "" H 8475 3775 50  0000 C CNN
F 3 "" H 8475 3775 50  0000 C CNN
	1    8475 3775
	0    1    1    0   
$EndComp
Connection ~ 7850 4275
Text Notes 3800 2450 0    60   ~ 0
1. Kiedy jest ładowanie baterii, a włącznik będzie WYłączony, to nie będzie żadnego feedbaku (migającej diody etc). \n2. Kiedy będzie WŁĄczony, i podłączone ładowanie, to program będzie pokazywał na diodzie stan ładowania.\n3. Kiedy będzie WŁĄczony i nie będzie podłączone ładowanie, to mamy normalne działanie.\nPomysł z diodą schottky między +5V a +BATT miał tę wadę, że gdy włącznik byłby WŁĄczony, to ok. 5V szło by bezpośrednio do baterii.
$Comp
L gp8-clock-rescue:R-RESCUE-gp8-clock R2
U 1 1 58BD3A3D
P 5275 4400
F 0 "R2" V 5355 4400 50  0000 C CNN
F 1 "10k" V 5275 4400 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 5205 4400 30  0001 C CNN
F 3 "" H 5275 4400 30  0000 C CNN
	1    5275 4400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR033
U 1 1 58BD4121
P 5275 4625
F 0 "#PWR033" H 5275 4375 50  0001 C CNN
F 1 "GND" H 5369 4588 50  0000 L CNN
F 2 "" H 5275 4625 60  0000 C CNN
F 3 "" H 5275 4625 60  0000 C CNN
	1    5275 4625
	1    0    0    -1  
$EndComp
Wire Wire Line
	5275 4625 5275 4550
Wire Wire Line
	5275 4250 5275 3800
Connection ~ 5275 3800
Text Notes 5500 4475 1    160  ~ 0
*
NoConn ~ 5025 3900
Wire Wire Line
	6875 3125 6700 3125
Wire Wire Line
	6700 3025 6700 3125
Wire Wire Line
	7300 3775 7300 3925
Text HLabel 3300 3800 0    60   Output ~ 0
progress
Text HLabel 3300 3900 0    60   Output ~ 0
complete
$Comp
L gp8-clock-rescue:R-RESCUE-gp8-clock R4
U 1 1 58C05AB7
P 7025 3125
F 0 "R4" V 7105 3125 50  0000 C CNN
F 1 "5k6" V 7025 3125 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 6955 3125 30  0001 C CNN
F 3 "" H 7025 3125 30  0000 C CNN
	1    7025 3125
	0    1    1    0   
$EndComp
$Comp
L gp8-clock-rescue:R-RESCUE-gp8-clock R5
U 1 1 58C05C11
P 7450 3125
F 0 "R5" V 7530 3125 50  0000 C CNN
F 1 "5k6" V 7450 3125 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 7380 3125 30  0001 C CNN
F 3 "" H 7450 3125 30  0000 C CNN
	1    7450 3125
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR034
U 1 1 58C05C80
P 7725 3125
F 0 "#PWR034" H 7725 2875 50  0001 C CNN
F 1 "GND" H 7819 3088 50  0000 L CNN
F 2 "" H 7725 3125 60  0000 C CNN
F 3 "" H 7725 3125 60  0000 C CNN
	1    7725 3125
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7725 3125 7600 3125
Wire Wire Line
	7300 3125 7250 3125
$Comp
L power:+BATT #PWR035
U 1 1 58C06D4A
P 6700 3025
F 0 "#PWR035" H 6700 2875 50  0001 C CNN
F 1 "+BATT" H 6700 3165 50  0000 C CNN
F 2 "" H 6700 3025 60  0000 C CNN
F 3 "" H 6700 3025 60  0000 C CNN
	1    6700 3025
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3125 5700 3125
Connection ~ 6700 3125
Text HLabel 7250 3000 1    60   Output ~ 0
sense
Wire Wire Line
	7250 3125 7250 3000
Connection ~ 7250 3125
Wire Wire Line
	2425 3600 3700 3600
Wire Wire Line
	3700 3600 3875 3600
Wire Wire Line
	3800 4225 3800 4400
Wire Wire Line
	5150 3600 5150 3700
Wire Wire Line
	5150 3600 5350 3600
Wire Wire Line
	3400 3800 3875 3800
Wire Wire Line
	3550 3900 3875 3900
Wire Wire Line
	7300 3775 7400 3775
Wire Wire Line
	7300 3925 7300 3975
Wire Wire Line
	8350 3775 8475 3775
Wire Wire Line
	7850 4275 8350 4275
Wire Wire Line
	5275 3800 5450 3800
Wire Wire Line
	6700 3125 6700 3775
Wire Wire Line
	7250 3125 7175 3125
$EndSCHEMATC
