EESchema Schematic File Version 2
LIBS:iwasz-kicad
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:gp8-clock-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
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
L STM32F0-LQFP48 U3
U 1 1 56329BF0
P 6550 4425
F 0 "U3" H 6550 4075 60  0000 C CNN
F 1 "STM32F072CB / STM32F042C6" H 6550 3975 60  0000 C CNN
F 2 "w_smd_lqfp:lqfp48" H 7000 4125 60  0001 C CNN
F 3 "" H 7000 4125 60  0000 C CNN
F 4 "µC" H 6550 4425 60  0001 C CNN "Opis"
	1    6550 4425
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 56329D4C
P 8050 3775
F 0 "C13" H 8075 3875 50  0000 L CNN
F 1 "100nF" H 8075 3675 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 8088 3625 30  0001 C CNN
F 3 "" H 8050 3775 60  0000 C CNN
F 4 "Decoupling capacitor" H 8050 3775 60  0001 C CNN "Opis"
	1    8050 3775
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 5632A30E
P 8350 3775
F 0 "C14" H 8375 3875 50  0000 L CNN
F 1 "4.7µF" H 8375 3675 50  0000 L CNN
F 2 "w_smd_cap:c_0805" H 8388 3625 30  0001 C CNN
F 3 "" H 8350 3775 60  0000 C CNN
F 4 "Decoupling capacitor" H 8350 3775 60  0001 C CNN "Opis"
	1    8350 3775
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5632A456
P 8350 4075
F 0 "#PWR01" H 8350 3825 50  0001 C CNN
F 1 "GND" H 8350 3925 50  0000 C CNN
F 2 "" H 8350 4075 60  0000 C CNN
F 3 "" H 8350 4075 60  0000 C CNN
	1    8350 4075
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5632A638
P 7225 5775
F 0 "C9" H 7250 5875 50  0000 L CNN
F 1 "100nF" H 7250 5675 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 7263 5625 30  0001 C CNN
F 3 "" H 7225 5775 60  0000 C CNN
F 4 "Decoupling capacitor" H 7225 5775 60  0001 C CNN "Opis"
	1    7225 5775
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 5632A77A
P 7550 5775
F 0 "C10" H 7575 5875 50  0000 L CNN
F 1 "100nF" H 7575 5675 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 7588 5625 30  0001 C CNN
F 3 "" H 7550 5775 60  0000 C CNN
F 4 "Decoupling capacitor" H 7550 5775 60  0001 C CNN "Opis"
	1    7550 5775
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 5632A7B5
P 7850 5775
F 0 "C11" H 7875 5875 50  0000 L CNN
F 1 "4.7µF" H 7875 5675 50  0000 L CNN
F 2 "w_smd_cap:c_0805" H 7888 5625 30  0001 C CNN
F 3 "" H 7850 5775 60  0000 C CNN
F 4 "Decoupling capacitor" H 7850 5775 60  0001 C CNN "Opis"
	1    7850 5775
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5632A81C
P 7850 6125
F 0 "#PWR02" H 7850 5875 50  0001 C CNN
F 1 "GND" H 7850 5975 50  0000 C CNN
F 2 "" H 7850 6125 60  0000 C CNN
F 3 "" H 7850 6125 60  0000 C CNN
	1    7850 6125
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5632B571
P 6225 2775
F 0 "C8" H 6250 2875 50  0000 L CNN
F 1 "100nF" H 6250 2675 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 6263 2625 30  0001 C CNN
F 3 "" H 6225 2775 60  0000 C CNN
F 4 "Decoupling capacitor" H 6225 2775 60  0001 C CNN "Opis"
	1    6225 2775
	0    -1   -1   0   
$EndComp
$Comp
L C C7
U 1 1 5632B578
P 6225 2450
F 0 "C7" H 6250 2550 50  0000 L CNN
F 1 "100nF" H 6250 2350 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 6263 2300 30  0001 C CNN
F 3 "" H 6225 2450 60  0000 C CNN
F 4 "Decoupling capacitor" H 6225 2450 60  0001 C CNN "Opis"
	1    6225 2450
	0    -1   -1   0   
$EndComp
$Comp
L C C6
U 1 1 5632B57F
P 6225 2150
F 0 "C6" H 6250 2250 50  0000 L CNN
F 1 "4.7µF" H 6250 2050 50  0000 L CNN
F 2 "w_smd_cap:c_0805" H 6263 2000 30  0001 C CNN
F 3 "" H 6225 2150 60  0000 C CNN
F 4 "Decoupling capacitor" H 6225 2150 60  0001 C CNN "Opis"
	1    6225 2150
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR03
U 1 1 5632B585
P 6525 2150
F 0 "#PWR03" H 6525 1900 50  0001 C CNN
F 1 "GND" H 6525 2000 50  0000 C CNN
F 2 "" H 6525 2150 60  0000 C CNN
F 3 "" H 6525 2150 60  0000 C CNN
	1    6525 2150
	0    -1   -1   0   
