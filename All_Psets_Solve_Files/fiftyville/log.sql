-- Keep a log of any SQL queries you execute as you solve the mystery.
/* information
1- the thief left before 10 minutes
2- flought on earliest plane on 29
3- used ATM on Leggett Street before crime
*/

-- query to read description
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time
-- – each of their interview transcripts mentions the bakery.

-- getting information OF EXITS from bakery for passes after 10:15 and within 10 minutes
SELECT name FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit' ORDER BY hour,minute;
/* suspects from bakery
+---------+
|  name   |
+---------+
| Vanessa |
| Bruce   |
| Barry   |
| Luca    |
| Sofia   |
| Iman    |
| Diana   |
| Kelsey  |
+---------+
*/
-- reading interviews
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

/* transcript
| 161 | Ruth    | 2021 | 7     | 28  |
 Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
  If you have security footage from the bakery parking lot,
  you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | 2021 | 7     | 28  |
 I don't know the thief's name, but it was someone I recognized. Earlier this morning,
 before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street
 and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | 2021 | 7     | 28  |
 As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
 In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
 The thief then asked the person on the other end of the phone to purchase the flight ticket. |
*/

-- decreasing suspects by detecting who used visa
SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
/*
+---------+
|  name   |
+---------+
| Bruce   |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |
+---------+
*/

-- INTERSECTING IDS
SELECT id,name,phone_number,passport_number,license_plate FROM(SELECT * FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')
INTERSECT
SELECT id,name,phone_number,passport_number,license_plate FROM(SELECT * FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit' ORDER BY hour,minute);
-- suspects name,information
/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+-------+----------------+-----------------+---------------+
*/

-- reducing by who flought tommorow on earliest plane of 29
SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour,minute ;
-- destination airport is of id 4 and trip id is 36
-- determining destination airport
SELECT * FROM airports WHERE id = 4;
-- City is New York City

-- determining which was on plane
SELECT passport_number FROM passengers WHERE flight_id = 36 AND passport_number IN (7049073643, 8496433585, 3592750733, 5773159633);
-- two suspects
/*+-----------------+
| passport_number |
+-----------------+
| 5773159633 Bruce|
| 8496433585 Luca |
+-----------------+*/

-- determine through calls
SELECT * FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND name IN ('Bruce', 'Luca');
/*
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45
*/

-- the accompiler
SELECT name FROM people WHERE phone_number = '(375) 555-8161';
/*+-------+
| name  |
+-------+
| Robin |
+-------+
*/