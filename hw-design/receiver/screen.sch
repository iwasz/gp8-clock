EESchema Schematic File Version 4
LIBS:gp8-clock-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
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
L iwasz-kicad:weight-scale-lcd U2
U 1 1 58BEC91B
P 4400 1950
F 0 "U2" H 4400 2050 60  0000 C CNN
F 1 "weight-scale-lcd" H 4400 1950 60  0000 C CNN
F 2 "iwasz:weight-scale-lcd" H 4400 1950 60  0001 C CNN
F 3 "https://www.aliexpress.com/item/Free-shipping-5-digits-7-segment-LCD-display-custom-made-LCM-automatic-weighing-scale-size-57/32440251274.html?spm=2114.13010608.0.0.Yvp5IW" H 4400 1950 60  0001 C CNN
	1    4400 1950
	1    0    0    -1  
$EndComp
Text Notes 4250 1500 0    60   ~ 0
LCD screen
$Comp
L iwasz-kicad:PCF85176T U7
U 1 1 58BEC923
P 6200 4175
F 0 "U7" H 6200 5712 60  0000 C CNN
F 1 "PCF85176T" H 6200 5606 60  0000 C CNN
F 2 "micro-philips:TSSOP56-6" H 975 2025 60  0001 C CNN
F 3 "http://www.farnell.com/datasheets/1923814.pdf?_ga=1.120212686.734114644.1428524414" H 975 2025 60  0001 C CNN
	1    6200 4175
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 2925 6900 2350
Wire Wire Line
	6900 2350 3650 2350
Wire Wire Line
	3650 2350 3650 2300
Wire Wire Line
	3750 2300 3750 3025
Wire Wire Line
	3750 3025 5500 3025
Wire Wire Line
	3850 2300 3850 2925
Wire Wire Line
	3850 2925 5500 2925
Wire Wire Line
	3950 2300 3950 3125
Wire Wire Line
	3950 3125 5500 3125
Wire Wire Line
	4050 2300 4050 3225
Wire Wire Line
	4050 3225 5500 3225
Wire Wire Line
	4150 2300 4150 3325
Wire Wire Line
	4150 3325 5500 3325
Wire Wire Line
	4250 2300 4250 3425
Wire Wire Line
	4250 3425 5500 3425
Wire Wire Line
	4350 2300 4350 3525
Wire Wire Line
	4350 3525 5500 3525
Wire Wire Line
	4450 2300 4450 3625
Wire Wire Line
	4450 3625 5500 3625
Wire Wire Line
	4550 2300 4550 3725
Wire Wire Line
	4550 3725 5500 3725
Wire Wire Line
	4650 2300 4650 3825
Wire Wire Line
	4650 3825 5500 3825
Wire Wire Line
	4750 2300 4750 3925
Wire Wire Line
	4750 3925 5500 3925
Wire Wire Line
	4850 2300 4850 4025
Wire Wire Line
	4850 4025 5500 4025
Wire Wire Line
	4950 2300 4950 4125
Wire Wire Line
	4950 4125 5500 4125
Wire Wire Line
	5050 2300 5050 4225
Wire Wire Line
	5050 4225 5500 4225
Wire Wire Line
	5150 2300 5150 4325
Wire Wire Line
	5150 4325 5500 4325
NoConn ~ 5500 4425
NoConn ~ 5500 4525
NoConn ~ 5500 4625
NoConn ~ 5500 4725
NoConn ~ 5500 4825
NoConn ~ 5500 4925
NoConn ~ 5500 5025
NoConn ~ 5500 5125
NoConn ~ 5500 5225
NoConn ~ 5500 5325
NoConn ~ 5500 5425
NoConn ~ 5500 5525
NoConn ~ 5500 5625
NoConn ~ 6900 5625
NoConn ~ 6900 5525
NoConn ~ 6900 5425
NoConn ~ 6900 5325
NoConn ~ 6900 5225
NoConn ~ 6900 5125
NoConn ~ 6900 5025
NoConn ~ 6900 4925
NoConn ~ 6900 4825
NoConn ~ 6900 4725
NoConn ~ 6900 4625
NoConn ~ 6900 4525
NoConn ~ 6900 4425
NoConn ~ 6900 4325
NoConn ~ 6900 4225
$Comp
L power:GND #PWR036
U 1 1 58BEC967
P 7075 3125
F 0 "#PWR036" H 7075 2875 50  0001 C CNN
F 1 "GND" H 7075 2975 50  0000 C CNN
F 2 "" H 7075 3125 60  0000 C CNN
F 3 "" H 7075 3125 60  0000 C CNN
	1    7075 3125
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6900 3125 7000 3125
Wire Wire Line
	6900 3225 7000 3225
Wire Wire Line
	7000 3125 7000 3225
Connection ~ 7000 3125
Wire Wire Line
	7000 3325 6900 3325
Connection ~ 7000 3225
Wire Wire Line
	7000 3425 6900 3425
Connection ~ 7000 3325
Wire Wire Line
	7000 3525 6900 3525
Connection ~ 7000 3425
Wire Wire Line
	7000 3625 6900 3625
Connection ~ 7000 3525
NoConn ~ 6900 3925
NoConn ~ 6900 3825
$Comp
L power:+3.3V #PWR037
U 1 1 58BEC980
P 6975 3025
F 0 "#PWR037" H 6975 2875 50  0001 C CNN
F 1 "+3.3V" H 6975 3165 50  0000 C CNN
F 2 "" H 6975 3025 60  0000 C CNN
F 3 "" H 6975 3025 60  0000 C CNN
	1    6975 3025
	0    1    1    0   
$EndComp
Wire Wire Line
	6900 3025 6975 3025
$Comp
L power:+3.3V #PWR038
U 1 1 58BEC987
P 6975 3725
F 0 "#PWR038" H 6975 3575 50  0001 C CNN
F 1 "+3.3V" H 6975 3865 50  0000 C CNN
F 2 "" H 6975 3725 60  0000 C CNN
F 3 "" H 6975 3725 60  0000 C CNN
	1    6975 3725
	0    1    1    0   
$EndComp
Wire Wire Line
	6900 3725 6975 3725
Text HLabel 6900 4025 2    60   Input ~ 0
scl
Text HLabel 6900 4125 2    60   BiDi ~ 0
sda
Wire Wire Line
	7000 3125 7075 3125
Wire Wire Line
	7000 3225 7000 3325
Wire Wire Line
	7000 3325 7000 3425
Wire Wire Line
	7000 3425 7000 3525
Wire Wire Line
	7000 3525 7000 3625
$EndSCHEMATC
