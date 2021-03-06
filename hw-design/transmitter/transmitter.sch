EESchema Schematic File Version 5
LIBS:transmitter-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L iwasz-kicad:MCP73833 U2
U 1 1 564286AB
P 3850 1325
F 0 "U2" H 3825 1812 60  0000 C CNN
F 1 "MCP73833" H 3825 1706 60  0000 C CNN
F 2 "Package_SSOP:MSOP-10_3x3mm_P0.5mm" H 3900 1375 60  0001 C CNN
F 3 "http://pl.farnell.com/microchip/mcp73833-fci-un/ic-charge-control-li-ion-1a-msop/dp/1605576" H 3900 1375 60  0001 C CNN
	1    3850 1325
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:CP-RESCUE-transmitter C1
U 1 1 564286B0
P 1800 1400
F 0 "C1" H 1825 1500 50  0000 L CNN
F 1 "10µF" H 1825 1300 50  0000 L CNN
F 2 "iwasz:c_tant_B-pins21" H 1838 1250 30  0001 C CNN
F 3 "" H 1800 1400 60  0000 C CNN
	1    1800 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 564286B2
P 1800 1625
F 0 "#PWR01" H 1800 1375 50  0001 C CNN
F 1 "GND" H 1800 1475 50  0000 C CNN
F 2 "" H 1800 1625 60  0000 C CNN
F 3 "" H 1800 1625 60  0000 C CNN
	1    1800 1625
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:R-RESCUE-transmitter R3
U 1 1 564286B3
P 2675 2150
F 0 "R3" V 2755 2150 50  0000 C CNN
F 1 "560R" V 2675 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2605 2150 30  0001 C CNN
F 3 "" H 2675 2150 30  0000 C CNN
	1    2675 2150
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:R-RESCUE-transmitter R2
U 1 1 564286B4
P 2475 2150
F 0 "R2" V 2555 2150 50  0000 C CNN
F 1 "560R" V 2475 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2405 2150 30  0001 C CNN
F 3 "" H 2475 2150 30  0000 C CNN
	1    2475 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 564286B6
P 3175 2375
F 0 "#PWR02" H 3175 2125 50  0001 C CNN
F 1 "GND" H 3175 2225 50  0000 C CNN
F 2 "" H 3175 2375 60  0000 C CNN
F 3 "" H 3175 2375 60  0000 C CNN
	1    3175 2375
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:R-RESCUE-transmitter R4
U 1 1 564286B9
P 3850 1750
F 0 "R4" V 3930 1750 50  0000 C CNN
F 1 "3k3" V 3850 1750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3780 1750 30  0001 C CNN
F 3 "" H 3850 1750 30  0000 C CNN
	1    3850 1750
	0    1    1    0   
$EndComp
Text Notes 3700 1950 0    60   ~ 0
300mA, 2kR = 500mA, 1k2 = 800mA
$Comp
L power:GND #PWR03
U 1 1 564286BB
P 5450 1125
F 0 "#PWR03" H 5450 875 50  0001 C CNN
F 1 "GND" H 5450 975 50  0000 C CNN
F 2 "" H 5450 1125 60  0000 C CNN
F 3 "" H 5450 1125 60  0000 C CNN
	1    5450 1125
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_SPDT SW1
U 1 1 564286BC
P 5225 725
F 0 "SW1" H 5225 825 50  0000 C CNN
F 1 "power" H 5225 900 50  0000 C CNN
F 2 "iwasz:MFP 201 NR" H 5225 725 60  0001 C CNN
F 3 "http://lispol.pl/product,2183,wylacznik_kolyskowy_mini_czarny.html" H 5225 725 60  0001 C CNN
F 4 "Kołyskowy włącznik zasilania." H 5225 725 60  0001 C CNN "Opis"
	1    5225 725 
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:Q_NPN_CBE-RESCUE-transmitter Q1
U 1 1 564296EA
P 9550 3950
F 0 "Q1" H 9743 3996 50  0000 L CNN
F 1 "2N3904" H 9743 3904 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 9750 4050 29  0001 C CNN
F 3 "http://pl.farnell.com/fairchild-semiconductor/2n3904bu/transistor-npn-40v-200ma-to-92/dp/1700648" H 9550 3950 60  0001 C CNN
F 4 "0.75" H 9550 3950 50  0001 C CNN "price1"
F 5 "http://pl.farnell.com/on-semiconductor/2n3904tar/transistor-npn-40v-0-2a-to-92/dp/2822517?MER=sy-me-pd-mi-alte" H 9550 3950 50  0001 C CNN "Datasheet2"
F 6 "0.36" H 9550 3950 50  0001 C CNN "price2"
	1    9550 3950
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:Q_NPN_CBE-RESCUE-transmitter Q2
U 1 1 564299AB
P 9750 4425
F 0 "Q2" H 9944 4471 50  0000 L CNN
F 1 "2N3904" H 9944 4379 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92" H 9950 4525 29  0001 C CNN
F 3 "http://pl.farnell.com/fairchild-semiconductor/2n3904bu/transistor-npn-40v-200ma-to-92/dp/1700648" H 9750 4425 60  0001 C CNN
F 4 "0.75" H 9750 4425 50  0001 C CNN "price"
F 5 "http://pl.farnell.com/on-semiconductor/2n3904tar/transistor-npn-40v-0-2a-to-92/dp/2822517?MER=sy-me-pd-mi-alte" H 9750 4425 50  0001 C CNN "Datasheet2"
F 6 "0.36" H 9750 4425 50  0001 C CNN "price2"
	1    9750 4425
	-1   0    0    -1  