$EndComp
$Comp
L C C5
U 1 1 5632C969
P 4725 4875
F 0 "C5" H 4750 4975 50  0000 L CNN
F 1 "10nF" H 4750 4775 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 4763 4725 30  0001 C CNN
F 3 "" H 4725 4875 60  0000 C CNN
F 4 "Decoupling capacitor" H 4725 4875 60  0001 C CNN "Opis"
	1    4725 4875
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5632D031
P 4425 4875
F 0 "C2" H 4450 4975 50  0000 L CNN
F 1 "1µF" H 4450 4775 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 4463 4725 30  0001 C CNN
F 3 "" H 4425 4875 60  0000 C CNN
F 4 "Decoupling capacitor" H 4425 4875 60  0001 C CNN "Opis"
	1    4425 4875
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5632D5AE
P 4425 5150
F 0 "#PWR04" H 4425 4900 50  0001 C CNN
F 1 "GND" H 4425 5000 50  0000 C CNN
F 2 "" H 4425 5150 60  0000 C CNN
F 3 "" H 4425 5150 60  0000 C CNN
	1    4425 5150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5632E153
P 5300 4575
F 0 "#PWR05" H 5300 4325 50  0001 C CNN
F 1 "GND" H 5300 4425 50  0000 C CNN
F 2 "" H 5300 4575 60  0000 C CNN
F 3 "" H 5300 4575 60  0000 C CNN
	1    5300 4575
	0    1    1    0   
$EndComp
NoConn ~ 5500 3875
$Comp
L Crystal Y1
U 1 1 5632FE9D
P 4925 4175
F 0 "Y1" V 4879 4306 50  0000 L CNN
F 1 "8MHz" V 4971 4306 50  0000 L CNN
F 2 "w_crystal:crystal_hc-49s" H 4925 4175 60  0001 C CNN
F 3 "" H 4925 4175 60  0000 C CNN
	1    4925 4175
	0    1    1    0   
$EndComp
$Comp
L R R22
U 1 1 563308C8
P 5225 4375
F 0 "R22" V 5305 4375 50  0000 C CNN
F 1 "220R" V 5225 4375 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 5155 4375 30  0001 C CNN
F 3 "" H 5225 4375 30  0000 C CNN
	1    5225 4375
	0    1    1    0   
$EndComp
$Comp
L C C4
U 1 1 56330F7F
P 4600 4375
F 0 "C4" H 4625 4475 50  0000 L CNN
F 1 "?10pF" H 4625 4275 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 4638 4225 30  0001 C CNN
F 3 "" H 4600 4375 60  0000 C CNN
F 4 "Decoupling capacitor" H 4600 4375 60  0001 C CNN "Opis"
	1    4600 4375
	0    1    1    0   
$EndComp
$Comp
L C C3
U 1 1 56331087
P 4600 3975
F 0 "C3" H 4625 4075 50  0000 L CNN
F 1 "?10pF" H 4625 3875 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 4638 3825 30  0001 C CNN
F 3 "" H 4600 3975 60  0000 C CNN
F 4 "Decoupling capacitor" H 4600 3975 60  0001 C CNN "Opis"
	1    4600 3975
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 56332E1B
P 1775 6575
F 0 "D1" H 1775 6675 50  0000 C CNN
F 1 "LED" H 1775 6475 50  0000 C CNN
F 2 "iwasz:weight-scale-backlight" H 1775 6575 60  0001 C CNN
F 3 "" H 1775 6575 60  0000 C CNN
	1    1775 6575
	0    -1   -1   0   
$EndComp
$Comp
L R R9
U 1 1 56333024
P 1775 6125
F 0 "R9" V 1855 6125 50  0000 C CNN
F 1 "560R" V 1775 6125 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 1705 6125 30  0001 C CNN
F 3 "" H 1775 6125 30  0000 C CNN
	1    1775 6125
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR06
U 1 1 563333C1
P 1775 7375
F 0 "#PWR06" H 1775 7125 50  0001 C CNN
F 1 "GND" H 1775 7225 50  0000 C CNN
F 2 "" H 1775 7375 60  0000 C CNN
F 3 "" H 1775 7375 60  0000 C CNN
	1    1775 7375
	1    0    0    -1  
$EndComp
Text Notes 2050 6775 1    60   ~ 0
Backlight
$Comp
L +3.3V #PWR07
U 1 1 56335DD4
P 6000 2050
F 0 "#PWR07" H 6000 1900 50  0001 C CNN
F 1 "+3.3V" H 6000 2190 50  0000 C CNN
F 2 "" H 6000 2050 60  0000 C CNN
F 3 "" H 6000 2050 60  0000 C CNN
	1    6000 2050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR08
