#include <stdio.h>
#include <stdlib.h>

#define BUSINESS_START 1
#define BUSINESS_END 15
#define ECONOMY_START 16
#define ECONOMY_END 45

int businessSeats[15] = {0}; // 0 = available, 1 = booked
int economySeats[30] = {0};  // 0 = available, 1 = booked

int isBusinessWindow(int seat) {
    return seat == 3 || seat == 6 || seat == 9 || seat == 12 || seat == 15;
}

int isEconomyWindow(int seat) {
    return seat % 6 == 0;
}

int isSeatBooked(int seat) {
    if (seat >= BUSINESS_START && seat <= BUSINESS_END)
        return businessSeats[seat - 1];
    else if (seat >= ECONOMY_START && seat <= ECONOMY_END)
        return economySeats[seat - ECONOMY_START];
    return -1;
}

void bookSeat(int seat) {
    if (seat >= BUSINESS_START && seat <= BUSINESS_END)
        businessSeats[seat - 1] = 1;
    else if (seat >= ECONOMY_START && seat <= ECONOMY_END)
        economySeats[seat - ECONOMY_START] = 1;
}

void displayAvailableSeats() {
    printf("\nAvailable Business Class Seats (1-15):\n");
    for (int i = 0; i < 15; i++) {
        if (!businessSeats[i])
            printf("%d ", i + 1);
    }

    printf("\nAvailable Economy Class Seats (16-45):\n");
    for (int i = 0; i < 30; i++) {
        if (!economySeats[i])
            printf("%d ", i + 16);
    }

    printf("\n\nNote: Seats 21 and 34 are reserved for Air Hosts.\n");
}

void calculateFare(int seat) {
    int fare = 0;

    if (seat >= BUSINESS_START && seat <= BUSINESS_END) {
        fare = 82000;
        if (isBusinessWindow(seat)) {
            fare += 2050;
            printf("✅ Window-side Business Seat.\n");
        } else {
            printf("✅ Aisle-side Business Seat.\n");
        }
    } else if (seat >= ECONOMY_START && seat <= ECONOMY_END) {
        if (seat == 21 || seat == 34) {
            printf("🎉 Seat reserved for air host. No charge.\n");
            return;
        }
        fare = 72000;
        if (isEconomyWindow(seat)) {
            fare += 1368;
            printf("✅ Window-side Economy Seat.\n");
        } else {
            printf("✅ Aisle-side Economy Seat.\n");
        }
    }

    printf("💰 Total Fare for Seat %d: %d PKR\n", seat, fare);
}

int main() {
    int choice, seat, again;

    printf("******** Welcome to PIA Flight PK-171 (Islamabad to Madinah) ********\n");

    do {
        displayAvailableSeats();

        printf("\nChoose Class:\n1. Business Class\n2. Economy Class\nYour choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter a seat number (1 to 15): ");
            scanf("%d", &seat);
            if (seat < BUSINESS_START || seat > BUSINESS_END) {
                printf("❌ Invalid Business Class seat.\n");
                continue;
            }
        } else if (choice == 2) {
            printf("Enter a seat number (16 to 45, except 21 and 34): ");
            scanf("%d", &seat);
            if (seat < ECONOMY_START || seat > ECONOMY_END || seat == 21 || seat == 34) {
                if (seat == 21 || seat == 34)
                    printf("🎉 This seat is for Air Host. No booking required.\n");
                else
                    printf("❌ Invalid Economy Class seat.\n");
                continue;
            }
        } else {
            printf("❌ Invalid class choice.\n");
            continue;
        }

        if (isSeatBooked(seat)) {
            printf("❌ Seat %d is already booked. Try another.\n", seat);
        } else {
            bookSeat(seat);
            calculateFare(seat);
            printf("✅ Booking confirmed for seat %d.\n", seat);
        }

        printf("\nDo you want to book another ticket? (1 = Yes / 0 = No): ");
        scanf("%d", &again);
    } while (again == 1);

    printf("\n✅ Thank you for flying with PIA. Have a safe journey! ✈️\n");
    return 0;
}