$EndComp
$Comp
L Device:LED D4
U 1 1 5642AB44
P 8950 3475
F 0 "D4" H 8950 3575 50  0000 C CNN
F 1 "VISHAY TSAL6200" H 9600 3475 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm_Horizontal_O3.81mm_Z3.0mm" H 8950 3475 60  0001 C CNN
F 3 "http://pl.farnell.com/vishay/tsal6200/ir-emitter-940nm-5mm-through-hole/dp/3152856?CMP=i-ddd7-00001003" H 8950 3475 60  0001 C CNN
F 4 "0.36" H 8950 3475 50  0001 C CNN "price"
	1    8950 3475
	0    -1   -1   0   
$EndComp
$Comp
L transmitter-rescue:R-RESCUE-transmitter R7
U 1 1 5642B573
P 10375 3750
F 0 "R7" V 10455 3750 50  0000 C CNN
F 1 "1k" V 10375 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10305 3750 30  0001 C CNN
F 3 "" H 10375 3750 30  0000 C CNN
	1    10375 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:D D5
U 1 1 5642B61C
P 10375 4675
F 0 "D5" H 10375 4775 50  0000 C CNN
F 1 "1N4148" H 10375 4575 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 10375 4675 60  0001 C CNN
F 3 "http://pl.farnell.com/multicomp/1n4148ws/diode-small-sig-100v-0-15a-sod/dp/2675148?st=1n4148" H 10375 4675 60  0001 C CNN
F 4 "0.27" H 10375 4675 50  0001 C CNN "price"
	1    10375 4675
	0    -1   -1   0   
$EndComp
$Comp
L Device:D D6
U 1 1 5642B929
P 10375 5025
F 0 "D6" H 10375 5125 50  0000 C CNN
F 1 "1N4148" H 10375 4925 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 10375 5025 60  0001 C CNN
F 3 "http://pl.farnell.com/multicomp/1n4148ws/diode-small-sig-100v-0-15a-sod/dp/2675148?st=1n4148" H 10375 5025 60  0001 C CNN
F 4 "0.27" H 10375 5025 50  0001 C CNN "price"
	1    10375 5025
	0    -1   -1   0   
$EndComp
$Comp
L power:+BATT #PWR04
U 1 1 5642C222
P 5475 625
F 0 "#PWR04" H 5475 475 50  0001 C CNN
F 1 "+BATT" H 5475 765 50  0000 C CNN
F 2 "" H 5475 625 60  0000 C CNN
F 3 "" H 5475 625 60  0000 C CNN
	1    5475 625 
	0    1    1    0   
$EndComp
$Comp
L transmitter-rescue:R-RESCUE-transmitter R6
U 1 1 5642DDC4
P 9125 3950
F 0 "R6" V 9205 3950 50  0000 C CNN
F 1 "1k" V 9125 3950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9055 3950 30  0001 C CNN
F 3 "" H 9125 3950 30  0000 C CNN
	1    9125 3950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5642E340