U 1 1 56336C0B
P 8500 3575
F 0 "#PWR08" H 8500 3425 50  0001 C CNN
F 1 "+3.3V" H 8500 3715 50  0000 C CNN
F 2 "" H 8500 3575 60  0000 C CNN
F 3 "" H 8500 3575 60  0000 C CNN
	1    8500 3575
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR09
U 1 1 5633746D
P 8000 5550
F 0 "#PWR09" H 8000 5400 50  0001 C CNN
F 1 "+3.3V" H 8000 5690 50  0000 C CNN
F 2 "" H 8000 5550 60  0000 C CNN
F 3 "" H 8000 5550 60  0000 C CNN
	1    8000 5550
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR010
U 1 1 56337C8A
P 4275 4675
F 0 "#PWR010" H 4275 4525 50  0001 C CNN
F 1 "+3.3V" H 4275 4815 50  0000 C CNN
F 2 "" H 4275 4675 60  0000 C CNN
F 3 "" H 4275 4675 60  0000 C CNN
	1    4275 4675
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR011
U 1 1 563385BD
P 4250 4375
F 0 "#PWR011" H 4250 4125 50  0001 C CNN
F 1 "GND" H 4250 4225 50  0000 C CNN
F 2 "" H 4250 4375 60  0000 C CNN
F 3 "" H 4250 4375 60  0000 C CNN
	1    4250 4375
	0    1    1    0   
$EndComp
$Comp
L Q_NPN_BCE Q1
U 1 1 5633990D
P 1675 7050
F 0 "Q1" H 1869 7096 50  0000 L CNN
F 1 "BC847" H 1869 7004 50  0000 L CNN
F 2 "w_smd_trans:sot23" H 1875 7150 29  0001 C CNN
F 3 "" H 1675 7050 60  0000 C CNN
	1    1675 7050
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5633C9C5
P 1250 7050
F 0 "R3" V 1330 7050 50  0000 C CNN
F 1 "1k" V 1250 7050 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 1180 7050 30  0001 C CNN
F 3 "" H 1250 7050 30  0000 C CNN
	1    1250 7050
	0    -1   -1   0   
$EndComp
Text Label 1025 7050 2    60   ~ 0
backlight
Wire Wire Line
	7775 3575 8500 3575
Wire Wire Line
	8350 3575 8350 3625
Wire Wire Line
	8050 3625 8050 3575
Connection ~ 8050 3575
Wire Wire Line
	8350 3925 8350 4075
Wire Wire Line
	8050 3925 8050 3975
Wire Wire Line
	7550 3975 8350 3975
Connection ~ 8350 3975
Wire Wire Line
	7100 5425 7100 5550
Wire Wire Line
	7100 5550 8000 5550
Wire Wire Line
	7850 5550 7850 5625
Wire Wire Line
	7550 5625 7550 5550
Connection ~ 7550 5550
Wire Wire Line
	7225 5625 7225 5550
Connection ~ 7225 5550
Wire Wire Line
	7850 5925 7850 6125
Wire Wire Line
	7225 5925 7225 6000
Wire Wire Line
	7000 6000 7850 6000
Connection ~ 7850 6000
Wire Wire Line
	7550 5925 7550 6000
Connection ~ 7550 6000
Wire Wire Line
	6000 2050 6000 3375
Wire Wire Line
	6075 2450 6000 2450
Connection ~ 6000 2450
Wire Wire Line
	6075 2775 6000 2775
Connection ~ 6000 2775
Wire Wire Line
	6375 2150 6525 2150
Wire Wire Line
	6450 2775 6375 2775
Wire Wire Line
	6450 2150 6450 2950
Wire Wire Line
	6375 2450 6450 2450
Connection ~ 6450 2450
Connection ~ 6000 2150
Wire Wire Line
	4275 4675 5500 4675
Wire Wire Line
	4725 4725 4725 4675
Connection ~ 4725 4675
Wire Wire Line
	4725 5025 4725 5075
Wire Wire Line
	4725 5075 4425 5075
Wire Wire Line
	4425 5025 4425 5150
Connection ~ 4425 5075
Wire Wire Line
	5500 4575 5300 4575
Wire Wire Line
	6100 2950 6100 3375
Wire Wire Line
	7000 5425 7000 6000
Wire Wire Line
	5500 4375 5375 4375
Wire Wire Line
	4425 3975 4450 3975
Connection ~ 4425 4675
Wire Wire Line
	4250 4375 4450 4375
Wire Wire Line
	4750 4375 5075 4375
Wire Wire Line
	4750 3975 5225 3975
Wire Wire Line
	4925 3975 4925 4025
Wire Wire Line
	4925 4325 4925 4375
Connection ~ 4925 4375
Wire Wire Line
	5225 3975 5225 4275
Wire Wire Line
	5225 4275 5500 4275
Connection ~ 4925 3975
Wire Wire Line
	6000 2150 6075 2150
Connection ~ 6450 2150
Connection ~ 8350 3575
Connection ~ 7850 5550
Wire Wire Line
	4425 4725 4425 4675
Wire Wire Line
	4425 4375 4425 3975
Connection ~ 4425 4375
Wire Wire Line
	1775 7250 1775 7375
Wire Wire Line
	1400 7050 1475 7050
Wire Wire Line
	1775 6725 1775 6850
Wire Wire Line
	1775 6275 1775 6425
Wire Wire Line
	1775 5800 1775 5975
