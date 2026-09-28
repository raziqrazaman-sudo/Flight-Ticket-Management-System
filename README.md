# ✈️ Kodo Airlines - Flight Ticket Management System

A beginner-friendly C++ console application designed to manage flight bookings, calculate dynamic ticket prices, apply multiple discounts, process taxes, and generate daily sales reports.

---

## 🌟 Key Features

* **Interactive Booking Loop:** Run bookings for multiple customers back-to-back, with options to continue or exit the system at any time.
* **Customer Information Collection:** Safely collects and stores customer details including Name, Email, and Phone Number.
* **Flight & Cabin Selection:** Choose between:
  * **Journey Type:** One-way or Round-trip.
  * **Destinations:** Malaysia to Japan, Singapore, or the USA.
  * **Cabin Classes:** Economy, Business, or First Class.
* **Smart Date Validation:** Ensures departure and return dates are correctly typed in the `DD/MM/YYYY` format using character checks and loops.
* **Passenger & Pricing Management:** Takes counts for adults and children, automatically making child tickets 25% cheaper than adult fares.
* **Multi-Tier Discount System:** Automatically calculates and applies various savings:
  * **15% off** for trips to Japan.
  * **15% off** for registered members.
  * **10% off** when entering the promo code `CheapFlight`.
  * **5% extra off** if the total base charge reaches RM 6,700 or more.
* **Tax & Final Calculation:** Combines charges, subtracts all accumulated discounts, adds a 6% Sales and Services Tax (SST), and computes the final payable amount.
* **Receipt Generation:** Prints a neat, itemized summary bill directly to the console for each confirmed booking.
* **Daily Analytics & Reporting:** Tracks daily total revenue and automatically identifies the **"Famous"** (most popular) and **"Infamous"** (least popular) destinations when exiting the program.

---

## 🛠️ Technologies Used
* **Language:** C++
* **Standard Libraries:** `<iostream>`, `<iomanip>`, `<cstring>`, `<cctype>`

---

## 🚀 How to Run the Program

1. Open your C++ IDE (such as Dev-C++, Code::Blocks, or Visual Studio) or terminal.
2. Compile the source code:
   ```bash
   g++ main.cpp -o kodo_airlines
---
Project Develop: 25 January 2026