P 10375 5725
F 0 "#PWR05" H 10375 5475 50  0001 C CNN
F 1 "GND" H 10375 5575 50  0000 C CNN
F 2 "" H 10375 5725 60  0000 C CNN
F 3 "" H 10375 5725 60  0000 C CNN
	1    10375 5725
	1    0    0    -1  
$EndComp
$Comp
L iwasz-kicad:usb-micro U1
U 1 1 5642F35D
P 1025 975
F 0 "U1" H 1075 875 60  0000 C CNN
F 1 "usb-micro" H 1075 975 60  0000 C CNN
F 2 "iwasz:conn_usb_B_micro_smd-2-nohole" H 1075 975 60  0001 C CNN
F 3 "pl.farnell.com/fci/10104111-0001lf/micro-usb-2-0-type-ab-receptacle/dp/2293755" H 1075 975 60  0001 C CNN
	1    1025 975 
	-1   0    0    1   
$EndComp
NoConn ~ 1625 1025
NoConn ~ 1625 925 
NoConn ~ 1625 825 
$Comp
L power:GND #PWR06
U 1 1 56430901
P 1775 725
F 0 "#PWR06" H 1775 475 50  0001 C CNN
F 1 "GND" H 1775 575 50  0000 C CNN
F 2 "" H 1775 725 60  0000 C CNN
F 3 "" H 1775 725 60  0000 C CNN
	1    1775 725 
	0    -1   -1   0   
$EndComp
$Comp
L iwasz-kicad:CD4047 U3
U 1 1 5643208F
P 3425 3800
F 0 "U3" H 3425 4050 60  0000 C CNN
F 1 "CD4047" V 3425 3600 60  0000 C CNN
F 2 "Package_SOIC:SOIC-14_3.9x8.7mm_P1.27mm" H 3425 3800 60  0001 C CNN
F 3 "http://pl.farnell.com/texas-instruments/cd4047bm96/ic-mono-astbl-multvibrtr-125ns/dp/2342523" H 3425 3800 60  0001 C CNN
	1    3425 3800
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:POT-RESCUE-transmitter RV1
U 1 1 564338A3
P 2300 3575
F 0 "RV1" H 2300 3446 50  0000 C CNN
F 1 "20k" H 2300 3354 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 2300 3575 60  0001 C CNN
F 3 "http://pl.farnell.com/bourns/3006p-1-203lf/trimmer-15-turn-20k/dp/9352341" H 2300 3575 60  0001 C CNN
	1    2300 3575
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:C-RESCUE-transmitter C2
U 1 1 56428D62
P 2300 3175
F 0 "C2" H 2325 3275 50  0000 L CNN
F 1 "47nF" H 2325 3075 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2338 3025 30  0001 C CNN
F 3 "" H 2300 3175 60  0000 C CNN
	1    2300 3175
	0    1    1    0   
$EndComp
$Comp
L power:+BATT #PWR07
U 1 1 5642B6EA
P 1850 3950
F 0 "#PWR07" H 1850 3800 50  0001 C CNN
F 1 "+BATT" H 1850 4090 50  0000 C CNN
F 2 "" H 1850 3950 60  0000 C CNN
F 3 "" H 1850 3950 60  0000 C CNN
	1    1850 3950
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5642BCB4
P 2625 4250
F 0 "#PWR08" H 2625 4000 50  0001 C CNN
F 1 "GND" H 2625 4100 50  0000 C CNN
F 2 "" H 2625 4250 60  0000 C CNN
F 3 "" H 2625 4250 60  0000 C CNN
	1    2625 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR09
U 1 1 5642DA91
P 4300 3550
F 0 "#PWR09" H 4300 3400 50  0001 C CNN
F 1 "+BATT" H 4300 3690 50  0000 C CNN
F 2 "" H 4300 3550 60  0000 C CNN
F 3 "" H 4300 3550 60  0000 C CNN
	1    4300 3550
	0    1    1    0   
$EndComp
NoConn ~ 4225 3850
NoConn ~ 4225 3650
$Comp
L power:GND #PWR010
U 1 1 5642EAB6
P 4300 4250
F 0 "#PWR010" H 4300 4000 50  0001 C CNN
F 1 "GND" H 4300 4100 50  0000 C CNN
F 2 "" H 4300 4250 60  0000 C CNN
F 3 "" H 4300 4250 60  0000 C CNN
	1    4300 4250
	1    0    0    -1  