Wire Wire Line
	1100 7050 1025 7050
Connection ~ 7225 6000
Connection ~ 8050 3975
Wire Wire Line
	6450 2950 6100 2950
Connection ~ 6450 2775
$Comp
L TSOP39538 U1
U 1 1 5635A808
P 1225 4200
F 0 "U1" H 1225 4500 60  0000 C CNN
F 1 "TSOP39538" V 1025 4200 60  0000 C CNN
F 2 "w_pin_strip:pin_strip_3" H 1225 4200 60  0001 C CNN
F 3 "http://pl.farnell.com/vishay/tsop39538/ir-receiver-minicast-agc5-38khz/dp/2251377?ost=TSOP39538&anyFilterApplied=false&searchView=table&iscrfnonsku=false&ddkey=http%3Apl-PL%2FElement14_Poland%2Fsearch" H 1225 4200 60  0001 C CNN
	1    1225 4200
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 5635B357
P 2050 4200
F 0 "R13" V 2130 4200 50  0000 C CNN
F 1 "1R" V 2050 4200 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 1980 4200 30  0001 C CNN
F 3 "" H 2050 4200 30  0000 C CNN
	1    2050 4200
	0    1    1    0   
$EndComp
$Comp
L C C1
U 1 1 5635B5D7
P 1800 4475
F 0 "C1" H 1825 4575 50  0000 L CNN
F 1 "C" H 1825 4375 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 1838 4325 30  0001 C CNN
F 3 "" H 1800 4475 60  0000 C CNN
	1    1800 4475
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5635C6F6
P 1800 4750
F 0 "#PWR012" H 1800 4500 50  0001 C CNN
F 1 "GND" H 1800 4600 50  0000 C CNN
F 2 "" H 1800 4750 60  0000 C CNN
F 3 "" H 1800 4750 60  0000 C CNN
	1    1800 4750
	1    0    0    -1  
$EndComp
Text Label 1575 4100 0    60   ~ 0
ir
$Comp
L +3.3V #PWR013
U 1 1 5635C99B
P 2300 4200
F 0 "#PWR013" H 2300 4050 50  0001 C CNN
F 1 "+3.3V" H 2300 4340 50  0000 C CNN
F 2 "" H 2300 4200 60  0000 C CNN
F 3 "" H 2300 4200 60  0000 C CNN
	1    2300 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	1575 4200 1900 4200
Wire Wire Line
	2200 4200 2300 4200
Wire Wire Line
	1800 4325 1800 4200
Connection ~ 1800 4200
Wire Wire Line
	1800 4625 1800 4750
Wire Wire Line
	1575 4300 1650 4300
Wire Wire Line
	1650 4300 1650 4675
Wire Wire Line
	1650 4675 1800 4675
Connection ~ 1800 4675
Text Label 6600 5425 3    60   ~ 0
ir
$Sheet
S 5825 850  1075 400 
U 56372EC6
F0 "Sheet56372EC5" 60
F1 "power.sch" 60
F2 "progress" O L 5825 925 60 
F3 "complete" O L 5825 1025 60 
F4 "sense" O L 5825 1125 60 
$EndSheet
Wire Wire Line
	7550 3875 7775 3875
Wire Wire Line
	7775 3875 7775 3575
$Comp
L usb-micro U4
U 1 1 56392056
P 9475 4550
F 0 "U4" H 9525 4450 60  0000 C CNN
F 1 "usb-micro" H 9525 4550 60  0000 C CNN
F 2 "w_conn_pc:conn_usb_B_micro_smd-2" H 9525 4550 60  0001 C CNN
F 3 "" H 9525 4550 60  0000 C CNN
	1    9475 4550
	1    0    0    -1  
$EndComp
$Comp
L R R24
U 1 1 5639361D
P 8600 4600
F 0 "R24" V 8680 4600 50  0000 C CNN
F 1 "22R" V 8600 4600 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 8530 4600 30  0001 C CNN
F 3 "" H 8600 4600 30  0000 C CNN
F 4 "Terminacja USB" V 8600 4600 60  0001 C CNN "Opis"
	1    8600 4600
	0    1    1    0   
$EndComp
$Comp
L R R23
U 1 1 563937F9
P 8375 4500
F 0 "R23" V 8455 4500 50  0000 C CNN
F 1 "22R" V 8375 4500 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 8305 4500 30  0001 C CNN
F 3 "" H 8375 4500 30  0000 C CNN
F 4 "Terminacja USB" V 8375 4500 60  0001 C CNN "Opis"
	1    8375 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	8875 4500 8525 4500
Wire Wire Line
	8875 4600 8750 4600
Wire Wire Line
	8225 4500 7975 4500
Wire Wire Line
	7975 4500 7975 4275
Wire Wire Line
	7975 4275 7550 4275
Wire Wire Line
	8450 4600 8050 4600
Wire Wire Line
	8050 4600 8050 4175
Wire Wire Line
	8050 4175 7550 4175
