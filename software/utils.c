#include <stdio.h>
#include "utils.h"
#include "main.h"
#include "utils.h"
#include "vl53l5cx_api.h"

// Définition de la distance critique en millimètres (ici: 20cm)
#define SEUIL_MUR_MM 200


void setup(void){
	// --- A. Geston des LEDs ---
	// 1. Allumeir LED_STATUS (PA2) : Le système est vivant
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

	// 2. Éteindre LED_ALERTE (PB3) au démarrage
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);


	// --- B. Séquence d'allumage du Capteur ---
	// 1. Activer l'alimentation
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_Delay(10);

	// 2. Reset du capteur
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_Delay(10);

	// 3. Activer le mode I2C
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_Delay(10);


	// --- C. Initialisation du Driver VL53L0X ---
	mon_capteur.I2cHandle = &hi2c2;
	mon_capteur.I2cDevAddr = 0x52;


	if (VL53L0X_DataInit(&mon_capteur) == VL53L0X_ERROR_NONE) {
		VL53L0X_StaticInit(&mon_capteur);
		VL53L0X_PerformRefCalibration(&mon_capteur, NULL, NULL);
		VL53L0X_PerformRefSpadManagement(&mon_capteur, NULL, NULL);
		VL53L0X_SetDeviceMode(&mon_capteur, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
		VL53L0X_StartMeasurement(&mon_capteur);
	}
	else {
		// Erreur : Clignotement rapide de la LED Status
		while(1) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
			HAL_Delay(100);
		}
	}
}


void loop(void){
	VL53L0X_GetRangingMeasurementData(&mon_capteur, &mesure);
	if (mesure.RangeStatus == 0) {
		uint16_t distance = mesure.RangeMilliMeter;

		// --- LOGIQUE ---
		// Si la distance est inférieure à 20cm (200mm)
		if (distance < 200) {
			// Allumer la LED d'alerte sur PB3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
			// Signaler au robot
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
		}
		else {
			// Éteindre la LED d'alerte sur PB3
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
			// Relâcher le signal robot
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		}
	}


	HAL_Delay(50); // Pause
	}