$EndComp
$Comp
L iwasz-kicad:CD4047 U4
U 1 1 5642FF31
P 6750 3800
F 0 "U4" H 6750 4050 60  0000 C CNN
F 1 "CD4047" V 6750 3600 60  0000 C CNN
F 2 "Package_SOIC:SOIC-14_3.9x8.7mm_P1.27mm" H 6750 3800 60  0001 C CNN
F 3 "http://pl.farnell.com/texas-instruments/cd4047bm96/ic-mono-astbl-multvibrtr-125ns/dp/2342523" H 6750 3800 60  0001 C CNN
	1    6750 3800
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:POT-RESCUE-transmitter RV2
U 1 1 5642FF37
P 5625 3575
F 0 "RV2" H 5625 3446 50  0000 C CNN
F 1 "47k" H 5625 3354 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 5625 3575 60  0001 C CNN
F 3 "http://pl.farnell.com/vishay-sfernice/t18503kt10/trimmer-18-turn-50k/dp/1141464" H 5625 3255 60  0001 C CNN
	1    5625 3575
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:C-RESCUE-transmitter C4
U 1 1 5642FF3D
P 5625 3175
F 0 "C4" H 5650 3275 50  0000 L CNN
F 1 "100pF" H 5650 3075 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5663 3025 30  0001 C CNN
F 3 "" H 5625 3175 60  0000 C CNN
	1    5625 3175
	0    1    1    0   
$EndComp
$Comp
L power:+BATT #PWR011
U 1 1 5642FF50
P 5625 4250
F 0 "#PWR011" H 5625 4100 50  0001 C CNN
F 1 "+BATT" H 5625 4390 50  0000 C CNN
F 2 "" H 5625 4250 60  0000 C CNN
F 3 "" H 5625 4250 60  0000 C CNN
	1    5625 4250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5642FF56
P 5950 4250
F 0 "#PWR012" H 5950 4000 50  0001 C CNN
F 1 "GND" H 5950 4100 50  0000 C CNN
F 2 "" H 5950 4250 60  0000 C CNN
F 3 "" H 5950 4250 60  0000 C CNN
	1    5950 4250
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR013
U 1 1 5642FF62
P 7625 3550
F 0 "#PWR013" H 7625 3400 50  0001 C CNN
F 1 "+BATT" H 7625 3690 50  0000 C CNN
F 2 "" H 7625 3550 60  0000 C CNN
F 3 "" H 7625 3550 60  0000 C CNN
	1    7625 3550
	0    1    1    0   
$EndComp
NoConn ~ 7550 3850
NoConn ~ 7550 3650
$Comp
L power:GND #PWR014
U 1 1 5642FF70
P 7625 4250
F 0 "#PWR014" H 7625 4000 50  0001 C CNN
F 1 "GND" H 7625 4100 50  0000 C CNN
F 2 "" H 7625 4250 60  0000 C CNN
F 3 "" H 7625 4250 60  0000 C CNN
	1    7625 4250
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:C-RESCUE-transmitter C3
U 1 1 56430513
P 4825 3950
F 0 "C3" H 4850 4050 50  0000 L CNN
F 1 "47nF" H 4850 3850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4863 3800 30  0001 C CNN
F 3 "" H 4825 3950 60  0000 C CNN
	1    4825 3950
	0    1    1    0   
$EndComp
$Comp
L transmitter-rescue:R-RESCUE-transmitter R5
U 1 1 56434DD1
P 5075 3575
F 0 "R5" V 5155 3575 50  0000 C CNN
F 1 "33k" V 5075 3575 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5005 3575 30  0001 C CNN
F 3 "" H 5075 3575 30  0000 C CNN
	1    5075 3575
	0    1    1    0   
$EndComp
$Comp
L power:+BATT #PWR015
U 1 1 5643E337
P 10375 3075
F 0 "#PWR015" H 10375 2925 50  0001 C CNN
F 1 "+BATT" H 10375 3215 50  0000 C CNN
F 2 "" H 10375 3075 60  0000 C CNN
F 3 "" H 10375 3075 60  0000 C CNN
	1    10375 3075
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:R-RESCUE-transmitter R8
U 1 1 56439A92
P 9750 5225
F 0 "R8" V 9800 5375 50  0000 C CNN
F 1 "2R" V 9750 5225 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9680 5225 30  0001 C CNN
F 3 "" H 9750 5225 30  0000 C CNN
	1    9750 5225
	-1   0    0    1   