$Comp
L GND #PWR014
U 1 1 563942BE
P 8800 4875
F 0 "#PWR014" H 8800 4625 50  0001 C CNN
F 1 "GND" H 8800 4725 50  0000 C CNN
F 2 "" H 8800 4875 60  0000 C CNN
F 3 "" H 8800 4875 60  0000 C CNN
	1    8800 4875
	1    0    0    -1  
$EndComp
Wire Wire Line
	8875 4800 8800 4800
Wire Wire Line
	8800 4800 8800 4875
NoConn ~ 8875 4700
$Comp
L +5V #PWR015
U 1 1 56394835
P 8800 4250
F 0 "#PWR015" H 8800 4100 50  0001 C CNN
F 1 "+5V" H 8800 4390 50  0000 C CNN
F 2 "" H 8800 4250 60  0000 C CNN
F 3 "" H 8800 4250 60  0000 C CNN
	1    8800 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 4400 8875 4400
Wire Wire Line
	8800 4400 8800 4250
Text Label 5500 4875 2    60   ~ 0
backlight
$Comp
L SW_PUSH SW1
U 1 1 563A18C5
P 8375 2475
F 0 "SW1" H 8375 2731 50  0000 C CNN
F 1 "SW_PUSH" H 8375 2639 50  0000 C CNN
F 2 "iwasz:tact-switch-smd" H 8375 2475 60  0001 C CNN
F 3 "" H 8375 2475 60  0000 C CNN
	1    8375 2475
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 563A1C3D
P 8775 2775
F 0 "#PWR016" H 8775 2525 50  0001 C CNN
F 1 "GND" H 8775 2625 50  0000 C CNN
F 2 "" H 8775 2775 60  0000 C CNN
F 3 "" H 8775 2775 60  0000 C CNN
	1    8775 2775
	1    0    0    -1  
$EndComp
Wire Wire Line
	8675 2475 8775 2475
Wire Wire Line
	8775 2475 8775 2775
Wire Wire Line
	6850 2475 8075 2475
Wire Wire Line
	6850 3050 6850 2475
Wire Wire Line
	6300 3050 6850 3050
$Comp
L C C12
U 1 1 563A524D
P 7900 2700
F 0 "C12" H 7925 2800 50  0000 L CNN
F 1 "100nF" H 7925 2600 50  0000 L CNN
F 2 "w_smd_cap:c_0603" H 7938 2550 30  0001 C CNN
F 3 "" H 7900 2700 60  0000 C CNN
F 4 "Decoupling capacitor" H 7900 2700 60  0001 C CNN "Opis"
	1    7900 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 2550 7900 2475
Connection ~ 7900 2475
$Comp
L GND #PWR017
U 1 1 563A5573
P 7900 2900
F 0 "#PWR017" H 7900 2650 50  0001 C CNN
F 1 "GND" H 7900 2750 50  0000 C CNN
F 2 "" H 7900 2900 60  0000 C CNN
F 3 "" H 7900 2900 60  0000 C CNN
	1    7900 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 2900 7900 2850
$Comp
L CONN_01X04 P3
U 1 1 5685989A
P 9475 1450
F 0 "P3" V 9440 1206 50  0000 R CNN
F 1 "CONN_01X04" V 9348 1206 50  0000 R CNN
F 2 "w_pin_strip:pin_strip_2mm_4" H 9475 1450 50  0001 C CNN
F 3 "http://lispol.com/produkt/wtyk-goldpin-1x40-prosty-r-200mm---ph1x40" H 9475 1450 50  0001 C CNN
	1    9475 1450
	0    -1   -1   0   
$EndComp
$Comp
L R R31
U 1 1 56859F8E
P 9425 1950
F 0 "R31" H 9495 1996 50  0000 L CNN
F 1 "22R" H 9495 1904 50  0000 L CNN
F 2 "w_smd_resistors:r_0603" V 9355 1950 50  0001 C CNN
F 3 "" H 9425 1950 50  0000 C CNN
	1    9425 1950
	1    0    0    -1  
$EndComp
$Comp
L R R32
U 1 1 5685AAAC
P 9625 1950
F 0 "R32" H 9695 1996 50  0000 L CNN
F 1 "22R" H 9695 1904 50  0000 L CNN
F 2 "w_smd_resistors:r_0603" V 9555 1950 50  0001 C CNN
F 3 "" H 9625 1950 50  0000 C CNN
	1    9625 1950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5685C48D
P 9525 2225
F 0 "#PWR018" H 9525 1975 50  0001 C CNN
F 1 "GND" H 9525 2075 50  0000 C CNN
F 2 "" H 9525 2225 60  0000 C CNN
F 3 "" H 9525 2225 60  0000 C CNN
	1    9525 2225
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR019
U 1 1 5685C531
P 9325 2225
F 0 "#PWR019" H 9325 2075 50  0001 C CNN
F 1 "+3.3V" H 9325 2365 50  0000 C CNN
F 2 "" H 9325 2225 60  0000 C CNN
F 3 "" H 9325 2225 60  0000 C CNN
	1    9325 2225
	-1   0    0    1   
