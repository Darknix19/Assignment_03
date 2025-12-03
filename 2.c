#include <stdio.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets) {
    if (fuel <= 0) {
        printf("Mission failed: Fuel exhausted at Planet %d\n", planet);
        return 0;
    }
    if (planet > totalPlanets) {
        printf("Mission successful: All planets visited\n");
        return 1;
    }

    fuel -= consumption;
    fuel += recharge;
    if (planet % 4 == 0) fuel += solarBonus;

    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    return calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main() {
    int fuel = 500;
    int consumption = 80;
    int recharge = 20;
    int solarBonus = 100;
    int totalPlanets = 10;

    calculateFuel(fuel, consumption, recharge, solarBonus, 1, totalPlanets);
    return 0;
}