$EndComp
$Comp
L transmitter-rescue:C-RESCUE-transmitter C5
U 1 1 56441557
P 4250 3275
F 0 "C5" H 4275 3375 50  0000 L CNN
F 1 "100nF" H 4275 3175 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4288 3125 30  0001 C CNN
F 3 "" H 4250 3275 60  0000 C CNN
	1    4250 3275
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 564425F7
P 4250 3025
F 0 "#PWR016" H 4250 2775 50  0001 C CNN
F 1 "GND" H 4250 2875 50  0000 C CNN
F 2 "" H 4250 3025 60  0000 C CNN
F 3 "" H 4250 3025 60  0000 C CNN
	1    4250 3025
	-1   0    0    1   
$EndComp
$Comp
L transmitter-rescue:C-RESCUE-transmitter C6
U 1 1 564445C8
P 7575 3275
F 0 "C6" H 7600 3375 50  0000 L CNN
F 1 "100nF" H 7600 3175 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7613 3125 30  0001 C CNN
F 3 "" H 7575 3275 60  0000 C CNN
	1    7575 3275
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 564445CE
P 7575 3025
F 0 "#PWR017" H 7575 2775 50  0001 C CNN
F 1 "GND" H 7575 2875 50  0000 C CNN
F 2 "" H 7575 3025 60  0000 C CNN
F 3 "" H 7575 3025 60  0000 C CNN
	1    7575 3025
	-1   0    0    1   
$EndComp
$Comp
L transmitter-rescue:CP-RESCUE-transmitter C7
U 1 1 56445A00
P 10650 4350
F 0 "C7" H 10675 4450 50  0000 L CNN
F 1 "10µF" H 10675 4250 50  0000 L CNN
F 2 "iwasz:c_tant_B-pins21" H 10688 4200 30  0001 C CNN
F 3 "" H 10650 4350 60  0000 C CNN
	1    10650 4350
	1    0    0    -1  
$EndComp
$Comp
L transmitter-rescue:test-double-RESCUE-transmitter P5
U 1 1 568206AD
P 4675 1575
F 0 "P5" H 4925 1725 60  0000 C CNN
F 1 "test-double" H 4675 1525 60  0001 C CNN
F 2 "iwasz:testpad-2p" H 4675 1575 60  0001 C CNN
F 3 "" H 4675 1575 60  0000 C CNN
	1    4675 1575
	1    0    0    -1  
$EndComp
$Comp
L iwasz-kicad:test-double P3
U 1 1 568227A9
P 3225 2100
F 0 "P3" H 3368 2231 60  0000 C CNN
F 1 "test-double" H 3425 2000 60  0001 C CNN
F 2 "iwasz:testpad-2p" H 3325 1950 60  0001 C CNN
F 3 "" H 3325 1950 60  0000 C CNN
	1    3225 2100
	1    0    0    -1  
$EndComp
$Comp
L iwasz-kicad:Led_x2-CA D1
U 1 1 5682BA41
P 2575 1625
F 0 "D1" V 2529 1833 50  0000 L CNN
F 1 "Led_x2-CA" V 2621 1833 50  0000 L CNN
F 2 "iwasz:led_3mm-3pins" H 2575 1625 50  0001 C CNN
F 3 "http://lispol.com/produkt/dioda-led-3mm-czerwonazielona-wsp-anoda---3arg9hwb" H 2575 1625 50  0001 C CNN
	1    2575 1625
	0    1    1    0   
$EndComp
$Comp
L iwasz-kicad:test-double P11
U 1 1 5683745B
P 9675 3725
F 0 "P11" H 10025 3725 60  0000 C CNN
F 1 "test-double" H 9875 3625 60  0001 C CNN
F 2 "iwasz:testpad-2p" H 9775 3575 60  0001 C CNN
F 3 "" H 9775 3575 60  0000 C CNN
	1    9675 3725
	1    0    0    -1  