$EndComp
Wire Wire Line
	9325 1650 9325 2225
Wire Wire Line
	9425 1650 9425 1800
Wire Wire Line
	9525 1650 9525 2225
Wire Wire Line
	9625 1650 9625 1800
Wire Wire Line
	9625 2100 9625 2525
Wire Wire Line
	9425 2100 9425 2525
Text Label 9425 2525 3    60   ~ 0
swdio
Text Label 9625 2525 3    60   ~ 0
swdclk
$Comp
L test-double P2
U 1 1 568619B5
P 3850 4475
F 0 "P2" H 3994 4344 60  0000 C CNN
F 1 "test-double" H 4050 4375 60  0001 C CNN
F 2 "iwasz:testpad-2p" H 3950 4325 60  0001 C CNN
F 3 "" H 3950 4325 60  0000 C CNN
	1    3850 4475
	-1   0    0    1   
$EndComp
Wire Wire Line
	5500 4475 3850 4475
Wire Wire Line
	6300 3050 6300 3375
Text Label 7100 3375 1    60   ~ 0
swdclk
Wire Wire Line
	6200 3050 6200 3375
Wire Wire Line
	5450 1025 5450 3975
Wire Wire Line
	5450 3975 5500 3975
$Comp
L Photores R25
U 1 1 5688CAC9
P 4250 2675
F 0 "R25" H 4458 2721 50  0000 L CNN
F 1 "Photores" H 4458 2629 50  0000 L CNN
F 2 "photo-elements:T0-46-A10XX" V 4180 2675 50  0001 C CNN
F 3 "http://www.aliexpress.com/item/Free-Shipping-50-x-5528-Light-Dependent-Resistor-LDR-5MM-Photoresistor-wholesale-and-retail-Photoconductive-resistance/1783947297.html" H 4250 2675 50  0001 C CNN
	1    4250 2675
	1    0    0    -1  
$EndComp
$Comp
L R R26
U 1 1 5688D3A4
P 4250 3125
F 0 "R26" H 4320 3171 50  0000 L CNN
F 1 "10k" H 4320 3079 50  0000 L CNN
F 2 "w_smd_resistors:r_0603" V 4180 3125 50  0001 C CNN
F 3 "" H 4250 3125 50  0000 C CNN
	1    4250 3125
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 5688E43B
P 4250 3375
F 0 "#PWR020" H 4250 3125 50  0001 C CNN
F 1 "GND" H 4250 3225 50  0000 C CNN
F 2 "" H 4250 3375 60  0000 C CNN
F 3 "" H 4250 3375 60  0000 C CNN
	1    4250 3375
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR021
U 1 1 5688EC14
P 4250 2350
F 0 "#PWR021" H 4250 2200 50  0001 C CNN
F 1 "+3.3V" H 4250 2490 50  0000 C CNN
F 2 "" H 4250 2350 60  0000 C CNN
F 3 "" H 4250 2350 60  0000 C CNN
	1    4250 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2350 4250 2425
Wire Wire Line
	4250 2925 4250 2975
Wire Wire Line
	4250 3275 4250 3375
Wire Wire Line
	4250 2925 5275 2925
Wire Wire Line
	5275 2925 5275 4075
Wire Wire Line
	5275 4075 5500 4075
Text Label 5500 4175 2    60   ~ 0
sound
$Comp
L Q_NPN_BCE Q3
U 1 1 56896E10
P 5275 7150
F 0 "Q3" H 5575 7200 50  0000 R CNN
F 1 "BC847" H 5875 7100 50  0000 R CNN
F 2 "w_smd_trans:sot23" H 5475 7250 29  0001 C CNN
F 3 "" H 5275 7150 60  0000 C CNN
	1    5275 7150
	1    0    0    -1  
$EndComp
$Comp
L R R27
U 1 1 56896E1C
P 4800 7150
F 0 "R27" V 4880 7150 50  0000 C CNN
F 1 "1k" V 4800 7150 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 4730 7150 30  0001 C CNN
F 3 "" H 4800 7150 30  0000 C CNN
	1    4800 7150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 7150 4575 7150
Wire Wire Line
	4950 7150 5075 7150
$Comp
L GND #PWR022
U 1 1 56896E24
P 5375 7425
F 0 "#PWR022" H 5375 7175 50  0001 C CNN
F 1 "GND" H 5375 7275 50  0000 C CNN
F 2 "" H 5375 7425 60  0000 C CNN
F 3 "" H 5375 7425 60  0000 C CNN
	1    5375 7425
	1    0    0    -1  
$EndComp
Wire Wire Line
	5375 7350 5375 7425
Wire Wire Line
	5375 6525 5375 6950
Wire Wire Line
	5375 5875 5375 6325