$EndComp
$Comp
L iwasz-kicad:test-double P4
U 1 1 56841380
P 4500 4000
F 0 "P4" V 4643 4078 60  0000 L CNN
F 1 "test-double" H 4700 3900 60  0001 C CNN
F 2 "iwasz:testpad-2p" H 4600 3850 60  0001 C CNN
F 3 "" H 4600 3850 60  0000 C CNN
	1    4500 4000
	0    1    1    0   
$EndComp
$Comp
L iwasz-kicad:test-double P2
U 1 1 5684210E
P 2050 3950
F 0 "P2" V 2193 4028 60  0000 L CNN
F 1 "test-double" H 2250 3850 60  0001 C CNN
F 2 "iwasz:testpad-2p" H 2150 3800 60  0001 C CNN
F 3 "" H 2150 3800 60  0000 C CNN
	1    2050 3950
	0    1    1    0   
$EndComp
Wire Wire Line
	1625 1125 1800 1125
Wire Wire Line
	1800 1125 1800 1250
Connection ~ 1800 1125
Wire Wire Line
	1800 1550 1800 1625
Wire Wire Line
	3250 1225 3075 1225
Wire Wire Line
	3075 1225 3075 1125
Connection ~ 3075 1125
Wire Wire Line
	2475 1925 2475 2000
Wire Wire Line
	2675 1925 2675 2000
Wire Wire Line
	2675 2300 2675 2400
Wire Wire Line
	2675 2400 2925 2400
Wire Wire Line
	2925 2400 2925 1325
Wire Wire Line
	2925 1325 3250 1325
Wire Wire Line
	2475 2300 2475 2475
Wire Wire Line
	2475 2475 3050 2475
Wire Wire Line
	3050 2475 3050 1425
Wire Wire Line
	3050 1425 3250 1425
Wire Wire Line
	3250 1525 3175 1525
Wire Wire Line
	3175 1525 3175 1750
Wire Wire Line
	4575 1425 4400 1425
Wire Wire Line
	4400 1525 4450 1525
Wire Wire Line
	4450 1525 4450 1750
Wire Wire Line
	4450 1750 4000 1750
Wire Wire Line
	3175 1750 3700 1750
Connection ~ 3175 1750
Wire Wire Line
	4400 1125 4525 1125
Wire Wire Line
	4525 1225 4400 1225
Wire Wire Line
	4525 725  4525 1125
Connection ~ 4525 1125
Wire Wire Line
	9650 3725 9650 3750
Wire Wire Line
	9650 4150 9650 4225
Wire Wire Line
	9750 5450 10375 5450
Wire Wire Line
	10375 5175 10375 5450
Wire Wire Line
	10375 4875 10375 4825
Wire Wire Line
	10375 3900 10375 4425
Wire Wire Line
	9950 4425 10375 4425
Connection ~ 10375 4425
Wire Wire Line
	9275 3950 9350 3950
Connection ~ 10375 5450
Wire Wire Line
	1625 725  1775 725 
Wire Wire Line
	2625 3550 2625 3475
Wire Wire Line
	2525 3475 2525 3175
Wire Wire Line
	2525 3175 2450 3175
Wire Wire Line
	2150 3175 1675 3175
Wire Wire Line
	1675 3750 2625 3750
Wire Wire Line
	2625 3850 2550 3850
Wire Wire Line
	2550 3850 2550 3950
Wire Wire Line
	1850 3950 2050 3950
Wire Wire Line
	2550 4050 2625 4050
Connection ~ 2550 3950
Wire Wire Line
	2625 4150 2625 4250
Wire Wire Line
	2625 3475 2525 3475
Wire Wire Line
	2550 3575 2550 3650
Wire Wire Line
	2550 3650 2625 3650
Wire Wire Line
	4225 3550 4250 3550
Wire Wire Line
	4225 3750 4300 3750
Wire Wire Line
	4300 3750 4300 4050
Wire Wire Line
	4300 4050 4225 4050
Wire Wire Line
	4300 4150 4225 4150
Connection ~ 4300 4050
Connection ~ 4300 4150
Wire Wire Line
	5950 3550 5950 3475
Wire Wire Line
	5850 3475 5850 3175
Wire Wire Line
	5850 3175 5775 3175
Wire Wire Line
	4850 3175 5475 3175
Wire Wire Line
	5225 3575 5300 3575
Wire Wire Line
	4850 3750 5950 3750
Connection ~ 5300 3575
Wire Wire Line
	5625 3850 5625 4050