Text Label 4575 7150 2    60   ~ 0
sound
$Comp
L SPEAKER SP1
U 1 1 56898ED0
P 5675 6425
F 0 "SP1" H 5644 5959 50  0000 C CNN
F 1 "BUZZER" H 5644 6051 50  0000 C CNN
F 2 "Buzzers_Beepers:Buzzer_12x9.5RM7.6" H 5675 6425 50  0001 C CNN
F 3 "http://lispol.com/produkt/buzzer-z-generatorem-na-5v---tmb12a05" H 5675 6425 50  0001 C CNN
	1    5675 6425
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR023
U 1 1 56A9F06D
P 1775 5800
F 0 "#PWR023" H 1775 5650 50  0001 C CNN
F 1 "+BATT" H 1775 5940 50  0000 C CNN
F 2 "" H 1775 5800 60  0000 C CNN
F 3 "" H 1775 5800 60  0000 C CNN
	1    1775 5800
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR024
U 1 1 56AA0ED8
P 5375 5875
F 0 "#PWR024" H 5375 5725 50  0001 C CNN
F 1 "+BATT" H 5375 6015 50  0000 C CNN
F 2 "" H 5375 5875 60  0000 C CNN
F 3 "" H 5375 5875 60  0000 C CNN
	1    5375 5875
	1    0    0    -1  
$EndComp
NoConn ~ 6100 5425
NoConn ~ 6200 5425
NoConn ~ 6300 5425
NoConn ~ 6400 5425
NoConn ~ 6500 5425
Text Label 7550 4075 0    60   ~ 0
swdio
NoConn ~ 7550 4975
NoConn ~ 7550 4875
NoConn ~ 7550 4775
NoConn ~ 7550 4675
NoConn ~ 7550 4575
$Comp
L R R1
U 1 1 58BDDCC3
P 6600 2800
F 0 "R1" V 6680 2800 50  0000 C CNN
F 1 "10k" V 6600 2800 50  0000 C CNN
F 2 "w_smd_resistors:r_0603" V 6530 2800 30  0001 C CNN
F 3 "" H 6600 2800 30  0000 C CNN
F 4 "Terminacja USB" V 6600 2800 60  0001 C CNN "Opis"
	1    6600 2800
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR025
U 1 1 58BDE01B
P 6600 2550
F 0 "#PWR025" H 6600 2300 50  0001 C CNN
F 1 "GND" H 6600 2400 50  0000 C CNN
F 2 "" H 6600 2550 60  0000 C CNN
F 3 "" H 6600 2550 60  0000 C CNN
	1    6600 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	6600 2650 6600 2550
Wire Wire Line
	6400 3375 6400 3175
Wire Wire Line
	6400 3175 6600 3175
Wire Wire Line
	6600 3175 6600 2950
Wire Wire Line
	6200 3050 5550 3050
Wire Wire Line
	5550 3050 5550 925 
Wire Wire Line
	5550 925  5825 925 
Wire Wire Line
	5450 1025 5825 1025
$Sheet
S 7650 850  1250 400 
U 58BEC4DE
F0 "screen" 60
F1 "screen.sch" 60
F2 "scl" I L 7650 925 60 
F3 "sda" B L 7650 1025 60 
$EndSheet
$Comp
L CONN_01X04 P6
U 1 1 58BF1DCB
P 10625 1450
F 0 "P6" V 10590 1206 50  0000 R CNN
F 1 "CONN_01X04" V 10498 1206 50  0000 R CNN
F 2 "w_pin_strip:pin_strip_2mm_4" H 10625 1450 50  0001 C CNN
F 3 "http://lispol.com/produkt/wtyk-goldpin-1x40-prosty-r-200mm---ph1x40" H 10625 1450 50  0001 C CNN
	1    10625 1450
	0    -1   -1   0   
$EndComp
Text Label 7550 4375 0    60   ~ 0
consoleRx
Text Label 7550 4475 0    60   ~ 0
consoleTx
Text Label 10475 1650 3    60   ~ 0
consoleTx
Text Label 10575 1650 3    60   ~ 0
consoleRx
$Comp
L GND #PWR026
U 1 1 58BF47B7
P 10675 1750
F 0 "#PWR026" H 10675 1500 50  0001 C CNN
F 1 "GND" H 10675 1600 50  0000 C CNN
F 2 "" H 10675 1750 60  0000 C CNN
F 3 "" H 10675 1750 60  0000 C CNN
	1    10675 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10675 1650 10675 1750
Text Label 3925 4425 1    60   ~ 0
nrst
Wire Wire Line
	3925 4425 3925 4475
Connection ~ 3925 4475
Text Label 10775 1650 3    60   ~ 0
nrst
Wire Wire Line
	7650 1025 6950 1025
Wire Wire Line
	6950 1025 6950 3225
Wire Wire Line
	6950 3225 6500 3225
Wire Wire Line
	6500 3225 6500 3375
Wire Wire Line
	6600 3375 6600 3300
Wire Wire Line
	6600 3300 7025 3300
Wire Wire Line
	7025 3300 7025 925 
Wire Wire Line
	7025 925  7650 925 