Wire Wire Line
	5950 4150 5950 4250
Wire Wire Line
	5625 3425 5300 3425
Wire Wire Line
	5950 3475 5850 3475
Wire Wire Line
	5875 3575 5875 3650
Wire Wire Line
	5875 3650 5950 3650
Wire Wire Line
	7550 3550 7575 3550
Wire Wire Line
	7550 3750 7625 3750
Wire Wire Line
	7625 3750 7625 4050
Wire Wire Line
	7625 4050 7550 4050
Wire Wire Line
	7625 4150 7550 4150
Connection ~ 7625 4050
Connection ~ 7625 4150
Wire Wire Line
	4225 3950 4500 3950
Wire Wire Line
	4850 3175 4850 3575
Wire Wire Line
	4850 3575 4925 3575
Wire Wire Line
	5300 3425 5300 3575
Connection ~ 4850 3575
Wire Wire Line
	7550 3950 7825 3950
Wire Wire Line
	5625 4050 5950 4050
Wire Wire Line
	5950 3850 5625 3850
Connection ~ 5625 4050
Connection ~ 10375 3200
Wire Wire Line
	9750 5375 9750 5450
Wire Wire Line
	4250 3025 4250 3125
Wire Wire Line
	4250 3425 4250 3550
Connection ~ 4250 3550
Wire Wire Line
	7575 3025 7575 3125
Wire Wire Line
	7575 3425 7575 3550
Connection ~ 7575 3550
Wire Wire Line
	10650 3200 10650 4200
Wire Wire Line
	10650 5450 10650 4500
Wire Wire Line
	3175 2100 3225 2100
Connection ~ 3175 2100
Wire Wire Line
	2575 1325 2575 1125
Connection ~ 2575 1125
Wire Wire Line
	7825 3975 7825 3950
Connection ~ 7825 3950
Wire Wire Line
	4500 4000 4500 3950
Connection ~ 4500 3950
Wire Wire Line
	8950 3200 10375 3200
Wire Wire Line
	10375 3075 10375 3200
Connection ~ 2050 3950
Connection ~ 9650 3725
Wire Wire Line
	4400 1325 4750 1325
Wire Wire Line
	5775 3575 5875 3575
Wire Wire Line
	2450 3575 2550 3575
Text Notes 725  4975 0    60   ~ 0
Zmierzony pobór prądu to 41mA przy baterii na full (4.15V)
Wire Wire Line
	8950 3725 9650 3725
Wire Wire Line
	1800 1125 2575 1125
Wire Wire Line
	3075 1125 3250 1125
Wire Wire Line
	3175 1750 3175 2100
Wire Wire Line
	4525 1125 5075 1125
Wire Wire Line
	4525 1125 4525 1225
Wire Wire Line
	10375 4425 10375 4525
Wire Wire Line
	10375 5450 10650 5450
Wire Wire Line
	10375 5450 10375 5725
Wire Wire Line
	2550 3950 2550 4050
Wire Wire Line
	2550 3950 2625 3950
Wire Wire Line
	4300 4050 4300 4150
Wire Wire Line
	4300 4150 4300 4250
Wire Wire Line
	5300 3575 5475 3575
Wire Wire Line
	7625 4050 7625 4150
Wire Wire Line
	7625 4150 7625 4250
Wire Wire Line
	4850 3575 4850 3750
Wire Wire Line
	10375 3200 10650 3200
Wire Wire Line
	10375 3200 10375 3600
Wire Wire Line
	4250 3550 4300 3550
Wire Wire Line
	7575 3550 7625 3550
Wire Wire Line
	3175 2100 3175 2375
Wire Wire Line
	2575 1125 3075 1125
Wire Wire Line
	7825 3950 8975 3950
Wire Wire Line
	4500 3950 4675 3950
Wire Wire Line
	2050 3950 2550 3950
Wire Wire Line
	9650 3725 9675 3725
$Comp
L Device:Battery_Cell BT1
U 1 1 5A849764
P 5275 1125
F 0 "BT1" V 5530 1175 50  0000 C CNN
F 1 "Battery_Cell" V 5439 1175 50  0000 C CNN
F 2 "Battery:BatteryHolder_MPD_BH-18650-PC2" V 5275 1185 50  0001 C CNN
F 3 "" V 5275 1185 50  0001 C CNN
	1    5275 1125
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5375 1125 5400 1125
$Comp
L Device:R R1
U 1 1 5A862F3F
P 4900 1325
F 0 "R1" V 4693 1325 50  0000 C CNN
F 1 "10k" V 4784 1325 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4830 1325 50  0001 C CNN
F 3 "" H 4900 1325 50  0001 C CNN
	1    4900 1325
	0    1    1    0   
$EndComp
Wire Wire Line
	5050 1325 5400 1325
Wire Wire Line
	5400 1325 5400 1125
Connection ~ 5400 1125
Wire Wire Line
	5400 1125 5450 1125
Wire Wire Line
	8950 3200 8950 3325
Wire Wire Line
	8950 3625 8950 3725
$Comp
L transmitter-rescue:R-RESCUE-transmitter R10
U 1 1 5A84900A
P 9650 5225
F 0 "R10" V 9700 5375 50  0000 C CNN
F 1 "4R" V 9650 5225 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9580 5225 30  0001 C CNN
F 3 "" H 9650 5225 30  0000 C CNN
	1    9650 5225
	-1   0    0    1   
$EndComp
$Comp
L transmitter-rescue:R-RESCUE-transmitter R9
U 1 1 5A8490B8
P 9550 5225
F 0 "R9" V 9600 5375 50  0000 C CNN
F 1 "8R" V 9550 5225 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9480 5225 30  0001 C CNN
F 3 "" H 9550 5225 30  0000 C CNN
	1    9550 5225
	-1   0    0    1   
$EndComp
Wire Wire Line
	9550 5375 9550 5450
Wire Wire Line
	9550 5450 9650 5450
Connection ~ 9750 5450
Wire Wire Line
	9650 5375 9650 5450
Connection ~ 9650 5450
Wire Wire Line
	9650 5450 9750 5450
$Comp
L Switch:SW_SP3T SW2
U 1 1 5A854645
P 9650 4850
F 0 "SW2" V 9604 4996 50  0000 L CNN
F 1 "SW_SP3T" V 9695 4996 50  0000 L CNN
F 2 "iwasz:MFP-1323-R" H 9025 5025 50  0001 C CNN
F 3 "" H 9025 5025 50  0001 C CNN
	1    9650 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	9650 4625 9650 4650
Wire Wire Line
	9550 5050 9550 5075
Wire Wire Line
	9650 5050 9650 5075
Wire Wire Line
	9750 5050 9750 5075
$Comp
L iwasz-kicad:test-double P7
U 1 1 568406C0
P 7825 3975
F 0 "P7" V 7968 4053 60  0000 L CNN
F 1 "test-double" H 8025 3875 60  0001 C CNN
F 2 "iwasz:testpad-2p" H 7925 3825 60  0001 C CNN
F 3 "" H 7925 3825 60  0000 C CNN
	1    7825 3975
	0    1    1    0   
$EndComp
Text Notes 9050 5675 0    50   ~ 0
Dobrać eksperymentalnie.\nOryginalnie był tylko 2R.
Wire Wire Line
	4975 3950 5950 3950
Wire Wire Line
	5625 4050 5625 4250
Wire Wire Line
	4525 725  5025 725 
Wire Wire Line
	5425 625  5475 625 
Wire Wire Line
	2300 3425 2075 3425
Wire Wire Line
	2075 3425 2075 3575
Wire Wire Line
	2075 3575 2150 3575
Wire Wire Line
	1675 3175 1675 3575
$Comp
L transmitter-rescue:R-RESCUE-transmitter R11
U 1 1 5D1EB727
P 1875 3575
F 0 "R11" V 1955 3575 50  0000 C CNN
F 1 "0R" V 1875 3575 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1805 3575 30  0001 C CNN
F 3 "" H 1875 3575 30  0000 C CNN
	1    1875 3575
	0    1    1    0   
$EndComp
Wire Wire Line
	1725 3575 1675 3575
Connection ~ 1675 3575
Wire Wire Line
	1675 3575 1675 3750
Wire Wire Line
	2025 3575 2075 3575
Connection ~ 2075 3575
Text Notes 1600 2975 3    50   ~ 0
R11 można wybrać tak, żeby potencjometr\ndziałał jako fine-tune
$EndSCHEMATC