NoConn ~ 6700 3375
NoConn ~ 6800 3375
NoConn ~ 6900 3375
NoConn ~ 7000 3375
NoConn ~ 5500 4975
$Comp
L CONN_01X01 J1
U 1 1 58BFFC77
P 1175 1725
F 0 "J1" H 1253 1766 50  0000 L CNN
F 1 "CONN_01X01" H 1253 1675 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_DIN965_Pad" H -125 -525 50  0001 C CNN
F 3 "" H -125 -525 50  0001 C CNN
	1    1175 1725
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J2
U 1 1 58C00842
P 1150 2225
F 0 "J2" H 1228 2266 50  0000 L CNN
F 1 "CONN_01X01" H 1228 2175 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.00mm" H -150 -25 50  0001 C CNN
F 3 "" H -150 -25 50  0001 C CNN
	1    1150 2225
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J3
U 1 1 58C00D05
P 1150 2375
F 0 "J3" H 1228 2416 50  0000 L CNN
F 1 "CONN_01X01" H 1228 2325 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.00mm" H -150 125 50  0001 C CNN
F 3 "" H -150 125 50  0001 C CNN
	1    1150 2375
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J4
U 1 1 58C00F2B
P 1150 2525
F 0 "J4" H 1228 2566 50  0000 L CNN
F 1 "CONN_01X01" H 1228 2475 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.00mm" H -150 275 50  0001 C CNN
F 3 "" H -150 275 50  0001 C CNN
	1    1150 2525
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J5
U 1 1 58C00F31
P 1150 2675
F 0 "J5" H 1228 2716 50  0000 L CNN
F 1 "CONN_01X01" H 1228 2625 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.00mm" H -150 425 50  0001 C CNN
F 3 "" H -150 425 50  0001 C CNN
	1    1150 2675
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J6
U 1 1 58C01052
P 1150 2825
F 0 "J6" H 1228 2866 50  0000 L CNN
F 1 "CONN_01X01" H 1228 2775 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.00mm" H -150 575 50  0001 C CNN
F 3 "" H -150 575 50  0001 C CNN
	1    1150 2825
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J7
U 1 1 58C01058
P 1150 2975
F 0 "J7" H 1228 3016 50  0000 L CNN
F 1 "CONN_01X01" H 1228 2925 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.00mm" H -150 725 50  0001 C CNN
F 3 "" H -150 725 50  0001 C CNN
	1    1150 2975
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J8
U 1 1 58C0105E
P 1150 3125
F 0 "J8" H 1228 3166 50  0000 L CNN
F 1 "CONN_01X01" H 1228 3075 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.00mm" H -150 875 50  0001 C CNN
F 3 "" H -150 875 50  0001 C CNN
	1    1150 3125
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J9
U 1 1 58C01064
P 1150 3275
F 0 "J9" H 1228 3316 50  0000 L CNN
F 1 "CONN_01X01" H 1228 3225 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.00mm" H -150 1025 50  0001 C CNN
F 3 "" H -150 1025 50  0001 C CNN
	1    1150 3275
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J12
U 1 1 58C011F6
P 1175 1575
F 0 "J12" H 1253 1616 50  0000 L CNN
F 1 "CONN_01X01" H 1253 1525 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_DIN965_Pad" H -125 -675 50  0001 C CNN
F 3 "" H -125 -675 50  0001 C CNN
	1    1175 1575
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J11
U 1 1 58C01274
P 1175 1425
F 0 "J11" H 1253 1466 50  0000 L CNN
F 1 "CONN_01X01" H 1253 1375 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_DIN965_Pad" H -125 -825 50  0001 C CNN
F 3 "" H -125 -825 50  0001 C CNN
	1    1175 1425
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X01 J10
U 1 1 58C0127A
P 1175 1275
F 0 "J10" H 1253 1316 50  0000 L CNN
F 1 "CONN_01X01" H 1253 1225 50  0000 L CNN
F 2 "Mounting_Holes:MountingHole_3.2mm_M3_DIN965_Pad" H -125 -975 50  0001 C CNN
F 3 "" H -125 -975 50  0001 C CNN
	1    1175 1275
	1    0    0    -1  
$EndComp
NoConn ~ 5500 4775
NoConn ~ 6700 5425
NoConn ~ 6800 5425
NoConn ~ 6900 5425
Wire Wire Line
	5825 1125 5775 1125
Text Label 5775 1125 3    60   ~ 0
sense
Text Label 6000 5425 3    60   ~ 0
sense
NoConn ~ 975  1275
NoConn ~ 975  1425
NoConn ~ 975  1575
NoConn ~ 975  1725
NoConn ~ 950  2225
NoConn ~ 950  2375
NoConn ~ 950  2525
NoConn ~ 950  2675
NoConn ~ 950  2825
NoConn ~ 950  2975
NoConn ~ 950  3125
NoConn ~ 950  3275
Text Notes 800  5375 0    60   ~ 0
Uwaga na pinout, bo każdy receiver ma inny!!\nMontaż po stronie komponentów (nie ekranu).\nDobre : TSOP39138\nZłe : TSOP39538
Text Notes 3825 2075 0    60   ~ 0
TODO foto-R do PA2!
$EndSCHEMATC